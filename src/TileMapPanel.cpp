#include <sstream>

#include "../include/TileMapPanel.hpp"
#include "../include/Resources.hpp"
#include "../include/Vec2.hpp"
#include "../include/InputHandler.hpp"
#include "../include/Camera.hpp"

int TileMapPanel::nextId;

TileMapPanel::TileMapPanel(TileSet& tileSet, TileMap& tileMap, CollisionMap& collisionMap, ObjectMap& objectMap, Rect rect, std::string imgPath, int& selectedTile, int& selectedLayer, int& selectedCollision, int* selectedTab, int& selectedObject, LevelEditorState::Tools& selectedTool) :
	Panel(rect, imgPath),
	cursorPos_(rect.x(), rect.y(), Resources::TILE_WIDTH, Resources::TILE_HEIGHT),
	cursorBg_("../img/interface/editor/btn_1.png"),
	firstDragClick_(-1,-1),
	curDragClick_(-1,-1),
	previousSelectedObject_(selectedObject),
	ziplineMode_(false),
	ziplineBegin_(-1,-1),
	ziplineEnd_(-1,-1)
{
	tileSet_ = &tileSet;
	tileMap_ = &tileMap;
	objectMap_ = &objectMap;
	collisionMap_ = &collisionMap;

	selectedTile_ = &selectedTile;
	selectedLayer_ = &selectedLayer;
	selectedCollision_ = &selectedCollision;
	selectedTab_ = selectedTab;
	selectedTool_ = &selectedTool;
	selectedObject_ = &selectedObject;

	ObjectInfo info = objectMap_->getGlobalObject(*selectedObject_);
	if (!info.filename.empty())
	{
		objectSp_ = new Sprite(info.filename.c_str(), info.frameCount, info.frameTime);
		objectSp_->setScaleX(info.scaleX);
		objectSp_->setScaleY(info.scaleY);
		objectSpRotation_ = info.rotation;
	}
	else
	{
		objectSp_ = new Sprite("../img/interface/editor/btn_4.png");
		objectSpRotation_ = 0;
	}

	nextId = objectMap_->getLastObjectId() + 1;
	loadObjects();

}


TileMapPanel::~TileMapPanel()
{
	tileMap_ = nullptr;
	tileSet_ = nullptr;
	collisionMap_ = nullptr;
	objectMap_ = nullptr;
	delete selectedTile_;
	delete selectedTool_;
	delete selectedLayer_;
	delete selectedObject_;
	delete objectSp_;
}


void TileMapPanel::update()
{
	Panel::update();

	if (*selectedObject_ != previousSelectedObject_)
	{
		ObjectInfo info = objectMap_->getGlobalObject(*selectedObject_);
		if (!info.filename.empty())
		{
			delete objectSp_;
			objectSp_ = new Sprite(info.filename.c_str(), info.frameCount, info.frameTime);
			objectSp_->setScaleX(info.scaleX);
			objectSp_->setScaleY(info.scaleY);
			objectSpRotation_ = info.rotation;
		}
		else
		{
			objectSp_ = new Sprite("../img/interface/editor/btn_4.png");
			objectSpRotation_ = 0;
		}
	}

	if (InputHandler::getInstance().keyPress('z'))
	{
		ziplineMode_ = ziplineMode_ ? false : true;
		ziplineBegin_ = Vec2(-1,-1);
		ziplineEnd_ = Vec2(-1,-1);
	}


	if (rect_.isInside(InputHandler::getInstance().getMouse()))
	{
		if(ziplineMode_)
		{
			if (InputHandler::getInstance().mousePress(LEFT_MOUSE_BUTTON))
			{
				if (ziplineBegin_ == Vec2(-1,-1))
				{
					ziplineBegin_ = InputHandler::getInstance().getMouse() + Camera::pos_ - Vec2(rect_.x(), rect_.y());
				}
				else
				{
					ziplineEnd_ = InputHandler::getInstance().getMouse() + Camera::pos_ - Vec2(rect_.x(), rect_.y());
					float angle = LineInclination(ziplineBegin_, ziplineEnd_);
					float distance = Distance(ziplineBegin_, ziplineEnd_);
					float scaleX = distance / 48;
					objectMap_->addZipline(nextId++, ziplineBegin_.x(), ziplineBegin_.y() + ProjectY(distance, angle) / 2, angle, scaleX);
					/*int old = *selectedObject_;
					*selectedObject_ = objectMap_->globalSize() - 1;
					placeObject(ziplineBegin_.x(), ziplineBegin_.y(), 2);
					*selectedObject_ = old;*/

					/*ziplineMode_ = false;
					ziplineBegin_ = Vec2(-1,-1);
					ziplineEnd_ = Vec2(-1,-1);*/
				}
			}
		}
		else
		{
			Vec2 speedChangePerLayer(0,0);
			switch(*selectedLayer_)
			{
				case 0:
					speedChangePerLayer = Camera::pos_ * (-0.5);
					break;
				case 4:
					speedChangePerLayer = Camera::pos_ * 0.5;
					break;
				case 5:
					speedChangePerLayer = Camera::pos_ * 0.75;
					break;
				default:
					break;
			}
			if (*selectedTab_ == 1) // collision
				speedChangePerLayer = Vec2(0,0);

			// Tile da tela q o ponteiro do mouse está em cima
			int tileX = (int)((InputHandler::getInstance().getMouseX() - rect_.x() + Camera::pos_.x() - speedChangePerLayer.x() ) / Resources::TILE_WIDTH);
			int tileY = (int)((InputHandler::getInstance().getMouseY() - rect_.y() + Camera::pos_.y() - speedChangePerLayer.y() ) / Resources::TILE_HEIGHT);

			// Mover o cursor para este tile
			cursorPos_.x( tileX * Resources::TILE_WIDTH + rect_.x() + speedChangePerLayer.x() );
			cursorPos_.y( tileY * Resources::TILE_HEIGHT + rect_.y() + speedChangePerLayer.y() );

			if (InputHandler::getInstance().mousePress(LEFT_MOUSE_BUTTON))
			{
				if(*selectedTool_ == LevelEditorState::Tools::ADD) {
					if (*selectedTab_ == 0)
						placeTile(tileX, tileY);
					else if (*selectedTab_ == 1)
						placeCollisionTile(tileX, tileY);
					else
						placeObject(
							InputHandler::getInstance().getMouseX() - objectSp_->getWidth() / 2 + Camera::pos_.x() - speedChangePerLayer.x() - rect_.x(), 
							InputHandler::getInstance().getMouseY() - objectSp_->getHeight() / 2 + Camera::pos_.y() - speedChangePerLayer.y() - rect_.y(),
							*selectedLayer_
						);
				} else if (*selectedTool_ == LevelEditorState::Tools::DELETE) {
					if (*selectedTab_ == 0)
						deleteTile(tileX, tileY);
					else if (*selectedTab_ == 1)
						deleteCollisionTile(tileX, tileY);
					else
						deleteObject(
							InputHandler::getInstance().getMouseX() + Camera::pos_.x(), 
							InputHandler::getInstance().getMouseY() + Camera::pos_.y(),
							*selectedLayer_);
				}
			}
			else if (*selectedTab_ != 2 && InputHandler::getInstance().isMouseDown(LEFT_MOUSE_BUTTON))
			{
				Vec2 v = Vec2(
					tileX * Resources::TILE_WIDTH + rect_.x(),
					tileY * Resources::TILE_HEIGHT + rect_.y()
				);
				if (firstDragClick_ == Vec2(-1,-1)) {
					firstDragClick_ = v;
				} else {
					curDragClick_ = v;
				}
			}
			else if (*selectedTab_ != 2 && firstDragClick_ != Vec2(-1,-1) && InputHandler::getInstance().mouseRelease(LEFT_MOUSE_BUTTON))
			{
				int bigX, smallX;
				int bigY, smallY;
				if(firstDragClick_.x() <= curDragClick_.x()) {
					smallX = firstDragClick_.x();
					bigX = curDragClick_.x();
				} else {
					smallX = curDragClick_.x();
					bigX = firstDragClick_.x();
				}
				if(firstDragClick_.y() <= curDragClick_.y()) {
					smallY = firstDragClick_.y();
					bigY = curDragClick_.y();
				} else {
					smallY = curDragClick_.y();
					bigY = firstDragClick_.y();
				}

				for(int x = smallX; x<=bigX; x+=Resources::TILE_WIDTH) {
					for(int y = smallY; y<=bigY; y+=Resources::TILE_HEIGHT) {
						if(*selectedTool_ == LevelEditorState::Tools::ADD) {
							if (*selectedTab_ == 0)
								placeTile(
									((x - rect_.x()) / Resources::TILE_WIDTH) + 1, // nao me pergunte por que + 1
									(y - rect_.y()) / Resources::TILE_HEIGHT
								);
							else if (*selectedTab_ == 1)
								placeCollisionTile(
									((x - rect_.x()) / Resources::TILE_WIDTH) + 1, // nao me pergunte por que + 1
									(y - rect_.y()) / Resources::TILE_HEIGHT
								);
						} else if (*selectedTool_ == LevelEditorState::Tools::DELETE) {
							if (*selectedTab_ == 0)
								deleteTile(
									((x - rect_.x()) / Resources::TILE_WIDTH) + 1,
									(y - rect_.y()) / Resources::TILE_HEIGHT
								);
							else if (*selectedTab_ == 1)
								deleteCollisionTile(
									((x - rect_.x()) / Resources::TILE_WIDTH) + 1, // nao me pergunte por que + 1
									(y - rect_.y()) / Resources::TILE_HEIGHT
								);
						}
					}
				}

				firstDragClick_ = Vec2(-1,-1);
				curDragClick_ = Vec2(-1,-1);
			}
		}
	}

	if (InputHandler::getInstance().keyPress('s'))
	{
		tileMap_->save();
		collisionMap_->save();
		objectMap_->save();
	}

	previousSelectedObject_ = *selectedObject_;
}


void TileMapPanel::render()
{
	Panel::render();

	// LAYER 5
	tileMap_->renderLayer(5, rect_.x(), rect_.y());
	for (auto object : objects_)
		if (object.layer == 5)
			object.sprite.render(object.pos.x() + rect_.x() + Camera::pos_.x() * 0.75, 
				                 object.pos.y() + rect_.y() + Camera::pos_.y() * 0.75,
				                 object.rotation);

	// LAYER 4
	tileMap_->renderLayer(4, rect_.x(), rect_.y());
	for (auto object : objects_)
		if (object.layer == 4)
			object.sprite.render(object.pos.x() + rect_.x() + Camera::pos_.x() * 0.5, 
				                 object.pos.y() + rect_.y() + Camera::pos_.y() * 0.5,
				                 object.rotation);

	// LAYER 3
	tileMap_->renderLayer(3, rect_.x(), rect_.y());
	for (auto object : objects_)
		if (object.layer == 3)
			object.sprite.render(object.pos.x() + rect_.x(), 
				                 object.pos.y() + rect_.y(),
				                 object.rotation);

	// LAYER 2
	tileMap_->renderLayer(2, rect_.x(), rect_.y());
	for (auto object : objects_)
	{
		// std::cout << object.pos.x() << ", " << object.pos.y() << std::endl;
		if (object.layer == 2)
			object.sprite.render(object.pos.x() + rect_.x(), 
				                 object.pos.y() + rect_.y(),
				                 object.rotation);
	}

	// LAYER 1
	tileMap_->renderLayer(1, rect_.x(), rect_.y());
	for (auto object : objects_)
		if (object.layer == 1)
			object.sprite.render(object.pos.x() + rect_.x(), 
				                 object.pos.y() + rect_.y(),
				                 object.rotation);

	// LAYER 0
	tileMap_->renderLayer(0, rect_.x(), rect_.y());
	for (auto object : objects_)
		if (object.layer == 0)
			object.sprite.render(object.pos.x() + rect_.x() - Camera::pos_.x() * 0.5, 
				                 object.pos.y() + rect_.y() - Camera::pos_.y() * 0.5,
				                 object.rotation);

	collisionMap_->render(rect_.x(), rect_.y());

	// CURSORES
	if (!ziplineMode_)
	{
		// Cursor quando tá só hover
		if (rect_.isInside(InputHandler::getInstance().getMouse()))
		{
			if (*selectedTab_ == 0 && *selectedTool_ == LevelEditorState::Tools::ADD)
				tileSet_->render(*selectedTile_, cursorPos_.x(), cursorPos_.y());
			else if (*selectedTab_ == 2 && *selectedTool_ == LevelEditorState::Tools::ADD)
			{
				objectSp_->render(
					InputHandler::getInstance().getMouseX() - objectSp_->getWidth() / 2 + Camera::pos_.x(), 
					InputHandler::getInstance().getMouseY() - objectSp_->getHeight() / 2 + Camera::pos_.y(),
					objectSpRotation_
				);
			}
			else if (*selectedTab_ != 2)
				cursorBg_.render(cursorPos_.x(), cursorPos_.y());
		}

		// Cursor com drag
		if (firstDragClick_ != Vec2(-1,-1) && *selectedTab_ != 2) {
			int bigX, smallX;
			int bigY, smallY;
			if(firstDragClick_.x() <= curDragClick_.x()) {
				smallX = firstDragClick_.x();
				bigX = curDragClick_.x();
			} else {
				smallX = curDragClick_.x();
				bigX = firstDragClick_.x();
			}
			if(firstDragClick_.y() <= curDragClick_.y()) {
				smallY = firstDragClick_.y();
				bigY = curDragClick_.y();
			} else {
				smallY = curDragClick_.y();
				bigY = firstDragClick_.y();
			}


			Vec2 speedChangePerLayer(0,0);
			switch(*selectedLayer_)
			{
				case 0:
					speedChangePerLayer = Camera::pos_ * (-0.5);
					break;
				case 4:
					speedChangePerLayer = Camera::pos_ * 0.5;
					break;
				case 5:
					speedChangePerLayer = Camera::pos_ * 0.75;
					break;
				default:
					break;
			}
			if (*selectedTab_ == 1) // collision
				speedChangePerLayer = Vec2(0,0);

			for(int x = smallX; x<=bigX; x+=Resources::TILE_WIDTH) {
				for(int y = smallY; y<=bigY; y+=Resources::TILE_HEIGHT) {
					if (*selectedTab_ != 1 && *selectedTool_ == LevelEditorState::Tools::ADD)
						tileSet_->render(*selectedTile_, 
						                 x + speedChangePerLayer.x(), 
						                 y + speedChangePerLayer.y());
					else
						cursorBg_.render(x + speedChangePerLayer.x(), 
							             y + speedChangePerLayer.y());
				}
			}
		}
	}
}


void TileMapPanel::placeTile(int x, int y)
{
	tileMap_->tileMatrix_[
		x +
		y*tileMap_->getWidth() +
		(*selectedLayer_)*tileMap_->getWidth()*tileMap_->getHeight()
	] = *selectedTile_;
}

void TileMapPanel::deleteTile(int x, int y)
{
	tileMap_->tileMatrix_[
		x +
		y*tileMap_->getWidth() +
		(*selectedLayer_)*tileMap_->getWidth()*tileMap_->getHeight()
	] = -1;
}


void TileMapPanel::placeCollisionTile(int x, int y)
{
	collisionMap_->collisionMatrix_[
		x +
		y*collisionMap_->getWidth()
	] = *selectedCollision_;
}

void TileMapPanel::deleteCollisionTile(int x, int y)
{
	collisionMap_->collisionMatrix_[
		x +
		y*collisionMap_->getWidth()
	] = -1;
}


void TileMapPanel::placeObject(int x, int y, int layer)
{
	Object object;
	object.id = nextId++;
	object.layer = layer;
	object.sprite = *objectSp_;
	object.pos = Rect(x, y, object.sprite.getWidth(), object.sprite.getHeight());
	object.rotation = objectSpRotation_;

	objects_.emplace_back(object);

	objectMap_->addObject(*selectedObject_, object.id, x, y, layer);
}

void TileMapPanel::deleteObject(int x, int y, int layer)
{
	int lastFound;
	for (int i = 0; i < (int)objects_.size(); i++)
	{
		if (objects_[i].layer == layer && (objects_[i].pos + Vec2(rect_.x(), rect_.y())).isInside(Vec2(x, y)))
			lastFound = i;
	}

	if (lastFound < (int)objects_.size())
	{
		objectMap_->deleteObject(objects_[lastFound].id);
		objects_.erase(objects_.begin() + lastFound);
	}
}

void TileMapPanel::loadObjects()
{
	std::vector<LocalObjectInfo> info = objectMap_->getLocalObjects();

	for (auto objInfo : info)
	{
		Object object;
		object.id = objInfo.id;
		object.layer = objInfo.layer;
		if (objInfo.filename.empty())
		{
			object.sprite = Sprite("../img/interface/editor/btn_4.png");
		}
		else
		{
			object.sprite = Sprite(objInfo.filename.c_str(), objInfo.frameCount, objInfo.frameTime);
			object.sprite.setScaleX(objInfo.scaleX);
			object.sprite.setScaleY(objInfo.scaleY);
		}
		object.pos = Rect(objInfo.x, objInfo.y, object.sprite.getWidth(), object.sprite.getHeight());
		object.rotation = objInfo.rotation;

		objects_.emplace_back(object);
	}
}
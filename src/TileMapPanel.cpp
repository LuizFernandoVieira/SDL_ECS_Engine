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
	firstDragClick_(),
	curDragClick_(),
	previousSelectedObject_(selectedObject)
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
	objectSp_ = new Sprite(info.filename.c_str(), info.frameCount, info.frameTime);

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

	if (*selectedTab_ == 2 && *selectedObject_ != previousSelectedObject_)
	{
		ObjectInfo info = objectMap_->getGlobalObject(*selectedObject_);
		objectSp_ = new Sprite(info.filename.c_str(), info.frameCount, info.frameTime);
	}

	if (rect_.isInside(InputHandler::getInstance().getMouse()))
	{
		double speedChangePerLayer;
		switch(*selectedLayer_)
		{
			case 0:
				speedChangePerLayer = -0.5;
				break;
			case 1:
				speedChangePerLayer = 0;
				break;
			case 2:
				speedChangePerLayer = 0.5;
				break;
			case 3:
				speedChangePerLayer = 0.75;
				break;
			default:
				break;
		}
		if (*selectedTab_ == 1)
			speedChangePerLayer = 0;

		// Tile da tela q o ponteiro do mouse está em cima
		int tileX = (int)((InputHandler::getInstance().getMouseX() - rect_.x() + Camera::pos_.x() - speedChangePerLayer * Camera::pos_.x() ) / Resources::TILE_WIDTH);
		int tileY = (int)((InputHandler::getInstance().getMouseY() - rect_.y() + Camera::pos_.y() - speedChangePerLayer * Camera::pos_.y() ) / Resources::TILE_HEIGHT);

		// Mover o cursor para este tile
		cursorPos_.x( tileX * Resources::TILE_WIDTH + rect_.x() + speedChangePerLayer * Camera::pos_.x() );
		cursorPos_.y( tileY * Resources::TILE_HEIGHT + rect_.y() + speedChangePerLayer * Camera::pos_.y() );

		if (InputHandler::getInstance().mousePress(LEFT_MOUSE_BUTTON))
		{
			if(*selectedTool_ == LevelEditorState::Tools::ADD) {
				if (*selectedTab_ == 0)
					placeTile(tileX, tileY);
				else if (*selectedTab_ == 1)
					placeCollisionTile(tileX, tileY);
				else
					placeObject(
						InputHandler::getInstance().getMouseX() - objectSp_->getWidth() / 2, 
						InputHandler::getInstance().getMouseY() - objectSp_->getHeight() / 2
					);
			} else if (*selectedTool_ == LevelEditorState::Tools::DELETE) {
				if (*selectedTab_ == 0)
					deleteTile(tileX, tileY);
				else if (*selectedTab_ == 1)
					deleteCollisionTile(tileX, tileY);
				else
					deleteObject(InputHandler::getInstance().getMouseX(), InputHandler::getInstance().getMouseY());
			}
		}
		else if (*selectedTab_ != 2 && InputHandler::getInstance().isMouseDown(LEFT_MOUSE_BUTTON))
		{
			Vec2 v = Vec2(
				tileX * Resources::TILE_WIDTH + rect_.x(),
				tileY * Resources::TILE_HEIGHT + rect_.y()
			);
			if (firstDragClick_ == Vec2()) {
				firstDragClick_ = v;
			} else {
				curDragClick_ = v;
			}
		}
		else if (*selectedTab_ != 2 && InputHandler::getInstance().mouseRelease(LEFT_MOUSE_BUTTON))
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

			firstDragClick_ = Vec2();
			curDragClick_ = Vec2();
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
	tileMap_->render(rect_.x(), rect_.y());
	collisionMap_->render(rect_.x(), rect_.y());

	// Renderizar objetos
	for (auto object : objects_)
		object.sprite.render(object.pos.x(), object.pos.y());

	// Cursor quando tá só hover
	if (rect_.isInside(InputHandler::getInstance().getMouse()))
	{
		if (*selectedTab_ == 0 && *selectedTool_ == LevelEditorState::Tools::ADD)
			tileSet_->render(*selectedTile_, cursorPos_.x(), cursorPos_.y());
		else if (*selectedTab_ == 2 && *selectedTool_ == LevelEditorState::Tools::ADD)
			objectSp_->render(
				InputHandler::getInstance().getMouseX() - objectSp_->getWidth() / 2, 
				InputHandler::getInstance().getMouseY() - objectSp_->getHeight() / 2
			);
		else if (*selectedTab_ != 2)
			cursorBg_.render(cursorPos_.x(), cursorPos_.y());
	}

	// Cursor com drag
	if (firstDragClick_ != Vec2() && *selectedTab_ != 2) {
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

		double speedChangePerLayer;
		switch(*selectedLayer_)
		{
			case 0:
				speedChangePerLayer = -0.5;
				break;
			case 1:
				speedChangePerLayer = 0;
				break;
			case 2:
				speedChangePerLayer = 0.5;
				break;
			case 3:
				speedChangePerLayer = 0.75;
				break;
			default:
				break;
		}
		if (*selectedTab_ == 1)
			speedChangePerLayer = 0;

		for(int x = smallX; x<=bigX; x+=Resources::TILE_WIDTH) {
			for(int y = smallY; y<=bigY; y+=Resources::TILE_HEIGHT) {
				if (*selectedTab_ != 1 && *selectedTool_ == LevelEditorState::Tools::ADD)
					tileSet_->render(*selectedTile_, 
					                 x + speedChangePerLayer * Camera::pos_.x(), 
					                 y + speedChangePerLayer * Camera::pos_.y());
				else
					cursorBg_.render(x + speedChangePerLayer * Camera::pos_.x(), 
						             y + speedChangePerLayer * Camera::pos_.y());
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


void TileMapPanel::placeObject(int x, int y)
{
	Object object;
	object.id = nextId++;
	object.sprite = *objectSp_;
	object.pos = Rect(x, y, object.sprite.getWidth(), object.sprite.getHeight());

	objects_.emplace_back(object);

	objectMap_->addObject(*selectedObject_, object.id, x, y);
}

void TileMapPanel::deleteObject(int x, int y)
{
	int lastFound;
	for (int i = 0; i < (int)objects_.size(); i++)
	{
		if (objects_[i].pos.isInside(Vec2(x, y)))
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
		object.sprite = Sprite(objInfo.filename.c_str(), objInfo.frameCount, objInfo.frameTime);
		object.pos = Rect(objInfo.x, objInfo.y, object.sprite.getWidth(), object.sprite.getHeight());

		objects_.emplace_back(object);
	}
}
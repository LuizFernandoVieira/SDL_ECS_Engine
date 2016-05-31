#include <sstream>

#include "../include/TileMapPanel.hpp"
#include "../include/Globals.hpp"
#include "../include/Vec2.hpp"
#include "../include/InputHandler.hpp"
#include "../include/Camera.hpp"

TileMapPanel::TileMapPanel(TileSet& tileSet, TileMap& tileMap, CollisionMap& collisionMap, Rect rect, std::string imgPath, int& selectedTile, int& selectedLayer, int& selectedCollision, int* selectedTab, LevelEditorState::Tools& selectedTool) :
	Panel(rect, imgPath),
	cursorPos_(rect.x(), rect.y(), Globals::TILE_WIDTH, Globals::TILE_HEIGHT),
	cursorBg_("../img/interface/editor/btn_1.png"),
	firstDragClick_(),
	curDragClick_()
{
	tileSet_ = &tileSet;
	tileMap_ = &tileMap;
	collisionMap_ = &collisionMap;

	selectedTile_ = &selectedTile;
	selectedLayer_ = &selectedLayer;
	selectedCollision_ = &selectedCollision;
	selectedTab_ = selectedTab;
	selectedTool_ = &selectedTool;
}


TileMapPanel::~TileMapPanel()
{
	tileMap_ = nullptr;
	tileSet_ = nullptr;
	collisionMap_ = nullptr;
	delete selectedTile_;
	delete selectedTool_;
	delete selectedLayer_;
}


void TileMapPanel::update()
{
	Panel::update();

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
		int tileX = (int)((InputHandler::getInstance().getMouseX() - rect_.x() + Camera::pos_.x() - speedChangePerLayer * Camera::pos_.x() ) / Globals::TILE_WIDTH);
		int tileY = (int)((InputHandler::getInstance().getMouseY() - rect_.y() + Camera::pos_.y() - speedChangePerLayer * Camera::pos_.y() ) / Globals::TILE_HEIGHT);

		// Mover o cursor para este tile
		cursorPos_.x( tileX * Globals::TILE_WIDTH + rect_.x() + speedChangePerLayer * Camera::pos_.x() );
		cursorPos_.y( tileY * Globals::TILE_HEIGHT + rect_.y() + speedChangePerLayer * Camera::pos_.y() );

		if (InputHandler::getInstance().mousePress(LEFT_MOUSE_BUTTON))
		{
			if(*selectedTool_ == LevelEditorState::Tools::ADD) {
				if (*selectedTab_ == 0)
					placeTile(tileX, tileY);
				else if (*selectedTab_ == 1)
					placeCollisionTile(tileX, tileY);
			} else if (*selectedTool_ == LevelEditorState::Tools::DELETE) {
				if (*selectedTab_ == 0)
					deleteTile(tileX, tileY);
				else if (*selectedTab_ == 1)
					deleteCollisionTile(tileX, tileY);
			}
		}
		else if (InputHandler::getInstance().isMouseDown(LEFT_MOUSE_BUTTON))
		{
			Vec2 v = Vec2(
				tileX * Globals::TILE_WIDTH + rect_.x(),
				tileY * Globals::TILE_HEIGHT + rect_.y()
			);
			if (firstDragClick_ == Vec2()) {
				firstDragClick_ = v;
			} else {
				curDragClick_ = v;
			}
		}
		else if (InputHandler::getInstance().mouseRelease(LEFT_MOUSE_BUTTON))
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

			for(int x = smallX; x<=bigX; x+=Globals::TILE_WIDTH) {
				for(int y = smallY; y<=bigY; y+=Globals::TILE_HEIGHT) {
					if(*selectedTool_ == LevelEditorState::Tools::ADD) {
						if (*selectedTab_ == 0)
							placeTile(
								((x - rect_.x()) / Globals::TILE_WIDTH) + 1, // nao me pergunte por que + 1
								(y - rect_.y()) / Globals::TILE_HEIGHT
							);
						else if (*selectedTab_ == 1)
							placeCollisionTile(
								((x - rect_.x()) / Globals::TILE_WIDTH) + 1, // nao me pergunte por que + 1
								(y - rect_.y()) / Globals::TILE_HEIGHT
							);
					} else if (*selectedTool_ == LevelEditorState::Tools::DELETE) {
						if (*selectedTab_ == 0)
							deleteTile(
								((x - rect_.x()) / Globals::TILE_WIDTH) + 1,
								(y - rect_.y()) / Globals::TILE_HEIGHT
							);
						else if (*selectedTab_ == 1)
							deleteCollisionTile(
								((x - rect_.x()) / Globals::TILE_WIDTH) + 1, // nao me pergunte por que + 1
								(y - rect_.y()) / Globals::TILE_HEIGHT
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
	}
}


void TileMapPanel::render()
{
	Panel::render();
	tileMap_->render(rect_.x(), rect_.y());
	if (rect_.isInside(InputHandler::getInstance().getMouse()))
	{
		if (*selectedTab_ != 1 && *selectedTool_ == LevelEditorState::Tools::ADD)
			tileSet_->render(*selectedTile_, cursorPos_.x(), cursorPos_.y());
		else
			cursorBg_.render(cursorPos_.x(), cursorPos_.y());
	}
	collisionMap_->render(rect_.x(), rect_.y());

	// Renderizar cursor por cima dos tiles selecionados com drag
	if (firstDragClick_ != Vec2()) {
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

		for(int x = smallX; x<=bigX; x+=Globals::TILE_WIDTH) {
			for(int y = smallY; y<=bigY; y+=Globals::TILE_HEIGHT) {
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
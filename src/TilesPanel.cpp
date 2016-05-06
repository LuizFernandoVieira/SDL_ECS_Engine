#include <sstream>

#include "../include/TilesPanel.hpp"
#include "../include/Globals.hpp"
#include "../include/Vec2.hpp"
#include "../include/InputHandler.hpp"
#include "../include/Camera.hpp"

TilesPanel::TilesPanel(TileSet& tileSet, TileMap& tileMap, Rect rect, std::string imgPath, int& selectedTile) : 
	Panel(rect, imgPath), 
	cursorBg_("../img/god.png"),
	cursorPos_(rect.x(), rect.y(), Globals::TILE_WIDTH, Globals::TILE_HEIGHT),
	firstDragClick_(),
	curDragClick_()
{
	tileSet_ = &tileSet;
	tileMap_ = &tileMap;

	tileMapFilename_ = "../map/tileMap.txt"; // MUDAR ISSO!!!!

	selectedTile_ = &selectedTile;
}


TilesPanel::~TilesPanel()
{
	tileMap_ = nullptr;
	tileSet_ = nullptr;
}


void TilesPanel::update()
{
	Panel::update();

	if (rect_.isInside(InputHandler::getInstance().getMouse()))
	{
		// Tile da tela q o ponteiro do mouse está em cima
		int tileX = (int)((InputHandler::getInstance().getMouseX() - rect_.x() + Camera::getPosition().x()) / Globals::TILE_WIDTH);
		int tileY = (int)((InputHandler::getInstance().getMouseY() - rect_.y() + Camera::getPosition().y()) / Globals::TILE_HEIGHT);

		// Mover o cursor para este tile
		cursorPos_.x( tileX * Globals::TILE_WIDTH + rect_.x() );
		cursorPos_.y( tileY * Globals::TILE_HEIGHT + rect_.y() );

		if (InputHandler::getInstance().mousePress(LEFT_MOUSE_BUTTON))
		{
			placeTile(tileX, tileY);
		} else if (InputHandler::getInstance().isMouseDown(LEFT_MOUSE_BUTTON)) {
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
	}
}


void TilesPanel::render()
{
	Panel::render();
	tileMap_->render(rect_.x(), rect_.y());
	cursorBg_.render(cursorPos_.x(), cursorPos_.y());

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
		for(int x = smallX; x<=bigX; x+=Globals::TILE_WIDTH) {
			for(int y = smallY; y<=bigY; y+=Globals::TILE_HEIGHT) {
				cursorBg_.render(x, y);
			}
		}
	}
}


void TilesPanel::placeTile(int x, int y)
{
	std::fstream fs;
	int mapWidth;
	int mapHeight;
	int mapDepth;
	char comma;
	char* endOfLine;
	char aux;

	fs.open(tileMapFilename_, std::fstream::in | std::fstream::out);

	if(!fs.is_open())
	{
		std::cout << "ERRO: nao foi possivel abrir o tile map " << tileMapFilename_ << std::endl;
	}

	fs >> mapWidth;
	fs >> comma;
	fs >> mapHeight;
	fs >> comma;
	fs >> mapDepth;
	fs >> comma;

	int location = x + y*mapWidth + 0*mapWidth*mapHeight;
	int withComma = 3;

	fs.seekp(fs.tellg(), std::ios_base::beg);

	// linebreak diferente no apple e nos outros SOS
	#ifdef __APPLE__
		int firstBreakLine = 2;
		fs.seekp( location * withComma + firstBreakLine + y, std::ios_base::cur );
	#else
		fs.seekp( (location-1) * withComma + y * 2, std::ios_base::cur );
	#endif

	std::ostringstream ss;
	ss << *selectedTile_;
	std::string correctString = ss.str();
	if(*selectedTile_ < 10) {
		correctString = "0" + correctString;
	}
	fs << correctString.c_str();

	fs.close();

	tileMap_->tileMatrix_[x + y*mapWidth + 0*mapWidth*mapHeight] = *selectedTile_;
}
#include "../include/TilesPanel.hpp"
#include "../include/Globals.hpp"
#include "../include/Vec2.hpp"
#include "../include/InputHandler.hpp"

TilesPanel::TilesPanel(TileSet& tileSet, TileMap& tileMap, Rect rect, std::string imgPath) : 
	Panel(rect, imgPath), cursorBg_("../img/god.png"),
	cursorPos_(rect.x(), rect.y(), Globals::TILE_WIDTH, Globals::TILE_HEIGHT)
{
	tileSet_ = &tileSet;
	tileMap_ = &tileMap;

	tileMapFilename_ = "../map/tileMap.txt"; // MUDAR ISSO!!!!
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
		int tileX = (int)((InputHandler::getInstance().getMouseX() - rect_.x()) / Globals::TILE_WIDTH);
		int tileY = (int)((InputHandler::getInstance().getMouseY() - rect_.y()) / Globals::TILE_HEIGHT);

		// Mover o cursor para este tile
		cursorPos_.x( tileX * Globals::TILE_WIDTH + rect_.x() );
		cursorPos_.y( tileY * Globals::TILE_HEIGHT + rect_.y() );

		if (InputHandler::getInstance().mousePress(LEFT_MOUSE_BUTTON))
		{
			placeTile(tileX, tileY);
		}
	}
}


void TilesPanel::render()
{
	Panel::render();
	tileMap_->render(rect_.x(), rect_.y());
	cursorBg_.render(cursorPos_.x(), cursorPos_.y());
}


void TilesPanel::placeTile(int x, int y)
{
	std::fstream fs;
	int mapWidth;
	int mapHeight;
	int mapDepth;
	char comma;

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
	int firstBreakLine = 2;

	// std::cout << "(x,y): " << x << ", " << y << std::endl;
	// std::cout << "linear: " << location << std::endl;

	fs.seekp(fs.tellg(), std::ios_base::beg);
	fs.seekp( location * withComma + firstBreakLine + y, std::ios_base::cur );

	fs << "02";

	fs.close();


	tileMap_->tileMatrix_[x + y*mapWidth + 0*mapWidth*mapHeight] = 02;
}
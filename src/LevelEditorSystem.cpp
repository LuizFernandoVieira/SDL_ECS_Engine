#include "../include/LevelEditorSystem.hpp"
#include "../include/Globals.hpp"
#include "../include/InputHandler.hpp"
#include "../include/Rect.hpp"


LevelEditorSystem::LevelEditorSystem(TileMap& tileMap, std::string tileMapFilename)
{
	tileMap_ = &tileMap;
	tileMapFilename_ = tileMapFilename;
}


LevelEditorSystem::~LevelEditorSystem()
{
	delete tileMap_;
}


void LevelEditorSystem::update(TransformComponent* tc)
{
	// Tile da tela q o ponteiro do mouse está em cima
	int tileX = (int)(InputHandler::getInstance().getMouseX() / Globals::TILE_WIDTH) * Globals::TILE_WIDTH;
	int tileY = (int)(InputHandler::getInstance().getMouseY() / Globals::TILE_HEIGHT) * Globals::TILE_HEIGHT;

	// Mover o God para este tile
	Rect* rect = new Rect( tileX, tileY, Globals::TILE_WIDTH, Globals::TILE_HEIGHT );
	tc->setRect(*rect);

	if (InputHandler::getInstance().mousePress(LEFT_MOUSE_BUTTON))
	{
		placeTile(tileX / Globals::TILE_WIDTH, tileY / Globals::TILE_HEIGHT);
	}
}


void LevelEditorSystem::placeTile(int x, int y)
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
#include <sstream>

#include "../include/TilesPanel.hpp"
#include "../include/Globals.hpp"
#include "../include/Vec2.hpp"
#include "../include/InputHandler.hpp"
#include "../include/Camera.hpp"

TilesPanel::TilesPanel(TileSet& tileSet, TileMap& tileMap, Rect rect, std::string imgPath, int& selectedTile, LevelEditorState::Tools& selectedTool) : 
	Panel(rect, imgPath), 
	cursorPos_(rect.x(), rect.y(), Globals::TILE_WIDTH, Globals::TILE_HEIGHT),
	cursorBg_("../img/god.png"),
	firstDragClick_(),
	curDragClick_()
{
	tileSet_ = &tileSet;
	tileMap_ = &tileMap;

	tileMapFilename_ = "../map/tileMap.txt"; // MUDAR ISSO!!!!

	selectedTile_ = &selectedTile;
	selectedTool_ = &selectedTool;
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
			if(*selectedTool_ == LevelEditorState::Tools::ADD) {
				placeTile(tileX, tileY);
			} else if (*selectedTool_ == LevelEditorState::Tools::DELETE) {
				deleteTile(tileX, tileY);
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
						placeTile( 
							((x - rect_.x()) / Globals::TILE_WIDTH) + 1, // nao me pergunte por que + 1
							(y - rect_.y()) / Globals::TILE_HEIGHT
						);
					} else if (*selectedTool_ == LevelEditorState::Tools::DELETE) {
						deleteTile(
							((x - rect_.x()) / Globals::TILE_WIDTH) + 1,
							(y - rect_.y()) / Globals::TILE_HEIGHT
						);
					}
				}
			}

			firstDragClick_ = Vec2();
			curDragClick_ = Vec2();
		}
	}
}


void TilesPanel::render()
{
	Panel::render();
	tileMap_->render(rect_.x(), rect_.y());
	// cursorBg_.render(cursorPos_.x(), cursorPos_.y());
	tileSet_->render(*selectedTile_, cursorPos_.x(), cursorPos_.y());

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
		for(int x = smallX; x<=bigX; x+=Globals::TILE_WIDTH) {
			for(int y = smallY; y<=bigY; y+=Globals::TILE_HEIGHT) {
				// cursorBg_.render(x, y);
				tileSet_->render(*selectedTile_, x, y);
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
	int withComma = 3;		// tamanho de cada tile no arquivo, dois digitos mais virgula

	fs.seekp(fs.tellg(), std::ios_base::beg);

	// linebreak diferente no apple e nos outros SOS
	#ifdef __APPLE__
		int firstBreakLine = 2;		// tamanho dos dois primeiros line breaks
		fs.seekp( location * withComma + firstBreakLine + y, std::ios_base::cur ); // + y para line breaks no final de cada linha
	#else
		fs.seekp( (location-1) * withComma + y * 2, std::ios_base::cur ); // nao me pergunte por que essa conta
	#endif

	std::ostringstream ss;
	ss << *selectedTile_;
	std::string correctString = ss.str();
	if(*selectedTile_ < 10) {
		correctString = "0" + correctString;
	}
	fs << correctString.c_str();

	fs.close();

	// Alterar visualização em runtime
	tileMap_->tileMatrix_[x + y*mapWidth + 0*mapWidth*mapHeight] = *selectedTile_;
}

void TilesPanel::deleteTile(int x, int y)
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
	int withComma = 3;		// tamanho de cada tile no arquivo, dois digitos mais virgula

	fs.seekp(fs.tellg(), std::ios_base::beg);

	// linebreak diferente no apple e nos outros SOS
	#ifdef __APPLE__
		int firstBreakLine = 2;		// tamanho dos dois primeiros line breaks
		fs.seekp( location * withComma + firstBreakLine + y, std::ios_base::cur ); // + y para line breaks no final de cada linha
	#else
		fs.seekp( (location-1) * withComma + y * 2, std::ios_base::cur ); // nao me pergunte por que essa conta
	#endif

	fs << "-1";

	fs.close();

	// Alterar visualização em runtime
	tileMap_->tileMatrix_[x + y*mapWidth + 0*mapWidth*mapHeight] = -1;
}
#include "../include/TileMap.hpp"

TileMap::TileMap(const char* file, TileSet* tileSet)
{
	load(file);
	tileSet_ = tileSet;
}

void TileMap::load(const char* file)
{
	tileMatrix_.clear();

	std::ifstream ifs;
	char comma;

	ifs.open(file, std::ifstream::in);

	if(!ifs.is_open())
	{
		std::string fileStr(file);
		//throw ExcecaoArquivo("Erro na abertura do arquivo de tile map " + fileStr);
		std::cout << "tileMap exception" << std::endl;
	}

	ifs >> mapWidth_;
	ifs >> comma;
	ifs >> mapHeight_;
	ifs >> comma;
	ifs >> mapDepth_;
	ifs >> comma;

	int curValue;

	while(ifs.good())
	{
		ifs >> curValue;
		ifs >> comma;
		tileMatrix_.emplace_back(curValue);
	}

	ifs.close();
}

void TileMap::setTileSet(TileSet* tileSet)
{
	tileSet_ = tileSet;
}

int& TileMap::at(int x, int y, int z)
{
	return tileMatrix_[ x + y*mapWidth_ + z*mapWidth_*mapHeight_ ];
}

void TileMap::render(int cameraX, int cameraY)
{
	for (int i = 0; i < mapDepth_; i++) {
		renderLayer(i, cameraX, cameraY);
	}
	tileSet_->render (02, 0, 0);
}

void TileMap::renderLayer(int layer, int cameraX, int cameraY)
{
	// std::cout << "idj: " << at(31, 16, 0) << std::endl;
	for (int i = 0; i < mapHeight_; i++) {
		for (int j = 0; j < mapWidth_; j++) {
			if (at(j, i, layer) >= 0) {
				// if (j == 31 && i == 16) {
				// 	std::cout << "-: " << (unsigned)at(j, i, layer) << std::endl;
				// 	std::cout << "A: " << j * tileSet_->getTileWidth() << std::endl;
				// 	std::cout << "B: " << i * tileSet_->getTileHeight() << std::endl;
				// }
				tileSet_->render( 
					(unsigned)at(j, i, layer), 
					(float)(j * tileSet_->getTileWidth() - cameraX * layer), 
					(float)(i * tileSet_->getTileHeight() - cameraY * layer) 
				);
			}
		}
	}
}

int TileMap::getWidth() const
{
	return mapWidth_;
}

int TileMap::getHeight() const
{
	return mapHeight_;
}

int TileMap::getDepth() const
{
	return mapDepth_;
}
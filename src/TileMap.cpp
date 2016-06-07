#include <sstream>

#include "../include/TileMap.hpp"
#include "../include/Camera.hpp"
#include "../include/Resources.hpp"

TileMap::TileMap(const char* file, TileSet* tileSet) : filename_(file)
{
	load();
	tileSet_ = tileSet;
}

void TileMap::load()
{
	tileMatrix_.clear();

	std::ifstream ifs;
	char comma;

	ifs.open(filename_, std::ifstream::in);

	if(!ifs.is_open())
	{
		std::cout << "Erro na abertura do arquivo de tile map para leitura" << std::endl;
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

void TileMap::save()
{
	std::ofstream ofs(filename_, std::ofstream::out | std::ofstream::trunc);
	if(!ofs.is_open())
	{
		std::cout << "Erro na abertura do arquivo de tile map para escrita" << std::endl;
	}

	ofs << mapWidth_;
	ofs << ',';
	ofs << mapHeight_;
	ofs << ',';
	ofs << mapDepth_;
	ofs << ',';

	ofs << std::endl;
	ofs << std::endl;

	for (int z = 0; z < mapDepth_; z++)
	{
		for (int y = 0; y < mapHeight_; y++)
		{
			for (int x = 0; x < mapWidth_; x++)
			{
				// to_string
				std::ostringstream ss;
				int value = at(x, y, z);
				ss << value;
				std::string strValue = ss.str();
				if(value >= 0 && value < 10) {
					strValue = "0" + strValue;
				}
				ofs << strValue;
				ofs << ',';
			}
			ofs << std::endl;
		}
		ofs << std::endl;
		ofs << std::endl;
	}

	ofs.close();
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
	for (int i = mapDepth_ - 1; i >= 0; i--) {
		renderLayer(i, cameraX, cameraY);
	}
}

void TileMap::renderLayer(int layer, int cameraX, int cameraY)
{

	int tileX = (Camera::pos_.x() / tileSet_->getTileWidth()) - 2;
	int tileY = (Camera::pos_.y() / tileSet_->getTileHeight()) - 2;
	int tileW = ((Camera::pos_.x() + Resources::WINDOW_WIDTH) / tileSet_->getTileWidth()) + 2;
	int tileH = ((Camera::pos_.y() + Resources::WINDOW_HEIGHT) / tileSet_->getTileHeight()) + 2;

	for (int i = tileY >= 0 ? tileY : 0; 
		i < (tileH < mapHeight_ ? tileH : mapHeight_); 
		i++)
	{
		for (int j = tileX >= 0 ? tileX : 0; 
			j < (tileW < mapWidth_ ? tileW : mapWidth_); 
			j++)
		{
			if (at(j, i, layer) >= 0)
			{
				switch(layer)
				{
					case 0:
						tileSet_->render( 
							(unsigned)at(j, i, layer), 
							(float)(j * tileSet_->getTileWidth()  + cameraX - Camera::pos_.x() * (double)0.5), 
							(float)(i * tileSet_->getTileHeight() + cameraY - Camera::pos_.y() * (double)0.5) 
						);
						break;
					case 1:
						tileSet_->render( 
							(unsigned)at(j, i, layer), 
							(float)(j * tileSet_->getTileWidth()  + cameraX), 
							(float)(i * tileSet_->getTileHeight() + cameraY) 
						);
						break;
					case 2:
						tileSet_->render( 
							(unsigned)at(j, i, layer), 
							(float)(j * tileSet_->getTileWidth()  + cameraX + Camera::pos_.x() * (double)0.5), 
							(float)(i * tileSet_->getTileHeight() + cameraY + Camera::pos_.y() * (double)0.5) 
						);
						break;
					case 3:
						tileSet_->render( 
							(unsigned)at(j, i, layer), 
							(float)(j * tileSet_->getTileWidth()  + cameraX + Camera::pos_.x() * (double)0.75), 
							(float)(i * tileSet_->getTileHeight() + cameraY + Camera::pos_.y() * (double)0.75) 
						);
						break;
					default:
						break;
				}
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
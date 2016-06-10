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

void TileMap::render(int x, int y)
{
	for (int i = mapDepth_ - 1; i >= 0; i--) {
		renderLayer(i, x, y);
	}
}

void TileMap::renderLayer(int layer, int x, int y)
{
	Vec2 layerSpeed;
	int tileX = 0, tileY = 0, tileW = mapWidth_, tileH = mapHeight_;

	switch (layer)
	{
		case 0:
			layerSpeed = Camera::pos_ * -0.5;
			break;
		default:
		case 1:
			tileX = (Camera::pos_.x()/* - layerSpeed.x()*/ / tileSet_->getTileWidth()) - 2;
			tileY = (Camera::pos_.y() /*- layerSpeed.y()*/ / tileSet_->getTileHeight()) - 2;
			tileW = ((Camera::pos_.x()/* + layerSpeed.x()*/ + Resources::WINDOW_WIDTH) / tileSet_->getTileWidth()) + 2;
			tileH = ((Camera::pos_.y() /*+ layerSpeed.y()*/ + Resources::WINDOW_HEIGHT) / tileSet_->getTileHeight()) + 2;
			layerSpeed = Vec2(0,0);
			break;
		case 2:
			layerSpeed = Camera::pos_ * 0.5;
			break;
		case 3:
			layerSpeed = Camera::pos_ * 0.75;
			break;
	}


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
				tileSet_->render( 
					(unsigned)at(j, i, layer), 
					(float)(j * tileSet_->getTileWidth() + x + layerSpeed.x()), 
					(float)(i * tileSet_->getTileHeight() + y + layerSpeed.y())
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
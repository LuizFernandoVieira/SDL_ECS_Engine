#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <vector>
#include <fstream>
#include <iostream>
#include <string>

#include "TileSet.hpp"

class TileMap
{
public:
	TileMap(const char* file, TileSet* tileSet);
	void load();
	void save();
	void setTileSet(TileSet* tileSet);
	int& at(int x, int y, int z=0);
	void render(int cameraX, int cameraY);
	void renderLayer(int layer, int cameraX, int cameraY);
	int getWidth() const;
	int getHeight() const;
	int getDepth() const;
	std::vector<int> tileMatrix_;
private:
	TileSet* tileSet_;
	std::string filename_;
	int mapWidth_;
	int mapHeight_;
	int mapDepth_;
};

#endif
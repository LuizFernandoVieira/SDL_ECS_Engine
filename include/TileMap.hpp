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
	TileMap(const char* file, int width, int height);
	void newTileMap(int width, int height);
	void load();
	void save();
	void setTileSet(TileSet* tileSet);
	int& at(int x, int y, int z=0);
	void render(int x, int y);
	void renderLayer(int layer, int x, int y);
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

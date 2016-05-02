#ifndef TILESET_HPP
#define TILESET_HPP

#include <iostream>

#include "Sprite.hpp"

class TileSet
{
public:
	TileSet(int tileWidth, int tileHeight, const char* file);
	void render(unsigned index, float x, float y);
	int getTileWidth() const;
	int getTileHeight() const;
	int getNumberOfTiles();
private:
	Sprite* tileSet_;
	int rows_;
	int columns_;
	int tileWidth_;
	int tileHeight_;
};

#endif
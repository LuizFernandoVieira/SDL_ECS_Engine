#ifndef TILESPANEL_HPP
#define TILESPANEL_HPP

#include <string>
#include <iostream>

#include "Rect.hpp"
#include "Vec2.hpp"
#include "Sprite.hpp"
#include "TileSet.hpp"
#include "TileMap.hpp"
#include "Panel.hpp"

class TilesPanel : public Panel
{
public:
	TilesPanel(TileSet& tileSet, TileMap& tileMap, Rect rect, std::string imgPath, int& selectedTile);
	~TilesPanel();
	virtual void update();
	virtual void render();

private:
	void placeTile(int x, int y);

	TileSet* tileSet_;
	TileMap* tileMap_;
	std::string tileMapFilename_;

	Rect cursorPos_;
	Sprite cursorBg_;

	Vec2 firstDragClick_;
	Vec2 curDragClick_;

	int* selectedTile_;
};

#endif
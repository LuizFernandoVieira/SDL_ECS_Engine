#ifndef TILEMAPPANEL_HPP
#define TILEMAPPANEL_HPP

#include <string>
#include <iostream>

#include "Rect.hpp"
#include "Vec2.hpp"
#include "Sprite.hpp"
#include "TileSet.hpp"
#include "TileMap.hpp"
#include "Panel.hpp"
#include "LevelEditorState.hpp"

class TileMapPanel : public Panel
{
public:
	TileMapPanel(TileSet& tileSet, TileMap& tileMap, Rect rect, std::string imgPath, int& selectedTile, int& selectedLayer, LevelEditorState::Tools& selectedTool);
	~TileMapPanel();
	void update();
	void render();

private:
	void placeTile(int x, int y);
	void deleteTile(int x, int y);

	TileSet* tileSet_;
	TileMap* tileMap_;
	std::string tileMapFilename_;

	Rect cursorPos_;
	Sprite cursorBg_;

	Vec2 firstDragClick_;
	Vec2 curDragClick_;

	int* selectedTile_;
	int* selectedLayer_;

	LevelEditorState::Tools* selectedTool_;
};

#endif

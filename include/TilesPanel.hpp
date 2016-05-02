#ifndef TILESPANEL_HPP
#define TILESPANEL_HPP

#include <string>

#include "Panel.hpp"
#include "TileSet.hpp"
#include "TileMap.hpp"
#include "LevelEditorSystem.hpp"

class TilesPanel : public Panel
{
public:
	TilesPanel(TileSet& tileSet, Rect rect, std::string imgPath);
	~TilesPanel(){}
	virtual void update();
	virtual void render();

private:
	TileSet* tileSet_;
	TileMap* tileMap_;

	LevelEditorSystem* editorSystem_;
};

#endif
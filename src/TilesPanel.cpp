#include "../include/TilesPanel.hpp"
#include "../include/Rect.hpp"
// #include "../include/InputHandler.hpp"

TilesPanel::TilesPanel(TileSet& tileSet, Rect rect, std::string imgPath) : Panel(rect, imgPath)
{
	tileSet_ = &tileSet;
	tileMap_ = new TileMap("../map/tileMap.txt", tileSet_);

	// editorSystem_ = new LevelEditorSystem(*tileMap_, "../map/tileMap.txt");
}


void TilesPanel::update()
{
	Panel::update();
	
}


void TilesPanel::render()
{
	Panel::render();
	tileMap_->render(rect_.x(), rect_.y());
}
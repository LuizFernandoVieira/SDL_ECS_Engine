#ifndef TILESETANDOBJECTSPANEL_HPP
#define TILESETANDOBJECTSPANEL_HPP

#include <string>

#include "Panel.hpp"
#include "Rect.hpp"
#include "Button.hpp"
#include "StaticSprite.hpp"

class TileSetAndObjectsPanel : public Panel
{
public:
	TileSetAndObjectsPanel(Rect rect, std::string imgPath);
	~TileSetAndObjectsPanel();
	void update();
	void render();

	enum Tab {
		TILES,
		COLLISION,
		OBJECTS
	};

	void addButton(Button& button, Tab tab);
	// void addButton(Button& button);
	TileSetAndObjectsPanel::Tab getSelectedTab();

private:
	TileSetAndObjectsPanel::Tab selectedTab_;

	std::vector<Button> tileButtons_;
	std::vector<Button> collisionButtons_;

	int tabButtonHeight;

	StaticSprite* objectSp;
	Button* previousObject;
	Rect previousObjectProportions;
	Button* nextObject;
	Rect nextObjectProportions;
};



#endif

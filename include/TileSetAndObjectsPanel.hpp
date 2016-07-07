#ifndef TILESETANDOBJECTSPANEL_HPP
#define TILESETANDOBJECTSPANEL_HPP

#include <string>

#include "Panel.hpp"
#include "Rect.hpp"
#include "Button.hpp"
#include "StaticSprite.hpp"
#include "Sprite.hpp"
#include "ObjectMap.hpp"
#include "Text.hpp"

#define SCROLL_SPEED 400

class TileSetAndObjectsPanel : public Panel
{
public:
	TileSetAndObjectsPanel(Rect rect, std::string imgPath, ObjectMap* objectMap, int& selectedObject);
	~TileSetAndObjectsPanel();
	void update();
	void render();

	enum Tab {
		TILES,
		COLLISION,
		OBJECTS
	};

	void addButton(Button& button, Tab tab);
	TileSetAndObjectsPanel::Tab& getSelectedTab();
	int& getScroll();

private:
	void createButtons();
	void createObjectSprite();
	void resize();

	int scroll_;

	TileSetAndObjectsPanel::Tab selectedTab_;

	std::vector<Button*> tileButtons_;
	std::vector<Button*> collisionButtons_;

	int tabButtonHeight_;

	int& selectedObject_;
	ObjectMap* objectMap_;
	Text objectName_;
	StaticSprite* objectSp_;

	Button* previousObject;
	Rect previousObjectProportions;
	Button* nextObject;
	Rect nextObjectProportions;
};

#endif

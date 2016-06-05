#ifndef TILESETANDOBJECTSPANEL_HPP
#define TILESETANDOBJECTSPANEL_HPP

#include <string>

#include "Panel.hpp"
#include "Rect.hpp"
#include "Button.hpp"
#include "StaticSprite.hpp"
#include "Sprite.hpp"
#include "ObjectMap.hpp"

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
	// void addButton(Button& button);
	TileSetAndObjectsPanel::Tab& getSelectedTab();

private:
	void createButtons();
	void createObjectSprite();
	void resize();

	TileSetAndObjectsPanel::Tab selectedTab_;

	std::vector<Button> tileButtons_;
	std::vector<Button> collisionButtons_;

	int tabButtonHeight_;

	int& selectedObject_;
	ObjectMap* objectMap_;
	std::string objectName_;
	StaticSprite* objectSp_;

	Button* previousObject;
	Rect previousObjectProportions;
	Button* nextObject;
	Rect nextObjectProportions;

	// pugi::xml_document globalObjects_;
	// int selectedObject_;
	// pugi::xml_node getSelectedObjectXML(int index);
};



#endif

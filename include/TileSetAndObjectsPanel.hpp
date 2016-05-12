#ifndef TILESETANDOBJECTSPANEL_HPP
#define TILESETANDOBJECTSPANEL_HPP

#include <string>

#include "Panel.hpp"
#include "Rect.hpp"
#include "Button.hpp"

class TileSetAndObjectsPanel : public Panel
{
public:
	TileSetAndObjectsPanel(Rect rect, std::string imgPath);
	~TileSetAndObjectsPanel();
	void update();
	void render();

  enum Tab {
    TILES,
    OBJECTS
  };

  void addButton(Button& button, Tab tab);
  TileSetAndObjectsPanel::Tab getSelectedTab();
private:
  TileSetAndObjectsPanel::Tab selectedTab_;

  std::vector<std::pair<Button*, Tab>> tileButtons_;

  int tabButtonHeight;
};



#endif

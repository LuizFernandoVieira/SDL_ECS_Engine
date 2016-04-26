#ifndef NAVIGATIONPANEL_HPP
#define NAVIGATIONPANEL_HPP

#include "Panel.hpp"
#include "Sprite.hpp"

class NavigationPanel : public Panel
{
public:
	NavigationPanel(Rect& rect, std::string imgPath);
	~NavigationPanel(){}
	void update();
	void render();
};

#endif
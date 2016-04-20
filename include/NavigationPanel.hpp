#ifndef NAVIGATIONPANEL_HPP
#define NAVIGATIONPANEL_HPP

#include "Sprite.hpp"

class NavigationPanel
{
public:
	NavigationPanel(int screenWidth, int screenHeight);
	~NavigationPanel(){}
	void update();
	void render();

private:
	int screenWidth_;
	int screenHeight_;
	float width_;
	Sprite border_;
};

#endif
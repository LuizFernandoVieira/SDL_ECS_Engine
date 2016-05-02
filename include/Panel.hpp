#ifndef PANEL_HPP
#define PANEL_HPP

#include <vector>
#include <string>

#include "Sprite.hpp"
#include "Rect.hpp"
#include "Button.hpp"

class Panel
{
public:
	Panel(Rect rect, std::string imgPath);
	~Panel() {}
	virtual void update();
	virtual void render();
	void add(Button& button, Rect rect);
	void add(Panel& panel, Rect rect);
	Rect getRect();
	void setRect(Rect rect);
protected:
	std::vector<std::pair<Panel*, Rect>> panels_;
	std::vector<std::pair<Button*, Rect>> buttons_;
	Rect rect_;
	Sprite bg_;
};

#endif
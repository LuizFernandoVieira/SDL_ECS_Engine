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
	void update();
	void render();
	void add(Panel panel, Rect rect);
	void add(Button button);
	Rect getRect();
	void setRect(Rect rect);
private:
	std::vector<std::pair<Panel, Rect> > panels_;
	std::vector<Button> buttons_;
	Rect rect_;
	Sprite bg_;
};

#endif
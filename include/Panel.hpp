#ifndef PANEL_HPP
#define PANEL_HPP

#include <vector>
#include <string>

#include "Sprite.hpp"
#include "Button.hpp"

class Panel
{
public:
	Panel(Rect& rect, std::string imgPath);
	~Panel() {}
	void update();
	void render();
	void add(Panel& panel);
	void add(Button& button);
private:
	std::vector<Panel> panels_;
	std::vector<Button> buttons_;
	Rect rect_;
	Sprite bg_;
};

#endif
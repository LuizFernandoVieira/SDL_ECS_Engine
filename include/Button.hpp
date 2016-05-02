#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>

#include "StaticSprite.hpp"
#include "Rect.hpp"

class Button
{
public:
	Button(Rect rect, std::string imgPath);
	~Button();
	virtual void update();
	virtual void render();
	Rect getRect();
	void setRect(Rect rect);
	bool isResizable();
	void setResizable(bool resizable);
private:
	Rect rect_;
	StaticSprite sprite_;
	bool resizable_;
};

#endif
#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>
#include <functional>

#include "StaticSprite.hpp"
#include "Rect.hpp"

class Button
{
public:
	Button(Rect rect, std::string imgPath);
	~Button();
	void update();
	void render(int scroll = 0);
	Rect& getRect();
	void setRect(Rect rect);
	bool isResizable();
	void setResizable(bool resizable);
	void setSpriteClip(Rect clip);
private:
	Rect rect_;
	StaticSprite sprite_;
	bool resizable_;
};

#endif

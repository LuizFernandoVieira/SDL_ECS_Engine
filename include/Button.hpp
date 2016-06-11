#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>
#include <functional>

#include "StaticSprite.hpp"
#include "Rect.hpp"
// #include "IState.hpp"

class Button
{
public:
	Button(Rect rect, std::string imgPath/*, std::function<void(State*)> execute*/);
	~Button();
	void update();
	void render();
	Rect& getRect();
	void setRect(Rect rect);
	bool isResizable();
	void setResizable(bool resizable);
	void setSpriteClip(Rect clip);

	// std::function<void(State*)> execute_;

private:
	Rect rect_;
	StaticSprite sprite_;
	bool resizable_;
};

#endif

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Sprite.hpp"

class Button
{
public:
	Button();
	~Button();
	void update(float dt);
	void render();
private:
	Sprite sprite_;
};

#endif
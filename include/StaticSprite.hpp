#ifndef STATICSPRITE_HPP
#define STATICSPRITE_HPP

#ifdef __APPLE__
	#include <SDL2/SDL.h>
#else
	#include "SDL.h"
#endif

#include "Sprite.hpp"

class StaticSprite : public Sprite
{
public:
	StaticSprite();
	StaticSprite(const char* file, int frameCount = 1, float frameTime = 1);
	~StaticSprite();
	void render(int x, int y, float angle = 0);
};

#endif
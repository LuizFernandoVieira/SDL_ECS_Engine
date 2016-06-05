#ifndef SPRITE_HPP
#define SPRITE_HPP

#ifdef __APPLE__
	#include <SDL2/SDL.h>
#else
	#include "SDL.h"
#endif

#include <memory>

class Sprite
{
public:
	Sprite();
	Sprite(const char* file, int frameCount = 1, float frameTime = 1);
	virtual ~Sprite();
	void open(const char* file);
	void setClip(int x, int y, int w, int h);
	virtual void render(int x, int y, float angle = 0, bool flip = false);
	void renderSelection(int x, int y);
	void update(float dt);
	int getWidth();
	int getHeight();
	bool isOpen();
	void setScaleX(float scale);
	void setScaleY(float scale);
	void setFrame(int frame);
	void setFrameCount(int frameCount);
	void setFrameTime(float frameTime);
protected:
	std::shared_ptr<SDL_Texture> texture_;
	int width_;
	int height_;
	SDL_Rect clipRect_;
	float scaleX_;
	float scaleY_;
	int frameCount_;
	int currentFrame_;
	float timeElapsed_;
	float frameTime_;
};

#endif
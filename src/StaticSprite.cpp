#include "../include/StaticSprite.hpp"
#include "../include/Game.hpp"

StaticSprite::StaticSprite() : Sprite()
{

}

StaticSprite::StaticSprite(const char* file, int frameCount, float frameTime) :
Sprite(file, frameCount, frameTime)
{

}

StaticSprite::~StaticSprite()
{

}

void StaticSprite::render(int x, int y, float angle)
{
	SDL_Rect dstRect;

	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = clipRect_.w * scaleX_;
	dstRect.h = clipRect_.h * scaleY_;

	SDL_RenderCopyEx ( Game::getInstance().getRenderer(), texture_.get(), &clipRect_, &dstRect, (double)angle, NULL, SDL_FLIP_NONE );

}
#include "../include/Sprite.hpp"
#include "../include/Game.hpp"
#include "../include/Resources.hpp"
#include "../include/Camera.hpp"

Sprite::Sprite()
{
	texture_ = NULL;
	scaleX_ = 1;
	scaleY_ = 1;
	frameCount_ = 1;
	frameTime_ = 1;
	timeElapsed_ = 0.0;
	currentFrame_ = 0;
	setClip(0, 0, width_ / frameCount_, height_);
}

Sprite::Sprite(const char* file, int frameCount, float frameTime)
{
	texture_ = NULL;
	scaleX_ = 1;
	scaleY_ = 1;
	frameCount_ = frameCount;
	frameTime_ = frameTime;
	timeElapsed_ = 0.0;
	currentFrame_ = 0;
	open(file);
	setClip(0, 0, width_ / frameCount_, height_);
}

Sprite::~Sprite()
{

}

void Sprite::open(const char* file)
{
	texture_ = Resources::GetImage(file);
	SDL_QueryTexture ( texture_.get(), NULL, NULL, &width_, &height_ );
}

void Sprite::setClip(int x, int y, int w, int h)
{
	clipRect_.x = x;
	clipRect_.y = y;
	clipRect_.w = w;
	clipRect_.h = h;
}

void Sprite::render(int x, int y, float angle)
{
	SDL_Rect dstRect;

	dstRect.x = x - Camera::getPosition().x();
	dstRect.y = y - Camera::getPosition().y();
	dstRect.w = clipRect_.w * scaleX_;
	dstRect.h = clipRect_.h * scaleY_;

	SDL_RenderCopyEx ( Game::getInstance().getRenderer(), texture_.get(), &clipRect_, &dstRect, (double)angle, NULL, SDL_FLIP_NONE );
}

void Sprite::renderSelection(int x, int y)
{
	SDL_Renderer* renderer = Game::getInstance().getRenderer();
	SDL_RenderDrawLine(renderer, x, y, clipRect_.w + x, y);
	SDL_RenderDrawLine(renderer, x, y, x, clipRect_.h + y);
	SDL_RenderDrawLine(renderer, x, y, clipRect_.w + x, clipRect_.h + y);
	SDL_RenderDrawLine(renderer, clipRect_.w + x, y, clipRect_.w + x, clipRect_.h + y);
	SDL_RenderDrawLine(renderer, x, clipRect_.h + y, clipRect_.w + x, clipRect_.h + y);
	SDL_RenderDrawLine(renderer, clipRect_.w + x, y, x, clipRect_.h + y);
}

int Sprite::getWidth()
{
	return (width_ / frameCount_) * scaleX_;
}

int Sprite::getHeight()
{
	return height_ * scaleY_;
}

bool Sprite::isOpen()
{
	return texture_ == NULL ? false : true;
}

void Sprite::setScaleX(float scale)
{
	scaleX_ = scale;
}

void Sprite::setScaleY(float scale)
{
	scaleY_ = scale;
}

void Sprite::update(float dt)
{
	timeElapsed_ += dt;
	if (timeElapsed_ >= frameTime_)
	{
		setFrame(currentFrame_ + 1);
		timeElapsed_ = 0.0;
	}
}

void Sprite::setFrame(int frame)
{
	if(frame >= frameCount_) {
		currentFrame_ = frame % frameCount_;
	} else {
		currentFrame_ = frame;
	}
	setClip( currentFrame_ * width_ / frameCount_, 0, width_ / frameCount_, height_ );
}

void Sprite::setFrameCount(int frameCount)
{
	frameCount_ = frameCount;
}

void Sprite::setFrameTime(float frameTime)
{
	frameTime_ = frameTime;
}
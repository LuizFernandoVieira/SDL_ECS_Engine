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
	loopBackFrame_ = 0;
	width_ = 0;
	height_ = 0;
	setClip(0, 0, 0, 0);
}

Sprite::Sprite(const char* file, int frameCount, float frameTime)
{
	texture_ = NULL;
	scaleX_ = 1;
	scaleY_ = 1;
	frameCount_ = frameCount;
	frameTime_ = frameTime;
	loopBackFrame_ = 0;
	timeElapsed_ = 0.0;
	currentFrame_ = 0;
	open(file);
	setClip(0, 0, width_ / frameCount_, height_);
}

Sprite::Sprite(const char* file, int frameCount, float frameTime, int loopBackFrame)
{
	texture_ = NULL;
	scaleX_ = 1;
	scaleY_ = 1;
	frameCount_ = frameCount;
	frameTime_ = frameTime;
	loopBackFrame_ = loopBackFrame;
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

void Sprite::render(int x, int y, float angle, bool flip)
{
	SDL_Rect dstRect;

	dstRect.x = x - Camera::pos_.x();
	dstRect.y = y - Camera::pos_.y();
	dstRect.w = clipRect_.w * scaleX_;
	dstRect.h = clipRect_.h * scaleY_;

/*	SDL_Point rotPoint;
	rotPoint.x = x;
	rotPoint.y = y;*/

	SDL_RenderCopyEx ( Game::getInstance().getRenderer(), texture_.get(), &clipRect_, &dstRect, (double)angle, /*&rotPoint*/NULL, flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE );
}

void Sprite::renderSelection(int x, int y)
{
	SDL_Renderer* renderer = Game::getInstance().getRenderer();

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

	SDL_RenderDrawLine(renderer, x, y, clipRect_.w + x, y);
	SDL_RenderDrawLine(renderer, x, y, x, clipRect_.h + y);
	SDL_RenderDrawLine(renderer, x, y, clipRect_.w + x, clipRect_.h + y);
	SDL_RenderDrawLine(renderer, clipRect_.w + x, y, clipRect_.w + x, clipRect_.h + y);
	SDL_RenderDrawLine(renderer, x, clipRect_.h + y, clipRect_.w + x, clipRect_.h + y);
	SDL_RenderDrawLine(renderer, clipRect_.w + x, y, x, clipRect_.h + y);

/*	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_Rect rectangle;

	rectangle.x = x;
	rectangle.y = y;
	rectangle.w = clipRect_.w + x;
	rectangle.h = clipRect_.h + y;
	SDL_RenderFillRect(renderer, &rectangle);*/

/*	Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

	SDL_Surface* surface = SDL_CreateRGBSurface(0,
                                  clipRect_.w,
                                  clipRect_.h,
                                  32,
                                  rmask,
                                  gmask,
                                  bmask,
                                  amask);
	SDL_SetSurfaceAlphaMod(surface, 100);

	SDL_Texture* texture =  SDL_CreateTextureFromSurface(renderer,
                                                         surface);

	SDL_Rect srcrect, dstrect;

	srcrect.x = 0;
	srcrect.y = 0;
	srcrect.w = clipRect_.w;
	srcrect.h = clipRect_.h;
	dstrect.x = x;
	dstrect.y = y;
	dstrect.w = clipRect_.w + x;
	dstrect.h = clipRect_.h + y;

	SDL_RenderCopy(renderer, texture,
                   &srcrect,
                   &dstrect);*/
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
		currentFrame_ = loopBackFrame_;
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
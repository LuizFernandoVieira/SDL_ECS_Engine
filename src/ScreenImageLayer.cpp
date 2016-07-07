#include <sstream>

#include "../include/ScreenImageLayer.hpp"
#include "../include/Camera.hpp"
#include "../include/Resources.hpp"
#include "../include/Game.hpp"

ImageLayer::ImageLayer(const char* file)
{
	texture_ = NULL;

	scale_x = 1;
	scale_y = 1;
	width_ = 0;
	height_ = 0;
	setClip(0, 0, 0, 0);


	open(file);
	setClip(0, 0, width_, height_);

}

void ImageLayer::open(const char* file)
{
	texture_ = Resources::GetImage(file);
	SDL_QueryTexture ( texture_.get(), NULL, NULL, &width_, &height_ );
}
void ImageLayer::setClip(int x, int y, int w, int h)
{
	clipRect_.x = x;
	clipRect_.y = y;
	clipRect_.w = w;
	clipRect_.h = h;
}

void ImageLayer::Render(){
	
	SDL_Rect dstRect;

	dstRect.x = offset_x - (Camera::pos_.x() * parallax_x);
	dstRect.y = offset_y - (Camera::pos_.y() * parallax_y);
	dstRect.w = clipRect_.w * scale_x;
	dstRect.h = clipRect_.h * scale_y;

	SDL_RenderCopy ( Game::getInstance().getRenderer(), texture_.get(), &clipRect_, &dstRect);
}


#include "../include/Button.hpp"
#include "../include/InputHandler.hpp"

Button::Button(Rect rect, std::string imgPath): rect_(rect), sprite_(imgPath.c_str())
{
	sprite_.setScaleX( rect_.w() / (float)sprite_.getWidth() );
	sprite_.setScaleY( rect_.h() / (float)sprite_.getHeight() );
	resizable_ = false;
}

Button::~Button()
{
	
}

void Button::update()
{
	if (InputHandler::getInstance().mousePress(LEFT_MOUSE_BUTTON))
	{
		if (rect_.isInside(InputHandler::getInstance().getMouse()))
		{
			// DO SOMETHING
			// execute();
		}
	}
}

void Button::render()
{
	sprite_.render(rect_.x(), rect_.y());
}

Rect Button::getRect() {
	return rect_;
}

void Button::setRect(Rect rect)
{
	rect_ = rect;
	if (resizable_)
	{
		sprite_.setScaleX(1.0);
		sprite_.setScaleY(1.0);
		sprite_.setScaleX( rect_.w() / (float)sprite_.getWidth() );
		sprite_.setScaleY( rect_.h() / (float)sprite_.getHeight() );
	}
}

bool Button::isResizable()
{
	return resizable_;
}

void Button::setResizable(bool resizable)
{
	resizable_ = resizable;
}

void Button::setSpriteClip(Rect clip)
{
	sprite_.setClip(clip.x(), clip.y(), clip.w(), clip.h());
	// sprite_.setScaleX(1.0);
	// sprite_.setScaleY(1.0);
	sprite_.setScaleX( rect_.w() / clip.w() );
	sprite_.setScaleY( rect_.h() / clip.h() );
}
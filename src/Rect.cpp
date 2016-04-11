#include "../include/Rect.hpp"

Rect::Rect()
{
	x_ = 0.0;
	y_ = 0.0;
	w_ = 0.0;
	h_ = 0.0;
}

Rect::Rect(float x, float y, float w, float h)
{
	x_ = x;
	y_ = y;
	w_ = w;
	h_ = h;
}

Vec2 Rect::getCenter()
{
	return Vec2( x_+(w_ /2), y_+(h_ /2) );
}


Rect Rect::operator+ (const Vec2& vec2)
{
	Rect rect;
	rect.x( x_ + vec2.x() );
	rect.y( y_ + vec2.y() );
	rect.w(w_);
	rect.h(h_);
	return rect;
}

bool Rect::isInside(Vec2 vec2)
{
	if ( vec2.x() >= x_ &&
		 vec2.x() <= x_ + w_ &&
		 vec2.y() >= y_ &&
		 vec2.y() <= y_ + h_ )
		return true;
	else
		return false;
}

float Distance(Rect r1, Rect r2)
{
	return Distance( r1.getCenter(), r2.getCenter() );
}
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

// Rect::Rect(Rect rect) 
// {
// 	x_ = rect.x;
// 	y_ = rect.y;
// 	w_ = rect.w;
// 	h_ = rect.h;
// }

Vec2 Rect::getCenter() const
{
	return Vec2( x_+(w_/2), y_+(h_/2) );
}
Vec2 Rect::getPivot() const
{
	return Vec2( x_, y_ );
}
Vec2 Rect::getBase() const
{
	return Vec2( x_+(w_/2), y_ + h_ );
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

Rect& Rect::operator+= (const Vec2& vec2)
{
	x_ += vec2.x();
	y_ += vec2.y();
	return (*this);
}

Rect Rect::operator* (const Rect& r)
{
	Rect rect;
	rect.x( x_ * r.x() );
	rect.y( y_ * r.y() );
	rect.w( w_ * r.w() );
	rect.h( h_ * r.h() );
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
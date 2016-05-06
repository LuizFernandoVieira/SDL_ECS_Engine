#include "../include/Vec2.hpp"

Vec2::Vec2()
{
	x_ = 0.0;
	y_ = 0.0;
}

Vec2::Vec2(float x, float y)
{
	x_ = x;
	y_ = y;
}

Vec2 Vec2::operator+ (const Vec2& v)
{
	Vec2 vec2;
	vec2.x( x_ + v.x() );
	vec2.y( y_ + v.y() );
	return vec2;
}

Vec2 Vec2::operator- (const Vec2& v)
{
	Vec2 vec2;
	vec2.x( x_ - v.x() );
	vec2.y( y_ - v.y() );
	return vec2;
}

// Vec2 Vec2::operator* (const Vec2& p)
// {
// 	Vec2 vec2;
// 	Vec2.setX(x_ * p.getX());
// 	Vec2.setY(y_ * p.getY());
// 	return Vec2;
// }

// Vec2 Vec2::operator/ (const Vec2& p)
// {
// 	Vec2 Vec2;
// 	Vec2.setX(x_ / p.getX());
// 	Vec2.setY(y_ / p.getY());
// 	return Vec2;
// }



// Vec2 Vec2::operator+ (const float& e) const
// {
// 	Vec2 Vec2;
// 	Vec2.setX(x_ + e);
// 	Vec2.setY(y_ + e);
// 	return Vec2;
// }

// Vec2 Vec2::operator- (const float& e) const
// {
// 	Vec2 Vec2;
// 	Vec2.setX(x_ - e);
// 	Vec2.setY(y_ - e);
// 	return Vec2;
// }

Vec2 Vec2::operator* (const float& e) const
{
	Vec2 vec2;
	vec2.x(x_ * e);
	vec2.y(y_ * e);
	return vec2;
}

// Vec2 Vec2::operator/ (const float& e) const
// {
// 	Vec2 Vec2;
// 	Vec2.setX(x_ / e);
// 	Vec2.setY(y_ / e);
// 	return Vec2;
// }

bool Vec2::operator== (const Vec2& v) const
{
	if(x_ == v.x() && y_ == v.y())
		return true;
	else
		return false;
}

bool Vec2::operator!= (const Vec2& v) const
{
	if(x_ != v.x() || y_ != v.y())
		return true;
	else
		return false;
}

void Vec2::Rotate(float angle)
{
	angle = angle * PI / 180; // converte de graus para radianos
	float curX = x_;
	float curY = y_;
	x_ = curX * cos(angle) - curY * sin(angle);
	y_ = curY * cos(angle) + curX * sin(angle);
}


void Vec2::Rotate(Vec2 vec2, float module, float angle)
{
	angle = angle * PI / 180;
	x_ = module * sin(angle) + vec2.x();
	y_ = module * cos(angle) + vec2.y();
}


float Distance(Vec2 v1, Vec2 v2)
{
	return sqrt( pow ( v2.x() - v1.x(), 2.0 ) + pow ( v2.y() - v1.y(), 2.0 ) );
}


float LineInclination(Vec2 v1, Vec2 v2)
{
	float angle = atan( (v2.y() - v1.y()) / (v2.x() - v1.x()) ) * 180 / PI; // converte para graus
	if (v1.x() > v2.x())
		return angle + 180;
	return angle;
}
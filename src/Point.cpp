#include "../include/Point.hpp"

Point::Point()
{
	x_ = 0.0;
	y_ = 0.0;
}

Point::Point(float x, float y)
{
	x_ = x;
	y_ = y;
}

// Point Point::operator+ (const Point& p)
// {
// 	Point point;
// 	point.setX(x_ + p.getX());
// 	point.setY(y_ + p.getY());
// 	return point;
// }

// Point Point::operator- (const Point& p)
// {
// 	Point point;
// 	point.setX(x_ - p.getX());
// 	point.setY(y_ - p.getY());
// 	return point;
// }

// Point Point::operator* (const Point& p)
// {
// 	Point point;
// 	point.setX(x_ * p.getX());
// 	point.setY(y_ * p.getY());
// 	return point;
// }

// Point Point::operator/ (const Point& p)
// {
// 	Point point;
// 	point.setX(x_ / p.getX());
// 	point.setY(y_ / p.getY());
// 	return point;
// }

// Point Point::operator+ (const float& e) const
// {
// 	Point point;
// 	point.setX(x_ + e);
// 	point.setY(y_ + e);
// 	return point;
// }

// Point Point::operator- (const float& e) const
// {
// 	Point point;
// 	point.setX(x_ - e);
// 	point.setY(y_ - e);
// 	return point;
// }

// Point Point::operator* (const float& e) const
// {
// 	Point point;
// 	point.setX(x_ * e);
// 	point.setY(y_ * e);
// 	return point;
// }

// Point Point::operator/ (const float& e) const
// {
// 	Point point;
// 	point.setX(x_ / e);
// 	point.setY(y_ / e);
// 	return point;
// }

float Point::getX()
{
	return x_;
}

float Point::getY()
{
	return y_;
}

void Point::setX(float x)
{
	x_ = x;
}

void Point::setY(float y)
{
	y_ = y;
}
#ifndef RECT_HPP
#define RECT_HPP

#include "Point.hpp"

class Rect
{
public:
	Rect();
	Rect(float x, float y, float w, float h);
	Point getCenter();
	float getX();
	float getY();
	float getW();
	float getH();
	void setX(float x);
	void setY(float y);
	void setW(float w);
	void setH(float h);
private:
	float x_;
	float y_;
	float w_;
	float h_;
};

#endif
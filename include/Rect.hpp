#ifndef RECT_HPP
#define RECT_HPP

#include "Vec2.hpp"

class Rect
{
public:
	Rect();
	Rect(float x, float y, float w, float h);
	// Rect(Rect rect);

	Vec2 getCenter() const;

	Rect operator+ (const Vec2&);
	Rect& operator+= (const Vec2&);
	Rect operator* (const Rect&);

	bool isInside(Vec2 vec2);

	float x() const { return x_; }
	float y() const { return y_; }
	float w() const { return w_; }
	float h() const { return h_; }
	void x(float x) { x_ = x; }
	void y(float y) { y_ = y; }
	void w(float w) { w_ = w; }
	void h(float h) { h_ = h; }
private:
	float x_;
	float y_;
	float w_;
	float h_;
};

float Distance(Rect r1, Rect r2);

#endif
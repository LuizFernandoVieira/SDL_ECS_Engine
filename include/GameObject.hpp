#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "Rect.hpp"

class GameObject
{
public:
	virtual ~GameObject() {}
	virtual void update(float dt) = 0;
	virtual void render() = 0;
	Rect getRect() { return rect_; }
	void setRect(Rect rect) { rect_ = rect; }
protected:
	Rect rect_;
};

#endif
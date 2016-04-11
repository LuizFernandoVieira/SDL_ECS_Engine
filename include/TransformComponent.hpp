#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP

#include "Component.hpp"
#include "Rect.hpp"

class TransformComponent : public Component
{
public:
	TransformComponent() { rect_ = new Rect(); }
	~TransformComponent() {}
	Rect* getRect() { return rect_; }
	void setRect(Rect& rect) { rect_ = &rect; }
private:
	Rect* rect_;
};

#endif
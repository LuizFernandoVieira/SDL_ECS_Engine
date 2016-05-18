#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP

#include "Component.hpp"
#include "Rect.hpp"

class TransformComponent : public Component
{
public:
	TransformComponent() : rect_() { /*rect_ = new Rect();*/ }
	TransformComponent(Rect rect) { rect_ = rect; }
	~TransformComponent() { /*delete rect_;*/ }

	Rect rect_;
};

#endif
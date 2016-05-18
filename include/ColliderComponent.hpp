#ifndef COLLIDERCOMPONENT_HPP
#define COLLIDERCOMPONENT_HPP

#include "Component.hpp"
#include "Rect.hpp"

class ColliderComponent : public Component
{
public:
	ColliderComponent() : rect_() { /*rect_ = new Rect();*/ }
	ColliderComponent(Rect rect) { rect_ = rect; }
	~ColliderComponent() { /*delete rect_;*/ }

	Rect rect_;
};

#endif
#ifndef COLLIDERCOMPONENT_HPP
#define COLLIDERCOMPONENT_HPP

#include "Component.hpp"
#include "Rect.hpp"

class ColliderComponent : public Component
{
public:
	ColliderComponent() : rect_() {}
	ColliderComponent(Rect rect) { rect_ = rect; }
	~ColliderComponent() {}

	Rect rect_;
};

#endif
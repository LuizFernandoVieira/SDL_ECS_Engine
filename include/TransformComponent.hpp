#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP

#include "Component.hpp"
#include "Rect.hpp"

class TransformComponent : public Component
{
public:
	TransformComponent() : rect_(), scale_(1,1), rotation_(0) {}
	TransformComponent(Rect rect) : scale_(1,1), rotation_(0) { rect_ = rect; }
	TransformComponent(Rect rect, Vec2 scale, float rotation) { rect_ = rect; scale_ = scale; rotation_ = rotation; }
	~TransformComponent() {}

	Rect rect_;
	Vec2 scale_;
	float rotation_;
};

#endif
#ifndef SPEEDCOMPONENT_HPP
#define SPEEDCOMPONENT_HPP

#include "Component.hpp"
#include "Vec2.hpp"

class SpeedComponent : public Component
{
public:
	SpeedComponent() : speed_() {}
	SpeedComponent(Vec2 speed) { speed_ = speed; }
	~SpeedComponent() {}

	Vec2 speed_;
};

#endif
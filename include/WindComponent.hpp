#ifndef WINDCOMPONENT_HPP
#define WINDCOMPONENT_HPP

#include "Component.hpp"

enum Direction { W_UP, W_DOWN, W_LEFT, W_RIGHT };

class WindComponent : public Component
{
public:
	WindComponent() : direction_(W_LEFT), speed_(100) {}
	WindComponent(Direction direction, float speed) { direction_ = direction; speed_ = speed; }
	~WindComponent() {}

	Direction direction_;
	float speed_;
};

#endif
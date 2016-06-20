#ifndef HEALTHCOMPONENT_HPP
#define HEALTHCOMPONENT_HPP

#include "Component.hpp"

class HealthComponent : public Component
{
public:
	HealthComponent() : health_(1) {}
	HealthComponent(int health) { health_ = health; }
	~HealthComponent() {}

	int health_;
};

#endif
#ifndef HEALTHCOMPONENT_HPP
#define HEALTHCOMPONENT_HPP

#include "Component.hpp"
#include "Timer.hpp"

class HealthComponent : public Component
{
public:
	HealthComponent() : health_(1), timeToDie_() {}
	HealthComponent(int health) : timeToDie_() { health_ = health; }
	~HealthComponent() {}

	int health_;
	Timer timeToDie_;
};

#endif
#ifndef GRAVITYSYSTEM_HPP
#define GRAVITYSYSTEM_HPP

#include <map>

#include "System.hpp"
#include "SpeedComponent.hpp"
#include "StateComponent.hpp"
#include "PhysicsComponent.hpp"

class GravitySystem : public System
{
public:
	GravitySystem();
	void update(
		float dt,
		std::map<int, SpeedComponent*> speed,
		std::map<int, PhysicsComponent*> physics,
		std::map<int, StateComponent*> state
	);
};

#endif
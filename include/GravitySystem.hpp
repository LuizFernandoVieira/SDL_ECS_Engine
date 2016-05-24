#ifndef GRAVITYSYSTEM_HPP
#define GRAVITYSYSTEM_HPP

#include <map>

#include "System.hpp"
#include "SpeedComponent.hpp"
#include "PhysicsComponent.hpp"

class GravitySystem : public System
{
public:
	GravitySystem();
	void update(
		float dt,
		std::map<int, SpeedComponent*> sc,
		std::map<int, PhysicsComponent*> pc
	);
};

#endif
#ifndef GRAVITYSYSTEM_HPP
#define GRAVITYSYSTEM_HPP

#include <map>

#include "System.hpp"
#include "TransformComponent.hpp"
#include "StateComponent.hpp"
#include "PhysicsComponent.hpp"

class GravitySystem : public System
{
public:
	GravitySystem();
	void update(
		float dt,
		std::map<int, TransformComponent*> tc,
		std::map<int, StateComponent*> sc,
		std::map<int, PhysicsComponent*> pc
	);
};

#endif
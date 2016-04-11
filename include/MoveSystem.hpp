#ifndef MOVESYSTEM_HPP
#define MOVESYSTEM_HPP

#include <map>

#include "System.hpp"
#include "TransformComponent.hpp"
#include "StateComponent.hpp"
#include "PhysicsComponent.hpp"

class MoveSystem : public System
{
public:
	MoveSystem();
	void update(
		std::map<int, TransformComponent*> tc,
		std::map<int, StateComponent*> sc,
		std::map<int, PhysicsComponent*> pc
	);
};

#endif
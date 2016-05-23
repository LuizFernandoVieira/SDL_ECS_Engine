#ifndef MOVESYSTEM_HPP
#define MOVESYSTEM_HPP

#include <map>

#include "System.hpp"
#include "TransformComponent.hpp"
#include "SpeedComponent.hpp"
// #include "PhysicsComponent.hpp"

class MoveSystem : public System
{
public:
	MoveSystem();
	void update(
		float dt,
		std::map<int, TransformComponent*> tc,
		std::map<int, SpeedComponent*> sc
	);
};

#endif
#ifndef MOVESYSTEM_HPP
#define MOVESYSTEM_HPP

#include <map>

#include "System.hpp"
#include "TransformComponent.hpp"
#include "SpeedComponent.hpp"

class MoveSystem : public System
{
public:
	MoveSystem();
	void update(
		float dt,
		std::map<int, TransformComponent*> transform,
		std::map<int, SpeedComponent*> speed
	);
};

#endif
#ifndef PLAYERSYSTEM_HPP
#define PLAYERSYSTEM_HPP

#include <map>

#include "System.hpp"
#include "StateComponent.hpp"
#include "SpeedComponent.hpp"

class PlayerSystem : public System
{
public:
	PlayerSystem();
	void update(
		float dt,
		PlayerStateComponent* state,
		SpeedComponent* speed
	);
};

#endif
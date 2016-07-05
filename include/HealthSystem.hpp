#ifndef HEALTHSYSTEM_HPP
#define HEALTHSYSTEM_HPP

#include <map>

#include "System.hpp"
#include "GameState.hpp"

class HealthSystem : public System
{
public:
	HealthSystem();
	void update(float dt, GameState& gameState);
};

#endif
#ifndef GRAVITYSYSTEM_HPP
#define GRAVITYSYSTEM_HPP

#include <map>

#include "System.hpp"
#include "GameState.hpp"

class GravitySystem : public System
{
public:
	GravitySystem();
	void update(float dt, GameState& gameState);
};

#endif
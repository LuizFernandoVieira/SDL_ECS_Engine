#ifndef MOVESYSTEM_HPP
#define MOVESYSTEM_HPP

#include <map>

#include "System.hpp"
#include "GameState.hpp"

class MoveSystem : public System
{
public:
	MoveSystem();
	void update(float dt, GameState& gameState);
};

#endif
#ifndef SYSTEM_HPP
#define SYSTEM_HPP

class GameState;

class System
{
public:
	~System() {}
	virtual void update(float dt, GameState& gameState) = 0;
};

#include "GameState.hpp"

#endif

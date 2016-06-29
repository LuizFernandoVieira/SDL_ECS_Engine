#ifndef ATTACKSYSTEM_HPP
#define ATTACKSYSTEM_HPP

#include <map>

#include "System.hpp"
#include "Timer.hpp"
#include "GameState.hpp"

class AttackSystem : public System
{
public:
	AttackSystem();
	void update(float dt, GameState& gameState);
private:
	Timer timer;
};

#endif
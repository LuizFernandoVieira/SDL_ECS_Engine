#ifndef AttackSYSTEM_HPP
#define AttackSYSTEM_HPP

#include "System.hpp"
#include "Timer.hpp"

class AttackSystem : public System
{
public:
	AttackSystem();
	void update(float dt, GameState& gameState);
private:
	Timer timer;
};

#endif
#ifndef ATTACKSYSTEM_HPP
#define ATTACKSYSTEM_HPP

#include <map>

#include "System.hpp"
#include "StateComponent.hpp"
#include "Timer.hpp"

class AttackSystem : public System
{
public:
	AttackSystem();
	void update(
		float dt,
		StateComponent* oldState,
		StateComponent* state
	);
private:
	Timer timer;
};

#endif
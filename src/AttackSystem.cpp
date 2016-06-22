#include "../include/AttackSystem.hpp"
#include <iostream>

AttackSystem::AttackSystem() : timer()
{

}

void AttackSystem::update(
	float dt,
	StateComponent* oldState,
	StateComponent* state)
{
	if (state->state_ == State::ATTACKING)
	{
		timer.update(dt);
		if (timer.get() >= 0.24)
		{
			state->state_ = State::IDLE;
			timer.restart();
		}
	}
}
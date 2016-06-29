#include "../include/AttackSystem.hpp"
#include "../include/StateComponent.hpp"

AttackSystem::AttackSystem() : timer()
{

}

void AttackSystem::update(float dt, GameState& gameState)
{
	StateComponent* state = gameState.mapState_[gameState.player_];
	
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
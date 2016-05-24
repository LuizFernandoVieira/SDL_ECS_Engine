#include "../include/PlayerJumpingState.hpp"
#include "../include/InputHandler.hpp"
#include "../include/PlayerFallingState.hpp"

PlayerJumpingState::PlayerJumpingState(EntityStateMachine& stateMachine) : EntityState(stateMachine) 
{

}

PlayerJumpingState::~PlayerJumpingState()
{

}

void PlayerJumpingState::handle(StateComponent* stateComp, SpeedComponent* speedComp)
{
	if (speedComp->speed_.y() > 0)
	{
		PlayerFallingState* state = new PlayerFallingState(*stateMachine_);
		stateMachine_->changeState(*state);
		if (speedComp->speed_.x() > 0)
			stateComp->setFacingRight(true);
		else if (speedComp->speed_.x() < 0)
			stateComp->setFacingRight(false);
	}
	else if (speedComp->speed_.x() > 0)
	{
		stateComp->setFacingRight(true);
	}
	else if (speedComp->speed_.x() < 0)
	{
		stateComp->setFacingRight(false);
	}

}
/*#include "../include/PlayerFallingState.hpp"
#include "../include/InputHandler.hpp"
#include "../include/PlayerIdleState.hpp"
#include "../include/PlayerWalkingState.hpp"

PlayerFallingState::PlayerFallingState(EntityStateMachine& stateMachine) : FallingState(stateMachine) 
{

}

PlayerFallingState::~PlayerFallingState()
{

}

void PlayerFallingState::handle(StateComponent* stateComp, SpeedComponent* speedComp)
{
	if (speedComp->speed_.y() == 0)
	{
		if (speedComp->speed_.x() > 0)
		{
			PlayerWalkingState* state = new PlayerWalkingState(*stateMachine_);
			stateMachine_->changeState(*state);
			stateComp->setFacingRight(true);
		}
		else if (speedComp->speed_.x() < 0)
		{
			PlayerWalkingState* state = new PlayerWalkingState(*stateMachine_);
			stateMachine_->changeState(*state);
			stateComp->setFacingRight(false);
		}
		else
		{
			PlayerIdleState* state = new PlayerIdleState(*stateMachine_);
			stateMachine_->changeState(*state);
		}
	}
	else if (speedComp->speed_.x() > 0)
	{
		stateComp->setFacingRight(true);
	}
	else if (speedComp->speed_.x() < 0)
	{
		stateComp->setFacingRight(false);
	}

}*/
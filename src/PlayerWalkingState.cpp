/*#include "../include/PlayerWalkingState.hpp"
#include "../include/InputHandler.hpp"
#include "../include/PlayerIdleState.hpp"
#include "../include/PlayerJumpingState.hpp"
#include "../include/PlayerFallingState.hpp"

PlayerWalkingState::PlayerWalkingState(EntityStateMachine& stateMachine) : WalkingState(stateMachine) 
{

}

PlayerWalkingState::~PlayerWalkingState()
{

}

void PlayerWalkingState::handle(StateComponent* stateComp, SpeedComponent* speedComp)
{
	if (speedComp->speed_.y() < 0)
	{
		PlayerJumpingState* state = new PlayerJumpingState(*stateMachine_);
		stateMachine_->changeState(*state);
		if (speedComp->speed_.x() > 0)
			stateComp->setFacingRight(true);
		else if (speedComp->speed_.x() < 0)
			stateComp->setFacingRight(false);
	}
	else if (speedComp->speed_.y() > 0)
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
	else
	{
		PlayerIdleState* state = new PlayerIdleState(*stateMachine_);
		stateMachine_->changeState(*state);
	}
}*/
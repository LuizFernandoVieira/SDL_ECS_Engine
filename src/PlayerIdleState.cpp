/*#include "../include/PlayerIdleState.hpp"
#include "../include/InputHandler.hpp"
#include "../include/PlayerWalkingState.hpp"
#include "../include/PlayerJumpingState.hpp"
#include "../include/PlayerFallingState.hpp"

PlayerIdleState::PlayerIdleState(EntityStateMachine& stateMachine) : IdleState(stateMachine) 
{

}

PlayerIdleState::~PlayerIdleState()
{

}

void PlayerIdleState::handle(StateComponent* stateComp, SpeedComponent* speedComp)
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
}*/
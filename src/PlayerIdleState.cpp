#include "../include/PlayerIdleState.hpp"
#include "../include/InputHandler.hpp"
#include "../include/PlayerWalkingState.hpp"
#include "../include/PlayerJumpingState.hpp"

#include <iostream>

PlayerIdleState::PlayerIdleState(EntityStateMachine& stateMachine) : IdleState(stateMachine) 
{

}

PlayerIdleState::~PlayerIdleState()
{

}

void PlayerIdleState::handle(StateComponent* stateComp, SpeedComponent* speedComp)
{
/*	if(InputHandler::getInstance().keyPress(UP_ARROW_KEY)) {
		// std::cout << "UP" << std::endl;
		// PlayerJumpingState* pjs = new PlayerJumpingState(*stateMachine_);
		// stateMachine_->changeState(*pjs);
	}
	else if(
		InputHandler::getInstance().isKeyDown(RIGHT_ARROW_KEY) &&
		!InputHandler::getInstance().isKeyDown(LEFT_ARROW_KEY)
	) {
		// std::cout << "RIGHT" << std::endl;
		PlayerWalkingState* pws = new PlayerWalkingState(*stateMachine_);
		stateMachine_->changeState(*pws);
		sc->setFacingRight(true);
	}
	else if(InputHandler::getInstance().isKeyDown(LEFT_ARROW_KEY)) {
		// std::cout << "LEFT" << std::endl;
		PlayerWalkingState* pws = new PlayerWalkingState(*stateMachine_);
		stateMachine_->changeState(*pws);
		sc->setFacingRight(false);
	}*/

	if (speedComp->speed_.y() > 0)
	{
		// stateMachine_->changeState(new PlayerJumpingState(*stateMachine_));
		// if (speedComp->speed_.x() > 0)
		// 	stateComp->setFacingRight(true)
		// else if (speedComp->speed_.x() < 0)
		// 	stateComp->setFacingRight(false);
	}
	else if (speedComp->speed_.y() < 0)
	{
		// stateMachine_->changeState(new PlayerFallingState(*stateMachine_));
		// if (speedComp->speed_.x() > 0)
		// 	stateComp->setFacingRight(true)
		// else if (speedComp->speed_.x() < 0)
		// 	stateComp->setFacingRight(false);
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
}
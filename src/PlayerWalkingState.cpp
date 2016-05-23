#include "../include/PlayerWalkingState.hpp"
#include "../include/InputHandler.hpp"
#include "../include/PlayerIdleState.hpp"

#include <iostream>

PlayerWalkingState::PlayerWalkingState(EntityStateMachine& stateMachine) : WalkingState(stateMachine) 
{

}

PlayerWalkingState::~PlayerWalkingState()
{

}

void PlayerWalkingState::handle(StateComponent* stateComp, SpeedComponent* speedComp)
{
/*	if(
		InputHandler::getInstance().isKeyDown(RIGHT_ARROW_KEY) && 
		InputHandler::getInstance().isKeyDown(LEFT_ARROW_KEY)
	) {
		// std::cout << "RIGHTLEFT WALKING" << std::endl;
		PlayerIdleState* pis = new PlayerIdleState(*stateMachine_);
		stateMachine_->changeState(*pis);
	}
	else if(InputHandler::getInstance().keyPress(UP_ARROW_KEY)) {
		// std::cout << "UP WALKING" << std::endl;
		// PlayerJumpingState* pjs = new PlayerJumpingState(*stateMachine_);
		// stateMachine_->changeState(*pjs);
	}
	else if(InputHandler::getInstance().isKeyDown(RIGHT_ARROW_KEY)) {
		// std::cout << "RIGHT WALKING" << std::endl;
		sc->setFacingRight(true);
	}
	else if(InputHandler::getInstance().keyPress(DOWN_ARROW_KEY)) {
		// std::cout << "DOWN WALKING" << std::endl;
	}
	else if(InputHandler::getInstance().isKeyDown(LEFT_ARROW_KEY)) {
		// std::cout << "LEFT WALKING" << std::endl;
		sc->setFacingRight(false);
	}
	else {
		// std::cout << "ELSE WALKING" << std::endl;
		PlayerIdleState* pis = new PlayerIdleState(*stateMachine_);
		stateMachine_->changeState(*pis);
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
}
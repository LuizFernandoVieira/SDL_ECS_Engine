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

void PlayerWalkingState::handle(StateComponent* sc)
{

	if(
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
	}

}
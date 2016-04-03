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

void PlayerIdleState::handle()
{

	if(InputHandler::getInstance().keyPress(UP_ARROW_KEY)) {
		std::cout << "UP" << std::endl;
		// PlayerJumpingState* pjs = new PlayerJumpingState(*stateMachine_);
		// stateMachine_->changeState(*pjs);
	}
	else if(
		InputHandler::getInstance().isKeyDown(RIGHT_ARROW_KEY) &&
		!InputHandler::getInstance().isKeyDown(LEFT_ARROW_KEY)
	) {
		std::cout << "RIGHT" << std::endl;
		PlayerWalkingState* pws = new PlayerWalkingState(*stateMachine_);
		stateMachine_->changeState(*pws);
	}
	else if(InputHandler::getInstance().keyPress(DOWN_ARROW_KEY)) {
		std::cout << "DOWN" << std::endl;
	}
	else if(InputHandler::getInstance().isKeyDown(LEFT_ARROW_KEY)) {
		std::cout << "LEFT" << std::endl;
		PlayerWalkingState* pws = new PlayerWalkingState(*stateMachine_);
		stateMachine_->changeState(*pws);
	}
}
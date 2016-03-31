#include "../include/PlayerIdleState.hpp"
#include "../include/InputHandler.hpp"
#include "../include/PlayerWalkingState.hpp"

#include <iostream>

PlayerIdleState::PlayerIdleState(EntityStateMachine& stateMachine) : EntityState(stateMachine) 
{

}

PlayerIdleState::~PlayerIdleState()
{

}

void PlayerIdleState::handle()
{

	if(InputHandler::getInstance().keyPress(UP_ARROW_KEY)) {
		std::cout << "UP" << std::endl;
	}
	if(InputHandler::getInstance().keyPress(RIGHT_ARROW_KEY)) {
		std::cout << "RIGHT" << std::endl;
		PlayerWalkingState* pws = new PlayerWalkingState(*stateMachine_);
		stateMachine_->changeState(*pws);
	}
	if(InputHandler::getInstance().keyPress(DOWN_ARROW_KEY)) {
		std::cout << "DOWN" << std::endl;
	}
	if(InputHandler::getInstance().keyPress(LEFT_ARROW_KEY)) {
		std::cout << "LEFT" << std::endl;
	}
}
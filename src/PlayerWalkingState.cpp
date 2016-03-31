#include "../include/PlayerWalkingState.hpp"
#include "../include/InputHandler.hpp"

#include <iostream>

PlayerWalkingState::PlayerWalkingState(EntityStateMachine& stateMachine) : EntityState(stateMachine) 
{

}

PlayerWalkingState::~PlayerWalkingState()
{

}

void PlayerWalkingState::handle()
{

	if(InputHandler::getInstance().keyPress(UP_ARROW_KEY)) {
		std::cout << "UP WALKING" << std::endl;
	}
	if(InputHandler::getInstance().keyPress(RIGHT_ARROW_KEY)) {
		std::cout << "RIGHT WALKING" << std::endl;
	}
	if(InputHandler::getInstance().keyPress(DOWN_ARROW_KEY)) {
		std::cout << "DOWN WALKING" << std::endl;
	}
	if(InputHandler::getInstance().keyPress(LEFT_ARROW_KEY)) {
		std::cout << "LEFT WALKING" << std::endl;
	}

}
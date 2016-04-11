#include "../include/PlayerJumpingState.hpp"
#include "../include/InputHandler.hpp"

#include <iostream>

PlayerJumpingState::PlayerJumpingState(EntityStateMachine& stateMachine) : EntityState(stateMachine) 
{

}

PlayerJumpingState::~PlayerJumpingState()
{

}

void PlayerJumpingState::handle(StateComponent* sc)
{

	if(InputHandler::getInstance().keyPress(UP_ARROW_KEY)) {
		std::cout << "UP JUMPING" << std::endl;
	}
	if(InputHandler::getInstance().keyPress(RIGHT_ARROW_KEY)) {
		std::cout << "RIGHT JUMPING" << std::endl;
	}
	if(InputHandler::getInstance().keyPress(DOWN_ARROW_KEY)) {
		std::cout << "DOWN JUMPING" << std::endl;
	}
	if(InputHandler::getInstance().keyPress(LEFT_ARROW_KEY)) {
		std::cout << "LEFT JUMPING" << std::endl;
	}

}
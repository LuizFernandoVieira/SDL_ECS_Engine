#include "../include/InputSystem.hpp"
#include "../include/InputHandler.hpp"
#include "../include/Resources.hpp"

InputSystem::InputSystem()
{

}

void InputSystem::update(
	unsigned player, 
	std::map<int, StateComponent*> stateComp,
	std::map<int, SpeedComponent*> speedComp)
{
	InputHandler& inputHandler = InputHandler::getInstance();


	if (inputHandler.isKeyDown(LEFT_ARROW_KEY) &&
		!inputHandler.isKeyDown(RIGHT_ARROW_KEY))
	{
		speedComp[player]->speed_.x(-Resources::PLAYER_WALK_SPEED);
	}
	else if (inputHandler.isKeyDown(RIGHT_ARROW_KEY) &&
		!inputHandler.isKeyDown(LEFT_ARROW_KEY))
	{
		speedComp[player]->speed_.x(Resources::PLAYER_WALK_SPEED);
	}
	else
	{
		speedComp[player]->speed_.x(0.0);
	}

	if (inputHandler.keyPress(SPACE_BAR))
	{
		// PULO
		// Checar se pode pular no estado atual
		if ( !stateComp[player]->getState()->is("JumpingState") &&
			!stateComp[player]->getState()->is("FallingState"))
			speedComp[player]->speed_.y(-Resources::PLAYER_JUMP_SPEED);
	}
}
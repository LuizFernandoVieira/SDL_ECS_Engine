#include "../include/InputSystem.hpp"
#include "../include/InputHandler.hpp"
#include "../include/Globals.hpp"

InputSystem::InputSystem()
{

}

void InputSystem::update(
	unsigned player,
	std::map<int, StateComponent*> stateComp,
	std::map<int, SpeedComponent*> speedComp)
{
	InputHandler& inputHandler = InputHandler::getInstance();


	if (
		(inputHandler.isKeyDown(LEFT_ARROW_KEY) &&
		!inputHandler.isKeyDown(RIGHT_ARROW_KEY)) ||
		(inputHandler.isGamePadDown(GAMEPAD_ARROW_LEFT) &&
		!inputHandler.isGamePadDown(GAMEPAD_ARROW_RIGHT))
	)
	{
		speedComp[player]->speed_.x(-Globals::PLAYER_WALK_SPEED);
	}
	else if (
		(inputHandler.isKeyDown(RIGHT_ARROW_KEY) &&
		!inputHandler.isKeyDown(LEFT_ARROW_KEY)) ||
		(inputHandler.isGamePadDown(GAMEPAD_ARROW_RIGHT) &&
		!inputHandler.isGamePadDown(GAMEPAD_ARROW_LEFT)))
	{
		speedComp[player]->speed_.x(Globals::PLAYER_WALK_SPEED);
	}
	else
	{
		speedComp[player]->speed_.x(0.0);
	}

	if (inputHandler.keyPress(SPACE_BAR) || inputHandler.gamePadPress(GAMEPAD_A))
	{
		// PULO
		// Checar se pode pular no estado atual
		if ( !stateComp[player]->getState()->is("JumpingState") &&
			!stateComp[player]->getState()->is("FallingState"))
			speedComp[player]->speed_.y(-Globals::PLAYER_JUMP_SPEED);
	}
}

#include "../include/InputSystem.hpp"
#include "../include/InputHandler.hpp"
#include "../include/Resources.hpp"

InputSystem::InputSystem()
{

}

void InputSystem::update(
	StateComponent* stateComp,
	SpeedComponent* speedComp)
{
	InputHandler& input = InputHandler::getInstance();

	if (stateComp->state_ != State::ZIPLINE)
	{
		if (
			(input.isKeyDown('a') &&
			!input.isKeyDown('d')) ||
			(input.isGamePadDown(GAMEPAD_ARROW_LEFT) &&
			!input.isGamePadDown(GAMEPAD_ARROW_RIGHT))
		)
		{
			// WALKING LEFT
			speedComp->speed_.x(-Resources::PLAYER_WALK_SPEED);
			stateComp->facingRight_ = false;
			if (stateComp->state_ != State::JUMPING && stateComp->state_ != State::FALLING && stateComp->state_ != State::GRAPPLE)
				stateComp->state_ = State::WALKING;
		}
		else if (
			(input.isKeyDown('d') &&
			!input.isKeyDown('a')) ||
			(input.isGamePadDown(GAMEPAD_ARROW_RIGHT) &&
			!input.isGamePadDown(GAMEPAD_ARROW_LEFT)))
		{
			// WALKING RIGHT
			speedComp->speed_.x(Resources::PLAYER_WALK_SPEED);
			stateComp->facingRight_ = true;
			if (stateComp->state_ != State::JUMPING && stateComp->state_ != State::FALLING && stateComp->state_ != State::GRAPPLE)
				stateComp->state_ = State::WALKING;
		}
		else
		{
			// BACK TO IDLE
			speedComp->speed_.x(0.0);
			if (stateComp->state_ != State::JUMPING && stateComp->state_ != State::FALLING && stateComp->state_ != State::GRAPPLE)
				stateComp->state_ = State::IDLE;
		}

		if (input.keyPress('w') || input.gamePadPress(GAMEPAD_A))
		{
			if (stateComp->state_ != State::JUMPING &&
				stateComp->state_ != State::FALLING)
			{
				// PULO
				speedComp->speed_.y(-Resources::PLAYER_JUMP_SPEED);
				stateComp->state_ = State::JUMPING;
			}
			else
			{
				stateComp->state_ = State::GRAPPLE;
			}
		}

		if (input.keyPress(SPACE_BAR))
		{
			if (stateComp->state_ == State::JUMPING ||
				stateComp->state_ == State::FALLING)
			{
				// ZIPLINE
			}
			else
			{
				// ATAQUE
			}
		}

		// GUARDA CHUVA
		// sei nem como
	}
}

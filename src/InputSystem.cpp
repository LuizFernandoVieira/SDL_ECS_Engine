#include "../include/InputSystem.hpp"
#include "../include/InputHandler.hpp"
#include "../include/Resources.hpp"
#include "../include/SpeedComponent.hpp"
#include "../include/StateComponent.hpp"
#include "../include/PhysicsComponent.hpp"
#include "../include/ColliderComponent.hpp"

InputSystem::InputSystem()
{

}

void InputSystem::update(float dt, GameState& gameState)
{
	InputHandler& input = InputHandler::getInstance();

	PlayerStateComponent* stateComp = (PlayerStateComponent*)gameState.mapState_[gameState.player_];
	SpeedComponent* speedComp = gameState.mapSpeed_[gameState.player_];
	PhysicsComponent* physicsComp = gameState.mapPhysics_[gameState.player_];
	ColliderComponent* colComp = gameState.mapCollider_[gameState.player_];

	physicsComp->gravityScale_ = 1.0;
	stateComp->umbrellaDirection_ = UmbrellaDirection::DOWN;
	stateComp->umbrellaState_ = UmbrellaState::CLOSED;

	if (stateComp->state_ != State::DYING && stateComp->state_ != State::DEAD)
	{
		if (stateComp->state_ != State::ZIPLINE && stateComp->state_ != State::ATTACKING)
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
		}

		if ( (input.keyPress('w') || input.gamePadPress(GAMEPAD_A)) &&
			 stateComp->state_ != State::ATTACKING &&
			 stateComp->state_ != State::GRAPPLE )
		{
			if (stateComp->state_ != State::JUMPING &&
				stateComp->state_ != State::FALLING)
			{
				// PULO
				speedComp->speed_.y(-Resources::PLAYER_JUMP_SPEED);
				stateComp->state_ = State::JUMPING;
				stateComp->fallTime_.restart();
			}
			else
			{
				// GRAPPLE
				stateComp->state_ = State::GRAPPLE;
				colComp->hitbox_ = Rect( stateComp->facingRight_ ? 15 : 15, -25, 20, 20);
			}
		}

		// GUARDA CHUVA
		if (input.isKeyDown('i') || input.isGamePadDown(GAMEPAD_Y))
		{
			stateComp->umbrellaDirection_ = UmbrellaDirection::UP;
			stateComp->umbrellaState_ = UmbrellaState::OPEN;
		}
		else if (input.isKeyDown('k'))
		{
			stateComp->umbrellaDirection_ = UmbrellaDirection::DOWN;
			stateComp->umbrellaState_ = UmbrellaState::OPEN;
		}
		else if (input.isKeyDown('j') || input.isGamePadDown(GAMEPAD_X))
		{
			stateComp->umbrellaDirection_ = stateComp->facingRight_ ? UmbrellaDirection::BACK : UmbrellaDirection::FRONT;
			stateComp->umbrellaState_ = UmbrellaState::OPEN;
		}
		else if (input.isKeyDown('l') || input.isGamePadDown(GAMEPAD_B))
		{
			stateComp->umbrellaDirection_ = stateComp->facingRight_ ? UmbrellaDirection::FRONT : UmbrellaDirection::BACK;
			stateComp->umbrellaState_ = UmbrellaState::OPEN;
		}

		/*if (input.keyPress(SPACE_BAR))
		{
			stateComp->umbrellaState_ = stateComp->umbrellaState_ == UmbrellaState::OPEN ? UmbrellaState::CLOSED : UmbrellaState::OPEN;
		}*/

		if (input.keyPress('e') && stateComp->state_ != State::ATTACKING)
		{
			if (stateComp->state_ != State::JUMPING &&
				stateComp->state_ != State::FALLING &&
				stateComp->state_ != State::GRAPPLE &&
				stateComp->state_ != State::ZIPLINE)
			{
				// ATAQUE
				stateComp->state_ = State::ATTACKING;
				colComp->hitbox_ = Rect( stateComp->facingRight_ ? 58 : -40, 30, 52, 48);
			}
		}

		/*if (input.keyPress('0'))
		{
			stateComp->state_ = State::DEAD;
			stateComp->umbrellaState_ = UmbrellaState::OPEN;
			stateComp->umbrellaDirection_ = UmbrellaDirection::UP;

			std::cout << "State: Dead // Code:" << stateComp->state_ << std::endl;
		}*/

		if (stateComp->state_ == State::FALLING)
		{
			if (stateComp->umbrellaState_ == UmbrellaState::OPEN &&
				stateComp->umbrellaDirection_ == UmbrellaDirection::UP)
				physicsComp->gravityScale_ = 0.5;
			else
			{
				physicsComp->gravityScale_ = 1.0;
				stateComp->fallTime_.update(dt);
			}
		}
		else
		{
			stateComp->fallTime_.restart();
		}
	}
}

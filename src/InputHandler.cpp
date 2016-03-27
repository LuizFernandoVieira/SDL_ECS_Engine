#include "../include/InputHandler.hpp"
#include "../include/JumpCommand.hpp"
#include "../include/MoveCommand.hpp"
#include "../include/PlaceTileCommand.hpp"

InputHandler::InputHandler()
{
	keySpace_ = new JumpCommand();
	keyA_ = new MoveCommand(false, false, false, true);
	keyD_ = new MoveCommand(false, true, false, false);
	keyW_ = new MoveCommand(true, false, false, false);
	keyS_ = new MoveCommand(false, false, true, false);
	keyT_ = new PlaceTileCommand(1, 1);

	for (int i = 0; i < 6; i++) {
		mouseState[i] = false;
		mouseUpdate[i] = 0;
	}

	for (int i = 0; i < 416; i++) {
		keyState[i] = false;
		keyUpdate[i] = 0;
	}

	quit = false;
	updateCounter = 0;
	mouseX = 0;
	mouseY = 0;
}

std::vector<Command*> InputHandler::handleInput()
{
	SDL_Event event;

	updateCounter++;
	quit = false;

	SDL_GetMouseState(&mouseX, &mouseY);

	std::vector<Command*> commands;

	while(SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT)
		{
			quit = true;
		}	

		if(event.type == SDL_KEYDOWN)
		{
			if(event.key.keysym.sym == UP_ARROW_KEY)
			{
				commands.emplace_back(keyW_);
			}
			if(event.key.keysym.sym == RIGHT_ARROW_KEY)
			{
				commands.emplace_back(keyD_);
			}
			if(event.key.keysym.sym == DOWN_ARROW_KEY)
			{
				commands.emplace_back(keyS_);
			}
			if(event.key.keysym.sym == LEFT_ARROW_KEY)
			{
				commands.emplace_back(keyA_);
			}

			if(event.key.keysym.sym == SPACE_BAR)
			{
				commands.emplace_back(keySpace_);
			}

			if(event.key.keysym.sym == SDLK_t)
			{
				keyT_ = new PlaceTileCommand((int)mouseX/32, (int)mouseY/32);
				commands.emplace_back(keyT_);
			}
		}

		if(event.type == SDL_CONTROLLERBUTTONDOWN)
		{
			if(event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
			{
				commands.emplace_back(keySpace_);
			}
		}

		if (event.type == SDL_KEYDOWN && !event.key.repeat)
		{
			if (event.key.keysym.sym < 0x40000000)
			{
				keyState[event.key.keysym.sym] = true;
				keyUpdate[event.key.keysym.sym] = updateCounter;
			}
			else
			{
				keyState[event.key.keysym.sym - 0x3FFFFF81] = true;
				keyUpdate[event.key.keysym.sym - 0x3FFFFF81] = updateCounter;
			}
		}

		if (event.type == SDL_KEYUP && !event.key.repeat)
		{
			if (event.key.keysym.sym < 0x40000000)
			{
				keyState[event.key.keysym.sym] = false;
				keyUpdate[event.key.keysym.sym] = updateCounter;
			}
			else
			{
				keyState[event.key.keysym.sym - 0x3FFFFF81] = false;
				keyUpdate[event.key.keysym.sym - 0x3FFFFF81] = updateCounter;
			}
		}
	}

	return commands;
}

bool InputHandler::keyPress(int key)
{
	int i = key;
	if (key >= 0x40000000) {
		i -= 0x3FFFFF81;
	}

	if ( keyState[i] && keyUpdate[i] == updateCounter ) {
		return true;
	} else {
		return false;
	}
}

bool InputHandler::keyRelease(int key)
{
	int i = key;
	if (key >= 0x40000000) {
		i -= 0x3FFFFF81;
	}

	if ( !keyState[i] && keyUpdate[i] == updateCounter ) {
		return true;
	} else {
		return false;
	}
}

bool InputHandler::isKeyDown(int key)
{
	int i = key;
	if (key >= 0x40000000) {
		i -= 0x3FFFFF81;
	}

	if (keyState[i]) {
		return true;
	} else {
		return false;
	}
}

bool InputHandler::mousePress(int button)
{
	if ( mouseState[button] && mouseUpdate[button] == updateCounter ) {
		return true;
	} else {
		return false;
	}
}

bool InputHandler::mouseRelease(int button)
{
	if ( !mouseState[button] && mouseUpdate[button] == updateCounter ) {
		return true;
	} else {
		return false;
	}
}

bool InputHandler::isMouseDown(int button)
{
	if (mouseState[button]) {
		return true;
	} else {
		return false;
	}
}

int InputHandler::getMouseX()
{
	return mouseX;
}

int InputHandler::getMouseY()
{
	return mouseY;
}

bool InputHandler::quitRequested()
{
	return quit;
}
#include "../include/InputHandler.hpp"
#include "../include/Resources.hpp"

InputHandler::InputHandler() : inputText()
{
	for (int i = 0; i < 6; i++) {
		mouseState[i] = false;
		mouseUpdate[i] = 0;
	}

	for (int i = 0; i < 416; i++) {
		keyState[i] = false;
		keyUpdate[i] = 0;
	}

	for (int i=0; i < 16; i++) {
		gamePadState[i] = false;
		gamePadUpdate[i] = 0;
	}

	quit = false;
	updateCounter = 0;
	mouseX = 0;
	mouseY = 0;
	screenResized = false;
}

InputHandler& InputHandler::getInstance()
{
	static InputHandler instance;
	return instance;
}

void InputHandler::update()
{
	SDL_Event event;

	updateCounter++;
	quit = false;
	screenResized = false;
	inputText.erase();

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			quit = true;
		}

		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			mouseState[event.button.button] = true;
			mouseUpdate[event.button.button] = updateCounter;
		}

		else if (event.type == SDL_MOUSEBUTTONUP)
		{
			mouseState[event.button.button] = false;
			mouseUpdate[event.button.button] = updateCounter;
		}

		else if (event.type == SDL_KEYDOWN && !event.key.repeat)
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

		else if (event.type == SDL_KEYUP && !event.key.repeat)
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

		else if (event.type == SDL_TEXTINPUT)
		{
			inputText += event.text.text;
		}

		else if (event.type == SDL_WINDOWEVENT)
		{
			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				Resources::WINDOW_WIDTH = event.window.data1;
				Resources::WINDOW_HEIGHT = event.window.data2;
				screenResized = true;
			}
		}

		// ANALOGICO (LA RA)
		else if (event.type == SDL_JOYAXISMOTION )
		{
			if( event.jaxis.which == 0 )
			{
				//X axis motion
				if( event.jaxis.axis == 0 )
				{
					if( event.jaxis.value < -JOYSTICK_DEAD_ZONE )
					{
						std::cout << "arrow left" << std::endl;
					}
					else if( event.jaxis.value > JOYSTICK_DEAD_ZONE )
					{
						std::cout << "arrow right" << std::endl;
					}
				}
				//Y axis motion
				if( event.jaxis.axis == 1 )
				{
					if( event.jaxis.value < -JOYSTICK_DEAD_ZONE )
					{
						std::cout << "arrow up" << std::endl;
					}
					else if( event.jaxis.value > JOYSTICK_DEAD_ZONE )
					{
						std::cout << "arrow down" << std::endl;
					}
				}
			}
		}

		// BUTTON EVENTS (LB RB ARROWS YXBA)
		else if (event.type == SDL_JOYBUTTONDOWN )
		{
				gamePadState[event.jbutton.button] = true;
				gamePadUpdate[event.jbutton.button] = updateCounter;
		}

		else if (event.type == SDL_JOYBUTTONUP )
		{
			gamePadState[event.jbutton.button] = false;
			gamePadUpdate[event.jbutton.button] = updateCounter;
		}

		// if (event.type == SDL_JOYBUTTONUP )
		// {
		// 	std::cout << "SDL_JOYBUTTONUP" << std::endl;
		// }

		// if (event.type == SDL_JOYBALLMOTION)
		// {
		// 	std::cout << "SDL_JOYBALLMOTION" << std::endl;
		// }
		//
		// if (event.type == SDL_JOYHATMOTION)
		// {
		// 	std::cout << "SDL_JOYHATMOTION" << std::endl;
		// }
	}
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

bool InputHandler::gamePadPress(int button)
{
	if ( gamePadState[button] && gamePadUpdate[button] == updateCounter ) {
		return true;
	} else {
		return false;
	}
}

bool InputHandler::gamePadRelease(int button)
{
	if ( !gamePadState[button] && gamePadUpdate[button] == updateCounter ) {
		return true;
	} else {
		return false;
	}
}

bool InputHandler::isGamePadDown(int button)
{
	if (gamePadState[button]) {
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

Vec2 InputHandler::getMouse()
{
	return Vec2(mouseX, mouseY);
}

bool InputHandler::quitRequested()
{
	return quit;
}

bool InputHandler::getScreenResized()
{
	return screenResized;
}

bool InputHandler::textInput()
{
	return !inputText.empty();
}

std::string InputHandler::getText()
{
	return inputText;
}
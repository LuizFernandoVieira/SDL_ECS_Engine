#include "../include/InputHandler.hpp"
#include "../include/Resources.hpp"

InputHandler::InputHandler()
{
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

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			quit = true;
		}

		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			mouseState[event.button.button] = true;
			mouseUpdate[event.button.button] = updateCounter;
		}

		if (event.type == SDL_MOUSEBUTTONUP)
		{
			mouseState[event.button.button] = false;
			mouseUpdate[event.button.button] = updateCounter;
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

		if (event.type == SDL_WINDOWEVENT)
		{
			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				// screenWidth = event.window.data1,
				// screenHeight = event.window.data2;
				Resources::WINDOW_WIDTH = event.window.data1;
				Resources::WINDOW_HEIGHT = event.window.data2;
				screenResized = true;
			}
		}

		// ANALOGICO (LA RA)
		if (event.type == SDL_JOYAXISMOTION )
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
		if (event.type == SDL_JOYBUTTONDOWN )
		{
			if (event.jbutton.button == 0) // A
			{
				std::cout << "A" << std::endl;
			}
			if (event.jbutton.button == 1) // B
			{
				std::cout << "B" << std::endl;
			}
			if (event.jbutton.button == 2) // X
			{
				std::cout << "X" << std::endl;
			}
			if (event.jbutton.button == 3) // Y
			{
				std::cout << "Y" << std::endl;
			}
			if (event.jbutton.button == 4) // LB
			{
				std::cout << "LB" << std::endl;
			}
			if (event.jbutton.button == 5) // RB
			{
				std::cout << "RB" << std::endl;
			}
			if (event.jbutton.button == 11) // A UP
			{
				std::cout << "ARROW UP" << std::endl;
			}
			if (event.jbutton.button == 12) // A DOWN
			{
				std::cout << "ARROW DOWN" << std::endl;
			}
			if (event.jbutton.button == 13) // A LEFT
			{
				std::cout << "ARROW LEFT" << std::endl;
			}
			if (event.jbutton.button == 14) // A RIGHT
			{
				std::cout << "ARROW RIGHT" << std::endl;
			}
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

// int InputHandler::getScreenWidth()
// {
// 	return screenWidth;
// }

// int InputHandler::getScreenHeight()
// {
// 	return screenHeight;
// }

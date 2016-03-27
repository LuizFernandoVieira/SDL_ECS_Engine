#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#ifdef __APPLE__
	#include <SDL2/SDL.h>
#else
	#include "SDL.h"
#endif

#include <iostream>
#include <vector>

#include "Command.hpp"

#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON SDL_BUTTON_RIGHT
#define SPACE_BAR SDLK_SPACE

class InputHandler
{
public:
	InputHandler();
	std::vector<Command*> handleInput();
	bool keyPress(int key);
	bool keyRelease(int key);
	bool isKeyDown(int key);
	bool mousePress(int button);
	bool mouseRelease(int button);
	bool isMouseDown(int button);
	int getMouseX();
	int getMouseY();
	bool quitRequested();
private:
	Command* keySpace_;
	Command* keyW_;
	Command* keyD_;
	Command* keyS_;
	Command* keyA_;
	Command* keyT_;
	bool mouseState[6];
	int mouseUpdate[6];
	bool keyState[416];
	int keyUpdate[416];
	bool quit;
	int updateCounter;
	int mouseX;
	int mouseY;
};

#endif
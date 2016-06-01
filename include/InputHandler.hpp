#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#ifdef __APPLE__
	#include <SDL2/SDL.h>
#else
	#include "SDL.h"
#endif

#include <iostream>
#include <vector>

#include "Vec2.hpp"

#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON SDL_BUTTON_RIGHT
#define SPACE_BAR SDLK_SPACE
#define GAMEPAD_A 0
#define GAMEPAD_B 1
#define GAMEPAD_X 2
#define GAMEPAD_Y 3
#define GAMEPAD_LB 4
#define GAMEPAD_RB 5
#define GAMEPAD_ARROW_UP 11
#define GAMEPAD_ARROW_DOWN 12
#define GAMEPAD_ARROW_LEFT 13
#define GAMEPAD_ARROW_RIGHT 14

class InputHandler
{
public:
	static InputHandler& getInstance();
	void update();
	bool keyPress(int key);
	bool keyRelease(int key);
	bool isKeyDown(int key);
	bool mousePress(int button);
	bool mouseRelease(int button);
	bool isMouseDown(int button);
	bool gamePadPress(int button);
	bool gamePadRelease(int button);
	bool isGamePadDown(int button);
	int getMouseX();
	int getMouseY();
	Vec2 getMouse();
	bool getScreenResized();
	// int getScreenWidth();
	// int getScreenHeight();
	bool quitRequested();
private:
	InputHandler();
	~InputHandler(){}
	bool mouseState[6];
	int mouseUpdate[6];
	bool keyState[416];
	int keyUpdate[416];
	bool gamePadState[15];
	int gamePadUpdate[15];
	bool quit;
	int updateCounter;
	int mouseX;
	int mouseY;
	const int JOYSTICK_DEAD_ZONE = 8000;
	// int screenWidth;
	// int screenHeight;
	bool screenResized;
};

#endif

#ifndef GAME_HPP
#define GAME_HPP

#ifdef __APPLE__
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_gamecontroller.h>
	#include <SDL2/SDL_mixer.h>
#else
	#include "SDL.h"
	#include "SDL_gamecontroller.h"
	#include "SDL_mixer.h"
#endif

#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "StateMachine.hpp"

class Game
{
public:
	Game(int width, int height);
	~Game();
	static Game& getInstance();
	void run();
	SDL_Renderer* getRenderer();
private:
	static Game* instance_;
	void initSDL();
	void initWindow(int width, int height);
	void initRenderer();
	void initControllers();
	void initAudio();
	void calculateDeltaTime();
	SDL_Window* window_;
	SDL_Renderer* renderer_;
	SDL_GameController* controller_;
	StateMachine* stateMachine_;
	float dt_;
	int frameStart_;
};

#endif
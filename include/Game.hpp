#ifndef GAME_HPP
#define GAME_HPP

#ifdef __APPLE__
	#include <SDL2/SDL.h>
	#include <SDL2_image/SDL_image.h>
	#include <SDL2/SDL_gamecontroller.h>
	#include <SDL2_mixer/SDL_mixer.h>
	#include <SDL2_ttf/SDL_ttf.h>
#else
	#include "SDL.h"
	#include "SDL_image.h"
	#include "SDL_gamecontroller.h"
	#include "SDL_mixer.h"
	#include "SDL_ttf.h"
#endif

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stack>
#include <memory>

#include "IState.hpp"

class Game
{
public:
	// Não me pergunte.... só sei q é por causa dos unique_ptr
	explicit Game(const char* name, int width, int height);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	~Game();

	static Game& getInstance();
	SDL_Renderer* getRenderer();

	void run();

	void push(IState* state);
	IState& getCurrentState();

private:
	static Game* instance_;

	void initSDL();
	void initWindow(const char* name, int width, int height);
	void initRenderer();
	void initControllers();
	void initAudio();
	void initTTF();

	void calculateDeltaTime();

	SDL_Window* window_;
	SDL_Renderer* renderer_;
	SDL_GameController* controller_;

	float dt_;
	int frameStart_;

	std::stack<std::unique_ptr<IState>> stateStack_;
	IState* storedState_;
};

#endif

#include "../include/Game.hpp"

Game* Game::instance_;

Game::Game(int width, int height)
{
	dt_ = 0.0;
	frameStart_ = 0;

	if (instance_ != NULL) {
		std::cerr << "Ja existe uma instancia do jogo executando" << std::endl;
		exit(1);
	}
	instance_ = this;

	initSDL();
	initWindow(width, height);
	initRenderer();
	initControllers();

	stateMachine_ = new StateMachine();
	stateMachine_->create();
}

Game::~Game()
{
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}

Game& Game::getInstance()
{
	return *instance_;
}

void Game::run()
{
	while(!stateMachine_->getState()->quitRequested())
	{
		calculateDeltaTime();
		stateMachine_->update(dt_);
		stateMachine_->render();
		SDL_RenderPresent(renderer_);
		if ( (float)(SDL_GetTicks() - frameStart_) < 1000.0 / 60.0 )
		{
			SDL_Delay( (1000.0/60.0) - (frameStart_ - SDL_GetTicks()) );
		}
	}
}

void Game::initSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << 
			std::endl;
		exit(1);
	}
}

void Game::initWindow(int width, int height)
{
	SDL_DisplayMode mode;
	if (SDL_GetDesktopDisplayMode(0, &mode) != 0) {
		std::cerr << "Erro na criacao da janela do jogo" << 
			std::endl << SDL_GetError() << std::endl;
		exit(1);
	}

	window_ = SDL_CreateWindow 
	( 	
		"title", 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		/*mode.w*/width, /*mode.h*/height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE 
	);
	if (window_ == NULL) {
		std::cerr << "Erro na criacao da janela do jogo" << 
			std::endl << SDL_GetError() << std::endl;
		exit(1);
	}

	// if (SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN) != 0) {
	// 	std::cerr << "Erro na criacao da janela do jogo" << 
	// 		std::endl << SDL_GetError() << std::endl;
	// 	exit(1);
	// }
	// SDL_MaximizeWindow(window_);
}

void Game::initRenderer()
{
	renderer_ = SDL_CreateRenderer 
	( 
		window_, -1, 
		SDL_RENDERER_ACCELERATED 
	);
	if (renderer_ == NULL) {
		std::cerr << "Erro na criacao do renderizador do jogo" << 
			std::endl << SDL_GetError() << std::endl;
		exit(1);
	}	
}

void Game::initControllers()
{
	for(int i=0; i<SDL_NumJoysticks(); i++)
	{
		if(SDL_IsGameController(i)) {
			printf("Index \'%i\' is a compatible controller, named \'%s\'\n", i, SDL_GameControllerNameForIndex(i));
			controller_ = SDL_GameControllerOpen(i);
			printf("Controller %i is mapped as \"%s\".\n", i, SDL_GameControllerMapping(controller_));
		} else {
			printf("Index \'%i\' is not a compatible controller.", i);
		}
	}
}

void Game::calculateDeltaTime()
{
	dt_ = (float)(SDL_GetTicks() - frameStart_) / 1000.0;
	frameStart_ = SDL_GetTicks();
}

SDL_Renderer* Game::getRenderer()
{
	return renderer_;
}
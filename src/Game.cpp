#include "../include/Game.hpp"
#include "../include/Resources.hpp"

Game* Game::instance_;

Game::Game(const char* name, int width, int height) : stateStack_()
{
	dt_ = 0.0;
	frameStart_ = 0;

	if (instance_ != NULL) {
		std::cerr << "Ja existe uma instancia do jogo executando" << std::endl;
		exit(1);
	}
	instance_ = this;

	initSDL();
	initWindow(name, width, height);
	initRenderer();
	initControllers();
	initAudio();
	initTTF();

	storedState_ = NULL;
}

Game::~Game()
{
	if (storedState_ != NULL)
		delete storedState_;

	TTF_Quit();
	Mix_Quit();
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();

	instance_ = NULL;
}

Game& Game::getInstance()
{
	return *instance_;
}

void Game::push(IState* state)
{
	storedState_ = state;
}

IState& Game::getCurrentState()
{
	return *stateStack_.top();
}

SDL_Renderer* Game::getRenderer()
{
	return renderer_;
}

float Game::getDeltaTime()
{
	return dt_;
}

void Game::calculateDeltaTime()
{
	int lastFrameStart = frameStart_;
	frameStart_ = SDL_GetTicks();
	dt_ = (float)(frameStart_ - lastFrameStart) / 1000.0;
	if (dt_ > 0.1) dt_ = 0.1;
}


void Game::run()
{
	if (storedState_ != NULL)
	{
		stateStack_.emplace(storedState_);
		storedState_ = NULL;
	}

	while(!stateStack_.empty() && !stateStack_.top()->quitRequested())
	{
		calculateDeltaTime();

		stateStack_.top()->update(dt_);
		stateStack_.top()->render();
		SDL_RenderPresent(renderer_);

		if (stateStack_.top()->popRequested())
		{
			stateStack_.pop();
			// Destruir todos os recursos carregados
			Resources::ClearImages();
			Resources::ClearSounds();
			Resources::ClearFonts();
			stateStack_.top()->resume();
		}
		if (storedState_ != NULL)
		{
			stateStack_.top()->pause();
			stateStack_.emplace(storedState_);
			storedState_ = NULL;
		}
		
		float frameEnd = (float)SDL_GetTicks();

		if((frameEnd-frameStart_) < (float)(1000.f / 60.0))
			while(frameEnd - frameStart_ <= (1000.f / 60.0))
				frameEnd = (float)SDL_GetTicks();
	}

	while (!stateStack_.empty())
		stateStack_.pop();

	Resources::ClearImages();
	Resources::ClearSounds();
	Resources::ClearFonts();
}

void Game::initSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << 
			std::endl;
		exit(1);
	}
}

void Game::initWindow(const char* name, int width, int height)
{
	SDL_DisplayMode mode;
	if (SDL_GetDesktopDisplayMode(0, &mode) != 0) {
		std::cerr << "Erro na criacao da janela do jogo" << 
			std::endl << SDL_GetError() << std::endl;
		exit(1);
	}

	window_ = SDL_CreateWindow 
	( 	
		name, 
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

void Game::initAudio(){
	//Initialize Audio
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)){
		printf( "SDL_mixer could not Open Audio! SDL_mixer Error: %s\n", Mix_GetError() );
		//system("PAUSE");
		exit(1);		
	}

	/*	Como nossa música será simulada por áudio, não há sentido na inicialização

	//Initialize Music
	if (Mix_Init(MIX_INIT_OGG) != MIX_INIT_OGG){
		printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
		system("PAUSE");
		exit(ERROR_INIT);	
	}
	*/
}

void Game::initTTF()
{
	if ( TTF_Init() != 0 )
	{
		std::cerr << "Erro na inicializacao da SDL_ttf: " << TTF_GetError() << std::endl;
		exit(1);
	}
}

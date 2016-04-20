#include "../include/LevelEditorState.hpp"
#include "../include/InputHandler.hpp"

#ifdef __APPLE__
	#include <SDL2/SDL.h>
#else
	#include "SDL.h"
#endif

LevelEditorState::LevelEditorState()
{
}

LevelEditorState::~LevelEditorState()
{
	delete leftPanel_;
}

void LevelEditorState::create(StateMachine& stateMachine)
{
	stateMachine_ = &stateMachine;
	quit = false;

	// SDL_DisplayMode mode;
	// if (SDL_GetDesktopDisplayMode(0, &mode) != 0) {
	// 	std::cerr << "Erro na criacao da janela do jogo" << 
	// 		std::endl << SDL_GetError() << std::endl;
	// 	exit(1);
	// }

	leftPanel_ = new NavigationPanel(/*mode.w*/1024, /*mode.h*/600);
}

void LevelEditorState::update(float dt)
{
	InputHandler::getInstance().update();

	leftPanel_->update();

	if(InputHandler::getInstance().quitRequested()) {
		setQuit(true);
	}
}

void LevelEditorState::render()
{
	leftPanel_->render();
}

void LevelEditorState::handle(StateEventEnum& event)
{

}
#include "../include/LevelEditorState.hpp"
#include "../include/InputHandler.hpp"

#ifdef __APPLE__
	#include <SDL2/SDL.h>
#else
	#include "SDL.h"
#endif

LevelEditorState::LevelEditorState() : 
mainPanel_(
	Rect(0,0,Globals::WINDOW_WIDTH, Globals::WINDOW_HEIGHT),
	"../img/bgTilePanel.png"
)
{
	
}

LevelEditorState::~LevelEditorState()
{
}

void LevelEditorState::create(StateMachine& stateMachine)
{
	stateMachine_ = &stateMachine;
	quit = false;
	initGUI();
}

void LevelEditorState::initGUI()
{
	Panel leftPanel_ = Panel();
	mainPanel.add(leftPanel_);
}

void LevelEditorState::update(float dt)
{
	InputHandler::getInstance().update();

	leftPanel_->update();

	if (InputHandler::getInstance().getScreenResized())
	{

	}

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
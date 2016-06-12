#include "../include/MainMenuState.hpp"
#include "../include/Game.hpp"
#include "../include/Resources.hpp"
#include "../include/InputHandler.hpp"
#include "../include/GameState.hpp"
#include "../include/EditorSelectState.hpp"

MainMenuState::MainMenuState() : 
	info_("../font/arial.ttf", 16, Text::TextStyle::BLENDED, "PRESS SPACE BAR TO START GAME, E TO START THE LEVEL EDITOR", Colors::black),
	bg_("../img/bg.png")
{
	info_.setPos(Resources::WINDOW_WIDTH / 2, Resources::WINDOW_HEIGHT / 2);
}

MainMenuState::~MainMenuState()
{

}


void MainMenuState::update(float dt)
{
	InputHandler& input = InputHandler::getInstance();
	input.update();

	if (input.keyPress('e'))
	{
		Game::getInstance().push(new EditorSelectState());
	}
	else if (input.keyPress(SPACE_BAR))
	{
		Game::getInstance().push(new GameState());
	}

	if (input.quitRequested()) {
		quit_ = true;
	}
}


void MainMenuState::render()
{
	bg_.render(0,0);
	info_.render();
}



void MainMenuState::pause()
{

}

void MainMenuState::resume()
{

}
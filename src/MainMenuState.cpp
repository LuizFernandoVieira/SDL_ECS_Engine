#include "../include/MainMenuState.hpp"
#include "../include/Game.hpp"
#include "../include/Resources.hpp"
#include "../include/InputHandler.hpp"
#include "../include/GameState.hpp"
#include "../include/EditorSelectState.hpp"

MainMenuState::MainMenuState() :
	bg_("../img/loading.png"),
	btnPlay_("../img/interface/editor/btn.png"),
	btnPlayPos_(300, 250, 200, 100),
	btnPlayText_("../font/arial.ttf", 16, Text::TextStyle::BLENDED, "Jogar", Colors::purple),
	btnMapEditor_("../img/interface/editor/btn.png"),
	btnMapEditorPos_(600, 250, 200, 100),
	btnMapEditorText_("../font/arial.ttf", 16, Text::TextStyle::BLENDED, "Editar", Colors::purple)
{
	btnPlayText_.setPos(400, 300);
	btnMapEditorText_.setPos(700, 300);

	btnPlay_.setScaleX(200 / btnPlay_.getWidth());
	btnPlay_.setScaleY(100 / btnPlay_.getHeight());
	btnMapEditor_.setScaleX(200 / btnMapEditor_.getWidth());
	btnMapEditor_.setScaleY(100 / btnMapEditor_.getHeight());
}

MainMenuState::~MainMenuState()
{

}

void MainMenuState::update(float dt)
{
	InputHandler& input = InputHandler::getInstance();
	input.update();

	if (input.mousePress(LEFT_MOUSE_BUTTON))
	{
		if (btnPlayPos_.isInside(input.getMouse()))
		{
			Game::getInstance().push(new GameState());
		}
		else if(btnMapEditorPos_.isInside(input.getMouse()))
		{
			Game::getInstance().push(new EditorSelectState());
		}
	}

	if (input.keyPress(SPACE_BAR))
		Game::getInstance().push(new GameState());


	if (input.quitRequested() || input.keyPress(ESCAPE_KEY))
	{
		quit_ = true;
	}
}

void MainMenuState::render()
{
	bg_.render(0,0);

	btnPlay_.render(btnPlayPos_.x(), btnPlayPos_.y());
	btnPlayText_.render();

	btnMapEditor_.render(btnMapEditorPos_.x(), btnMapEditorPos_.y());
	btnMapEditorText_.render();
}

void MainMenuState::pause()
{

}

void MainMenuState::resume()
{

}

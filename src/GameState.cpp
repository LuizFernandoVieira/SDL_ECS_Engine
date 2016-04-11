#include "../include/GameState.hpp"

GameState::GameState()
{

}

GameState::~GameState()
{
	delete firstLevel_;
}

void GameState::create(StateMachine& stateMachine)
{
	stateMachine_ = &stateMachine;
	quit = false;
	firstLevel_	= new FirstLevel(*this);
	firstLevel_->create();
}

void GameState::update(float dt)
{
	firstLevel_->update(dt);
}

void GameState::render()
{
	firstLevel_->render();
}

void GameState::handle(StateEventEnum& event)
{

}
#include "../include/GameState.hpp"

void GameState::create(StateMachine& stateMachine)
{
	setStateMachine(stateMachine);
	firstLevel_	= new FirstLevelEditor(*this);
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
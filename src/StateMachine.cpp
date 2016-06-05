#include "../include/StateMachine.hpp"
#include "../include/GameState.hpp"
#include "../include/LevelEditorState.hpp"

StateMachine::StateMachine()
{

}

StateMachine::~StateMachine()
{
	delete state_;
}

void StateMachine::create()
{
	 state_ = new GameState();
	//state_ = new LevelEditorState();
	state_->create(*this);
}

void StateMachine::update(float dt)
{
	state_->update(dt);
}

void StateMachine::render()
{
	state_->render();
}

void StateMachine::changeState(State& state)
{
	state_ = &state;
	state_->create(*this);
}

void StateMachine::handle(StateEventEnum& event)
{
	state_->handle(event);
}

State* StateMachine::getState()
{
	return state_;
}

void StateMachine::setState(State& state)
{
	state_ = &state;
}

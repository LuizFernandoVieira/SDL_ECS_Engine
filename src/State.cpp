#include "../include/State.hpp"

void State::create(StateMachine& stateMachine)
{
	stateMachine_ = &stateMachine;
	quit = false;
}

void State::update(float dt)
{
	
}

void State::render()
{
	
}

bool State::quitRequested()
{
	return quit;
}

StateMachine* State::getStateMachine()
{
	return stateMachine_;
}

void State::setStateMachine(StateMachine& stateMachine)
{
	stateMachine_ = &stateMachine;
}
#include "../include/State.hpp"

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
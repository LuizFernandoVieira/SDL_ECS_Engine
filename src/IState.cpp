#include "../include/IState.hpp"

bool IState::quitRequested()
{
	return quit;
}

StateMachine* IState::getStateMachine()
{
	return stateMachine_;
}

void IState::setStateMachine(StateMachine& stateMachine)
{
	stateMachine_ = &stateMachine;
}
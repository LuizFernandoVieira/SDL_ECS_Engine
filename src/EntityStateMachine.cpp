#include "../include/EntityStateMachine.hpp"
#include "../include/PlayerIdleState.hpp"

EntityStateMachine::EntityStateMachine()
{
	currentState_ = new PlayerIdleState(*this);
}

void EntityStateMachine::changeState(EntityState& state)
{
	delete currentState_;
	currentState_ = &state;
}

void EntityStateMachine::handle()
{
	currentState_->handle();
}

EntityState* EntityStateMachine::getCurrentState()
{ 
	return currentState_; 
}

void EntityStateMachine::setCurrentState(EntityState& state)
{ 
	currentState_ = &state; 
}
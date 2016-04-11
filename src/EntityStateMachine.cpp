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

void EntityStateMachine::handle(StateComponent* sc)
{
	currentState_->handle(sc);
}

EntityState* EntityStateMachine::getCurrentState()
{ 
	return currentState_; 
}

void EntityStateMachine::setCurrentState(EntityState& state)
{ 
	currentState_ = &state; 
}
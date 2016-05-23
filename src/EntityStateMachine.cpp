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

void EntityStateMachine::handle(StateComponent* stateComp, SpeedComponent* speedComp)
{
	currentState_->handle(stateComp, speedComp);
}

EntityState* EntityStateMachine::getCurrentState()
{ 
	return currentState_; 
}

void EntityStateMachine::setCurrentState(EntityState& state)
{ 
	currentState_ = &state; 
}
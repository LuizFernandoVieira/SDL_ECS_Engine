#include "../include/EntityStateMachine.hpp"
#include "../include/PlayerIdleState.hpp"

EntityStateMachine::EntityStateMachine(StateMachineType type) : changed_(false)
{
	switch(type)
	{
		case PLAYER:
			currentState_ = new PlayerIdleState(*this);
			break;
		case ENEMY:
			currentState_ = new PlayerIdleState(*this);
			break;
		case OBJECT:
			currentState_ = new PlayerIdleState(*this);
			break;
	}
}

void EntityStateMachine::changeState(EntityState& state)
{
	delete currentState_;
	currentState_ = &state;
	changed_ = true;
}

void EntityStateMachine::handle(StateComponent* stateComp, SpeedComponent* speedComp)
{
	changed_ = false;
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

bool EntityStateMachine::hasChanged()
{
	return changed_;
}
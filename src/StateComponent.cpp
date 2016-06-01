#include "../include/StateComponent.hpp"

StateComponent::StateComponent(StateMachineType type) : facingRight_(true)
{
	stateMachine_ = new EntityStateMachine(type);
}

EntityState* StateComponent::getState()
{
	return stateMachine_->getCurrentState();
}
#include "../include/StateComponent.hpp"

StateComponent::StateComponent() : facingRight_(true)
{
	stateMachine_ = new EntityStateMachine();
}

EntityState* StateComponent::getState()
{
	return stateMachine_->getCurrentState();
}
#include "../include/StateComponent.hpp"

StateComponent::StateComponent()
{
	stateMachine_ = new EntityStateMachine();
}
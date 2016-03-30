#ifndef ENTITYSTATE_HPP
#define ENTITYSTATE_HPP

#include "StateComponent.hpp"

class EntityStateMachine;

class EntityState
{
public:
	EntityState(EntityStateMachine& stateMachine) { stateMachine_ = &stateMachine; }
	virtual ~EntityState(){}
	virtual void handle() = 0;
protected:
	EntityStateMachine* stateMachine_;
};

#include "EntityStateMachine.hpp"

#endif
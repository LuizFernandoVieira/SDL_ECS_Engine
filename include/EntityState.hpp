#ifndef ENTITYSTATE_HPP
#define ENTITYSTATE_HPP

#include <string>

#include "StateComponent.hpp"

class EntityStateMachine;

class EntityState
{
public:
	EntityState(EntityStateMachine& stateMachine) { stateMachine_ = &stateMachine; }
	virtual ~EntityState(){}
	virtual void handle() = 0;
	// Checa tipo da classe imediatamente filha de EntityState
	virtual bool is(std::string) = 0;
protected:
	EntityStateMachine* stateMachine_;
};

#include "EntityStateMachine.hpp"

#endif
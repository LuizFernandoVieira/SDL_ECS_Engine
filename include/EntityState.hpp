#ifndef ENTITYSTATE_HPP
#define ENTITYSTATE_HPP

#include <string>

class EntityStateMachine;
class StateComponent;
class SpeedComponent;

class EntityState
{
public:
	EntityState(EntityStateMachine& stateMachine) { stateMachine_ = &stateMachine; }
	virtual ~EntityState(){}
	virtual void handle(StateComponent* stateComp, SpeedComponent* speedComp) = 0;
	// Checa tipo da classe imediatamente filha de EntityState
	virtual bool is(std::string) = 0;
protected:
	EntityStateMachine* stateMachine_;
};

#include "EntityStateMachine.hpp"
#include "StateComponent.hpp"
#include "SpeedComponent.hpp"

#endif
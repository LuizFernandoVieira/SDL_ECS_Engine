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
	virtual bool is(std::string name) { return name == name_ ? true : false; }
	virtual std::string getName() { return name_; }

protected:
	EntityState(EntityStateMachine& stateMachine, std::string name) : name_(name) { stateMachine_ = &stateMachine; }
	EntityStateMachine* stateMachine_;
	std::string name_;
};

#include "EntityStateMachine.hpp"
#include "StateComponent.hpp"
#include "SpeedComponent.hpp"

#endif
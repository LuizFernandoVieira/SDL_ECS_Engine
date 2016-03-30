#ifndef STATECOMPONENT_HPP
#define STATECOMPONENT_HPP

#include "Component.hpp"

class EntityStateMachine;

class StateComponent : public Component
{
public:
	StateComponent() {}
	~StateComponent() {}
	EntityStateMachine* getStateMachine() { return stateMachine_; }
	void setStateMachine(EntityStateMachine& stateMachine) { stateMachine_ = &stateMachine; }
private:
	EntityStateMachine* stateMachine_;
};

#include "EntityStateMachine.hpp"

#endif
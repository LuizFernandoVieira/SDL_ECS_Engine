#ifndef STATECOMPONENT_HPP
#define STATECOMPONENT_HPP

#include "Component.hpp"

class EntityStateMachine;
class EntityState;

class StateComponent : public Component
{
public:
	StateComponent();
	~StateComponent() {}

	EntityStateMachine* getStateMachine() { return stateMachine_; }
	void setStateMachine(EntityStateMachine& stateMachine) { stateMachine_ = &stateMachine; }
	EntityState* getState();

	bool isFacingRight() { return facingRight_; }
	void setFacingRight(bool facingRight) { facingRight_ = facingRight; }

private:
	EntityStateMachine* stateMachine_;
	bool facingRight_;
};

#include "EntityStateMachine.hpp"
#include "EntityState.hpp"

#endif
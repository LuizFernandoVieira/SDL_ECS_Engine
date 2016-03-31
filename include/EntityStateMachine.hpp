#ifndef ENTITYSTATEMACHINE_HPP
#define ENTITYSTATEMACHINE_HPP

class EntityState;

class EntityStateMachine
{
public:
	EntityStateMachine();
	void changeState(EntityState& state);
	void handle();
	EntityState* getCurrentState();
	void setCurrentState(EntityState& state);
private:
	EntityState* currentState_;
};

#include "EntityState.hpp"

#endif
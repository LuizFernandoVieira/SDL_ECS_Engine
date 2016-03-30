#ifndef ENTITYSTATEMACHINE_HPP
#define ENTITYSTATEMACHINE_HPP

#include "EntityState.hpp"

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

#endif
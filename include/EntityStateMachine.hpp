#ifndef ENTITYSTATEMACHINE_HPP
#define ENTITYSTATEMACHINE_HPP

#include "EntityState.hpp"
#include "StateComponent.hpp"
#include "SpeedComponent.hpp"

class EntityStateMachine
{
public:
	EntityStateMachine();
	void changeState(EntityState& state);
	void handle(StateComponent* stateComp, SpeedComponent* speedComp);
	EntityState* getCurrentState();
	void setCurrentState(EntityState& state);
	bool hasChanged();
private:
	EntityState* currentState_;
	bool changed_;
};


#endif
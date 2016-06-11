/*#ifndef PLAYERFALLINGSTATE_HPP
#define PLAYERFALLINGSTATE_HPP

#include "FallingState.hpp"
#include "StateComponent.hpp"

class PlayerFallingState : public FallingState
{
public:
	PlayerFallingState(EntityStateMachine& stateMachine);
	virtual ~PlayerFallingState();
	void handle(StateComponent* stateComp, SpeedComponent* speedComp);
};

#endif*/
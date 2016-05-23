#ifndef PLAYERWALKINGSTATE_HPP
#define PLAYERWALKINGSTATE_HPP

#include "WalkingState.hpp"
#include "StateComponent.hpp"
#include "SpeedComponent.hpp"

class PlayerWalkingState : public WalkingState
{
public:
	PlayerWalkingState(EntityStateMachine& stateMachine);
	virtual ~PlayerWalkingState();
	void handle(StateComponent* stateComp, SpeedComponent* speedComp);
};

#endif
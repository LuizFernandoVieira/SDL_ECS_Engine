#ifndef PLAYERWALKINGSTATE_HPP
#define PLAYERWALKINGSTATE_HPP

#include "WalkingState.hpp"
#include "StateComponent.hpp"

class PlayerWalkingState : public WalkingState
{
public:
	PlayerWalkingState(EntityStateMachine& stateMachine);
	virtual ~PlayerWalkingState();
	void handle(StateComponent* sc);
};

#endif
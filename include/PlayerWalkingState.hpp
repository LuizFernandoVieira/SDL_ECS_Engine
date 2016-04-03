#ifndef PLAYERWALKINGSTATE_HPP
#define PLAYERWALKINGSTATE_HPP

#include "WalkingState.hpp"

class PlayerWalkingState : public WalkingState
{
public:
	PlayerWalkingState(EntityStateMachine& stateMachine);
	virtual ~PlayerWalkingState();
	void handle();
};

#endif
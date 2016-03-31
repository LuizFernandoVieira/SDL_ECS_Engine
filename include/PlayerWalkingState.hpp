#ifndef PLAYERWALKINGSTATE_HPP
#define PLAYERWALKINGSTATE_HPP

#include "EntityState.hpp"

class PlayerWalkingState : public EntityState
{
public:
	PlayerWalkingState(EntityStateMachine& stateMachine);
	virtual ~PlayerWalkingState();
	void handle();
};

#endif
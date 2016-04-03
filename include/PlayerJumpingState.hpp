#ifndef PLAYERJUMPINGSTATE_HPP
#define PLAYERJUMPINGSTATE_HPP

#include "EntityState.hpp"

class PlayerJumpingState : public EntityState
{
public:
	PlayerJumpingState(EntityStateMachine& stateMachine);
	virtual ~PlayerJumpingState();
	void handle();
};

#endif
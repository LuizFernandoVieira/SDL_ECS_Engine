#ifndef PLAYERIDLESTATE_HPP
#define PLAYERIDLESTATE_HPP

#include "EntityState.hpp"

class PlayerIdleState : public EntityState
{
public:
	PlayerIdleState(EntityStateMachine& stateMachine);
	virtual ~PlayerIdleState();
	void handle();
};

#endif
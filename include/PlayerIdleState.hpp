#ifndef PLAYERIDLESTATE_HPP
#define PLAYERIDLESTATE_HPP

#include "IdleState.hpp"

class PlayerIdleState : public IdleState
{
public:
	PlayerIdleState(EntityStateMachine& stateMachine);
	virtual ~PlayerIdleState();
	void handle();
};

#endif
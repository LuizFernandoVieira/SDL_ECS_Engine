#ifndef PLAYERIDLESTATE_HPP
#define PLAYERIDLESTATE_HPP

#include "IdleState.hpp"
#include "StateComponent.hpp"

class PlayerIdleState : public IdleState
{
public:
	PlayerIdleState(EntityStateMachine& stateMachine);
	virtual ~PlayerIdleState();
	void handle(StateComponent* sc);
};

#endif
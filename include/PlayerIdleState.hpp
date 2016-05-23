#ifndef PLAYERIDLESTATE_HPP
#define PLAYERIDLESTATE_HPP

#include "IdleState.hpp"
#include "StateComponent.hpp"
#include "SpeedComponent.hpp"

class PlayerIdleState : public IdleState
{
public:
	PlayerIdleState(EntityStateMachine& stateMachine);
	virtual ~PlayerIdleState();
	void handle(StateComponent* stateComp, SpeedComponent* speedComp);
};

#endif
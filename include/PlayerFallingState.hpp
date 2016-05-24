#ifndef PLAYERFALLINGSTATE_HPP
#define PLAYERFALLINGSTATE_HPP

#include "EntityState.hpp"
#include "StateComponent.hpp"

class PlayerFallingState : public EntityState
{
public:
	PlayerFallingState(EntityStateMachine& stateMachine);
	virtual ~PlayerFallingState();
	void handle(StateComponent* stateComp, SpeedComponent* speedComp);
	
	bool is(std::string type)
	{ 
		if (type == "PlayerFallingState") 
			return true; 
		else
			return false;
	}
};

#endif
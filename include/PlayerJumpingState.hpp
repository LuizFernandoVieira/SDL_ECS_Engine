#ifndef PLAYERJUMPINGSTATE_HPP
#define PLAYERJUMPINGSTATE_HPP

#include "EntityState.hpp"
#include "StateComponent.hpp"

class PlayerJumpingState : public EntityState
{
public:
	PlayerJumpingState(EntityStateMachine& stateMachine);
	virtual ~PlayerJumpingState();
	void handle(StateComponent* sc);
	
	bool is(std::string type)
	{ 
		if (type == "PlayerJumpingState") 
			return true; 
		else
			return false;
	}
};

#endif
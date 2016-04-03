#ifndef IDLESTATE_HPP
#define IDLESTATE_HPP

#include <string>

#include "EntityState.hpp"

class IdleState : public EntityState
{
public:
	IdleState(EntityStateMachine& stateMachine);
	bool is(std::string type)
	{ 
		if (type == "IdleState") 
			return true; 
		else
			return false;
	}
};

#endif
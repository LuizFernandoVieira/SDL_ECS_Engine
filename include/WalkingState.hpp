#ifndef WALKINGSTATE_HPP
#define WALKINGSTATE_HPP

#include <string>

#include "EntityState.hpp"

class WalkingState : public EntityState
{
public:
	WalkingState(EntityStateMachine& stateMachine) : EntityState(stateMachine) {}
	bool is(std::string type)
	{ 
		if (type == "WalkingState") 
			return true; 
		else
			return false;
	}
};

#endif
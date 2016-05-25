#ifndef PLAYERJUMPINGSTATE_HPP
#define PLAYERJUMPINGSTATE_HPP

#include "JumpingState.hpp"
#include "StateComponent.hpp"

class PlayerJumpingState : public JumpingState
{
public:
	PlayerJumpingState(EntityStateMachine& stateMachine);
	virtual ~PlayerJumpingState();
	void handle(StateComponent* stateComp, SpeedComponent* speedComp);
	
	// bool is(std::string type)
	// { 
	// 	if (type == "PlayerJumpingState") 
	// 		return true; 
	// 	else
	// 		return false;
	// }
};

#endif
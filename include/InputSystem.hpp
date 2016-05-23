#ifndef INPUTSYSTEM_HPP
#define INPUTSYSTEM_HPP

#include <map>

#include "System.hpp"
#include "SpeedComponent.hpp"
#include "StateComponent.hpp"

class InputSystem : public System
{
public:
	InputSystem();
	void update(
		unsigned player,
		std::map<int, StateComponent*> stateComp,
		std::map<int, SpeedComponent*> speedComp
	);
};

#endif
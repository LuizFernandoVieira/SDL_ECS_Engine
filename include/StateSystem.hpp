/*#ifndef STATESYSTEM_HPP
#define STATESYSTEM_HPP

#include <map>

#include "System.hpp"
#include "StateComponent.hpp"
#include "SpeedComponent.hpp"

class StateSystem : public System
{
public:
	StateSystem();
	void update(
		std::map<int, StateComponent*> stateComp, 
		std::map<int, SpeedComponent*> speedComp
	);
};

#endif*/
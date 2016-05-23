#include "../include/StateSystem.hpp"

#include <iostream>

StateSystem::StateSystem()
{

}

void StateSystem::update(
	std::map<int, StateComponent*> stateComp, 
	std::map<int, SpeedComponent*> speedComp)
{
	for(auto it = stateComp.begin(); it != stateComp.end(); ++it) {
		it->second->getStateMachine()->handle(it->second, speedComp[it->first]);
	}
}

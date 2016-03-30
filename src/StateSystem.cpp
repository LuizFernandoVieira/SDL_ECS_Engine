#include "../include/StateSystem.hpp"

StateSystem::StateSystem()
{

}

void StateSystem::update(std::map<int, StateComponent*> sc)
{
	for(auto it = sc.begin(); it != sc.end(); ++it) {
		it->second->getStateMachine()->handle(); 
	}
}

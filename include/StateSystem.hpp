#ifndef STATESYSTEM_HPP
#define STATESYSTEM_HPP

#include <map>

#include "System.hpp"
#include "StateComponent.hpp"

class StateSystem : public System
{
public:
	StateSystem();
	void update(std::map<int, StateComponent*> sc);
};

#endif
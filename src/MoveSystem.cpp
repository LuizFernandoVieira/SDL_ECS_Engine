#include "../include/MoveSystem.hpp"

#include <iostream>

MoveSystem::MoveSystem()
{

}

void MoveSystem::update(
	std::map<int, TransformComponent*> tc,
	std::map<int, StateComponent*> sc,
	std::map<int, PhysicsComponent*> pc)
{
	std::cout << "OI" << std::endl;
	for (auto it = pc.begin(); it != pc.end(); ++it)
	{
		if (sc[it->first]->getStateMachine()->getCurrentState()->is("WalkingState"))
		{
			Rect* rect = tc[it->first]->getRect();
			rect->x(rect->x() + 5);
			tc[it->first]->setRect(*rect);
		}
	}
}
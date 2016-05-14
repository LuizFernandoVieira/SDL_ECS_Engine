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
	for (auto it = pc.begin(); it != pc.end(); ++it)
	{
		if (sc[it->first]->getStateMachine()->getCurrentState()->is("WalkingState"))
		{
			// Rect rect = tc[it->first]->getRect();
			// if (sc[it->first]->isFacingRight())
			// 	rect.x(rect.x() + 5);
			// else
			// 	rect.x(rect.x() - 5);
			// tc[it->first]->setRect(rect);
			if (sc[it->first]->isFacingRight())
				*tc[it->first]->rect_ = *tc[it->first]->rect_ + Vec2(5,0);
			else
				*tc[it->first]->rect_ = *tc[it->first]->rect_ + Vec2(-5,0);
		}
	}
}
#include "../include/MoveSystem.hpp"

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
			if (sc[it->first]->isFacingRight())
				tc[it->first]->rect_ = tc[it->first]->rect_ + Vec2(5,0);
			else
				tc[it->first]->rect_ = tc[it->first]->rect_ + Vec2(-5,0);
		}
	}
}
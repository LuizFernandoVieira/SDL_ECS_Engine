#include "../include/MoveSystem.hpp"

MoveSystem::MoveSystem()
{

}

void MoveSystem::update(
	float dt,
	std::map<int, TransformComponent*> tc,
	std::map<int, SpeedComponent*> sc)
{
	for (auto it = sc.begin(); it != sc.end(); ++it)
	{
		// if (sc[it->first]->getStateMachine()->getCurrentState()->is("WalkingState"))
		// {
		// 	if (sc[it->first]->isFacingRight())
		// 		tc[it->first]->rect_ = tc[it->first]->rect_ + Vec2(5,0);
		// 	else
		// 		tc[it->first]->rect_ = tc[it->first]->rect_ + Vec2(-5,0);
		// }
		tc[it->first]->rect_ += it->second->speed_ * dt;
	}
}
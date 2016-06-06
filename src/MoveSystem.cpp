#include "../include/MoveSystem.hpp"

MoveSystem::MoveSystem()
{

}

void MoveSystem::update(
	float dt,
	std::map<int, TransformComponent*> transform,
	std::map<int, SpeedComponent*> speed)
{
	for (auto& sp : speed)
	{
		transform[sp.first]->rect_ += sp.second->speed_ * dt;
	}
}
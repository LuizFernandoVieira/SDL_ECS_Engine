#include "../include/MoveSystem.hpp"
#include "../include/TransformComponent.hpp"
#include "../include/SpeedComponent.hpp"

MoveSystem::MoveSystem()
{

}

void MoveSystem::update(float dt, GameState& gameState)
{
	std::map<int, TransformComponent*> transform = gameState.mapTransform_;
	std::map<int, SpeedComponent*> speed = gameState.mapSpeed_;

	for (auto& sp : speed)
	{
		transform[sp.first]->rect_ += sp.second->speed_ * dt;
	}
}
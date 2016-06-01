#include "../include/GravitySystem.hpp"
#include "../include/Resources.hpp"

GravitySystem::GravitySystem()
{

}

void GravitySystem::update( 
	float dt,
	std::map<int, SpeedComponent*> sc,
	std::map<int, PhysicsComponent*> pc)
{
	for (auto it = pc.begin(); it != pc.end(); ++it)
	{
		if (sc[it->first]->speed_.y() < 0)
			sc[it->first]->speed_ += Vec2(0, Resources::GRAVITY * it->second->gravityScale_ * 0.2); // diminuir velocidade pra cima do pulo
		else
			sc[it->first]->speed_.y(Resources::GRAVITY * it->second->gravityScale_);
	}
}
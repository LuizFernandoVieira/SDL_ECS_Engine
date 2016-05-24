#include "../include/GravitySystem.hpp"
#include "../include/Globals.hpp"

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
			sc[it->first]->speed_ += Vec2(0, Globals::GRAVITY * it->second->gravityScale_ * 0.2); // diminuir velocidade pra cima do pulo
		else
			sc[it->first]->speed_.y(Globals::GRAVITY * it->second->gravityScale_);
	}
}
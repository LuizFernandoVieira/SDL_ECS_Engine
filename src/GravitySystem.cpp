#include "../include/GravitySystem.hpp"
#include "../include/Globals.hpp"

GravitySystem::GravitySystem()
{

}

void GravitySystem::update( 
	float dt,
	std::map<int, TransformComponent*> tc,
	std::map<int, StateComponent*> sc,
	std::map<int, PhysicsComponent*> pc)
{
	for (auto it = pc.begin(); it != pc.end(); ++it)
	{
		tc[it->first]->rect_.y( tc[it->first]->rect_.y() + Globals::GRAVITY * dt );

		// CHECAR COLISAO COM O CHAO
	}
}
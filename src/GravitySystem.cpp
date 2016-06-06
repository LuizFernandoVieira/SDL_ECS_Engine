#include "../include/GravitySystem.hpp"
#include "../include/Resources.hpp"

GravitySystem::GravitySystem()
{

}

void GravitySystem::update( 
	float dt,
	std::map<int, SpeedComponent*> speed,
	std::map<int, PhysicsComponent*> physics,
	std::map<int, StateComponent*> state)
{
	for (auto& phys : physics)
	{
		if (speed[phys.first]->speed_.y() < 0)
		{
			// TA PULANDO
			// Diminui a escala da gravidade
			speed[phys.first]->speed_ += Vec2(0, Resources::GRAVITY * phys.second->gravityScale_ * 0.2);
		}
		else
		{
			// TA CAINDO (A MENOS QUE ESTEJA COLIDINDO)
			speed[phys.first]->speed_.y(Resources::GRAVITY * phys.second->gravityScale_);
			state[phys.first]->state_ = State::FALLING;
		}
	}
}
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
			// Agora sim gravidade funciona como uma aceleracao (desaceleracao do pulo nesse caso)
			speed[phys.first]->speed_ += Vec2(0, Resources::GRAVITY * phys.second->gravityScale_ * dt * 4);
		}
		else
		{
			// TA CAINDO (A MENOS QUE ESTEJA COLIDINDO)
			if (state[phys.first]->state_ != State::ZIPLINE)
			{
				speed[phys.first]->speed_.y(Resources::GRAVITY * phys.second->gravityScale_);
				if (state[phys.first]->state_ != State::GRAPPLE)
					state[phys.first]->state_ = State::FALLING;
			}
		}
	}
}
#include "../include/GravitySystem.hpp"
#include "../include/Resources.hpp"
#include "../include/SpeedComponent.hpp"
#include "../include/StateComponent.hpp"
#include "../include/PhysicsComponent.hpp"

GravitySystem::GravitySystem()
{

}

void GravitySystem::update(float dt, GameState& gameState)
{
	std::map<int, SpeedComponent*> speed = gameState.mapSpeed_;
	std::map<int, PhysicsComponent*> physics = gameState.mapPhysics_;
	std::map<int, StateComponent*> state = gameState.mapState_;

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
				if (state[phys.first]->state_ != State::GRAPPLE && state[phys.first]->state_ != State::ATTACKING)
				{
					state[phys.first]->state_ = State::FALLING;
				}
			}
		}
	}
}
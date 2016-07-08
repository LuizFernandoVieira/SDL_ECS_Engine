#include "../include/HealthSystem.hpp"
#include "../include/HealthComponent.hpp"
#include "../include/StateComponent.hpp"
#include "../include/Resources.hpp"

HealthSystem::HealthSystem()
{

}

void HealthSystem::update(float dt, GameState& gameState)
{
	std::map<int, HealthComponent*> health = gameState.mapHealth_;
	std::map<int, StateComponent*> state = gameState.mapState_;

	for (auto& h : health)
	{
		if (h.first == gameState.player_ && h.second->health_ < 3)
		{
			playerRecoverTime_.update(dt);
			if (playerRecoverTime_.get() >= 10)
			{
				h.second->health_++;
				playerRecoverTime_.restart();
			}
		}
		if (h.second->invincible_)
		{
			h.second->timeToDie_.update(dt);
			if (h.second->timeToDie_.get() >= 4)
			{
				h.second->invincible_ = false;
				h.second->timeToDie_.restart();
			}
		}
		if (state[h.first]->state_ == State::DYING)
		{
			h.second->timeToDie_.update(dt);
			if (h.second->timeToDie_.get() >= Resources::DYING_TIME)
				state[h.first]->state_ = State::DEAD;
		}
		else if (h.second->health_ <= 0 && state[h.first]->state_ != State::DEAD)
		{
			state[h.first]->state_ = State::DYING;
			h.second->timeToDie_.restart();
			h.second->timeToDie_.update(dt);
		}
	}
}
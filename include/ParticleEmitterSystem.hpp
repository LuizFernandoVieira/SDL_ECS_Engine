#ifndef PARTICLEEMITTER_HPP
#define PARTICLEEMITTER_HPP

#include <map>

#include "System.hpp"
#include "GameState.hpp"
#include "TransformComponent.hpp"
#include "EmitterComponent.hpp"
#include "TimerComponent.hpp"
#include "SpeedComponent.hpp"
#include "ColliderComponent.hpp"
#include "EmissionRateSystem.hpp"
#include "CollisionRainTerrainSystem.hpp"
#include "Timer.hpp"

class ParticleEmitterSystem : public System
{
public:
	ParticleEmitterSystem(GameState& gameState);
	~ParticleEmitterSystem();
	void update(float dt, GameState& gameState);
	void render();
	void destroyParticleNow(int particle);
	void destroyParticle(int particle);
	void destroyAll();
private:
	static unsigned int nextId_;

	static std::map<int, TransformComponent*> mapTransform_;
	static std::map<int, RenderComponent*> mapR_;
	std::map<int, TimerComponent*> mapTimer_;
	std::map<int, SpeedComponent*> mapSpeed_;
	std::map<int, ColliderComponent*> mapCollider_;

	std::map<int, Timer*> mapT_;

	EmissionRateSystem emissionRateSystem_;
	CollisionRainTerrainSystem collisionRainTerrainSystem_;

	GameState& gameState_;
};

#endif

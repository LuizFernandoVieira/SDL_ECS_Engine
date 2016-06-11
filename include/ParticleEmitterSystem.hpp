#ifndef PARTICLEEMITTER_HPP
#define PARTICLEEMITTER_HPP

#include <map>

#include "System.hpp"
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
	ParticleEmitterSystem();
	void update(
		float dt,
		CollisionMap levelCollisionMap,
		TransformComponent* tc,
    EmitterComponent* ec,
    TimerComponent* timerComponent
	);
  void render();
	void destroyParticle(int particle);
private:
  static unsigned int nextId_;

  std::map<int, TransformComponent*> mapTransform_;
  std::map<int, RenderComponent*> mapRender_;
  std::map<int, TimerComponent*> mapTimer_;
	std::map<int, SpeedComponent*> mapSpeed_;
	std::map<int, ColliderComponent*> mapCollider_;

	std::map<int, Timer> mapT_;

  EmissionRateSystem emissionRateSystem_;
	CollisionRainTerrainSystem collisionRainTerrainSystem_;
};

#endif

#ifndef COLLISIONRAINTERRAINSYSTEM_HPP
#define COLLISIONRAINTERRAINSYSTEM_HPP

#include <map>
#include <vector>
#include <cmath>
#include <algorithm>

#include "Rect.hpp"
#include "TransformComponent.hpp"
#include "ColliderComponent.hpp"
#include "SpeedComponent.hpp"
#include "CollisionMap.hpp"

class ParticleEmitterSystem;

class CollisionRainTerrainSystem
{
public:
	CollisionRainTerrainSystem();
	void update(
    ParticleEmitterSystem& particleEmitterSystem,
		CollisionMap& collisionMap,
		std::map<int, TransformComponent*> oldTransfComp,
		std::map<int, TransformComponent*> transfComp,
		std::map<int, ColliderComponent*> colComp,
		std::map<int, SpeedComponent*> speedComp
	);
	void render(std::map<int, ColliderComponent*> collidersForRendering);
private:
	bool isColliding(const Rect& a, const Rect& b, float angleOfA, float angleOfB);
};

#include "ParticleEmitterSystem.hpp"

#endif

#ifndef COLLISIONSYSTEM_HPP
#define COLLISIONSYSTEM_HPP

#include <map>
#include <vector>
#include <cmath>
#include <algorithm>

#include "Rect.hpp"
#include "System.hpp"
#include "TransformComponent.hpp"
#include "ColliderComponent.hpp"
#include "SpeedComponent.hpp"
#include "StateComponent.hpp"
#include "CollisionMap.hpp"

class CollisionSystem : public System
{
public:
	CollisionSystem();
	void update(
		CollisionMap& collisionMap,
		std::map<int, TransformComponent*> oldTransform,
		std::map<int, TransformComponent*> transform,
		std::map<int, ColliderComponent*> collider,
		std::map<int, SpeedComponent*> speed,
		std::map<int, StateComponent*> state
	);
	// void render();
private:
	bool isColliding(const Rect& a, const Rect& b, float angleOfA, float angleOfB);

	void correctPosition(Rect& entityPos, Rect oldPos, Rect terrain, Vec2& speed, StateComponent* state);

	#ifdef _DEBUG
	std::vector<Rect> collidersToRender; // para renderizar colisores q estao colidindo
	#endif
};

#endif
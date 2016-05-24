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
#include "CollisionMap.hpp"

class CollisionSystem : public System
{
public:
	CollisionSystem();
	void update(
		CollisionMap& collisionMap,
		std::map<int, TransformComponent*> oldTransfComp,
		std::map<int, TransformComponent*> transfComp,
		std::map<int, ColliderComponent*> colComp,
		std::map<int, SpeedComponent*> speedComp
	);
	// void render();
private:
	bool isColliding(const Rect& a, const Rect& b, float angleOfA, float angleOfB);

	void correctPosition(Rect& entityPos, Rect oldPos, Rect terrain, Vec2& speed);

	// std::vector<Rect> coisaFeia; // para renderizar colisores q estao colidindo
};

#endif
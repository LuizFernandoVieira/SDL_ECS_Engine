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
#include "ZiplineComponent.hpp"
#include "WindComponent.hpp"
#include "CollisionMap.hpp"

class CollisionSystem : public System
{
public:
	CollisionSystem();
	void update(
		int player,
		CollisionMap& collisionMap,
		std::map<int, TransformComponent>& oldTransform,
		std::map<int, TransformComponent>& transform,
		std::map<int, ColliderComponent*> collider,
		std::map<int, SpeedComponent*> speed,
		std::map<int, StateComponent*> oldState,
		std::map<int, StateComponent*> state,
		std::map<int, ZiplineComponent*> zipline,
		std::map<int, WindComponent*> wind
	);

	void render();

private:
	bool isColliding(const Rect& a, const Rect& b, float angleOfA, float angleOfB);

	void updateTerrain(
		CollisionMap& collisionMap,
		std::map<int, TransformComponent>& oldTransform,
		std::map<int, TransformComponent>& transform,
		std::map<int, ColliderComponent*> collider,
		std::map<int, SpeedComponent*> speed,
		std::map<int, StateComponent*> state
	);
	void updateCollider(
		CollisionMap& collisionMap,
		std::map<int, TransformComponent>& oldTransform,
		std::map<int, TransformComponent>& transform,
		std::map<int, ColliderComponent*> collider,
		std::map<int, SpeedComponent*> speed,
		std::map<int, StateComponent*> state
	);
	void updateZipline(
		int player,
		std::map<int, TransformComponent>& transform,
		std::map<int, ColliderComponent*> collider,
		std::map<int, SpeedComponent*> speed,
		std::map<int, StateComponent*> oldState,
		std::map<int, StateComponent*> state,
		std::map<int, ZiplineComponent*> zipline
	);
	void updateWind(
		int player,
		std::map<int, TransformComponent>& transform,
		std::map<int, ColliderComponent*> collider,
		// std::map<int, SpeedComponent*> speed,
		// std::map<int, StateComponent*> oldState,
		// std::map<int, StateComponent*> state,
		std::map<int, WindComponent*> wind
	);

	void correctPosSolid(Rect& entityPos, Rect oldPos, Rect terrain, Vec2& speed, StateComponent* state);
	void correctPosDiagonalUp(Rect& entityPos, Rect oldPos, Rect terrain, Vec2& speed, StateComponent* state);
	void correctPosDiagonalDown(Rect& entityPos, Rect oldPos, Rect terrain, Vec2& speed, StateComponent* state);
	void correctPosCorner(Rect& entityPos, Rect oldPos, Rect terrain, Vec2& speed, StateComponent* state);

	//#ifdef _DEBUG
	std::vector<Rect> collidersToRender; // para renderizar colisores q estao colidindo
	//#endif
};

#endif

#ifndef COLLISIONSYSTEM_HPP
#define COLLISIONSYSTEM_HPP

#include <map>
#include <vector>
#include <cmath>
#include <algorithm>

#include "Rect.hpp"
#include "System.hpp"
#include "GameState.hpp"
#include "CollisionMap.hpp"

class CollisionSystem : public System
{
public:
	CollisionSystem();
	void update(float dt, GameState& gameState);
	void render(GameState& gameState);

private:
	bool isColliding(const Rect& a, const Rect& b, float angleOfA, float angleOfB);

	void updateTerrain(
		int player,
		CollisionMap& collisionMap,
		std::map<int, TransformComponent*> oldTransform,
		std::map<int, TransformComponent*> transform,
		std::map<int, ColliderComponent*> collider,
		std::map<int, SpeedComponent*> speed,
		std::map<int, StateComponent*> state,
		std::map<int, HealthComponent*> health
	);
	void updateCollider(
		std::map<int, TransformComponent*> transform,
		std::map<int, ColliderComponent*> collider,
		std::map<int, SpeedComponent*> speed,
		std::map<int, StateComponent*> state,
		std::map<int, HealthComponent*> health
	);
	void updateZipline(
		int player,
		std::map<int, TransformComponent*> transform,
		std::map<int, ColliderComponent*> collider,
		std::map<int, SpeedComponent*> speed,
		std::map<int, StateComponent*> oldState,
		std::map<int, StateComponent*> state,
		std::map<int, ZiplineComponent*> zipline
	);
	void updateWind(
		float dt,
		int player,
		std::map<int, TransformComponent*> transform,
		std::map<int, ColliderComponent*> collider,
		std::map<int, StateComponent*> state,
		std::map<int, WindComponent*> wind
	);

	void updateTriggers(GameState& gameState);

	void correctFloor(Rect& entityPos, Rect collider, Rect terrain, Vec2& speed);
	void correctWall(Rect& entityPos, Rect collider, Rect terrain, Vec2& speed);
	void correctCeiling(Rect& entityPos, Rect collider, Rect terrain, Vec2& speed);
	void correctFloorCeiling(Rect& entityPos, Rect collider, Rect terrain, Vec2& speed);
	void correctAllSides(Rect& entityPos, Rect collider, Rect terrain, Vec2& speed);
	void correctDiagonalUp(Rect& entityPos, Rect collider, Rect terrain, Vec2& speed);
	void correctDiagonalDown(Rect& entityPos, Rect collider, Rect terrain, Vec2& speed);

	std::vector<Rect> collidersToRender;
};

#endif

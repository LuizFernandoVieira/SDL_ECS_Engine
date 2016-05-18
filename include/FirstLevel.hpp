#ifndef FIRSTLEVEL_HPP
#define FIRSTLEVEL_HPP

#include "Level.hpp"
#include "TileSet.hpp"
#include "TileMap.hpp"
#include "CollisionMap.hpp"
#include "TransformComponent.hpp"
#include "StaticSprite.hpp"

class FirstLevel : public Level
{
public:
	FirstLevel();
	~FirstLevel();
	void render();
	std::vector<std::pair<int, TransformComponent*>> createTerrain(unsigned int& nextId);
private:
	StaticSprite bg;
	TileSet tileSet_;
	TileMap tileMap_;
	CollisionMap collisionMap_;
};

#endif
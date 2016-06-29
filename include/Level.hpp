#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>

#include "TransformComponent.hpp"
#include "CollisionMap.hpp"
#include "TileSet.hpp"
#include "TileMap.hpp"
#include "CollisionMap.hpp"
#include "TransformComponent.hpp"
#include "StaticSprite.hpp"
#include "pugixml.hpp"

class Level
{
public:
	Level();
	Level(pugi::xml_node source);
	~Level();
	void render(int layer);
	// std::vector<std::pair<int, TransformComponent*>> createTerrain(unsigned int&);
	CollisionMap& getCollisionMap();

private:
	StaticSprite bg;
	TileSet tileSet_;
	TileMap tileMap_;
	CollisionMap collisionMap_;
};

#endif

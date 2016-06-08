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
	void render(int layer);
	// std::vector<std::pair<int, TransformComponent*>> createTerrain(unsigned int& nextId);
	CollisionMap& getCollisionMap();
	pugi::xml_document& getObjectMap();

private:
	StaticSprite bg;
	TileSet tileSet_;
	TileMap tileMap_;
	ObjectMap objectMap_;
	CollisionMap collisionMap_;
};

#endif
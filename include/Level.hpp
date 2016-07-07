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

#include "../include/ScreenLayer.hpp"

class Level
{
public:
	Level();
	Level(pugi::xml_node source);
	~Level();
	void render(int layer);

	CollisionMap& getCollisionMap();

	short int max_layers;
	short int main_layer;

private:
	TileSet tileSet_;
	TileMap tileMap_;
	CollisionMap collisionMap_;

	std::vector<ScreenLayer*> screen;
};

#endif

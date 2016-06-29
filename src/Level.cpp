#include "../include/Level.hpp"
#include "../include/Resources.hpp"
#include "../include/pugixml.hpp"

Level::Level() :
	bg("../img/floresta_bg.png"),
	tileSet_(Resources::TILE_WIDTH, Resources::TILE_HEIGHT, Resources::TILE_SET_IMG.c_str()),
	tileMap_(Resources::TILE_MAP_TXT.c_str(), &tileSet_),
	collisionMap_(Resources::COLLISION_MAP_TXT.c_str())

	//TODO: Inserir elementos acima em config.txt, carregar dinamicamente
{

}

Level::Level(pugi::xml_node source) :
	bg("../img/floresta_bg.png"),
	tileSet_(Resources::TILE_WIDTH, Resources::TILE_HEIGHT, Resources::TILE_SET_IMG.c_str()),
	tileMap_(source.child("tilemap").attribute("file").value(), &tileSet_),
	collisionMap_(source.child("collision_map").attribute("file").value())
{
	/*
	

	tileSet_.Open();
	*/
}

Level::~Level()
{

}

// void Level::update(float dt)
// {

// }

void Level::render(int layer)
{
	if (layer == 3)
		bg.render(0,0);
	tileMap_.renderLayer(layer, 0, 0);
	// collisionMap_.render(0,0);
}


CollisionMap& Level::getCollisionMap()
{
	return collisionMap_;
}

/*std::vector<std::pair<int, TransformComponent*>> FirstLevel::createTerrain(unsigned int& nextId)
{
	std::vector<std::pair<int, TransformComponent*>> terrainEntities;
	for (int y = 0; y < collisionMap_.getHeight(); y++)
	{
		for (int x = 0; x < collisionMap_.getWidth(); x++)
		{
			if (collisionMap_.at(x, y) == 0)
			{
				terrainEntities.emplace_back( std::pair<int, TransformComponent*> (
					nextId++,
					new TransformComponent(Rect(
						x * Resources::TILE_WIDTH,
						y * Resources::TILE_HEIGHT,
						Resources::TILE_WIDTH,
						Resources::TILE_HEIGHT
					))
				));
			}
		}
	}

	return terrainEntities;
}*/

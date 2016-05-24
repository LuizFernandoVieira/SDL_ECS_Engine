#include "../include/FirstLevel.hpp"
#include "../include/Globals.hpp"


FirstLevel::FirstLevel() : 
	bg("../img/bg.png"),
	tileSet_(Globals::TILE_WIDTH, Globals::TILE_HEIGHT, "../img/maps/test/tile_set.png"),
	tileMap_("../map/tileMap.txt", &tileSet_),
	collisionMap_("../map/collisionMap.txt")
{

}

FirstLevel::~FirstLevel()
{

}

// void FirstLevel::update(float dt)
// {

// }

void FirstLevel::render()
{
	bg.render(0,0);
	tileMap_.render(0,0);
	// collisionMap_.render(0,0);
}


CollisionMap& FirstLevel::getCollisionMap()
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
						x * Globals::TILE_WIDTH,
						y * Globals::TILE_HEIGHT,
						Globals::TILE_WIDTH,
						Globals::TILE_HEIGHT
					))
				));
			}
		}
	}

	return terrainEntities;
}*/
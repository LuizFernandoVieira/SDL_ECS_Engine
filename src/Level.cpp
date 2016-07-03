#include "../include/Level.hpp"
#include "../include/Resources.hpp"
#include "../include/pugixml.hpp"

Level::Level() :
	tileSet_(Resources::TILE_WIDTH, Resources::TILE_HEIGHT, Resources::TILE_SET_IMG.c_str()),
	tileMap_(Resources::TILE_MAP_TXT.c_str(), &tileSet_),
	collisionMap_(Resources::COLLISION_MAP_TXT.c_str())
{
	screen.emplace_back("../img/bg.png");	//failsafe
}

Level::Level(pugi::xml_node source) :
	tileSet_(Resources::TILE_WIDTH, Resources::TILE_HEIGHT, Resources::TILE_SET_IMG.c_str()),
	tileMap_(source.child("tilemap").attribute("file").value(), &tileSet_),
	collisionMap_(source.child("collision_map").attribute("file").value())
{
	//printf("Attempting to open: %s \n", source.child("layers").first_child().attribute("file").value());
	
	//Checagem de tipo antes de emplacement de nova camada (será útil mais tarde)
	if (source.child("layers").first_child().attribute("static").as_bool() == true)
		screen.emplace_back(source.child("layers").first_child().attribute("file").value());

}

Level::~Level()
{
	for (auto& it : screen){
		//liberar camadas  
	}
}

// void Level::update(float dt)
// {

// }

void Level::render(int layer)
{
	if (layer == 3)
		screen[0].render(0,0);
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

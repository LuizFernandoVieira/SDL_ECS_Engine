#include "../include/FirstLevel.hpp"
#include "../include/Resources.hpp"


FirstLevel::FirstLevel() :
	bg("../img/bg.png"),
	tileSet_(Resources::TILE_WIDTH, Resources::TILE_HEIGHT, Resources::TILE_SET_IMG.c_str()),
	tileMap_(Resources::TILE_MAP_TXT.c_str(), &tileSet_),
	objectMap_(Resources::OBJECT_MAP_XML.c_str()),
	collisionMap_(Resources::COLLISION_MAP_TXT.c_str())

	//TODO: Inserir elementos acima em config.txt, carregar dinamicamente
{

}

FirstLevel::~FirstLevel()
{

}

// void FirstLevel::update(float dt)
// {

// }

void FirstLevel::render(int layer)
{
	if (layer == 3)
		bg.render(0,0);
	tileMap_.renderLayer(layer, 0, 0);
	// collisionMap_.render(0,0);
}


CollisionMap& FirstLevel::getCollisionMap()
{
	return collisionMap_;
}

pugi::xml_document& FirstLevel::getObjectMap()
{
	return objectMap_.getLocalXML();
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

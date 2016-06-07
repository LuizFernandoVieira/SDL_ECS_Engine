#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>

#include "TransformComponent.hpp"
#include "CollisionMap.hpp"
#include "ObjectMap.hpp"

class Level
{
public:
	virtual ~Level() {}
	virtual void render() = 0;
	// virtual std::vector<std::pair<int, TransformComponent*>> createTerrain(unsigned int&) = 0;
	virtual CollisionMap& getCollisionMap() = 0;
	virtual pugi::xml_document& getObjectMap() = 0;
};

#endif

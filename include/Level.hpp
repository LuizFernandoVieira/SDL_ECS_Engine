#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>

#include "TransformComponent.hpp"

class Level
{
public:
	virtual ~Level() {}
	virtual void render() = 0;
	virtual std::vector<std::pair<int, TransformComponent*>> createTerrain(unsigned int&) = 0;
};

#endif
#ifndef LEVELEDITORSYSTEM_HPP
#define LEVELEDITORSYSTEM_HPP

#include <string>

#include "System.hpp"
#include "TransformComponent.hpp"
#include "TileMap.hpp"

class LevelEditorSystem : public System
{
public:
	LevelEditorSystem(TileMap& tileMap, std::string tileMapFilename);
	~LevelEditorSystem();
	void update(TransformComponent* tc);
private:
	void placeTile(int x, int y);

	TileMap* tileMap_;
	std::string tileMapFilename_;
};

#endif
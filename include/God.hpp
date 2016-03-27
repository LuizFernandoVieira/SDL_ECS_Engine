#ifndef GOD_HPP
#define GOD_HPP

#include <fstream>

#include "GameActor.hpp"
#include "TileMap.hpp"
#include "Sprite.hpp"

class God : public GameActor
{
public:
	God(float x, float y, TileMap& tileMap);
	~God();
	void update(float dt);
	void render();
	void moveTo(float x, float y);
	void jump();
	void placeTile(int x, int y);
private:
	TileMap* tileMap_;
	Sprite sprite_;
};

#endif
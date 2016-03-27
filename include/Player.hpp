#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GameActor.hpp"
#include "Sprite.hpp"

class Player: public GameActor
{
public:
	Player(float x, float y);
	~Player();
	void update(float dt);
	void render();
	void moveTo(float x, float y);
	void jump();
	void placeTile(int x, int y);
private:
	Sprite sprite_;
};

#endif
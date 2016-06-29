#ifndef PLAYERRENDERSYSTEM_HPP
#define PLAYERRENDERSYSTEM_HPP

#include <map>

#include "System.hpp"
#include "GameState.hpp"

class PlayerRenderSystem : public System
{
public:
	PlayerRenderSystem();
	void update(float dt, GameState& gameState);
	void render(GameState& gameState);
};

#endif
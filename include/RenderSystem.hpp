#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include <map>

#include "System.hpp"
#include "GameState.hpp"

class RenderSystem : public System
{
public:
	RenderSystem();
	void update(float dt, GameState& gameState);
	void render(int layer, GameState& gameState);
};

#endif
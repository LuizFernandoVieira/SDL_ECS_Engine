#ifndef FIRSTLEVEL_HPP
#define FIRSTLEVEL_HPP

#include <map>
#include <vector>

#include "ILevel.hpp"
#include "State.hpp"
#include "InputHandler.hpp"
#include "TileSet.hpp"
#include "TileMap.hpp"
#include "RenderSystem.hpp"

class FirstLevel : public ILevel
{
public:
	FirstLevel(State& state);
	~FirstLevel();
	void create();
	void update(float dt);
	void render();
private:
	void createPlayer();
	State* state_;
	InputHandler* inputHandler_;

	unsigned int player_;
	static unsigned int nextId_;

	std::map<int, TransformComponent*> mapTransform_;
	std::map<int, RenderComponent*> mapRender_;

	RenderSystem* renderSystem_;
};

#endif
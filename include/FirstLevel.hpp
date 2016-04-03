#ifndef FIRSTLEVEL_HPP
#define FIRSTLEVEL_HPP

#include <map>
#include <vector>

#include "ILevel.hpp"
#include "State.hpp"
#include "TileSet.hpp"
#include "TileMap.hpp"
#include "StateSystem.hpp"
#include "RenderSystem.hpp"
#include "MoveSystem.hpp"

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
	TileSet* tileSet_;
	TileMap* tileMap_;
	unsigned int player_;
	static unsigned int nextId_;
	std::map<int, TransformComponent*> mapTransform_;
	std::map<int, StateComponent*> 	mapState_;
	std::map<int, RenderComponent*> mapRender_;
	std::map<int, PhysicsComponent*> mapPhysics_;
	StateSystem* stateSystem_;
	RenderSystem* renderSystem_;
	MoveSystem* moveSystem_;
};

#endif
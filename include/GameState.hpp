#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <map>

#include "State.hpp"
#include "StateMachine.hpp"
#include "StateEventEnum.hpp"
#include "Level.hpp"
#include "ColliderComponent.hpp"
#include "StateSystem.hpp"
#include "RenderSystem.hpp"
#include "MoveSystem.hpp"
#include "GravitySystem.hpp"

class GameState: public State
{
public:
	GameState();
	~GameState();
	void create(StateMachine& stateMachine);
	void update(float dt);
	void render();
	void handle(StateEventEnum& event);
private:
	void createPlayer();
	
	// FirstLevel firstLevel_;
	Level* level_;

	static unsigned int nextId_;
	unsigned int player_;

	std::map<int, TransformComponent*> mapTransform_;
	std::map<int, StateComponent*> 	mapState_;
	std::map<int, RenderComponent*> mapRender_;
	std::map<int, PhysicsComponent*> mapPhysics_;
	std::map<int, ColliderComponent*> mapCollider_;

	StateSystem stateSystem_;
	RenderSystem renderSystem_;
	MoveSystem moveSystem_;
	GravitySystem gravitySystem_;
};

#endif
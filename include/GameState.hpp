#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <map>

#include "State.hpp"
#include "StateMachine.hpp"
#include "StateEventEnum.hpp"
#include "Level.hpp"
#include "ColliderComponent.hpp"
#include "SpeedComponent.hpp"
#include "EmitterComponent.hpp"
#include "TimerComponent.hpp"
#include "InputSystem.hpp"
#include "StateSystem.hpp"
#include "RenderSystem.hpp"
#include "MoveSystem.hpp"
#include "GravitySystem.hpp"
#include "CollisionSystem.hpp"
#include "ParticleEmitterSystem.hpp"

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
	void createParticleEmitter();

	// FirstLevel firstLevel_;
	Level* level_;

	static unsigned int nextId_;

	unsigned int player_;
	unsigned int particleEmitter_;

	std::map<int, TransformComponent*> mapTransform_;
	std::map<int, StateComponent*> 	mapState_;
	std::map<int, RenderComponent*> mapRender_;
	std::map<int, PhysicsComponent*> mapPhysics_;
	std::map<int, ColliderComponent*> mapCollider_;
	std::map<int, SpeedComponent*> mapSpeed_;
	std::map<int, EmitterComponent*> mapEmitter_;
	std::map<int, TimerComponent*> mapTimer_;

	InputSystem inputSystem_;
	StateSystem stateSystem_;
	RenderSystem renderSystem_;
	MoveSystem moveSystem_;
	GravitySystem gravitySystem_;
	CollisionSystem collisionSystem_;
	ParticleEmitterSystem particleEmitterSystem_;
};

#endif

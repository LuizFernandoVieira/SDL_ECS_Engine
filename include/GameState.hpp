#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <map>

#include "IState.hpp"
#include "Level.hpp"
#include "ColliderComponent.hpp"
#include "SpeedComponent.hpp"
#include "EmitterComponent.hpp"
#include "TimerComponent.hpp"
#include "ZiplineComponent.hpp"
#include "SoundComponent.hpp"
#include "HealthComponent.hpp"
#include "WindComponent.hpp"
#include "InputSystem.hpp"
#include "PlayerRenderSystem.hpp"
#include "RenderSystem.hpp"
#include "MoveSystem.hpp"
#include "GravitySystem.hpp"
#include "CollisionSystem.hpp"
#include "SoundSystem.hpp"
#include "AttackSystem.hpp"
#include "ParticleEmitterSystem.hpp"
#include "Music.hpp"

class GameState: public IState
{
public:
	GameState();
	~GameState();

	void update(float dt);
	void render();

	void pause();
	void resume();

private:
	void createPlayer();
	void createParticleEmitter();
	void createMapObjects();
	void deleteDeadEntities();

	Level* level_;

	static unsigned int nextId_;

	unsigned int player_;
	unsigned int particleEmitter_;

	// #ifndef _DEBUG
	Music music;
	// #endif

	std::map<int, TransformComponent*> mapTransform_;
	std::map<int, StateComponent*> 	mapState_;
	std::map<int, PhysicsComponent*> mapPhysics_;
	std::map<int, ColliderComponent*> mapCollider_;
	std::map<int, SpeedComponent*> mapSpeed_;
	std::map<int, EmitterComponent*> mapEmitter_;
	std::map<int, TimerComponent*> mapTimer_;
	std::map<int, ZiplineComponent*> mapZipline_;
	std::map<int, SoundComponent*> mapSound_;
	std::map<int, HealthComponent*> mapHealth_;
	std::map<int, WindComponent*> mapWind_;

	static std::map<int, std::map<int, RenderComponent*>> mapRender_;
	PlayerRenderComponent playerRenderComponent_;

	InputSystem inputSystem_;
	RenderSystem renderSystem_;
	PlayerRenderSystem playerRenderSystem_;
	MoveSystem moveSystem_;
	GravitySystem gravitySystem_;
	CollisionSystem collisionSystem_;
	SoundSystem	soundSystem_;
	AttackSystem attackSystem_;
	ParticleEmitterSystem particleEmitterSystem_;
};

#endif

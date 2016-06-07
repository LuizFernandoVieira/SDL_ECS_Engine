#include <vector>
#include <unordered_map>

#include "../include/GameState.hpp"
#include "../include/Camera.hpp"
#include "../include/InputHandler.hpp"
#include "../include/FirstLevel.hpp"
#include "../include/TransformComponent.hpp"
#include "../include/StateComponent.hpp"
#include "../include/RenderComponent.hpp"

unsigned int GameState::nextId_ = 0;

GameState::GameState()
#ifndef _DEBUG
: music()
#endif
{
	//testando componente de música, não há necessidade de se carregar um arquivo
	//A própria music está carregando um arquivo teste
}

GameState::~GameState()
{
	mapTransform_.clear();
	mapState_.clear();
	mapRender_.clear();
	mapPhysics_.clear();
	mapCollider_.clear();
	mapSpeed_.clear();
}

void GameState::create(StateMachine& stateMachine)
{
	stateMachine_ = &stateMachine;
	quit = false;
	level_ = new FirstLevel();

	createPlayer();
	createMapObjects();
	// createParticleEmitter();
}

void GameState::update(float dt)
{
	InputHandler::getInstance().update();

	std::map<int, TransformComponent*> oldTransform = mapTransform_;
	std::map<int, StateComponent*> oldState = mapState_;

	#ifndef _DEBUG
	music.Update();
	#endif
	inputSystem_.update( mapState_[player_],	mapSpeed_[player_] );
	gravitySystem_.update( dt, mapSpeed_, mapPhysics_, mapState_ );
	// particleEmitterSystem_.update( dt, level_->getCollisionMap(), mapTransform_[particleEmitter_], mapEmitter_[particleEmitter_], mapTimer_[particleEmitter_] );
	moveSystem_.update( dt, mapTransform_, mapSpeed_ );
	collisionSystem_.update( level_->getCollisionMap(), oldTransform, mapTransform_, mapCollider_, mapSpeed_, mapState_ );
	// stateSystem_.update( mapState_, mapSpeed_ );
	renderSystem_.update( dt, oldState, mapState_, mapRender_ );
	playerRenderSystem_.update( dt, (PlayerStateComponent*)oldState[player_], (PlayerStateComponent*)mapState_[player_], &playerRenderComponent_ ); // ai q feio

	Camera::update(dt);

	if(InputHandler::getInstance().quitRequested()) {
		quit = true;
	}
}

void GameState::render()
{
	level_->render(); // dividir isso em layers depois

	renderSystem_.render(mapTransform_, mapState_, mapRender_);
	playerRenderSystem_.render(mapTransform_[player_], (PlayerStateComponent*)mapState_[player_], &playerRenderComponent_); // ai q feio

	// particleEmitterSystem_.render();

	#ifdef _DEBUG
	collisionSystem_.render();
	#endif
}

void GameState::handle(StateEventEnum& event)
{

}


void GameState::createPlayer()
{
	player_ = nextId_;
	nextId_++;

	mapTransform_.emplace(player_, new TransformComponent(Rect(352, 100, 52, 90)));
	mapCollider_.emplace(player_, new ColliderComponent(Rect(0, 0, 52, 90)));
	mapState_.emplace(player_, new PlayerStateComponent());
	mapPhysics_.emplace(player_, new PhysicsComponent());
	mapSpeed_.emplace(player_, new SpeedComponent());

	playerRenderComponent_.addSprite(State::IDLE, UmbrellaState::CLOSED, UmbrellaDirection::DOWN, 
		Sprite("../img/characters/player/idle.png"));
	playerRenderComponent_.addSprite(State::WALKING, UmbrellaState::CLOSED, UmbrellaDirection::DOWN, 
		Sprite("../img/characters/player/idle.png"));
	playerRenderComponent_.addSprite(State::JUMPING, UmbrellaState::CLOSED, UmbrellaDirection::DOWN, 
		Sprite("../img/characters/player/idle.png"));
	playerRenderComponent_.addSprite(State::FALLING, UmbrellaState::CLOSED, UmbrellaDirection::DOWN, 
		Sprite("../img/characters/player/idle.png"));

	Camera::follow(mapTransform_[player_]);
}

void GameState::createParticleEmitter()
{
	particleEmitter_ = nextId_;
	nextId_++;

	mapTransform_.emplace(particleEmitter_, new TransformComponent(Rect(300, 250, 32, 32)));
	mapEmitter_.emplace(particleEmitter_, new EmitterComponent(0.01));
	mapTimer_.emplace(particleEmitter_, new TimerComponent());
}


void GameState::createMapObjects()
{
	pugi::xml_document& objects = level_->getObjectMap();

	for (auto obj : objects.children())
	{
		pugi::xml_node aux;

		// TRANSFORM
		aux = obj.child("transform");
		mapTransform_.emplace(nextId_, new TransformComponent(Rect(
			aux.attribute("x").as_float(),
			aux.attribute("y").as_float(),
			aux.attribute("w").as_float(),
			aux.attribute("h").as_float()
		)));

		// RENDER
		if ((aux = obj.child("render")))
		{
			mapRender_.emplace(nextId_, new RenderComponent());

			for (auto sprite : aux.children())
			{
				State state = (State)sprite.attribute("state").as_int();
				mapRender_[nextId_]->addSprite(state, Sprite(sprite.attribute("filename").value(), 
				                                             sprite.attribute("frame_count").as_int(),
				                                             sprite.attribute("frame_time").as_float()));
			}
		}

		// COLLIDER
		if ((aux = obj.child("collider")))
		{
			mapCollider_.emplace(nextId_, new ColliderComponent(Rect(
				aux.attribute("x").as_float(),
				aux.attribute("y").as_float(),
				aux.attribute("w").as_float(),
				aux.attribute("h").as_float()
			)));
		}

		// SPEED
		if ((aux = obj.child("speed")))
		{
			mapSpeed_.emplace(nextId_, new SpeedComponent());
		}

		// STATE
		if ((aux = obj.child("state")))
		{
			mapState_.emplace(nextId_, new StateComponent());
		}

		// PHYSICS
		if ((aux = obj.child("physics")))
		{
			mapPhysics_.emplace(nextId_, new PhysicsComponent(aux.attribute("gravity_scale").as_float()));
		}

		// EMITTER
		if ((aux = obj.child("emitter")))
		{
			mapEmitter_.emplace(nextId_, new EmitterComponent(aux.attribute("emission_rate").as_float()));
		}

		// TIMER
		if ((aux = obj.child("timer")))
		{
			mapTimer_.emplace(nextId_, new TimerComponent());
		}

		nextId_++;
	}
}
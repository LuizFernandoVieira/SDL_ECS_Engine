#include <vector>
#include <unordered_map>

#include "../include/GameState.hpp"
#include "../include/Camera.hpp"
#include "../include/InputHandler.hpp"
#include "../include/FirstLevel.hpp"
#include "../include/TransformComponent.hpp"
#include "../include/StateComponent.hpp"
#include "../include/RenderComponent.hpp"
#include "../include/SoundComponent.hpp"


unsigned int GameState::nextId_ = 0;

GameState::GameState()
: music()
{
	mapRender_[0] = std::map<int, RenderComponent*>();
	mapRender_[1] = std::map<int, RenderComponent*>();
	mapRender_[2] = std::map<int, RenderComponent*>();
	mapRender_[3] = std::map<int, RenderComponent*>();
	
	//testando componente de música, não há necessidade de se carregar um arquivo
	//A própria music está carregando um arquivo teste

	level_ = new FirstLevel();

	createPlayer();
	createMapObjects();
	// createParticleEmitter();
}

GameState::~GameState()
{
	delete level_;
	nextId_ = 0;

	mapTransform_.clear();
	mapState_.clear();
	mapPhysics_.clear();
	mapCollider_.clear();
	mapSpeed_.clear();
	mapEmitter_.clear();
	mapTimer_.clear();
	mapZipline_.clear();
	mapSound_.clear();

	mapRender_[0].clear();
	mapRender_[1].clear();
	mapRender_[2].clear();
	mapRender_[3].clear();
	mapRender_.clear();

	Camera::unfollow();
	Camera::pos_ = Vec2(0,0);
}



void GameState::update(float dt)
{
	InputHandler::getInstance().update();

	std::map<int, TransformComponent*> oldTransform = mapTransform_;
	std::map<int, StateComponent*> oldState = mapState_;

	music.Update();
	inputSystem_.update( mapState_[player_],	mapSpeed_[player_] );
	gravitySystem_.update( dt, mapSpeed_, mapPhysics_, mapState_ );
	// particleEmitterSystem_.update( dt, level_->getCollisionMap(), mapTransform_[particleEmitter_], mapEmitter_[particleEmitter_], mapTimer_[particleEmitter_] );
	moveSystem_.update( dt, mapTransform_, mapSpeed_ );
	collisionSystem_.update( player_, level_->getCollisionMap(), oldTransform, mapTransform_, mapCollider_, mapSpeed_, oldState, mapState_, mapZipline_ );
	renderSystem_.update( dt, mapTransform_, oldState, mapState_, mapRender_ );
	playerRenderSystem_.update( dt, mapTransform_[player_], (PlayerStateComponent*)oldState[player_], (PlayerStateComponent*)mapState_[player_], &playerRenderComponent_ ); // ai q feio
	soundSystem_.update(oldState, mapState_, mapSound_);

	Camera::update(dt);


	if (InputHandler::getInstance().keyPress(ESCAPE_KEY)) {
		pop_ = true;
	}
	if (InputHandler::getInstance().quitRequested()) {
		quit_ = true;
	}
}

void GameState::render()
{
	level_->render(3);
	renderSystem_.render(3, mapTransform_, mapState_, mapRender_[3]);

	level_->render(2);
	renderSystem_.render(2, mapTransform_, mapState_, mapRender_[2]);

	level_->render(1);
	renderSystem_.render(1, mapTransform_, mapState_, mapRender_[1]);

	// renderSystem_.render(mapTransform_, mapState_, mapRender_);
	playerRenderSystem_.render(mapTransform_[player_], (PlayerStateComponent*)mapState_[player_], &playerRenderComponent_); // ai q feio

	// particleEmitterSystem_.render();

	// collisionSystem_.render();

	level_->render(0);
	renderSystem_.render(0, mapTransform_, mapState_, mapRender_[0]);
}



void GameState::pause()
{

}

void GameState::resume()
{

}


void GameState::createPlayer()
{
	player_ = nextId_;
	nextId_++;


	mapTransform_.emplace(player_, new TransformComponent(Rect(352, 100, 52, 90), Vec2(0.2, 0.2), 0));
	mapCollider_.emplace(player_, new ColliderComponent(Rect(0, 0, 52, 90)));
	mapState_.emplace(player_, new PlayerStateComponent());
	mapPhysics_.emplace(player_, new PhysicsComponent());
	mapSpeed_.emplace(player_, new SpeedComponent());
	mapSound_.emplace(player_, new SoundComponent());

	playerRenderComponent_.addSprite(State::IDLE, UmbrellaState::CLOSED, UmbrellaDirection::DOWN, 
		Sprite("../img/characters/player/idle.png", 24, 0.01));
	playerRenderComponent_.addSprite(State::WALKING, UmbrellaState::CLOSED, UmbrellaDirection::DOWN, 
		Sprite("../img/characters/player/running_front_closed.png", 24, 0.01));
	playerRenderComponent_.addSprite(State::JUMPING, UmbrellaState::CLOSED, UmbrellaDirection::DOWN, 
		Sprite("../img/characters/player/jumping_front_closed.png", 23, 0.01));
	playerRenderComponent_.addSprite(State::FALLING, UmbrellaState::CLOSED, UmbrellaDirection::DOWN, 
		Sprite("../img/characters/player/falling_front_closed.png", 11, 0.01));

/*	playerRenderComponent_.addSprite(State::IDLE, UmbrellaState::CLOSED, UmbrellaDirection::DOWN, 
		Sprite("../img/characters/idle.png"));
	playerRenderComponent_.addSprite(State::WALKING, UmbrellaState::CLOSED, UmbrellaDirection::DOWN, 
		Sprite("../img/characters/idle.png"));
	playerRenderComponent_.addSprite(State::JUMPING, UmbrellaState::CLOSED, UmbrellaDirection::DOWN, 
		Sprite("../img/characters/idle.png"));
	playerRenderComponent_.addSprite(State::FALLING, UmbrellaState::CLOSED, UmbrellaDirection::DOWN, 
		Sprite("../img/characters/idle.png"));*/

	mapSound_[player_]->addSound(State::JUMPING, Sound("../audio/character_jump.wav"));
	mapSound_[player_]->addSound(State::FALLING, Sound("../audio/character_fall.wav"));	//Mudar para ("estado: colidindo com o chão")

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
			RenderComponent* renderComp = new RenderComponent();

			for (auto sprite : aux.children())
			{
				State state = (State)sprite.attribute("state").as_int();
				renderComp->addSprite(state, Sprite(sprite.attribute("filename").value(), 
				                                    sprite.attribute("frame_count").as_int(),
				                                    sprite.attribute("frame_time").as_float()));
			}

			if (obj.attribute("layer"))
				mapRender_[obj.attribute("layer").as_int()].emplace(nextId_, renderComp);
			else
				mapRender_[1].emplace(nextId_, renderComp);
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
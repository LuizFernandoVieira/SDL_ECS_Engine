#ifdef __APPLE__
	#include <SDL2/SDL.h>
#else
	#include "SDL.h"
#endif
#include <vector>
#include <unordered_map>
#include <exception>

#include "../include/Game.hpp"
#include "../include/GameState.hpp"
#include "../include/Camera.hpp"
#include "../include/InputHandler.hpp"
#include "../include/FirstLevel.hpp"
#include "../include/TransformComponent.hpp"
#include "../include/StateComponent.hpp"
#include "../include/RenderComponent.hpp"
#include "../include/SoundComponent.hpp"
#include "../include/StaticSprite.hpp"

unsigned int GameState::nextId_ = 0;
std::map<int, std::map<int, RenderComponent*>> GameState::mapRender_;

GameState::GameState()
: music()
	//testando componente de música, não há necessidade de se carregar um arquivo
	//A própria music está carregando um arquivo teste
{
	StaticSprite loadScreen("../img/bg.png");
	loadScreen.render(0,0);
	SDL_RenderPresent(Game::getInstance().getRenderer());
	
	try{
		mapRender_[0] = std::map<int, RenderComponent*>();
		mapRender_[1] = std::map<int, RenderComponent*>();
		mapRender_[2] = std::map<int, RenderComponent*>();
		mapRender_[3] = std::map<int, RenderComponent*>();
		mapRender_[4] = std::map<int, RenderComponent*>();
		mapRender_[5] = std::map<int, RenderComponent*>();

		level_ = new FirstLevel();

		// createPlayer();
		createMapObjects();
		// createParticleEmitter();

		Camera::follow(mapTransform_[player_]);
	}
	catch (std::exception& e)
	{
		std::cout << "DEU MERDA: " << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "DEU MUITA MERDA" << std::endl;
	}

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
	mapHealth_.clear();
	mapWind_.clear();

	mapRender_[0].clear();
	mapRender_[1].clear();
	mapRender_[2].clear();
	mapRender_[3].clear();
	mapRender_[4].clear();
	mapRender_[5].clear();

	Camera::unfollow();
	Camera::pos_ = Vec2(0,0);
}



void GameState::update(float dt)
{
	InputHandler::getInstance().update();

	std::map<int, TransformComponent*> oldTransform = mapTransform_;
	std::map<int, StateComponent*> oldState = mapState_;

	music.Update();
	inputSystem_.update( (PlayerStateComponent*)mapState_[player_], mapSpeed_[player_], mapPhysics_[player_], mapCollider_[player_] );
	gravitySystem_.update( dt, mapSpeed_, mapPhysics_, mapState_ );
	// particleEmitterSystem_.update( dt, level_->getCollisionMap(), mapTransform_[particleEmitter_], mapEmitter_[particleEmitter_], mapTimer_[particleEmitter_] );
	moveSystem_.update( dt, mapTransform_, mapSpeed_ );
	attackSystem_.update( dt, oldState[player_], mapState_[player_] );
	collisionSystem_.update( player_, level_->getCollisionMap(), oldTransform, mapTransform_, mapCollider_, mapSpeed_, oldState, mapState_, mapZipline_, mapWind_ );
	renderSystem_.update( dt, oldState, mapState_, mapRender_ );
	playerRenderSystem_.update( dt, (PlayerStateComponent*)oldState[player_], (PlayerStateComponent*)mapState_[player_], &playerRenderComponent_ ); // ai q feio
	soundSystem_.update(oldState, mapState_, mapSound_);

	Camera::update(dt);

	deleteDeadEntities();

/*	if (mapState_[player_]->state_ == State::IDLE)
		std::cout << "IDLE" << std::endl;
	else if (mapState_[player_]->state_ == State::WALKING)
		std::cout << "WALKING" << std::endl;
	else if (mapState_[player_]->state_ == State::JUMPING)
		std::cout << "JUMPING" << std::endl;
	else if (mapState_[player_]->state_ == State::FALLING)
		std::cout << "FALLING" << std::endl;
	else if (mapState_[player_]->state_ == State::GRAPPLE)
		std::cout << "GRAPPLE" << std::endl;
	else if (mapState_[player_]->state_ == State::ZIPLINE)
		std::cout << "ZIPLINE" << std::endl;
	else if (mapState_[player_]->state_ == State::ATTACKING)
		std::cout << "ATTACKING" << std::endl;*/

	if (InputHandler::getInstance().keyPress(ESCAPE_KEY)) {
		pop_ = true;
	}
	if (InputHandler::getInstance().quitRequested()) {
		quit_ = true;
	}
}

void GameState::render()
{
	level_->render(5);
	renderSystem_.render(5, mapTransform_, mapState_, mapRender_[5]);

	level_->render(4);
	renderSystem_.render(4, mapTransform_, mapState_, mapRender_[4]);

	level_->render(3);
	renderSystem_.render(3, mapTransform_, mapState_, mapRender_[3]);

	level_->render(2);
	renderSystem_.render(2, mapTransform_, mapState_, mapRender_[2]);

	// renderSystem_.render(mapTransform_, mapState_, mapRender_);
	playerRenderSystem_.render(mapTransform_[player_], (PlayerStateComponent*)mapState_[player_], &playerRenderComponent_); // ai q feio

	// particleEmitterSystem_.render();

	// collisionSystem_.render();

	level_->render(1);
	renderSystem_.render(1, mapTransform_, mapState_, mapRender_[1]);

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

	mapTransform_.emplace(player_, new TransformComponent(Rect(352, 100, 52, 90), Vec2(0.3, 0.3), 0));
	mapCollider_.emplace(player_, new ColliderComponent( Rect(0, 0, 52, 90), Rect(10, -10, 20, 20) ));
	mapState_.emplace(player_, new PlayerStateComponent());
	mapPhysics_.emplace(player_, new PhysicsComponent());
	mapSpeed_.emplace(player_, new SpeedComponent());
	mapSound_.emplace(player_, new SoundComponent());
	mapHealth_.emplace(player_, new HealthComponent(1));

	playerRenderComponent_.addSprite(State::IDLE, UmbrellaState::CLOSED, UmbrellaDirection::DOWN, 
		Sprite("../img/characters/player/idle.png", 24, 0.01));
	playerRenderComponent_.addSprite(State::WALKING, UmbrellaState::CLOSED, UmbrellaDirection::DOWN, 
		Sprite("../img/characters/player/running_front_closed.png", 24, 0.02));

	playerRenderComponent_.addSprite(State::JUMPING, UmbrellaState::CLOSED, UmbrellaDirection::DOWN, 
		Sprite("../img/characters/player/jumping_front_closed.png", 23, 0.01));
	playerRenderComponent_.addSprite(State::FALLING, UmbrellaState::CLOSED, UmbrellaDirection::DOWN, 
		Sprite("../img/characters/player/falling_front_closed.png", 11, 0.01));
	playerRenderComponent_.addSprite(State::GRAPPLE, UmbrellaState::CLOSED, UmbrellaDirection::DOWN, 
		Sprite("../img/characters/player/zipline_grapple.png", 11, 0.02));
	playerRenderComponent_.addSprite(State::ZIPLINE, UmbrellaState::CLOSED, UmbrellaDirection::DOWN, 
		Sprite("../img/characters/player/zipline.png", 19, 0.01));

	mapSound_[player_]->addSound(State::JUMPING, Sound("../audio/character_jump.wav"));
	mapSound_[player_]->addSound(State::FALLING, Sound("../audio/character_fall.wav"));	//Mudar para ("estado: colidindo com o chão")
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
		mapTransform_.emplace(nextId_, new TransformComponent(
			Rect( aux.child("rect").attribute("x").as_float(),
			      aux.child("rect").attribute("y").as_float(),
			      aux.child("rect").attribute("w").as_float(),
			      aux.child("rect").attribute("h").as_float() ),
			Vec2( aux.child("scale").attribute("x").as_float(),
			      aux.child("scale").attribute("y").as_float() ),
			aux.child("rotation").attribute("value").as_float()
		));

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
				mapRender_[2].emplace(nextId_, renderComp);
		}

		// PLAYER RENDER
		if ((aux = obj.child("player_render")))
		{
			for (auto sprite : aux.children())
			{
				State state = (State)sprite.attribute("state").as_int();
				UmbrellaState umb = (UmbrellaState)sprite.attribute("umbrella_state").as_int();
				UmbrellaDirection umbDir = (UmbrellaDirection)sprite.attribute("umbrella_direction").as_int();
				playerRenderComponent_.addSprite(state, umb, umbDir, Sprite(sprite.attribute("filename").value(), 
				                                                            sprite.attribute("frame_count").as_int(),
				                                                            sprite.attribute("frame_time").as_float()));
			}

			player_ = nextId_;
		}

		// SOUND
		if ((aux = obj.child("sound")))
		{
			mapSound_.emplace(nextId_, new SoundComponent());

			for (auto sound : aux.children())
			{
				State state = (State)sound.attribute("state").as_int();
				mapSound_[nextId_]->addSound( state, Sound(sound.attribute("filename").value()) );
			}
		}

		// COLLIDER
		if ((aux = obj.child("collider")))
		{
			mapCollider_.emplace(nextId_, new ColliderComponent(
				Rect( aux.child("hurtbox").attribute("x").as_float(),
				      aux.child("hurtbox").attribute("y").as_float(),
				      aux.child("hurtbox").attribute("w").as_float(),
				      aux.child("hurtbox").attribute("h").as_float() ),
				Rect( aux.child("hitbox").attribute("x").as_float(),
				      aux.child("hitbox").attribute("y").as_float(),
				      aux.child("hitbox").attribute("w").as_float(),
				      aux.child("hitbox").attribute("h").as_float() )
			));
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

		// PLAYER_STATE
		if ((aux = obj.child("player_state")))
		{
			mapState_.emplace(nextId_, new PlayerStateComponent());
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

		// ZIPLINE
		if ((aux = obj.child("zipline")))
		{
			mapZipline_.emplace(nextId_, new ZiplineComponent(
				Vec2(aux.child("start").attribute("x").as_float(), aux.child("start").attribute("y").as_float()),
				Vec2(aux.child("end").attribute("x").as_float(), aux.child("end").attribute("y").as_float())
			));
		}

		// HEALTH
		if ((aux = obj.child("health")))
		{
			mapHealth_.emplace(nextId_, new HealthComponent(aux.attribute("value").as_float()));
		}

		// WIND
		if ((aux = obj.child("wind")))
		{
			mapWind_.emplace(nextId_, new WindComponent( (Direction)aux.attribute("direction").as_float(),
			                                             aux.attribute("speed").as_float() ));
		}

		nextId_++;
	}
}


void GameState::deleteDeadEntities()
{
	for (auto& health : mapHealth_ )
	{
		if (health.second->health_ <= 0)
		{
			int id = health.first;
			
			mapTransform_.erase(id);
			mapState_.erase(id);
			mapPhysics_.erase(id);
			mapCollider_.erase(id);
			mapSpeed_.erase(id);
			mapEmitter_.erase(id);
			mapTimer_.erase(id);
			mapZipline_.erase(id);
			mapSound_.erase(id);
			mapHealth_.erase(id);

			mapRender_[0].erase(id);
			mapRender_[1].erase(id);
			mapRender_[2].erase(id);
			mapRender_[3].erase(id);
			mapRender_[4].erase(id);
		}
	}
}
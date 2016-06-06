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
	createParticleEmitter();
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
	particleEmitterSystem_.update( dt, level_->getCollisionMap(), mapTransform_[particleEmitter_], mapEmitter_[particleEmitter_], mapTimer_[particleEmitter_] );
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

	particleEmitterSystem_.render();

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

	// std::unordered_map<std::string, Sprite> playerSprites;

	// playerSprites.emplace("IdleState", Sprite("../img/characters/player_parado_32x32.png", 16, 0.1));
	// playerSprites.emplace("WalkingState", Sprite("../img/characters/player_correndo_32x32.png", 8, 0.1));
	// playerSprites.emplace("JumpingState", Sprite("../img/characters/player_pulando_32x64.png", 5, 0.1));
	// playerSprites.emplace("FallingState", Sprite("../img/characters/player_caindo_34x40.png"));

	// mapRender_.emplace(player_, new RenderComponent(playerSprites));
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

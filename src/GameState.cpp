#include <vector>
#include <unordered_map>

#include "../include/GameState.hpp"
#include "../include/Camera.hpp"
#include "../include/InputHandler.hpp"
#include "../include/FirstLevel.hpp"
#include "../include/TransformComponent.hpp"
#include "../include/StateComponent.hpp"
#include "../include/RenderComponent.hpp"
//#include "../include/Music.hpp"

unsigned int GameState::nextId_ = 0;

GameState::GameState()
: music()
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

	// Criar colisores do terreno
	/*std::vector<std::pair<int, TransformComponent*>> terrainEntities = level_->createTerrain(nextId_);
	for (int i = 0; i < (int)terrainEntities.size(); i++)
	{
		mapTransform_.emplace(terrainEntities[i].first, terrainEntities[i].second);
	}*/
}

void GameState::update(float dt)
{
	InputHandler::getInstance().update();
	music.Update();

	inputSystem_.update(
		player_,
		mapState_,
		mapSpeed_
	);
	gravitySystem_.update(
		dt,
		mapSpeed_,
		mapPhysics_
	);

	particleEmitterSystem_.update(
		dt,
		level_->getCollisionMap(),
		mapTransform_[particleEmitter_],
		mapEmitter_[particleEmitter_],
		mapTimer_[particleEmitter_]
	);

	std::map<int, TransformComponent*> oldTransform = mapTransform_;

	moveSystem_.update(
		dt,
		mapTransform_,
		mapSpeed_
	);
	collisionSystem_.update(
		level_->getCollisionMap(),
		oldTransform,
		mapTransform_,
		mapCollider_,
		mapSpeed_
	);
	stateSystem_.update(
		mapState_,
		mapSpeed_
	);
	renderSystem_.update(
		dt,
		mapState_,
		mapRender_
	);

	Camera::update(dt);

	if(InputHandler::getInstance().quitRequested()) {
		quit = true;
	}
}

void GameState::render()
{
	level_->render();
	renderSystem_.render(mapTransform_, mapState_, mapRender_);
	particleEmitterSystem_.render();
	// collisionSystem_.render();
}

void GameState::handle(StateEventEnum& event)
{

}


void GameState::createPlayer()
{
	player_ = nextId_;
	nextId_++;

	mapTransform_.emplace(player_, new TransformComponent(Rect(352, 100, 32, 32)));
	mapCollider_.emplace(player_, new ColliderComponent(Rect(0, 0, 32, 32)));
	mapState_.emplace(player_, new StateComponent());
	mapPhysics_.emplace(player_, new PhysicsComponent());
	mapSpeed_.emplace(player_, new SpeedComponent());

	// mapRender_.emplace(player_, new RenderComponent(new Sprite("../img/player.png")));
	std::unordered_map<std::string, Sprite> playerSprites;

	playerSprites.emplace("IdleState", Sprite("../img/characters/player_parado_32x32.png", 16, 0.1));
	playerSprites.emplace("WalkingState", Sprite("../img/characters/player_correndo_32x32.png", 8, 0.1));
	playerSprites.emplace("JumpingState", Sprite("../img/characters/player_pulando_32x64.png", 5, 0.1));
	playerSprites.emplace("FallingState", Sprite("../img/characters/player_caindo_34x40.png"));

	mapRender_.emplace(player_, new RenderComponent(playerSprites));

	mapRender_[player_]->setCurrentSprite("IdleState");

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

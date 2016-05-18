#include <vector>

#include "../include/GameState.hpp"
#include "../include/Camera.hpp"
#include "../include/InputHandler.hpp"
#include "../include/FirstLevel.hpp"
#include "../include/TransformComponent.hpp"
#include "../include/StateComponent.hpp"
#include "../include/RenderComponent.hpp"

unsigned int GameState::nextId_ = 0;

GameState::GameState()
{

}

GameState::~GameState()
{
	mapTransform_.clear();
	mapState_.clear();
	mapRender_.clear();
	mapPhysics_.clear();
	mapCollider_.clear();
}

void GameState::create(StateMachine& stateMachine)
{
	stateMachine_ = &stateMachine;
	quit = false;
	// firstLevel_	= new FirstLevel();
	level_ = new FirstLevel();

	createPlayer();

	// Criar colisores do terreno
	std::vector<std::pair<int, TransformComponent*>> terrainEntities = level_->createTerrain(nextId_);
	for (int i = 0; i < (int)terrainEntities.size(); i++)
	{
		mapTransform_.emplace(terrainEntities[i].first, terrainEntities[i].second);
	}
}

void GameState::update(float dt)
{
	InputHandler::getInstance().update();

	gravitySystem_.update(dt, mapTransform_, mapState_, mapPhysics_);
	stateSystem_.update(mapState_);
	moveSystem_.update(mapTransform_, mapState_, mapPhysics_);

	Camera::update(dt);

	if(InputHandler::getInstance().quitRequested()) {
		quit = true;
	}
}

void GameState::render()
{
	level_->render();
	renderSystem_.update(mapTransform_, mapRender_);
}

void GameState::handle(StateEventEnum& event)
{

}


void GameState::createPlayer()
{
	player_ = nextId_;
	nextId_++;

	mapTransform_.emplace(player_, new TransformComponent(Rect(512, 300, 32, 32)));
	mapCollider_.emplace(player_, new ColliderComponent(Rect(512, 300, 32, 32)));
	mapState_.emplace(player_, new StateComponent());
	mapPhysics_.emplace(player_, new PhysicsComponent());
	mapRender_.emplace(player_, new RenderComponent(new Sprite("../img/player.png")));

	Camera::follow(mapTransform_[player_]);
}

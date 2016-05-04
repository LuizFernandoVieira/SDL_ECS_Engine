#include "../include/FirstLevel.hpp"
#include "../include/Camera.hpp"
#include "../include/InputHandler.hpp"
#include "../include/TransformComponent.hpp"
#include "../include/StateComponent.hpp"
#include "../include/RenderComponent.hpp"
#include "../include/Globals.hpp"

unsigned int FirstLevel::nextId_ = 0;

FirstLevel::FirstLevel(State& state)
{
	state_ = &state;

	tileSet_ = new TileSet(Globals::TILE_WIDTH, Globals::TILE_HEIGHT, "../img/ground.png");
	tileMap_ = new TileMap("../map/tileMap.txt", tileSet_);

	createPlayer();

	stateSystem_ = StateSystem();
	renderSystem_ = RenderSystem();
	moveSystem_ = MoveSystem();
}

FirstLevel::~FirstLevel()
{

}

void FirstLevel::create()
{

}

void FirstLevel::update(float dt)
{
	InputHandler::getInstance().update();

	stateSystem_.update(mapState_);
	moveSystem_.update(mapTransform_, mapState_, mapPhysics_);

	if(InputHandler::getInstance().quitRequested()) {
		state_->setQuit(true);
	}
}

void FirstLevel::render()
{
	tileMap_->render(0,0);
	renderSystem_.update(mapTransform_, mapRender_);
}

void FirstLevel::createPlayer()
{
	player_ = nextId_;
	nextId_++;
	mapTransform_.insert(std::pair<int,TransformComponent*> (player_, new TransformComponent()));
	mapState_.insert(std::pair<int,StateComponent*> (player_, new StateComponent()));
	mapPhysics_.insert(std::pair<int,PhysicsComponent*> (player_, new PhysicsComponent()));
	mapRender_.insert(std::pair<int,RenderComponent*> (player_, new RenderComponent(new Sprite("../img/player.png"))));
}

#include "../include/FirstLevel.hpp"
#include "../include/Camera.hpp"
#include "../include/Command.hpp"
#include "../include/InputHandler.hpp"
#include "../include/TransformComponent.hpp"
#include "../include/StateComponent.hpp"
#include "../include/RenderComponent.hpp"

unsigned int FirstLevel::nextId_ = 0;

FirstLevel::FirstLevel(State& state)
{
	state_ = &state;

	createPlayer();

	stateSystem_ = new StateSystem();
	renderSystem_ = new RenderSystem();
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

	stateSystem_->update(mapState_);

	if(InputHandler::getInstance().quitRequested()) {
		state_->setQuit(true);
	}
}

void FirstLevel::render()
{
	renderSystem_->update(mapTransform_, mapRender_);
}

void FirstLevel::createPlayer()
{
	player_ = nextId_;
	nextId_++;
	mapTransform_.insert(std::pair<int,TransformComponent*> (player_, new TransformComponent()));
	mapState_.insert(std::pair<int,StateComponent*> (player_, new StateComponent()));
	mapRender_.insert(std::pair<int,RenderComponent*> (player_, new RenderComponent(new Sprite("../img/god.png"))));
}

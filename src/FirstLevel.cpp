#include "../include/FirstLevel.hpp"
#include "../include/Camera.hpp"
#include "../include/Command.hpp"

#include "../include/TransformComponent.hpp"
#include "../include/RenderComponent.hpp"

unsigned int FirstLevel::nextId_ = 0;

FirstLevel::FirstLevel(State& state)
{
	state_ = &state;
	inputHandler_ =  new InputHandler();

	createPlayer();

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
	std::vector <Command*> commands = inputHandler_->handleInput();


	if (inputHandler_->quitRequested()) {
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
	mapRender_.insert(std::pair<int,RenderComponent*> (player_, new RenderComponent(new Sprite("../img/god.png"))));
}

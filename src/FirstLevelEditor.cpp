#include "../include/FirstLevelEditor.hpp"
#include "../include/Camera.hpp"
#include "../include/Command.hpp"

FirstLevelEditor::FirstLevelEditor(State& state)
{
	state_ = &state;
	// inputHandler_ =  new InputHandler();
	// Camera::setInputHandler(*inputHandler_);
	tileSet_ = new TileSet(32, 32, "../img/ground.png");
	tileMap_ = new TileMap("../map/tileMap.txt", tileSet_);
	god_ = new God(128, 128, *tileMap_);
}

FirstLevelEditor::~FirstLevelEditor()
{

}

void FirstLevelEditor::create()
{

}

void FirstLevelEditor::update(float dt)
{
	// std::vector <Command*> commands = inputHandler_->handleInput();
	// for(auto it = commands.begin(); it != commands.end(); ++it) {
	// 	(*it)->execute(*god_);
	// }

	god_->update(dt);

	Camera::update(dt);

	// if (inputHandler_->quitRequested()) {
	// 	state_->setQuit(true);
	// }
}

void FirstLevelEditor::render()
{
	tileMap_->render(
		Camera::getPosition().getX(), 
		Camera::getPosition().getY()
	);
	god_->render();
}

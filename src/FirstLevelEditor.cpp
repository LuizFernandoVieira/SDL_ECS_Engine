#include "../include/FirstLevelEditor.hpp"
#include "../include/Camera.hpp"

unsigned int FirstLevelEditor::nextId_ = 0;

FirstLevelEditor::FirstLevelEditor(State& state)
{
	state_ = &state;

	tileSet_ = new TileSet(32, 32, "../img/ground.png");
	tileMap_ = new TileMap("../map/tileMap.txt", tileSet_);

	createGod();
	
	// stateSystem_ = new StateSystem();
	renderSystem_ = new RenderSystem();
	editorSystem_ = new LevelEditorSystem(*tileMap_, "../map/tileMap.txt");
}

FirstLevelEditor::~FirstLevelEditor()
{

}

void FirstLevelEditor::create()
{

}

void FirstLevelEditor::update(float dt)
{
	InputHandler::getInstance().update();

	editorSystem_->update(mapTransform_[god_]);
	
	if(InputHandler::getInstance().quitRequested()) {
		state_->setQuit(true);
	}
}

void FirstLevelEditor::render()
{
	tileMap_->render(0,0);
	renderSystem_->update(mapTransform_, mapRender_);
}

void FirstLevelEditor::createGod()
{
	god_ = nextId_;
	nextId_++;
	mapTransform_.insert(std::pair<int,TransformComponent*> (god_, new TransformComponent()));
	// mapState_.insert(std::pair<int,StateComponent*> (god_, new StateComponent()));
	mapRender_.insert(std::pair<int,RenderComponent*> (god_, new RenderComponent(new Sprite("../img/god.png"))));
}

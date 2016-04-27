#include "../include/LevelEditorState.hpp"
#include "../include/InputHandler.hpp"
// #include "../include/Globals.hpp"

LevelEditorState::LevelEditorState() : 
mainPanel_(Rect(0,0,1024, 600), "../img/bgTilePanel.png")
{
	
}

LevelEditorState::~LevelEditorState()
{
}

void LevelEditorState::create(StateMachine& stateMachine)
{
	stateMachine_ = &stateMachine;
	quit = false;
	initGUI();
}

void LevelEditorState::initGUI()
{
	Rect leftRectProportion  = Rect(0, 0, 0.2, 1);
	Rect rightRectProportion = Rect(0.2, 0, 0.8, 1);

	Rect leftRect  = Rect(
		leftRectProportion.x() * mainPanel_.getRect().w() + mainPanel_.getRect().x(),
		leftRectProportion.y() * mainPanel_.getRect().h() + mainPanel_.getRect().y(),
		leftRectProportion.w() * mainPanel_.getRect().w(),
		leftRectProportion.h() * mainPanel_.getRect().h()
	);
	Rect rightRect = Rect(
		rightRectProportion.x() * mainPanel_.getRect().w() + mainPanel_.getRect().x(),
		rightRectProportion.y() * mainPanel_.getRect().h() + mainPanel_.getRect().y(),
		rightRectProportion.w() * mainPanel_.getRect().w(),
		rightRectProportion.h() * mainPanel_.getRect().h()
	);

	Panel leftPanel  = Panel(leftRect, "../img/leftPanelBg.png");
	Panel rightPanel = Panel(rightRect, "../img/leftPanelBg.png");

	mainPanel_.add(leftPanel, leftRectProportion);
	mainPanel_.add(rightPanel, rightRectProportion);
}

void LevelEditorState::update(float dt)
{
	InputHandler::getInstance().update();

	mainPanel_.update();

	// if (InputHandler::getInstance().getScreenResized())
	// {
	// 	mainPanel_.
	// }

	if(InputHandler::getInstance().quitRequested()) {
		setQuit(true);
	}
}

void LevelEditorState::render()
{
	mainPanel_.render();
}

void LevelEditorState::handle(StateEventEnum& event)
{

}
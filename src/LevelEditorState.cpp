#include "../include/LevelEditorState.hpp"
#include "../include/InputHandler.hpp"
#include "../include/Globals.hpp"
#include "../include/Camera.hpp"

LevelEditorState::LevelEditorState() : 
mainPanel_(Rect(0, 0, Globals::WINDOW_WIDTH, Globals::WINDOW_HEIGHT), "../img/bgTilePanel.png")
{
	tileSet_ = new TileSet(32, 32, "../img/ground.png");
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
	Rect leftRectProportion  = Rect(0.0, 0.00, 0.2, 1.0);
	Rect rightRectProportion = Rect(0.2, 0.00, 0.8, 1.0);
	Rect tilesRectProportion = Rect(0.1, 0.05, 0.8, 0.9);

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
	Rect tilesRect = Rect(
		tilesRectProportion.x() * leftRect.w() + leftRect.x(),
		tilesRectProportion.y() * leftRect.h() + leftRect.y(),
		tilesRectProportion.w() * leftRect.w(),
		tilesRectProportion.h() * leftRect.h()
	);

	Panel* leftPanel  = new Panel(leftRect, "../img/leftPanelBg.png");
	Panel* rightPanel = new TilesPanel(*tileSet_, rightRect, "../img/rightPanelBg.png");
	Panel* tilesPanel = new Panel(tilesRect, "../img/god.png");

	mainPanel_.add(*leftPanel, leftRectProportion);
	mainPanel_.add(*rightPanel, rightRectProportion);
	leftPanel->add(*tilesPanel, tilesRectProportion);

	int nTilesRow = tilesRect.w() / (32 + 2);
	int yOffset = 2;

	for(int i=0; i<tileSet_->getNumberOfTiles(); i++) {
		if (i % nTilesRow == 0 && i != 0)
			yOffset += tilesRect.y() + 4;
		Button* btn = new Button(Rect( (i % nTilesRow) * (32+2) + 2 + tilesRect.x(), yOffset + tilesRect.y(), 32, 32), "../img/bg.png");
		tilesPanel->add(*btn, Rect());
	}
}

void LevelEditorState::update(float dt)
{
	InputHandler::getInstance().update();

	if (InputHandler::getInstance().getScreenResized())
	{
		mainPanel_.setRect(Rect(0, 0, Globals::WINDOW_WIDTH, Globals::WINDOW_HEIGHT));
	}

	mainPanel_.update();

	Camera::update(dt);

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
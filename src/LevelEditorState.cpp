#include "../include/LevelEditorState.hpp"
#include "../include/InputHandler.hpp"
#include "../include/Globals.hpp"
#include "../include/Camera.hpp"

LevelEditorState::LevelEditorState() : 
mainPanel_(Rect(0, 0, Globals::WINDOW_WIDTH, Globals::WINDOW_HEIGHT), "../img/bgTilePanel.png")
{
	tileSet_ = new TileSet(Globals::TILE_WIDTH, Globals::TILE_HEIGHT, "../img/ground.png");
	tileMap_ = new TileMap("../map/tileMap.txt", tileSet_);
}

LevelEditorState::~LevelEditorState()
{
	delete tileMap_;
	delete tileSet_;
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

	Rect leftRect  = getPanelRect(mainPanel_.getRect(), leftRectProportion);
	Rect rightRect = getPanelRect(mainPanel_.getRect(), rightRectProportion);
	Rect tilesRect = getPanelRect(leftRect, tilesRectProportion);

	Panel* leftPanel  = new Panel(leftRect, "../img/leftPanelBg.png");
	Panel* rightPanel = new TilesPanel(*tileSet_, *tileMap_, rightRect, "../img/rightPanelBg.png");
	Panel* tilesPanel = new Panel(tilesRect, "../img/god.png");

	mainPanel_.add(*rightPanel, rightRectProportion);
	mainPanel_.add(*leftPanel, leftRectProportion);
	leftPanel->add(*tilesPanel, tilesRectProportion);

	int nTilesRow = tilesRect.w() / (Globals::TILE_WIDTH + 2);
	int curRow = 0;
	int curColumn = 0;

	for(int i=0; i<tileSet_->getNumberOfTiles(); i++, curColumn++)
	{
		if (i % nTilesRow == 0 && i != 0)
		{
			curRow++;
			curColumn = 0;
		}
		Button* btn = new Button(
			Rect(
				curColumn * (Globals::TILE_WIDTH + 2) + 2 + tilesRect.x(),
				curRow * (Globals::TILE_HEIGHT + 2) + 2 + tilesRect.y(),
				Globals::TILE_WIDTH, 
				Globals::TILE_HEIGHT), 
			"../img/ground.png"
		);
		btn->setSpriteClip(
			Rect(
				(i%tileSet_->getNumberOfColumns()) * Globals::TILE_WIDTH, 
				(int)(i/tileSet_->getNumberOfColumns()) * Globals::TILE_HEIGHT, 
				Globals::TILE_WIDTH, 
				Globals::TILE_HEIGHT )
		);
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


Rect LevelEditorState::getPanelRect(Rect& parent, Rect& proportions)
{
	return Rect(
		proportions.x() * parent.w() + parent.x(),
		proportions.y() * parent.h() + parent.y(),
		proportions.w() * parent.w(),
		proportions.h() * parent.h()
	);
}
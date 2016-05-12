#include "../include/LevelEditorState.hpp"
#include "../include/TilesPanel.hpp"
#include "../include/InputHandler.hpp"
#include "../include/Globals.hpp"
#include "../include/Camera.hpp"

LevelEditorState::LevelEditorState() : 
mainPanel_(Rect(0, 0, Globals::WINDOW_WIDTH, Globals::WINDOW_HEIGHT), "../img/bgTilePanel.png")
{
	tileSet_ = new TileSet(Globals::TILE_WIDTH, Globals::TILE_HEIGHT, "../img/ground.png");
	tileMap_ = new TileMap("../map/tileMap.txt", tileSet_);
	selectedTile_ = 0;
	selectedTool_ = ADD;
	selectedLayer_ = 1;
}

LevelEditorState::~LevelEditorState()
{
	delete tileMap_;
	delete tileSet_;
	delete addTilesBtn_;
	delete selectTilesBtn_;
	delete deleteTilesBtn_;
	tileButtons_.clear();
}

void LevelEditorState::create(StateMachine& stateMachine)
{
	stateMachine_ = &stateMachine;
	quit = false;
	initGUI();
}

void LevelEditorState::initGUI()
{
	// Proportion
	Rect leftRectProportion  				= Rect(0.0, 0.000, 0.20, 1.00);
	Rect rightRectProportion 				= Rect(0.2, 0.050, 0.80, 0.95);
	Rect tilesRectProportion 				= Rect(0.1, 0.100, 0.80, 0.80);
	Rect addTilesRectProportion 		= Rect(0.1, 0.025, 0.15, 0.05);
	Rect selectTilesRectProportion 	= Rect(0.3, 0.025, 0.15, 0.05);
	Rect deleteTilesRectProportion  = Rect(0.5, 0.025, 0.15, 0.05);
	Rect layersRectProportion   		= Rect(0.2, 0.000, 0.80, 0.05);

	Rect layerButton1RectProportion = Rect(0.1, 0.100, 0.10, 0.80);
	Rect layerButton2RectProportion = Rect(0.3, 0.100, 0.10, 0.80);
	Rect layerButton3RectProportion =	Rect(0.5, 0.100, 0.10, 0.80);
	Rect layerButton4RectProportion = Rect(0.7, 0.100, 0.10, 0.80);

	// Rect
	Rect leftRect  				= getPanelRect(mainPanel_.getRect(), leftRectProportion);
	Rect rightRect 				= getPanelRect(mainPanel_.getRect(), rightRectProportion);
	Rect tilesRect 				= getPanelRect(leftRect, tilesRectProportion);
	Rect addTilesRect 		= getPanelRect(leftRect, addTilesRectProportion);
	Rect selectTilesRect 	= getPanelRect(leftRect, selectTilesRectProportion);
	Rect deleteTilesRect 	= getPanelRect(leftRect, deleteTilesRectProportion);
	Rect layersRect 			= getPanelRect(mainPanel_.getRect(), layersRectProportion);

	Rect layerButton1Rect = getPanelRect(layersRect, layerButton1RectProportion);
	Rect layerButton2Rect = getPanelRect(layersRect, layerButton2RectProportion);
	Rect layerButton3Rect = getPanelRect(layersRect, layerButton3RectProportion);
	Rect layerButton4Rect = getPanelRect(layersRect, layerButton4RectProportion);

	// Panel
	Panel* leftPanel  = new Panel(leftRect, "../img/leftPanelBg.png");
	Panel* rightPanel = new TilesPanel(*tileSet_, *tileMap_, rightRect, "../img/rightPanelBg.png", selectedTile_, selectedLayer_, selectedTool_);
	Panel* tilesPanel = new Panel(tilesRect, "../img/god.png");

	Panel* layersPanel = new Panel(layersRect, "../img/lp.png");

	// Button
	addTilesBtn_ 		= new Button(addTilesRect, "../img/addTilesBtn.png", tileBtnExecute);
	selectTilesBtn_ = new Button(selectTilesRect, "../img/addTilesBtn.png", tileBtnExecute);
	deleteTilesBtn_ = new Button(deleteTilesRect, "../img/addTilesBtn.png", tileBtnExecute);

	addTilesBtn_->setResizable(true);
	selectTilesBtn_->setResizable(true);
	deleteTilesBtn_->setResizable(true);

	layerButtons_.push_back(new Button(layerButton1Rect, "../img/lb.png", tileBtnExecute));
	layerButtons_.push_back(new Button(layerButton2Rect, "../img/lb.png", tileBtnExecute));
	layerButtons_.push_back(new Button(layerButton3Rect, "../img/lb.png", tileBtnExecute));
	layerButtons_.push_back(new Button(layerButton4Rect, "../img/lb.png", tileBtnExecute));

	layerButtons_[0]->setResizable(true);
	layerButtons_[1]->setResizable(true);
	layerButtons_[2]->setResizable(true);
	layerButtons_[3]->setResizable(true);	

	// Add
	mainPanel_.add(*rightPanel, rightRectProportion);
	mainPanel_.add(*leftPanel, leftRectProportion);
	mainPanel_.add(*layersPanel, layersRectProportion);
	
	leftPanel->add(*tilesPanel, tilesRectProportion);
	leftPanel->add(*addTilesBtn_, addTilesRectProportion);
	leftPanel->add(*selectTilesBtn_, selectTilesRectProportion);
	leftPanel->add(*deleteTilesBtn_, deleteTilesRectProportion);

	layersPanel->add(*layerButtons_[0], layerButton1RectProportion);
	layersPanel->add(*layerButtons_[1], layerButton2RectProportion);
	layersPanel->add(*layerButtons_[2], layerButton3RectProportion);
	layersPanel->add(*layerButtons_[3], layerButton4RectProportion);

	// Tile Buttons
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
			"../img/ground.png",
			tileBtnExecute
		);
		btn->setSpriteClip(
			Rect(
				(i%tileSet_->getNumberOfColumns()) * Globals::TILE_WIDTH, 
				(int)(i/tileSet_->getNumberOfColumns()) * Globals::TILE_HEIGHT, 
				Globals::TILE_WIDTH, 
				Globals::TILE_HEIGHT )
		);
		tilesPanel->add(*btn, Rect());
		tileButtons_.push_back(btn);
	}
}

void LevelEditorState::update(float dt)
{
	InputHandler::getInstance().update();

	if (InputHandler::getInstance().getScreenResized())
	{
		mainPanel_.setRect(Rect(0, 0, Globals::WINDOW_WIDTH, Globals::WINDOW_HEIGHT));
	}

	Camera::update(dt);

	mainPanel_.update();

	if (InputHandler::getInstance().mousePress(LEFT_MOUSE_BUTTON))
	{
		if (addTilesBtn_->getRect().isInside(InputHandler::getInstance().getMouse()))
		{
			selectedTool_ = ADD;
		} else if (selectTilesBtn_->getRect().isInside(InputHandler::getInstance().getMouse())) {
			selectedTool_ = SELECT;
		} else if (deleteTilesBtn_->getRect().isInside(InputHandler::getInstance().getMouse())) {
			selectedTool_ = DELETE;
		} else {
			for (int i = 0; i < (int)tileButtons_.size(); i++)
			{
				if (tileButtons_[i]->getRect().isInside(InputHandler::getInstance().getMouse()))
				{
					// tileButtons_[i]->execute_(this);
					selectedTile_ = i;
					break;
				}
			}
			for (int i = 0; i < layerButtons_.size(); i++)
			{
				if (layerButtons_[i]->getRect().isInside(InputHandler::getInstance().getMouse()))
				{
					// layerButtons_[i]->execute_(this);
					selectedLayer_ = i;
					break;
				}
			}
		}
	}

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


void tileBtnExecute(State* state)
{
	
}
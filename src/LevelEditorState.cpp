#include "../include/LevelEditorState.hpp"
#include "../include/TileMapPanel.hpp"
#include "../include/InputHandler.hpp"
#include "../include/Resources.hpp"
#include "../include/Camera.hpp"

LevelEditorState::LevelEditorState() :
mainPanel_(Rect(0, 0, Resources::WINDOW_WIDTH, Resources::WINDOW_HEIGHT), "../img/bgTilePanel.png")
{
	tileSet_ = new TileSet(Resources::TILE_WIDTH, Resources::TILE_HEIGHT, "../img/maps/test/tile_set.png");
	tileMap_ = new TileMap("../map/tileMap.txt", tileSet_);
	collisionMap_ = new CollisionMap("../map/collisionMap.txt");
	objectMap_ = new ObjectMap("../map/globalObjectMap.xml", "../map/objectMap.xml");
	selectedTile_ = 0;
	selectedTool_ = ADD;
	selectedLayer_ = 1;
	selectedCollision_ = 0;
	selectedTab_ = NULL;
	selectedObject_ = 0;

	// objectMap_->addObject(1, 0, 10, 20);
	// objectMap_->save();
}

LevelEditorState::~LevelEditorState()
{
	delete tileMap_;
	delete tileSet_;
	delete collisionMap_;
	delete objectMap_;
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
	Rect leftRectProportion  							= Rect(0.00, 0.000, 0.20, 1.00);
	Rect rightRectProportion 							= Rect(0.20, 0.050, 0.80, 0.95);
	Rect tileSetAndObjectsRectProportion 	= Rect(0.05, 0.100, 0.90, 0.80);
	Rect addTilesRectProportion 					= Rect(0.10, 0.025, 0.15, 0.05);
	Rect selectTilesRectProportion 				= Rect(0.30, 0.025, 0.15, 0.05);
	Rect deleteTilesRectProportion				= Rect(0.50, 0.025, 0.15, 0.05);
	Rect layersRectProportion   					= Rect(0.20, 0.000, 0.80, 0.05);

	Rect layerButton1RectProportion = Rect(0.1, 0.100, 0.10, 0.80);
	Rect layerButton2RectProportion = Rect(0.3, 0.100, 0.10, 0.80);
	Rect layerButton3RectProportion =	Rect(0.5, 0.100, 0.10, 0.80);
	Rect layerButton4RectProportion = Rect(0.7, 0.100, 0.10, 0.80);

	// Rect
	Rect leftRect  							= getPanelRect(mainPanel_.getRect(), leftRectProportion);
	Rect rightRect 							= getPanelRect(mainPanel_.getRect(), rightRectProportion);
	Rect tileSetAndObjectsRect	= getPanelRect(leftRect, tileSetAndObjectsRectProportion);
	Rect addTilesRect 					= getPanelRect(leftRect, addTilesRectProportion);
	Rect selectTilesRect 				= getPanelRect(leftRect, selectTilesRectProportion);
	Rect deleteTilesRect 				= getPanelRect(leftRect, deleteTilesRectProportion);
	Rect layersRect 						= getPanelRect(mainPanel_.getRect(), layersRectProportion);

	Rect layerButton1Rect = getPanelRect(layersRect, layerButton1RectProportion);
	Rect layerButton2Rect = getPanelRect(layersRect, layerButton2RectProportion);
	Rect layerButton3Rect = getPanelRect(layersRect, layerButton3RectProportion);
	Rect layerButton4Rect = getPanelRect(layersRect, layerButton4RectProportion);

	// Panel
	Panel* leftPanel  = new Panel(leftRect, "../img/interface/editor/left_panel.png");
	tileSetAndObjectsPanel_ = new TileSetAndObjectsPanel(tileSetAndObjectsRect, "../img/interface/editor/tile_set_panel.png", objectMap_, selectedObject_);
	selectedTab_ = &tileSetAndObjectsPanel_->getSelectedTab();
	Panel* rightPanel = new TileMapPanel(*tileSet_, *tileMap_, *collisionMap_, *objectMap_, rightRect, "../img/interface/editor/tile_map_panel.png", selectedTile_, selectedLayer_, selectedCollision_, (int*)selectedTab_, selectedObject_, selectedTool_);

	Panel* layersPanel = new Panel(layersRect, "../img/interface/editor/tile_set_panel.png");

	// Button
	addTilesBtn_ 		= new Button(addTilesRect, "../img/interface/editor/icone_03.png"/*, tileBtnExecute*/);
	selectTilesBtn_ = new Button(selectTilesRect, "../img/interface/editor/icone_04.png"/*, tileBtnExecute*/);
	deleteTilesBtn_ = new Button(deleteTilesRect, "../img/interface/editor/icone_05.png"/*, tileBtnExecute*/);

	addTilesBtn_->setResizable(true);
	selectTilesBtn_->setResizable(true);
	deleteTilesBtn_->setResizable(true);

	layerButtons_.push_back(new Button(layerButton1Rect, "../img/interface/editor/btn_4.png"/*, tileBtnExecute*/));
	layerButtons_.push_back(new Button(layerButton2Rect, "../img/interface/editor/btn_5.png"/*, tileBtnExecute*/));
	layerButtons_.push_back(new Button(layerButton3Rect, "../img/interface/editor/btn_6.png"/*, tileBtnExecute*/));
	layerButtons_.push_back(new Button(layerButton4Rect, "../img/interface/editor/btn_7.png"/*, tileBtnExecute*/));

	layerButtons_[0]->setResizable(true);
	layerButtons_[1]->setResizable(true);
	layerButtons_[2]->setResizable(true);
	layerButtons_[3]->setResizable(true);

	//                    pq caralhos esse rect vvvvv nao eh alterado??
	collisionButtons_.emplace_back(new Button(Rect(0,0,32,32), "../img/interface/editor/btn_5.png"));
	collisionButtons_.emplace_back(new Button(Rect(0,0,32,32), "../img/interface/editor/btn_collision_1.png"));
	collisionButtons_.emplace_back(new Button(Rect(0,0,32,32), "../img/interface/editor/btn_collision_2.png"));

	// Add
	mainPanel_.add(*rightPanel, rightRectProportion);
	mainPanel_.add(*leftPanel, leftRectProportion);
	mainPanel_.add(*layersPanel, layersRectProportion);

	leftPanel->add(*tileSetAndObjectsPanel_, tileSetAndObjectsRectProportion);
	leftPanel->add(*addTilesBtn_, addTilesRectProportion);
	leftPanel->add(*selectTilesBtn_, selectTilesRectProportion);
	leftPanel->add(*deleteTilesBtn_, deleteTilesRectProportion);

	layersPanel->add(*layerButtons_[0], layerButton1RectProportion);
	layersPanel->add(*layerButtons_[1], layerButton2RectProportion);
	layersPanel->add(*layerButtons_[2], layerButton3RectProportion);
	layersPanel->add(*layerButtons_[3], layerButton4RectProportion);

	// Tile Buttons
	int nTilesRow = tileSetAndObjectsRect.w() / (Resources::TILE_WIDTH + 2);
	int curRow = 0;
	int curColumn = 0;

	for(int i = 0; i < tileSet_->getNumberOfTiles(); i++, curColumn++)
	{
		if (i % nTilesRow == 0 && i != 0)
		{
			curRow++;
			curColumn = 0;
		}
		Button* btn = new Button(
			Rect(
				curColumn * (Resources::TILE_WIDTH + 2) + 2 + tileSetAndObjectsRect.x(),
				curRow * (Resources::TILE_HEIGHT + 2) + 2 + tileSetAndObjectsRect.y(),
				Resources::TILE_WIDTH,
				Resources::TILE_HEIGHT),
			"../img/maps/test/tile_set.png"//,
			// tileBtnExecute
		);
		btn->setSpriteClip(
			Rect(
				(i%tileSet_->getNumberOfColumns()) * Resources::TILE_WIDTH,
				(int)(i/tileSet_->getNumberOfColumns()) * Resources::TILE_HEIGHT,
				Resources::TILE_WIDTH,
				Resources::TILE_HEIGHT )
		);
		tileSetAndObjectsPanel_->addButton(*btn, TileSetAndObjectsPanel::Tab::TILES);
		tileButtons_.emplace_back(btn);
	}

	// Collision buttons
	curRow = 0;
	curColumn = 0;
	for (int i = 0; i < (int)collisionButtons_.size(); i++, curColumn++)
	{
		if (i % nTilesRow == 0 && i != 0)
		{
			curRow++;
			curColumn = 0;
		}
		collisionButtons_[i]->setRect(
			Rect(
				curColumn * (Resources::TILE_WIDTH + 2) + 2 + tileSetAndObjectsRect.x(),
				curRow * (Resources::TILE_HEIGHT + 2) + 2 + tileSetAndObjectsRect.y(),
				Resources::TILE_WIDTH,
				Resources::TILE_HEIGHT)
		);

		tileSetAndObjectsPanel_->addButton(*collisionButtons_[i], TileSetAndObjectsPanel::Tab::COLLISION);
	}
}

void LevelEditorState::update(float dt)
{
	InputHandler::getInstance().update();

	if (InputHandler::getInstance().getScreenResized())
	{
		mainPanel_.setRect(Rect(0, 0, Resources::WINDOW_WIDTH, Resources::WINDOW_HEIGHT));
	}

	Camera::update(dt);

	std::cout << tileButtons_[0]->getRect().x() << ", " << tileButtons_[0]->getRect().y() << ", " << tileButtons_[0]->getRect().w() << ", " << tileButtons_[0]->getRect().h() << std::endl;

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
			if (*selectedTab_ == TileSetAndObjectsPanel::Tab::TILES)
			{
				for (int i = 0; i < (int)tileButtons_.size(); i++)
				{
					if (tileButtons_[i]->getRect().isInside(InputHandler::getInstance().getMouse()))
					{
						// tileButtons_[i]->execute_(this);
						selectedTile_ = i;
						break;
					}
				}
			}
			else if (*selectedTab_ == TileSetAndObjectsPanel::Tab::COLLISION)
			{
				for (int i = 0; i < (int)collisionButtons_.size(); i++)
				{
					if (collisionButtons_[i]->getRect().isInside(InputHandler::getInstance().getMouse()))
					{
						selectedCollision_ = i;
						break;
					}
				}
			}
			for (int i = 0; i < (int)layerButtons_.size(); i++)
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


// void tileBtnExecute(State* state)
// {
//
// }

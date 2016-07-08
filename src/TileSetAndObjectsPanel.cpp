#include "../include/TileSetAndObjectsPanel.hpp"
#include "../include/Resources.hpp"
#include "../include/InputHandler.hpp"
#include "../include/Game.hpp"

TileSetAndObjectsPanel::TileSetAndObjectsPanel(Rect rect, std::string imgPath, ObjectMap* objectMap, int& selectedObject) :
	Panel(rect, imgPath), scroll_(0), selectedObject_(selectedObject),
	objectName_("../font/arial.ttf", 16, Text::TextStyle::BLENDED, "", Colors::black)
{
	selectedTab_ = TILES;
	objectMap_ = objectMap;

	createButtons();
	objectName_.setPos(rect_.x() + rect_.w() / 2, rect_.y() + 35);
	createObjectSprite();
}

TileSetAndObjectsPanel::~TileSetAndObjectsPanel()
{
	tileButtons_.clear();
}

void TileSetAndObjectsPanel::createButtons()
{
	// Criar botoes das abas
	Rect tileButtonProportions = Rect(0.05, 0.0, 0.3, 0.05);
	Rect collisionButtonProportions = Rect(0.35, 0.0, 0.3, 0.05);
	Rect objectButtonProportions = Rect(0.65, 0.0, 0.3, 0.05);

	Rect tileButtonRect = Rect(
		tileButtonProportions.x() * rect_.w() + rect_.x(),
		tileButtonProportions.y() * rect_.h() + rect_.y(),
		tileButtonProportions.w() * rect_.w(),
		tileButtonProportions.h() * rect_.h()
	);
	Rect collisionButtonRect = Rect(
		collisionButtonProportions.x() * rect_.w() + rect_.x(),
		collisionButtonProportions.y() * rect_.h() + rect_.y(),
		collisionButtonProportions.w() * rect_.w(),
		collisionButtonProportions.h() * rect_.h()
	);
	Rect objectButtonRect = Rect(
		objectButtonProportions.x() * rect_.w() + rect_.x(),
		objectButtonProportions.y() * rect_.h() + rect_.y(),
		objectButtonProportions.w() * rect_.w(),
		objectButtonProportions.h() * rect_.h()
	);

	Button* tileButton   = new Button(tileButtonRect, "../img/interface/editor/tiles.png"/*, nullptr*/);
	Button* collisionButton = new Button(collisionButtonRect, "../img/interface/editor/cols.png"/*, nullptr*/);
	Button* objectButton = new Button(objectButtonRect, "../img/interface/editor/objs.png"/*, nullptr*/);

	tileButton->setResizable(true);
	collisionButton->setResizable(true);
	objectButton->setResizable(true);

	add(*tileButton, tileButtonProportions);
	add(*collisionButton, collisionButtonProportions);
	add(*objectButton, objectButtonProportions);

	// Somar a altura dos botoes de tabs aos outros botoes
	tabButtonHeight_ = tileButtonRect.y();

	// Criar botoes de previous e next object
	previousObjectProportions = Rect(0.05, 0.5, 0.1, 0.04);
	nextObjectProportions = Rect(0.85, 0.5, 0.1, 0.04);

	Rect previousButtonRect = Rect(
		previousObjectProportions.x() * rect_.w() + rect_.x(),
		previousObjectProportions.y() * rect_.h() + rect_.y(),
		previousObjectProportions.w() * rect_.w(),
		previousObjectProportions.h() * rect_.h()
	);
	Rect nextButtonRect = Rect(
		nextObjectProportions.x() * rect_.w() + rect_.x(),
		nextObjectProportions.y() * rect_.h() + rect_.y(),
		nextObjectProportions.w() * rect_.w(),
		nextObjectProportions.h() * rect_.h()
	);

	previousObject   = new Button(previousButtonRect, "../img/leftBtn.png"/*, nullptr*/);
	nextObject = new Button(nextButtonRect, "../img/rightBtn.png"/*, nullptr*/);

	previousObject->setResizable(true);
	nextObject->setResizable(true);

	objectSp_ = NULL;
	createObjectSprite();
}

void TileSetAndObjectsPanel::createObjectSprite()
{
	if (objectSp_ != NULL)
		delete objectSp_;

	ObjectInfo objectInfo = objectMap_->getGlobalObject(selectedObject_);
	objectName_.setText(objectInfo.name);
	if (!objectInfo.filename.empty())
		objectSp_ = new StaticSprite(objectInfo.filename.c_str(), objectInfo.frameCount, objectInfo.frameTime);
	else
		objectSp_ = new StaticSprite("../img/interface/editor/btn_4.png");

	// escala do sprite, sem mudar proporcao largura/altura
	// objectSp_->setScaleX(1.0);
	// objectSp_->setScaleY(1.0);
	float proportion = (float)objectSp_->getWidth() / (float)objectSp_->getHeight();
	float scaleX = 0.9 * rect_.w() / (float)objectSp_->getWidth();
	objectSp_->setScaleX(scaleX);
	objectSp_->setScaleY(scaleX / proportion);
}

void TileSetAndObjectsPanel::update()
{
	Panel::update();
	InputHandler& input = InputHandler::getInstance();

	if (input.mouseWheelScroll() && rect_.isInside(input.getMouse()))
	{
		scroll_ += input.mouseWheelAmount() * SCROLL_SPEED * Game::getInstance().getDeltaTime();
		if (scroll_ < 0) scroll_ = 0;
	}

	if (input.getScreenResized())
	{
		resize();
	}

	if (input.mousePress(LEFT_MOUSE_BUTTON))
	{
		if (buttons_[0].first->getRect().isInside(input.getMouse()))
		{
			selectedTab_ = TILES;
		}
		else if (buttons_[1].first->getRect().isInside(input.getMouse()))
		{
			selectedTab_ = COLLISION;
		}
		else if (buttons_[2].first->getRect().isInside(input.getMouse()))
		{
			selectedTab_ = OBJECTS;
		}
		else if (selectedTab_ == OBJECTS)
		{
			if (previousObject->getRect().isInside(input.getMouse()))
			{
				selectedObject_ = ((selectedObject_ - 1 + objectMap_->globalSize()) % objectMap_->globalSize());	// decrementa dentro do range
				createObjectSprite();
			}
			else if (nextObject->getRect().isInside(input.getMouse()))
			{
				selectedObject_ = ((selectedObject_ + 1) % objectMap_->globalSize());	// incrementa dentro do range
				createObjectSprite();
			}
		}
	}
}

void TileSetAndObjectsPanel::render()
{
	Panel::render();
	if (selectedTab_ == TILES)
	{
		for(int i = 0; i < (int)tileButtons_.size(); i++)
		{
			if ( (rect_ + Vec2(0,scroll_)).isInside(tileButtons_[i]->getRect().getCenter()) )
			tileButtons_[i]->render(-scroll_);
		}
	}
	else if (selectedTab_ == OBJECTS)
	{
		objectName_.setPos(rect_.x() + rect_.w() / 2, rect_.y() + 35);
		objectName_.render();
		objectSp_->render(rect_.x() + 10, rect_.y() + 50);

		previousObject->render();
		nextObject->render();
	}
	else if (selectedTab_ == COLLISION)
	{
		for (int i = 0; i < (int)collisionButtons_.size(); i++)
		{
			collisionButtons_[i]->render();
		}
	}
}

// void TileSetAndObjectsPanel::addButton(Button& button, Tab tab)
// {
// 	tileButtons_.emplace_back(std::pair<Button*, Tab>(&button, tab));
// 	button.setRect(button.getRect() + Vec2(0, tabButtonHeight_));
// }
void TileSetAndObjectsPanel::addButton(Button& button, Tab tab)
{
	button.setRect(button.getRect() + Vec2(0, tabButtonHeight_));
	if (tab == TILES)
		tileButtons_.emplace_back(&button);
	else if (tab == COLLISION)
		collisionButtons_.emplace_back(&button);
}

TileSetAndObjectsPanel::Tab& TileSetAndObjectsPanel::getSelectedTab()
{
	return selectedTab_;
}

int& TileSetAndObjectsPanel::getScroll()
{
	return scroll_;
}

void TileSetAndObjectsPanel::resize()
{
	// resize dos botoes previous e next
	previousObject->setRect(Rect(
			previousObjectProportions.x() * rect_.w() + rect_.x(),
			previousObjectProportions.y() * rect_.h() + rect_.y(),
			previousObjectProportions.w() * rect_.w(),
			previousObjectProportions.h() * rect_.h()
	));
	nextObject->setRect(Rect(
			nextObjectProportions.x() * rect_.w() + rect_.x(),
			nextObjectProportions.y() * rect_.h() + rect_.y(),
			nextObjectProportions.w() * rect_.w(),
			nextObjectProportions.h() * rect_.h()
	));

	// resize dos botoes de tiles
	int nTilesRow = rect_.w() / (Resources::TILE_WIDTH + 2);
	// if (nTilesRow == 0)
	// 	nTilesRow = 1;
	int curRow = 0;
	int curColumn = 0;

	// Gambiarra pra atualizar a altura dos botoes
	tabButtonHeight_ = buttons_[0].first->getRect().y();

	for(int i = 0; i < (int)tileButtons_.size(); i++, curColumn++ )
	{
		if (i % nTilesRow == 0 && i != 0)
		{
			curRow++;
			curColumn = 0;
		}
		tileButtons_[i]->setRect(
			Rect(
				curColumn * (Resources::TILE_WIDTH + 2) + 2 + rect_.x(),
				curRow * (Resources::TILE_HEIGHT + 2) + 2 + rect_.y() + tabButtonHeight_,
				Resources::TILE_WIDTH,
				Resources::TILE_HEIGHT)
		);
	}

	// resize dos botoes de collision
	curRow = 0;
	curColumn = 0;

	for(int i = 0; i < (int)collisionButtons_.size(); i++, curColumn++ )
	{
		if (i % nTilesRow == 0 && i != 0)
		{
			curRow++;
			curColumn = 0;
		}
		collisionButtons_[i]->setRect(
			Rect(
				curColumn * (Resources::TILE_WIDTH + 2) + 2 + rect_.x(),
				curRow * (Resources::TILE_HEIGHT + 2) + 2 + rect_.y() + tabButtonHeight_,
				Resources::TILE_WIDTH,
				Resources::TILE_HEIGHT)
		);
	}
}

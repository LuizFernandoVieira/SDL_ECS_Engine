#include "../include/TileSetAndObjectsPanel.hpp"
#include "../include/Globals.hpp"
#include "../include/InputHandler.hpp"

TileSetAndObjectsPanel::TileSetAndObjectsPanel(Rect rect, std::string imgPath) :
  Panel(rect, imgPath)
{
  selectedTab_ = TILES;

  Rect tileButtonProportions = Rect(0.1, 0.0, 0.4, 0.05);
  Rect objectButtonProportions = Rect(0.5, 0.0, 0.4, 0.05);

  Rect tileButtonRect = Rect(
		tileButtonProportions.x() * rect_.w() + rect_.x(),
		tileButtonProportions.y() * rect_.h() + rect_.y(),
		tileButtonProportions.w() * rect_.w(),
		tileButtonProportions.h() * rect_.h()
	);
  Rect objectButtonRect = Rect(
  	objectButtonProportions.x() * rect_.w() + rect_.x(),
  	objectButtonProportions.y() * rect_.h() + rect_.y(),
  	objectButtonProportions.w() * rect_.w(),
  	objectButtonProportions.h() * rect_.h()
  );

  Button* tileButton   = new Button(tileButtonRect, "../img/lb.png"/*, nullptr*/);
  Button* objectButton = new Button(objectButtonRect, "../img/lp.png"/*, nullptr*/);

  tileButton->setResizable(true);
  objectButton->setResizable(true);

  add(*tileButton, tileButtonProportions);
  add(*objectButton, objectButtonProportions);

  // Somar a altura dos botoes de tabs aos outros botoes
  tabButtonHeight = tileButtonRect.y();
}

TileSetAndObjectsPanel::~TileSetAndObjectsPanel()
{
  tileButtons_.clear();
}

void TileSetAndObjectsPanel::update()
{
  Panel::update();

  if (InputHandler::getInstance().getScreenResized())
  {
    int nTilesRow = rect_.w() / (Globals::TILE_WIDTH + 2);
    if (nTilesRow == 0)
      nTilesRow = 1;
		int curRow = 0;
		int curColumn = 0;
		int i = 0;

    // Gambiarra pra atualizar a altura dos botoes
    tabButtonHeight = buttons_[0].first->getRect().y();

		for(auto it=tileButtons_.begin(); it!=tileButtons_.end(); ++it, i++, curColumn++ )
		{
      if (i % nTilesRow == 0 && i != 0)
      {
        curRow++;
        curColumn = 0;
      }
      it->first->setRect(
        Rect(
          curColumn * (Globals::TILE_WIDTH + 2) + 2 + rect_.x(),
          curRow * (Globals::TILE_HEIGHT + 2) + 2 + rect_.y() + tabButtonHeight,
          Globals::TILE_WIDTH,
          Globals::TILE_HEIGHT)
      );
    }
  }

  if (InputHandler::getInstance().mousePress(LEFT_MOUSE_BUTTON))
  {
    // if (buttons_[0].first->getRect().)
  }
}

void TileSetAndObjectsPanel::render()
{
  Panel::render();
  for(auto it=tileButtons_.begin(); it!=tileButtons_.end(); ++it)
  {
    it->first->render();
  }
}

void TileSetAndObjectsPanel::addButton(Button& button, Tab tab)
{
  tileButtons_.emplace_back(std::pair<Button*, Tab>(&button, tab));
  button.setRect(button.getRect() + Vec2(0, tabButtonHeight));
}


TileSetAndObjectsPanel::Tab TileSetAndObjectsPanel::getSelectedTab()
{
  return selectedTab_;
}

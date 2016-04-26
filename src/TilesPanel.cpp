#include "../include/TilesPanel.hpp"
#include "../include/InputHandler.hpp"

TilesPanel::TilesPanel(int screenWidth, int screenHeight) : border_("../img/bgTilePanel.png")
{
	screenWidth_ = screenWidth;
	screenHeight_ = screenHeight;

	width_ = 0.2;
	border_.setScaleX( (float)screenWidth_ * width_ / (float)border_.getWidth() );
	border_.setScaleY( (float)screenHeight_ / (float)border_.getHeight() );
}


void TilesPanel::update()
{
	if (InputHandler::getInstance().getScreenResized())
	{
		screenWidth_ = InputHandler::getInstance().getScreenWidth();
		screenHeight_ = InputHandler::getInstance().getScreenHeight();
		border_.setScaleX(1.0);
		border_.setScaleY(1.0);
		border_.setScaleX( (float)screenWidth_ * width_ / (float)border_.getWidth() );
		border_.setScaleY( (float)screenHeight_ * height_ / (float)border_.getHeight() );
	}
}


void TilesPanel::render()
{
	border_.render(0, 0);
}
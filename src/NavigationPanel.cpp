// #include "../include/NavigationPanel.hpp"
// #include "../include/InputHandler.hpp"

// NavigationPanel::NavigationPanel(int screenWidth, int screenHeight) : border_("../img/leftPanelBg.png")
// {
// 	screenWidth_ = screenWidth;
// 	screenHeight_ = screenHeight;

// 	width_ = 0.2;
// 	border_.setScaleX( (float)screenWidth_ * width_ / (float)border_.getWidth() );
// 	border_.setScaleY( (float)screenHeight_ / (float)border_.getHeight() );
// }


// void NavigationPanel::update()
// {
// 	if (InputHandler::getInstance().getScreenResized())
// 	{
// 		screenWidth_ = InputHandler::getInstance().getScreenWidth();
// 		screenHeight_ = InputHandler::getInstance().getScreenHeight();
// 		border_.setScaleX(1.0);
// 		border_.setScaleY(1.0);
// 		border_.setScaleX( (float)screenWidth_ * width_ / (float)border_.getWidth() );
// 		border_.setScaleY( (float)screenHeight_ / (float)border_.getHeight() );
// 	}
// }


// void NavigationPanel::render()
// {
// 	border_.render(0, 0);
// }
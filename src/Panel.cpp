#include "../include/Panel.hpp"
#include "../include/InputHandler.hpp"

Panel::Panel(Rect& rect, std::string imgPath) : rect_(rect), bg_(imgPath)
{
	
}


void Panel::update()
{
	if (InputHandler::getInstance().getScreenResized())
	{
		screenWidth_ = InputHandler::getInstance().getScreenWidth();
		screenHeight_ = InputHandler::getInstance().getScreenHeight();
		bg_.setScaleX(1.0);
		bg_.setScaleY(1.0);
		bg_.setScaleX( (float)screenWidth_ * width_ / (float)bg_.getWidth() );
		bg_.setScaleY( (float)screenHeight_ * height_ / (float)bg_.getHeight() );

		for(auto it=panels_.begin(); it!=panels_.end(); ++it ) {
			
		}
		for(auto it=buttons_.begin(); it!=buttons_.end(); ++it ) {
			
		}
	}

	for(auto it=panels_.begin(); it!=panels_.end(); ++it ) {
		it->update();
	}
	for(auto it=buttons_.begin(); it!=buttons_.end(); ++it ) {
		it->update();	
	}
}

void Panel::render()
{
	bg_.render(rect.x, rect.y);
	for(auto it=panels_.begin(); it!=panels_.end(); ++it ) {
		it->render();
	}
	for(auto it=buttons_.begin(); it!=buttons_.end(); ++it ) {
		it->render();
	}
}

void Panel::add(Panel& panel)
{
	panels_.emplace_back(panel);
}

void Panel::add(Button& button)
{
	buttons_.emplace_back(button);
}
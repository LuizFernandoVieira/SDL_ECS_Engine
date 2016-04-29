#include "../include/Panel.hpp"
#include "../include/InputHandler.hpp"

Panel::Panel(Rect rect, std::string imgPath) : rect_(rect), bg_(imgPath.c_str())
{
	bg_.setScaleX( rect_.w() / (float)bg_.getWidth() );
	bg_.setScaleY( rect_.h() / (float)bg_.getHeight() );
}


void Panel::update()
{
	if (InputHandler::getInstance().getScreenResized())
	{
		for(auto it=panels_.begin(); it!=panels_.end(); ++it )
		{
			Rect newPanelSize  = Rect(
				it->second.x() * rect_.w() + rect_.x(),
				it->second.y() * rect_.h() + rect_.y(),
				it->second.w() * rect_.w(),
				it->second.h() * rect_.h()
			);
			it->first->setRect(newPanelSize);
		}
		// for(auto it=buttons_.begin(); it!=buttons_.end(); ++it ) {
			
		// }
	}

	for(auto it=panels_.begin(); it!=panels_.end(); ++it ) {
		it->first->update();
	}
	// for(auto it=buttons_.begin(); it!=buttons_.end(); ++it ) {
	// 	it->update();	
	// }
}

void Panel::render()
{
	bg_.render(rect_.x(), rect_.y());
	for(auto it=panels_.begin(); it!=panels_.end(); ++it ) {
		it->first->render();
	}
	// for(auto it=buttons_.begin(); it!=buttons_.end(); ++it ) {
	// 	it->render();
	// }
}

void Panel::add(Panel& panel, Rect rect)
{
	panels_.emplace_back(std::pair<Panel*, Rect>(&panel, rect));
}

void Panel::add(Button button)
{
	buttons_.emplace_back(button);
}

Rect Panel::getRect() {
	return rect_;
}

void Panel::setRect(Rect rect)
{
	rect_ = rect;
	bg_.setScaleX(1.0);
	bg_.setScaleY(1.0);
	bg_.setScaleX( rect_.w() / (float)bg_.getWidth() );
	bg_.setScaleY( rect_.h() / (float)bg_.getHeight() );
}
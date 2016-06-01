#include "../include/Panel.hpp"
#include "../include/InputHandler.hpp"
#include "../include/Resources.hpp"

Panel::Panel(Rect rect, std::string imgPath) : rect_(rect), bg_(imgPath.c_str())
{
	bg_.setScaleX( rect_.w() / (float)bg_.getWidth() );
	bg_.setScaleY( rect_.h() / (float)bg_.getHeight() );
}


Panel::~Panel()
{
	panels_.clear();
	buttons_.clear();
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

		int nTilesRow = rect_.w() / (Resources::TILE_WIDTH + 2);
		int curRow = 0;
		int curColumn = 0;
		int i = 0;

		for(auto it=buttons_.begin(); it!=buttons_.end(); ++it, i++, curColumn++ )
		{
			if (it->first->isResizable())
			{
				Rect newButtonSize = Rect(
					it->second.x() * rect_.w() + rect_.x(),
					it->second.y() * rect_.h() + rect_.y(),
					it->second.w() * rect_.w(),
					it->second.h() * rect_.h()
				);
				it->first->setRect(newButtonSize);
			}
			else
			{
				if (i % nTilesRow == 0 && i != 0)
				{
					curRow++;
					curColumn = 0;
				}
				it->first->setRect(
					Rect( 
						curColumn * (Resources::TILE_WIDTH + 2) + 2 + rect_.x(),
						curRow * (Resources::TILE_HEIGHT + 2) + 2 + rect_.y(),
						Resources::TILE_WIDTH, 
						Resources::TILE_HEIGHT)
				);
			}
		}
	}

	for(auto it=panels_.begin(); it!=panels_.end(); ++it ) {
		it->first->update();
	}
	for(auto it=buttons_.begin(); it!=buttons_.end(); ++it ) {
		it->first->update();	
	}
}

void Panel::render()
{
	bg_.render(rect_.x(), rect_.y());
	for(auto it=panels_.begin(); it!=panels_.end(); ++it ) {
		it->first->render();
	}
	for(auto it=buttons_.begin(); it!=buttons_.end(); ++it ) {
		it->first->render();
	}
}

void Panel::add(Panel& panel, Rect rect)
{
	panels_.emplace_back(std::pair<Panel*, Rect>(&panel, rect));
}

void Panel::add(Button& button, Rect rect)
{
	buttons_.emplace_back(std::pair<Button*, Rect>(&button, rect));
}

Rect& Panel::getRect() {
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
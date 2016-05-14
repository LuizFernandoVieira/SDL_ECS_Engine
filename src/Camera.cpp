#include "../include/Camera.hpp"
#include "../include/InputHandler.hpp"
#include "../include/Globals.hpp"

// InputHandler* Camera::inputHandler_;
TransformComponent* Camera::focus_;
Vec2 Camera::pos_;
Vec2 Camera::speed_;

void Camera::follow(TransformComponent* focus)
{
	focus_ = focus;
}

void Camera::unfollow()
{
	focus_ = NULL;
}

void Camera::update(float dt)
{
	if(focus_ != NULL)
	{
		// pos_ = focus_->getRect().getCenter() + Vec2(-512,-300);
		// pos_ = Vec2 (focus_->rect_.getCenter().x() - Globals::WINDOW_WIDTH / 2,
									// focus_->rect_.getCenter().y() - Globals::WINDOW_HEIGHT / 2);
		pos_ = focus_->rect_->getCenter() - Vec2(Globals::WINDOW_WIDTH / 2, Globals::WINDOW_HEIGHT / 2);
	} 
	else 
	{
		// if(inputHandler_ != NULL)
		// {
			if(InputHandler::getInstance().isKeyDown(LEFT_ARROW_KEY))
			{
				speed_ = Vec2(-CAMERA_SPEED * dt, 0);
				// pos_ = Vec2(pos_.getX()+speed_.getX(), pos_.getY()+speed_.getY());
				pos_   = pos_ + speed_;
			}

			if(InputHandler::getInstance().isKeyDown(RIGHT_ARROW_KEY))
			{
				speed_ = Vec2(CAMERA_SPEED * dt, 0);
				// pos_ = Vec2(pos_.getX()+speed_.getX(), pos_.getY()+speed_.getY());
				pos_   = pos_ + speed_;
			}

			if(InputHandler::getInstance().isKeyDown(UP_ARROW_KEY))
			{
				speed_ = Vec2(0, -CAMERA_SPEED * dt);
				// pos_ = Vec2(pos_.getX()+speed_.getX(), pos_.getY()+speed_.getY());
				pos_   = pos_ + speed_;
			}

			if(InputHandler::getInstance().isKeyDown(DOWN_ARROW_KEY))
			{
				speed_ = Vec2(0, CAMERA_SPEED * dt);
				// pos_ = Vec2(pos_.getX()+speed_.getX(), pos_.getY()+speed_.getY());
				pos_   = pos_ + speed_;
			}
		}
	
}

Vec2 Camera::getPosition()
{
	return pos_;
}

// void Camera::setInputHandler(InputHandler& inputHandler)
// {
// 	inputHandler_ = &inputHandler;
// }
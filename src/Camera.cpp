#include "../include/Camera.hpp"

InputHandler* Camera::inputHandler_;
GameObject* Camera::focus_;
Vec2 Camera::pos_;
Vec2 Camera::speed_;

void Camera::follow(GameObject& focus)
{
	focus_ = &focus;
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
		pos_ = Vec2 (focus_->getRect().getCenter().x() - 512,
									focus_->getRect().getCenter().y() - 300);
	} 
	else 
	{
		if(inputHandler_ != NULL)
		{
			// if(inputHandler_->isKeyDown(LEFT_ARROW_KEY))
			// {
			// 	speed_ = Vec2(-CAMERA_SPEED * dt, 0);
			// 	pos_ = Vec2(pos_.getX()+speed_.getX(), pos_.getY()+speed_.getY());
			// 	// pos_   = pos_ + speed_;
			// }

			// if(inputHandler_->isKeyDown(RIGHT_ARROW_KEY))
			// {
			// 	speed_ = Vec2(CAMERA_SPEED * dt, 0);
			// 	pos_ = Vec2(pos_.getX()+speed_.getX(), pos_.getY()+speed_.getY());
			// 	// pos_   = pos_ + speed_;
			// }

			// if(inputHandler_->isKeyDown(UP_ARROW_KEY))
			// {
			// 	speed_ = Vec2(0, -CAMERA_SPEED * dt);
			// 	pos_ = Vec2(pos_.getX()+speed_.getX(), pos_.getY()+speed_.getY());
			// 	// pos_   = pos_ + speed_;
			// }

			// if(inputHandler_->isKeyDown(DOWN_ARROW_KEY))
			// {
			// 	speed_ = Vec2(0, CAMERA_SPEED * dt);
			// 	pos_ = Vec2(pos_.getX()+speed_.getX(), pos_.getY()+speed_.getY());
			// 	// pos_   = pos_ + speed_;
			// }
		}
	}
}

Vec2 Camera::getPosition()
{
	return pos_;
}

void Camera::setInputHandler(InputHandler& inputHandler)
{
	inputHandler_ = &inputHandler;
}
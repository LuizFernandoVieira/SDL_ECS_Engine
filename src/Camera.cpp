#include "../include/Camera.hpp"
#include "../include/Point.hpp"

InputHandler* Camera::inputHandler_;
GameObject* Camera::focus_;
Point Camera::pos_;
Point Camera::speed_;

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
		// pos_ = focus_->getRect().getCenter() + Point(-512,-300);
		pos_ = Point (focus_->getRect().getCenter().getX() - 512,
									focus_->getRect().getCenter().getY() - 300);
	} 
	else 
	{
		if(inputHandler_ != NULL)
		{
			// if(inputHandler_->isKeyDown(LEFT_ARROW_KEY))
			// {
			// 	speed_ = Point(-CAMERA_SPEED * dt, 0);
			// 	pos_ = Point(pos_.getX()+speed_.getX(), pos_.getY()+speed_.getY());
			// 	// pos_   = pos_ + speed_;
			// }

			// if(inputHandler_->isKeyDown(RIGHT_ARROW_KEY))
			// {
			// 	speed_ = Point(CAMERA_SPEED * dt, 0);
			// 	pos_ = Point(pos_.getX()+speed_.getX(), pos_.getY()+speed_.getY());
			// 	// pos_   = pos_ + speed_;
			// }

			// if(inputHandler_->isKeyDown(UP_ARROW_KEY))
			// {
			// 	speed_ = Point(0, -CAMERA_SPEED * dt);
			// 	pos_ = Point(pos_.getX()+speed_.getX(), pos_.getY()+speed_.getY());
			// 	// pos_   = pos_ + speed_;
			// }

			// if(inputHandler_->isKeyDown(DOWN_ARROW_KEY))
			// {
			// 	speed_ = Point(0, CAMERA_SPEED * dt);
			// 	pos_ = Point(pos_.getX()+speed_.getX(), pos_.getY()+speed_.getY());
			// 	// pos_   = pos_ + speed_;
			// }
		}
	}
}

Point Camera::getPosition()
{
	return pos_;
}

void Camera::setInputHandler(InputHandler& inputHandler)
{
	inputHandler_ = &inputHandler;
}
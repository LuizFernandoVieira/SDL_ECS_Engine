#include "../include/Camera.hpp"
#include "../include/InputHandler.hpp"
#include "../include/Resources.hpp"

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
		pos_ = focus_->rect_.getCenter() - Vec2(Resources::WINDOW_WIDTH / 2, Resources::WINDOW_HEIGHT / 2);
	}
	else 
	{
		if(InputHandler::getInstance().isKeyDown(LEFT_ARROW_KEY))
		{
			speed_ = Vec2(-CAMERA_SPEED * dt, 0);
			pos_   = pos_ + speed_;
		}

		if(InputHandler::getInstance().isKeyDown(RIGHT_ARROW_KEY))
		{
			speed_ = Vec2(CAMERA_SPEED * dt, 0);
			pos_   = pos_ + speed_;
		}

		if(InputHandler::getInstance().isKeyDown(UP_ARROW_KEY))
		{
			speed_ = Vec2(0, -CAMERA_SPEED * dt);
			pos_   = pos_ + speed_;
		}

		if(InputHandler::getInstance().isKeyDown(DOWN_ARROW_KEY))
		{
			speed_ = Vec2(0, CAMERA_SPEED * dt);
			pos_   = pos_ + speed_;
		}
	}

	if (pos_.x() < 0) pos_.x(0);
	else if (pos_.x() > Resources::MAP_WIDTH - Resources::WINDOW_WIDTH) pos_.x(Resources::MAP_WIDTH - Resources::WINDOW_WIDTH);
	if (pos_.y() < 0) pos_.y(0);
	else if (pos_.y() > Resources::MAP_HEIGHT - Resources::WINDOW_HEIGHT) pos_.y(Resources::MAP_HEIGHT - Resources::WINDOW_HEIGHT);
}

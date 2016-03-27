#include "../include/Player.hpp"

#include <iostream>

Player::Player(float x, float y) : sprite_("../img/player.png")
{
	rect_ = Rect(x, y, sprite_.getWidth(), sprite_.getHeight());
}

Player::~Player()
{

}

void Player::update(float dt)
{

}

void Player::render()
{
	sprite_.render(rect_.getX(), rect_.getY());
}

void Player::moveTo(float x, float y)
{
	rect_.setX(x);
	rect_.setY(y);
}

void Player::jump()
{
	std::cout << "JUMPING" << std::endl;
}

void Player::placeTile(int x, int y)
{

}
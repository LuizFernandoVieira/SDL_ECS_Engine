#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "InputHandler.hpp"
#include "GameObject.hpp"
#include "Vec2.hpp"

#define CAMERA_SPEED 300

class Camera
{
public:
	static void follow(GameObject& focus);
	static void unfollow();
	static void update(float dt);
	static Vec2 getPosition();
	static void setInputHandler(InputHandler& inputHandler);
private:
	static InputHandler* inputHandler_;
	static GameObject* focus_;
	static Vec2 pos_;
	static Vec2 speed_;
};

#endif
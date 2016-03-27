#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "InputHandler.hpp"
#include "GameObject.hpp"
#include "Point.hpp"

#define CAMERA_SPEED 300

class Camera
{
public:
	static void follow(GameObject& focus);
	static void unfollow();
	static void update(float dt);
	static Point getPosition();
	static void setInputHandler(InputHandler& inputHandler);
private:
	static InputHandler* inputHandler_;
	static GameObject* focus_;
	static Point pos_;
	static Point speed_;
};

#endif
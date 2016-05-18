#ifndef CAMERA_HPP
#define CAMERA_HPP

// #include "GameObject.hpp"
#include "TransformComponent.hpp"
#include "Vec2.hpp"

#define CAMERA_SPEED 300

class Camera
{
public:
	static void follow(TransformComponent* focus);
	static void unfollow();
	static void update(float dt);
	
	static Vec2 pos_;
	static Vec2 speed_;
private:
	static TransformComponent* focus_;
};

#endif
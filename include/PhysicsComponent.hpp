#ifndef PHYSICSCOMPONENT_HPP
#define PHYSICSCOMPONENT_HPP

#include "Component.hpp"
// #include "Vec2.hpp"

class PhysicsComponent : public Component
{
public:
	PhysicsComponent() : gravityScale_(1.0) {}
	PhysicsComponent(float gravityScale) : gravityScale_(gravityScale) {}
	~PhysicsComponent() {}

	float gravityScale_;
};

#endif
#ifndef PHYSICSCOMPONENT_HPP
#define PHYSICSCOMPONENT_HPP

#include "Component.hpp"
#include "Vec2.hpp"

class PhysicsComponent : public Component
{
public:
	PhysicsComponent() { speed_ = new Vec2(); }
	~PhysicsComponent() {}
	Vec2* getSpeed() { return speed_; }
	void setSpeed(Vec2& speed) { speed_ = &speed; }
private:
	Vec2* speed_;
};

#endif
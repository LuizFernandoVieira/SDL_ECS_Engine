#ifndef COLLIDERCOMPONENT_HPP
#define COLLIDERCOMPONENT_HPP

#include "Component.hpp"
#include "Rect.hpp"

class ColliderComponent : public Component
{
public:
	ColliderComponent() : hurtbox_(), hitbox_() {}
	ColliderComponent(Rect hurtbox) : hitbox_() { hurtbox_ = hurtbox; }
	ColliderComponent(Rect hurtbox, Rect hitbox) { hurtbox_ = hurtbox; hitbox_ = hitbox; }
	~ColliderComponent() {}

	Rect hurtbox_;
	Rect hitbox_;
};

#endif
#ifndef RENDERCOMPONENT_HPP
#define RENDERCOMPONENT_HPP

#include "Component.hpp"
#include "Sprite.hpp"

class RenderComponent : public Component
{
public:
	RenderComponent(Sprite* sprite) { sprite_ = sprite; }
	~RenderComponent() {}
	Sprite* getSprite() { return sprite_; }
	void setSprite(Sprite& sprite) { sprite_ = &sprite; }
private:
	Sprite* sprite_;
};

#endif
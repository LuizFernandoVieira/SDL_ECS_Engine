#ifndef RENDERCOMPONENT_HPP
#define RENDERCOMPONENT_HPP

#include <map>
#include <string>

#include "Component.hpp"
#include "Sprite.hpp"

class RenderComponent : public Component
{
public:
	// RenderComponent(std::unordered_map<std::string, Sprite> sprites) : sprites_(sprite) {}
	RenderComponent(Sprite* sprite) { sprite_ = sprite; }
	~RenderComponent() {}
	Sprite* getSprite() { return sprite_; }
	void setSprite(Sprite& sprite) { sprite_ = &sprite; }
private:
	Sprite* sprite_;
	// std::unordered_map<std::string, Sprite> sprites_;
	// Sprite& currentSprite_;
};

#endif
#ifndef RENDERCOMPONENT_HPP
#define RENDERCOMPONENT_HPP

#include <map>
#include <unordered_map>
#include <string>

#include "Component.hpp"
#include "Sprite.hpp"

class RenderComponent : public Component
{
public:
	RenderComponent(std::unordered_map<std::string, Sprite> sprites) : sprites_(sprites) { currentSprite_ = NULL; }
	// RenderComponent(Sprite* sprite) { sprite_ = sprite; }
	~RenderComponent() {}
	// Sprite* getSprite() { return sprite_; }
	// void setSprite(Sprite& sprite) { sprite_ = &sprite; }
	void addSprite(std::string state, Sprite sprite) { sprites_.emplace(state, sprite); }
	Sprite* getCurrentSprite() { return currentSprite_; }
	void setCurrentSprite(std::string state) { currentSprite_ = &sprites_[state]; }

private:
	// Sprite* sprite_;
	std::unordered_map<std::string, Sprite> sprites_;
	Sprite* currentSprite_;
};

#endif
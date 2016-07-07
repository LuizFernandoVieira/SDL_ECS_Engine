#ifndef RENDERCOMPONENT_HPP
#define RENDERCOMPONENT_HPP

#include <map>
#include <unordered_map>
#include <string>

#include "Component.hpp"
#include "StateComponent.hpp"
#include "Sprite.hpp"

struct SpriteKey
{
	State state;
	UmbrellaState umbrellaState;
	UmbrellaDirection umbrellaDirection;

	bool operator==(const SpriteKey& other) const {
		return (
			state == other.state &&
			umbrellaState == other.umbrellaState &&
			umbrellaDirection == other.umbrellaDirection
		);
	}
};

namespace std
{
	template <>
	struct hash<SpriteKey>
	{
		std::size_t operator()(const SpriteKey& k) const
		{
			using std::size_t;
			using std::hash;

			return ((hash<int>()((int)k.state)
					 ^ (hash<int>()((int)k.umbrellaState) << 1)) >> 1)
					 ^ (hash<int>()((int)k.umbrellaDirection) << 1);
		}
	};
}

class RenderComponent : public Component
{
public:
	RenderComponent() : sprites_() {}
	RenderComponent(std::unordered_map<State, Sprite> sprites) : sprites_(sprites) {}
	~RenderComponent() {}

	void addSprite(State state, Sprite sprite) { sprites_.emplace(state, sprite); }
	Sprite& getSprite(State state) {
		if (sprites_.find(state) != sprites_.end()) return sprites_[state];
		else return sprites_[State::IDLE];
	}

private:
	std::unordered_map<State, Sprite> sprites_;
};

class PlayerRenderComponent : public Component
{
public:
	PlayerRenderComponent() : sprites_() {}
	PlayerRenderComponent(std::unordered_map<SpriteKey, Sprite> sprites) : sprites_(sprites) {}
	~PlayerRenderComponent() {}

	void addSprite(SpriteKey spriteKey, Sprite sprite)
	{
		sprites_.emplace(spriteKey, sprite);
	}

	void addSprite(State state, UmbrellaState umbrellaState, UmbrellaDirection umbrellaDirection, Sprite sprite)
	{
		SpriteKey spriteKey;
		spriteKey.state = state;
		spriteKey.umbrellaState = umbrellaState;
		spriteKey.umbrellaDirection = umbrellaDirection;
		sprites_.emplace(spriteKey, sprite);
	}

	Sprite& getSprite(SpriteKey spriteKey)
	{
		if (sprites_.find(spriteKey) != sprites_.end())
			return sprites_[spriteKey];
		else
		{
			spriteKey.state = State::IDLE;
			spriteKey.umbrellaState = UmbrellaState::CLOSED;
			spriteKey.umbrellaDirection = UmbrellaDirection::DOWN;
			return sprites_[spriteKey];
		}
	}

private:
	std::unordered_map<SpriteKey, Sprite> sprites_;
};

#endif

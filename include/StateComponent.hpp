#ifndef STATECOMPONENT_HPP
#define STATECOMPONENT_HPP

#include "Component.hpp"

enum State
{
	IDLE,
	WALKING,
	JUMPING,
	FALLING,
	ATTACKING,
	GRAPPLE,
	ZIPLINE,
	SHOOT
};

enum UmbrellaState
{
	CLOSED,
	OPEN
};

enum UmbrellaDirection
{
	UP,
	FRONT,
	DOWN,
	BACK
};

namespace std
{
	template <>
	struct hash<State>
	{
		std::size_t operator()(const State& k) const
		{
			using std::size_t;
			using std::hash;

			return ((hash<int>()((int)k)
					 ^ (hash<int>()((int)k) << 1)));
		}
	};
}


class StateComponent : public Component
{
public:
	StateComponent() : state_(IDLE), facingRight_(true) {}

	State state_;
	bool facingRight_;
};


class PlayerStateComponent : public StateComponent
{
public:
	PlayerStateComponent() : StateComponent(), umbrellaState_(CLOSED), umbrellaDirection_(DOWN) {}

	UmbrellaState umbrellaState_;
	UmbrellaDirection umbrellaDirection_;
};


#endif
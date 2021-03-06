#ifndef STATECOMPONENT_HPP
#define STATECOMPONENT_HPP

#include "Component.hpp"
#include "Timer.hpp"

enum State
{
	IDLE,
	WALKING,
	JUMPING,
	FALLING,
	ATTACKING,
	GRAPPLE,
	ZIPLINE,
	SHOOT,
	DYING,
	DEAD,
	SUCKING
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
	PlayerStateComponent() : StateComponent(), umbrellaState_(CLOSED), umbrellaDirection_(DOWN), fallTime_(), coinCounter_(0) { current_checkpoint = 0;}

	short unsigned int current_checkpoint;
	UmbrellaState umbrellaState_;
	UmbrellaDirection umbrellaDirection_;
	Timer fallTime_;
	int coinCounter_;
};


#endif
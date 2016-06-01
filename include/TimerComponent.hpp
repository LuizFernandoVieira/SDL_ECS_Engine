#ifndef TIMERCOMPONENT_HPP
#define TIMERCOMPONENT_HPP

#include "Component.hpp"

class TimerComponent : public Component
{
public:
	TimerComponent() { time_ = 0.0; }
	~TimerComponent() {  }

	float time_;
};

#endif

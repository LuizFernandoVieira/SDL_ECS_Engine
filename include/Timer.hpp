#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
	inline Timer(){ time = 0.0; }
	inline void update(float dt) { time += dt; }
	inline void restart() { time = 0.0;	}
	inline float get() { return time; }

private:
	float time;
};

#endif

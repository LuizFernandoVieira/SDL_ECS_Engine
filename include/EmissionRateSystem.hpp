#ifndef EMISSIONRATESYSTEM_HPP
#define EMISSIONRATESYSTEM_HPP

#include "TimerComponent.hpp"

class EmissionRateSystem
{
public:
	EmissionRateSystem();
	void update(
		float dt,
		TimerComponent* tc
	);
private:
};

#endif

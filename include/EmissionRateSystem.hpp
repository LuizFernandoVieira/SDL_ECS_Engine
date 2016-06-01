#ifndef EMISSIONRATESYSTEM_HPP
#define EMISSIONRATESYSTEM_HPP

#include "System.hpp"
#include "TimerComponent.hpp"

class EmissionRateSystem : public System
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

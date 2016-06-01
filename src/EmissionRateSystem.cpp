#include "../include/EmissionRateSystem.hpp"

EmissionRateSystem::EmissionRateSystem()
{

}

void EmissionRateSystem::update(
  float dt,
  TimerComponent* tc
)
{
  tc->time_ += dt;
}

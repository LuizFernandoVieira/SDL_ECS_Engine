#ifndef EMITTERCOMPONENT_HPP
#define EMITTERCOMPONENT_HPP

#include <map>

#include "Component.hpp"
#include "TransformComponent.hpp"
#include "RenderComponent.hpp"

class EmitterComponent : public Component
{
public:
	EmitterComponent(float emissionRate) : emissionRate_(emissionRate) {  }
	~EmitterComponent() {  }

	std::map<int, TransformComponent*> mapTransform_;
  std::map<int, RenderComponent*> mapRender_;

  float emissionRate_;
};

#endif

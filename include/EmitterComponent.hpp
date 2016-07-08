#ifndef EMITTERCOMPONENT_HPP
#define EMITTERCOMPONENT_HPP

#include <map>
#include <string>

#include "Component.hpp"
#include "TransformComponent.hpp"
#include "RenderComponent.hpp"

class EmitterComponent : public Component
{
public:
	EmitterComponent()
	: emissionRate_(0.1),
		particlePath_("../img/waterdrop.png"),
		particleEndPath_("../img/waterdrop-colision.png"),
		frameCount_(1),
		xWidth_(1024),
		ySpeed_(10)
	{  }

	EmitterComponent(
		float emissionRate,
		std::string particlePath,
		std::string particleEndPath,
		int frameCount,
		int xWidth,
		int ySpeed
	)
	: emissionRate_(emissionRate),
		particlePath_(particlePath),
		particleEndPath_(particleEndPath),
		frameCount_(frameCount),
		xWidth_(xWidth),
		ySpeed_(ySpeed)
	{  }

	~EmitterComponent() { }

	std::map<int, TransformComponent*> mapTransform_;
  std::map<int, RenderComponent*> mapRender_;

  float emissionRate_;
	std::string particlePath_;
	std::string particleEndPath_;
	int frameCount_;
	int xWidth_;
	int ySpeed_;
};

#endif

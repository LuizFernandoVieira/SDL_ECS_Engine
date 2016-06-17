#ifndef ZIPLINECOMPONENT_HPP
#define ZIPLINECOMPONENT_HPP

#include "Component.hpp"
#include "Vec2.hpp"

class ZiplineComponent : public Component
{
public:
	ZiplineComponent() : start_(), end_() {}
	ZiplineComponent(Vec2 start, Vec2 end) { start_ = start; end_ = end; }
	~ZiplineComponent() {}

	Vec2 start_;
	Vec2 end_;
};

#endif
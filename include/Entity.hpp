#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <vector>

#include "Component.hpp"
#include "Rect.hpp"

class Entity
{
public:
	Entity();
	Entity(float x, float y);
	void addComponent(Component* component);
	Rect getRect();
	void setRect(Rect rect);
private:
	unsigned int id;
	static unsigned int nextId;
	Rect rect_;
	std::vector<Component*> components_;
};

#endif
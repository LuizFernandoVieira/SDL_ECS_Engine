#include "../include/Entity.hpp"

unsigned int Entity::nextId = 0;

Entity::Entity()
{
	id = nextId;
	nextId++;
}

void Entity::addComponent(Component* component)
{
	components_.emplace_back(component);
}

Rect Entity::getRect() { 
	return rect_; 
}

void Entity::setRect(Rect rect) { 
	rect_ = rect; 
}
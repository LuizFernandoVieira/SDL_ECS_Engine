#ifndef LEVEL_HPP
#define LEVEL_HPP

class ILevel
{
public:
	~ILevel() {}
	virtual void create() = 0;
	virtual void update(float dt) = 0;
	virtual void render() = 0;
};

#endif
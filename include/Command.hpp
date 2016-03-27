#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "GameActor.hpp"

class Command
{
public:
	virtual ~Command() {}
	virtual void execute(GameActor& gameActor) = 0;
};

#endif
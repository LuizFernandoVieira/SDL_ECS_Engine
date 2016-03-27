#ifndef JUMPCOMMAND_HPP
#define JUMPCOMMAND_HPP

#include "Command.hpp"
#include "GameObject.hpp"

class JumpCommand : public Command
{
public:
	virtual void execute(GameActor& gameActor)
	{
		gameActor.jump();
	}
};

#endif
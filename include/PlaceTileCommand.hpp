#ifndef PLACETILECOMMAND_HPP
#define PLACETILECOMMAND_HPP

#include "Command.hpp"

class PlaceTileCommand : public Command
{
public:
	PlaceTileCommand(int x, int y) { x_ = x; y_ = y; }
	virtual void execute(GameActor& gameActor)
	{
		gameActor.placeTile(x_, y_);
	}
private:
	int x_;
	int y_;
};

#endif
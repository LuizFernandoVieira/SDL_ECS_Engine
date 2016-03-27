#ifndef MOVECOMMAND_HPP
#define MOVECOMMAND_HPP

#include "Command.hpp"

class MoveCommand : public Command
{
public:
	MoveCommand(bool up, bool right, bool down, bool left) { up_ = up; right_ = right; down_ = down; left_=left; }
	virtual void execute(GameActor& gameActor)
	{
		if(up_) {
			gameActor.moveTo(gameActor.getRect().getX(), 
				gameActor.getRect().getY() - 5);	
		}
		if(right_) {
			gameActor.moveTo(gameActor.getRect().getX() + 5, 
				gameActor.getRect().getY());	
		} 
		if(down_) {
			gameActor.moveTo(gameActor.getRect().getX(), 
				gameActor.getRect().getY() + 5);	
		}
		if(left_) {
			gameActor.moveTo(gameActor.getRect().getX() - 5, 
				gameActor.getRect().getY());	
		}
	}
private:
	bool up_;
	bool right_;
	bool down_;
	bool left_;
};

#endif
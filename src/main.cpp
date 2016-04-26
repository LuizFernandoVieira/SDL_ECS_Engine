#include <iostream>

#include "../include/Game.hpp"
#include "../include/Globals.hpp"

int main(int argc, char *argv[])
{
	Game game = Game(Globals::WINDOW_WIDTH,Globals::WINDOW_HEIGHT);
	game.run();
	
	return 0;
}
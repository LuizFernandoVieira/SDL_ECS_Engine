#include <iostream>

#include "../include/Game.hpp"
#include "../include/Globals.hpp"

int Globals::WINDOW_WIDTH = 1024;
int Globals::WINDOW_HEIGHT = 600;

int main(int argc, char *argv[])
{

	Game game = Game(Globals::WINDOW_WIDTH,Globals::WINDOW_HEIGHT);
	game.run();
	
	return 0;
}
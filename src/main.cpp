#include <iostream>

#include "../include/Game.hpp"
// #include "../include/Globals.hpp"

int main(int argc, char *argv[])
{
	Game game = Game(1024,600);
	game.run();
	
	return 0;
}
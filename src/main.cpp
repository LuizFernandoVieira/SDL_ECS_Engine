#include <iostream>

#include "../include/Game.hpp"
#include "../include/Globals.hpp"

int Globals::WINDOW_WIDTH = 1024;
int Globals::WINDOW_HEIGHT = 600;
int Globals::TILE_WIDTH = 32;
int Globals::TILE_HEIGHT = 32;
int Globals::GRAVITY = 100; // pixels per second
float Globals::PLAYER_SPEED = 150; // pixels per second

int main(int argc, char *argv[])
{

	Game game = Game(Globals::WINDOW_WIDTH,Globals::WINDOW_HEIGHT);
	game.run();
	
	return 0;
}
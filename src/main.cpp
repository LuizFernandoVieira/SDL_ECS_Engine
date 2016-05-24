#include <iostream>

#include "../include/Game.hpp"
#include "../include/Globals.hpp"

int Globals::WINDOW_WIDTH = 1024;
int Globals::WINDOW_HEIGHT = 600;
int Globals::TILE_WIDTH = 32;
int Globals::TILE_HEIGHT = 32;
int Globals::GRAVITY = 200; // pixels per second
float Globals::PLAYER_WALK_SPEED = 200; // pixels per second
float Globals::PLAYER_JUMP_SPEED = 500; // pixels per second

int main(int argc, char *argv[])
{

	Game game = Game(Globals::WINDOW_WIDTH,Globals::WINDOW_HEIGHT);
	game.run();
	
	return 0;
}
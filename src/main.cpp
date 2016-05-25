#include <iostream>

#include "../include/Game.hpp"
#include "../include/Globals.hpp"
#define		CONFIG_FILE	"../config.txt"

int Globals::WINDOW_WIDTH 			= 0;
int Globals::WINDOW_HEIGHT 			= 0;
int Globals::TILE_WIDTH 			= 0;
int Globals::TILE_HEIGHT 			= 0;
int Globals::GRAVITY 				= 0; // pixels per second
float Globals::PLAYER_WALK_SPEED 	= 0; // pixels per second
float Globals::PLAYER_JUMP_SPEED 	= 0; // pixels per second


int main(int argc, char *argv[])
{
	Globals::Read(CONFIG_FILE);
	Game game = Game(Globals::WINDOW_WIDTH,Globals::WINDOW_HEIGHT);
	game.run();
	
	return 0;
}
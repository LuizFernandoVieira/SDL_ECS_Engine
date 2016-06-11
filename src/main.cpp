#include <iostream>

//#include <libxml/parser.h>

#include "../include/Game.hpp"
#include "../include/Resources.hpp"
#define		CONFIG_FILE	"../config.txt"
#define		CONFIG_XML	"../config.xml"



int main(int argc, char *argv[])
{
	Resources::Read(CONFIG_XML);
	Game game = Game(Resources::WINDOW_WIDTH,Resources::WINDOW_HEIGHT);
	game.run();
	
	return 0;
}
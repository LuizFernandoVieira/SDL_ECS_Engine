#ifdef __APPLE__
	# include <lua5.2/lua.hpp>
#endif

#include <iostream>

#include "../include/Game.hpp"
#include "../include/Resources.hpp"
#include "../include/MainMenuState.hpp"

#define		CONFIG_FILE	"../config.txt"
#define		CONFIG_XML	"../config.xml"

int main(int argc, char *argv[])
{
	Resources::Read(CONFIG_XML);

	Game game("Umbra", Resources::WINDOW_WIDTH,Resources::WINDOW_HEIGHT);
	game.push(new MainMenuState());
	game.run();

	return 0;
}

// #include <iostream>

// #include "../include/Game.hpp"
#include "../include/Globals.hpp"
#define		CONFIG_FILE	"../config.txt"

int Globals::WINDOW_WIDTH 			= 0;
int Globals::WINDOW_HEIGHT 			= 0;
int Globals::TILE_WIDTH 			= 0;
int Globals::TILE_HEIGHT 			= 0;
int Globals::GRAVITY 				= 0; // pixels per second
float Globals::PLAYER_WALK_SPEED 	= 0; // pixels per second
float Globals::PLAYER_JUMP_SPEED 	= 0; // pixels per second


/*int main(int argc, char *argv[])
{
	Globals::Read(CONFIG_FILE);
	Game game = Game(Globals::WINDOW_WIDTH,Globals::WINDOW_HEIGHT);
	game.run();
	
	return 0;
}
*/
#include "Json.hpp"

using json = nlohmann::json;

int main()
{
    // create a JSON object
    json j =
    {
        {"pi", 3.141},
        {"happy", true},
        {"name", "Niels"},
        {"nothing", nullptr},
        {
            "answer", {
                {"everything", 42}
            }
        },
        {"list", {1, 0, 2}},
        {
            "object", {
                {"currency", "USD"},
                {"value", 42.99}
            }
        }
    };

    // add new values
    j["new"]["key"]["value"] = {"another", "list"};

    // count elements
    j["size"] = j.size();

    // pretty print with indent of 4 spaces
    std::cout << std::setw(4) << j << '\n';
}
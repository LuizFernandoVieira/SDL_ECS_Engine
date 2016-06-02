#ifndef OBJECTMAP_HPP
#define OBJECTMAP_HPP

#ifdef __APPLE__
	#include <SDL2/SDL.h>
#else
	#include "SDL.h"
#endif

// #include <sstream>
#include <string>
// #include <vector>
#include <fstream>

#include "Json.hpp"
// #include "Rect.hpp"

class ObjectMap
{
public:
	ObjectMap(const char* file);
	void save();
	void load();
	// void render(int x, int y);
	// int& at(int x, int y);
	// int getWidth() const;
	// int getHeight() const;

	// std::vector<int> collisionMatrix_;
	nlohmann::json objectMap_;
private:

	std::string filename_;
};


#endif
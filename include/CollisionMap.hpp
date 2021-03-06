#ifndef COLLISIONMAP_HPP
#define COLLISIONMAP_HPP

#ifdef __APPLE__
	#include <SDL2/SDL.h>
#else
	#include "SDL.h"
#endif

#include <sstream>
#include <string>
#include <vector>
#include <fstream>

#include "Rect.hpp"

class CollisionMap
{
public:
	CollisionMap(const char* file);
	CollisionMap(const char* file, int width, int height);

	void newMap(int width, int height);
	void save();
	void load();
	void render(int x, int y);
	int& at(int x, int y);
	int getWidth() const;
	int getHeight() const;

	std::vector<int> collisionMatrix_;
private:
	void renderSelection(int collision, Rect rect);

	std::string filename_;
	
	int mapWidth_;
	int mapHeight_;
};


#endif
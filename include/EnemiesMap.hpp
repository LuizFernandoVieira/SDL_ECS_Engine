#ifndef ENEMIESMAP_HPP
#define ENEMIESMAP_HPP

#ifdef __APPLE__
	#include <SDL2/SDL.h>
#else
	#include "SDL.h"
#endif

#include <sstream>
#include <string>
#include <vector>
#include <fstream>

#include "pugixml.hpp"

struct ObjectInfo
{
	std::string name;
	std::string filename;
	int frameCount;
	float frameTime;
};

struct LocalObjectInfo
{
	int id;
	std::string filename;
	int frameCount;
	float frameTime;
	int x, y;
	int layer;
};

class ObjectMap
{
public:
	ObjectMap(std::string localObjects);

	void save();
	void loadGlobals();
	void loadLocals();

	pugi::xml_document& getLocalXML();

private:
	pugi::xml_document localObjects_;
};


#endif

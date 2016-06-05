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

#include "pugixml.hpp"
// #include "Rect.hpp"

typedef struct tpObjectInfo
{
	std::string name;
	std::string filename;
	int frameCount;
	float frameTime;
} ObjectInfo;

class ObjectMap
{
public:
	ObjectMap(std::string globalObjects, std::string localObjects);
	void save();
	void loadGlobals();
	void loadLocals();

	ObjectInfo getGlobalObject(int index);
	int globalSize();
	void addObject(int index, int id, int x, int y);
	int getLastObjectId();

private:
	pugi::xml_node getGlobalObjectNode(int index);

	pugi::xml_document globalObjects_;	// temporario?
	pugi::xml_document localObjects_;
	std::string globalFilename_;
	std::string localFilename_;
};


#endif
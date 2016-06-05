#ifndef OBJECTMAP_HPP
#define OBJECTMAP_HPP

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
// #include "Rect.hpp"

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
};

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
	std::vector<LocalObjectInfo> getLocalObjects();
	int getLastObjectId();
	void deleteObject(int id);

private:
	pugi::xml_node getGlobalObjectNode(int index);

	pugi::xml_document globalObjects_;	// temporario?
	pugi::xml_document localObjects_;
	std::string globalFilename_;
	std::string localFilename_;
};


#endif
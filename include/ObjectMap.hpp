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
	float scaleX, scaleY;
	float rotation;
};

struct LocalObjectInfo
{
	int id;
	std::string filename;
	int frameCount;
	float frameTime;
	int x, y;
	float scaleX, scaleY, rotation;
	int layer;
};

class ObjectMap
{
public:
	// Construtor pro editor
	ObjectMap(std::string globalObjects, std::string localObjects);
	// Construtor pro jogo
	ObjectMap(std::string localObjects);

	void save();
	void loadGlobals();
	void loadLocals();

	ObjectInfo getGlobalObject(int index);
	int globalSize();

	void addObject(int index, int id, int x, int y, int layer);
	void addZipline(int id, int x, int y, int angle, int scaleX);
	std::vector<LocalObjectInfo> getLocalObjects();

	pugi::xml_document& getLocalXML();

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
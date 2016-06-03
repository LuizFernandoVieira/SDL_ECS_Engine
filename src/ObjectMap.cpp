#include <iostream>

#include "../include/ObjectMap.hpp"

ObjectMap::ObjectMap(const char* file) : filename_(file)
{
	load();
}


void ObjectMap::load()
{
	// objectMap_.clear();

	// std::ifstream ifs(filename_, std::ifstream::in);
	// try
	// {
	// 	objectMap_.parse(ifs);
	// }
	// catch(...)
	// {
	// 	std::cout << "fudeu" << std::endl;
	// }
	// ifs.close();

	// std::cout << std::setw(4) << objectMap_ << std::endl;

	pugi::xml_document doc;
	// pugi::xml_parse_result result = doc.load_file("../map/objectMap.xml");
	// std::cout << "Load result: " << result.description() << ", object name: " << doc.child("object").value() << std::endl;
	pugi::xml_parse_result result = doc.load_file("../pugixml-1.7/docs/samples/tree.xml");
	std::cout << "Load result: " << result.description() << ", mesh name: " << doc.child("mesh").attribute("name").value() << std::endl;
}


void ObjectMap::save()
{

}
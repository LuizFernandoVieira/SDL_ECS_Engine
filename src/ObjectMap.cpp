#include <iostream>

#include "../include/ObjectMap.hpp"

using json = nlohmann::json;

ObjectMap::ObjectMap(const char* file) : filename_(file)
{
	// load();
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
}


void ObjectMap::save()
{

}
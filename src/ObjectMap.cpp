#include <iostream>

#include "../include/ObjectMap.hpp"

ObjectMap::ObjectMap(std::string globalObjects, std::string localObjects) : 
	globalFilename_(globalObjects),
	localFilename_(localObjects)
{
	loadGlobals();
	loadLocals();
}


void ObjectMap::loadGlobals()
{
	pugi::xml_parse_result result = globalObjects_.load_file(globalFilename_.c_str());
	if (!result)
		std::cout << "Erros ao carregar o mapa de objetos: " << result.description() << std::endl;

	// globalObjects_.print(std::cout);
}

void ObjectMap::loadLocals()
{
	pugi::xml_parse_result result = localObjects_.load_file(localFilename_.c_str());
	if (!result)
		std::cout << "Erros ao carregar o mapa de objetos: " << result.description() << std::endl;
}


void ObjectMap::save()
{
	localObjects_.save_file(localFilename_.c_str());
}


ObjectInfo ObjectMap::getGlobalObject(int index)
{
	pugi::xml_node object = globalObjects_.first_child();

	for (int i = 0; i < index; object = object.next_sibling(), i++);

	if (!object)
	{
		std::cout << "Erro, objeto não encontrado no mapa global" << std::endl;
		// throw aqui
	}

	pugi::xml_node sprite = object.child("render").first_child();
	while (std::string(sprite.attribute("state_name").value()) != "IdleState") sprite = sprite.next_sibling();

	ObjectInfo info;
	info.name = object.name();
	info.filename = sprite.attribute("filename").value();
	info.frameCount = sprite.attribute("frame_count").as_int();
	info.frameTime = sprite.attribute("frame_time").as_float();
	return info;
}

int ObjectMap::globalSize()
{
	int i = 0;
	for (auto object : globalObjects_.children())
		i++;
	return i;
}


pugi::xml_node ObjectMap::getGlobalObjectNode(int index)
{
	pugi::xml_node object = globalObjects_.first_child();

	for (int i = 0; i < index; object = object.next_sibling(), i++);

	if (!object)
		std::cout << "Erro, objeto não encontrado no mapa global" << std::endl;
		// throw bonito aqui qdo tiver exceptions

	return object;
}


void ObjectMap::addObject(int index, int id, int x, int y)
{
	pugi::xml_node object = getGlobalObjectNode(index);

	pugi::xml_node newObject = localObjects_.append_copy(object);
	newObject.append_attribute("id").set_value(id);

	pugi::xml_node transf;
	if (!newObject.child("transform"))
	{
		transf = newObject.append_child("transform");
		transf.append_attribute("x");
		transf.append_attribute("y");
		transf.append_attribute("w");
		transf.append_attribute("h");
	}
	else
	{
		transf = newObject.child("transform");
	}
	transf.attribute("x").set_value(x);
	transf.attribute("y").set_value(y);
}


int ObjectMap::getLastObjectId()
{
	return localObjects_.last_child().attribute("id").as_int();
}
#include <iostream>

#include "../include/ObjectMap.hpp"

ObjectMap::ObjectMap(std::string globalObjects, std::string localObjects) : 
	globalFilename_(globalObjects),
	localFilename_(localObjects)
{
	loadGlobals();
	loadLocals();
}

ObjectMap::ObjectMap(std::string localObjects) : localFilename_(localObjects)
{
	loadLocals();
}


void ObjectMap::loadGlobals()
{
	pugi::xml_parse_result result = globalObjects_.load_file(globalFilename_.c_str());
	if (!result)
		std::cout << "Mapa de objetos não carregado: " << result.description() << std::endl;

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

	pugi::xml_node sprite = object.child("render").find_child_by_attribute("sprite", "state", "0");

	ObjectInfo info;
	info.name = object.attribute("name").value();
	info.filename = sprite ? sprite.attribute("filename").value() : "";
	info.frameCount = sprite ? sprite.attribute("frame_count").as_int() : 1;
	info.frameTime = sprite ? sprite.attribute("frame_time").as_float() : 0;

	pugi::xml_node scale = object.child("transform").child("scale");
	info.scaleX = scale ? scale.attribute("x").as_float() : 1;
	info.scaleY = scale ? scale.attribute("y").as_float() : 1;

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


void ObjectMap::addObject(int index, int id, int x, int y, int layer)
{
	pugi::xml_node object = getGlobalObjectNode(index);

	pugi::xml_node newObject = localObjects_.child("world_objects").append_copy(object);
	newObject.append_attribute("id").set_value(id);
	newObject.append_attribute("layer").set_value(layer);

	pugi::xml_node transf;
	if (!newObject.child("transform"))
	{
		transf = newObject.append_child("transform");
		transf.append_child("rect");
		transf.child("rect").append_attribute("x");
		transf.child("rect").append_attribute("y");
		transf.child("rect").append_attribute("w");
		transf.child("rect").append_attribute("h");
		transf.append_child("scale");
		transf.child("scale").append_attribute("x");
		transf.child("scale").append_attribute("y");
		transf.child("scale").attribute("x").set_value(1);
		transf.child("scale").attribute("y").set_value(1);
		transf.append_child("rotation");
		transf.child("rotation").append_attribute("value");
		transf.child("rotation").attribute("value").set_value(0);
	}
	else
	{
		transf = newObject.child("transform");
	}
	transf.child("rect").attribute("x").set_value(x);
	transf.child("rect").attribute("y").set_value(y);
}


int ObjectMap::getLastObjectId()
{
	return localObjects_.child("world_objects").last_child().attribute("id").as_int();
}


std::vector<LocalObjectInfo> ObjectMap::getLocalObjects()
{
	std::vector<LocalObjectInfo> infos;
	for (auto object : localObjects_.child("world_objects").children())
	{
		LocalObjectInfo info;
		info.id = object.attribute("id").as_int();
		if (object.child("render"))
		{
			pugi::xml_node sprite = object.child("render").find_child_by_attribute("sprite", "state", "0");
			info.filename = sprite.attribute("filename").value();
			info.frameCount = sprite.attribute("frame_count").as_int();
			info.frameTime = sprite.attribute("frame_time").as_float();
		}
		else if (object.child("player_render"))
		{
			pugi::xml_node sprite = object.child("player_render").find_child_by_attribute("sprite", "state", "0");
			info.filename = sprite.attribute("filename").value();
			info.frameCount = sprite.attribute("frame_count").as_int();
			info.frameTime = sprite.attribute("frame_time").as_float();
		}
		else
			info.filename = "";
		pugi::xml_node transf = object.child("transform");
		info.x = transf.child("rect").attribute("x").as_int();
		info.y = transf.child("rect").attribute("y").as_int();
		info.scaleX = transf.child("scale").attribute("x").as_float();
		info.scaleY = transf.child("scale").attribute("y").as_float();
		info.rotation = transf.child("rotation").attribute("value").as_float();
		info.layer = object.attribute("layer") ? object.attribute("layer").as_int() : 2;

		infos.emplace_back(info);
	}

	return infos;
}


pugi::xml_document& ObjectMap::getLocalXML()
{
	return localObjects_;
}

void ObjectMap::deleteObject(int id)
{
	std::ostringstream temp;
	temp << id;
	localObjects_.child("world_objects").remove_child( localObjects_.child("world_objects").find_child_by_attribute("object", "id", temp.str().c_str()) );
}
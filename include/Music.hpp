#ifndef MUSIC_HPP
#define MUSIC_HPP

#ifdef __APPLE__
	#include <SDL2/SDL.h>
	#include <SDL2_mixer/SDL_mixer.h>
#else
	#include "SDL.h"
	#include "SDL_mixer.h"
#endif

#include <vector>
#include <unordered_map>
#include "pugixml.hpp"

#define _attribute	pugi::xml_attribute
#define _node		pugi::xml_node
#define _document	pugi::xml_document
#define _parse		pugi::xml_parse_result

#define AUDIO_MAXLAYERS 8

class Music
{
public:
	Music();
	Music(std::string file);
	~Music();

	void Play();
	void Stop();
	void Open(std::string file);
	bool IsOpen();

	void Update();

	void Load(_node source);
	void SetVolumes(std::string state);

private:
	Mix_Chunk* 	layer[AUDIO_MAXLAYERS];

	int			channel[AUDIO_MAXLAYERS];

	float 		volume[AUDIO_MAXLAYERS];
	float 		volumeCurrent[AUDIO_MAXLAYERS];

	std::unordered_map<std::string, int*>	volume_vector;
};
#endif
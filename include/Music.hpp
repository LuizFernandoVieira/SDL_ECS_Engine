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

	void Play();
	void Stop();
	void Open(std::string file);
	bool IsOpen();

	void Update();

private:
	static Mix_Chunk* 	layer[AUDIO_MAXLAYERS];

	int			channel[AUDIO_MAXLAYERS];

	float 		volume[AUDIO_MAXLAYERS];
	float 		volumeCurrent[AUDIO_MAXLAYERS];

	//----------------------------------------------
	//std::vector<int[AUDIO_MAXLAYERS]>	volume_vector;
	static std::unordered_map<std::string, int*>	volume_vector;

	//source = "music" node in config.xml
	public:
		static void ReadVolumes(_node source);
		void SetVolumes(std::string state);

};
#endif
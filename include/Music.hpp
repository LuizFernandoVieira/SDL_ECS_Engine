#ifndef MUSIC_HPP
#define MUSIC_HPP
#endif

#ifdef __APPLE__
	#include <SDL2/SDL.h>
	#include <SDL2_mixer/SDL_mixer.h>
#else
	#include "SDL.h"
	#include "SDL_mixer.h"
#endif

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
	Mix_Chunk* 	layer[AUDIO_MAXLAYERS];

	int			channel[AUDIO_MAXLAYERS];

	float 		volume[AUDIO_MAXLAYERS];
	float 		volumeCurrent[AUDIO_MAXLAYERS];
};

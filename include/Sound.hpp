#ifndef SOUND_HPP
#define SOUND_HPP

#include <iostream>
#include <unordered_map>

#ifdef __APPLE__
	#include <SDL2/SDL.h>
	#include <SDL2_mixer/SDL_mixer.h>
#else
	#include "SDL.h"
	#include "SDL_mixer.h"
#endif


class Sound{
	public:
		Sound();
		Sound(std::string file);

		void Play(int times = 0);
		void Stop();
		void Open(std::string file);
		bool IsOpen();

	private:
		Mix_Chunk* chunk;
		int channel;
};

#endif
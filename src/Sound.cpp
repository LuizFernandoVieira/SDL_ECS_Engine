#include <iostream>

#ifdef __APPLE__
	#include <SDL2/SDL.h>
	#include <SDL2_mixer/SDL_mixer.h>
#else
	#include "SDL.h"
	#include "SDL_mixer.h"
#endif

#include "../include/Sound.hpp"
#include "../include/Resources.hpp"

Sound::Sound(){
	chunk = nullptr;
	channel = 0;
}

Sound::Sound(std::string file){
	chunk = nullptr;
	channel = 0;

	Open(file);
}

void Sound::Play(int times){
	if (chunk != nullptr)
		if (times >= -1){
			channel = Mix_PlayChannel(-1, chunk, times);
			Mix_Volume(channel, MIX_MAX_VOLUME);
		}
}

void Sound::Stop(){
	Mix_HaltChannel(channel);
}

void Sound::Open(std::string file){
	chunk = Resources::GetSound(file);
}

bool Sound::IsOpen(){
	return (chunk != nullptr);
}

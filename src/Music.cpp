#include <iostream>
#include "SDL.h"
#include "SDL_mixer.h"

#include "../include/music.hpp"
#include "../include/resources.hpp"

#define MUSIC_FADE_TIME 350

Music::Music(){
}

Music::Music(std::string file){
}


void Music::Play(){
}

void Music::Stop(){
}

void Music::Open(std::string file){
	

	if (!IsOpen())
		std::cout << "ERROR RETRIEVING FILE" << std::endl;
}

bool Music::IsOpen(){
	//return (music != nullptr);
}

/*
#define AUDIO_MAXLAYERS 8

//typedef float values[AUDIO_MAXLAYERS] volume;

class Music
{
public:
	Music();
	Music(std::string file);

	void Play(int times = 0);
	void Stop();
	void Open(std::string file);
	bool IsOpen();

private:
	SDL_Chunk* 	layer[AUDIO_MAXLAYERS];
	float 		vloume[AUDIO_MAXLAYERS];
	
};
*/
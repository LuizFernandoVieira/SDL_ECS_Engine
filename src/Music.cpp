#include <iostream>

#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_mixer/SDL_mixer.h>
#else
#include "SDL.h"
#include "SDL_mixer.h"
#endif

#include "../include/music.hpp"
#include "../include/inputhandler.hpp"
#include "../include/resources.hpp"

#define MUSIC_FADE_TIME 100
#define VOLUME_THRESHOLD	10
#define VOLUME_SLIDE		5

#define testaudiolayer	"../audio/jump_test.wav"

#define musiclayer1		"../audio/umbra_test_piano.wav"
#define musiclayer2		"../audio/umbra_test_synth.wav"
#define musiclayer3		"../audio/umbra_test_flute.wav"
#define musiclayer4		"../audio/umbra_test_bass.wav"
#define musiclayer5		"../audio/umbra_test_violin.wav"

Music::Music(){
	int i;
	std::string layername 		= "";
	std::string volume_string 	= "";

	for (i = 0; i < AUDIO_MAXLAYERS; ++i)
		layer[i] = nullptr;

	//Test Sounds Loading
	layer[0] = Resources::GetSound(musiclayer1);
	layer[1] = Resources::GetSound(musiclayer2);
	layer[2] = Resources::GetSound(musiclayer3);
	layer[3] = Resources::GetSound(musiclayer4);
	layer[4] = Resources::GetSound(musiclayer5);

	/*
		Protótipo da função GetMusic

		Music::Open(std::string state){
			chama Resources::GetMusic(state)
		}

		bool Resources::GetMusic(std::string state, SDL_Chunk* layer)

			-	Recebe nome do estado atual (recebido), e vetor de camadas
			-	Retorna se funfou
	*/

	/*
		Protótipo da função GetVolume

		Durante Update, Music checa se
			player::state != currentState

		Caso seja verdade, Chama Resources::GetVolume

		Resources::GetVolume(std::string playerState, int*)

			-	Recebe nome do estado atual do player e
	*/

	for (i = 0; i < AUDIO_MAXLAYERS; i++){
		/*
		//Carregar Layers
		layername = testaudiolayer;
		layer[i] = Resources::GetSound(layername);

		*/
		//Carregar Volumes
		volumeCurrent[i] = 0;

		volume[i] = MIX_MAX_VOLUME - 20;
	}
	Play();
}

Music::Music(std::string file){
}


void Music::Play(){
	int i;
	for (i = 0; i < AUDIO_MAXLAYERS; i++){
		//std::cout << "playing" << std::endl;
		channel[i] = Mix_PlayChannel(-1, layer[i], -1);
		Mix_Volume(channel[i], volumeCurrent[i]);
	}
}

void Music::Stop(){
	Mix_HaltChannel(-1);
}

void Music::Open(std::string file){
	if (!IsOpen())
		std::cout << "ERROR RETRIEVING FILE" << std::endl;
}

bool Music::IsOpen(){
	for (int i = 0; i < AUDIO_MAXLAYERS; ++i)
		if (layer[i] != nullptr)
			return true;

	return false;
}

void Music::Update(){
	InputHandler& In = InputHandler::getInstance();

	short int i;
	short int volume_diff;

	//GetPlayerState
	//GetVolume

	//Volume Setting
	if (In.keyPress(NUMKEY_1)) {
		if (volume[0] == 0)
			volume[0] = MIX_MAX_VOLUME - 20;
		else volume[0] = 0;
	}

	if (In.keyPress(NUMKEY_2)) {
		if (volume[1] == 0)
			volume[1] = MIX_MAX_VOLUME - 20;
		else volume[1] = 0;
	}

	if (In.keyPress(NUMKEY_3)) {
		if (volume[2] == 0)
			volume[2] = MIX_MAX_VOLUME - 20;
		else volume[2] = 0;
	}

	if (In.keyPress(NUMKEY_4)) {
		if (volume[3] == 0)
			volume[3] = MIX_MAX_VOLUME - 20;
		else volume[3] = 0;
	}

	if (In.keyPress(NUMKEY_5)) {
		if (volume[4] == 0)
			volume[4] = MIX_MAX_VOLUME - 20;
		else volume[4] = 0;
	}

	if (In.keyPress(NUMKEY_6)) {
		if (volume[5] == 0)
			volume[5] = MIX_MAX_VOLUME - 20;
		else volume[5] = 0;
	}

	if (In.keyPress(NUMKEY_7)) {
		if (volume[6] == 0)
			volume[6] = MIX_MAX_VOLUME - 20;
		else volume[6] = 0;
	}

	if (In.keyPress(NUMKEY_8)) {
		if (volume[7] == 0)
			volume[7] = MIX_MAX_VOLUME - 20;
		else volume[7] = 0;
	}

	//Fading Loop
	for (i = 0; i < AUDIO_MAXLAYERS; i++){
		volume_diff = volume[i] - volumeCurrent[i];
		//std::cout << "Layer " << i << " has volume " << volumeCurrent[i] << "\t\t Target Volume: " << volume[i] << "\tVolume Diff: " << volume_diff << std::endl;

		//Volume Check
		if (volume_diff == 0)
			continue;

		//Volume Apply
		if (volume_diff > 0)
				volumeCurrent[i] += VOLUME_SLIDE;
		else	volumeCurrent[i] -= VOLUME_SLIDE;

		if (abs(volume_diff) < VOLUME_THRESHOLD){
			volumeCurrent[i] = volume[i];
		}

		Mix_Volume(channel[i], volumeCurrent[i]);
	}
}

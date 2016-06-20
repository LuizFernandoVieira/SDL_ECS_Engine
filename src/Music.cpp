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


#define musiclayer1		"../audio/umbra_test_piano.wav"
#define musiclayer2		"../audio/umbra_test_synth.wav"
#define musiclayer3		"../audio/umbra_test_flute.wav"
#define musiclayer4		"../audio/umbra_test_bass.wav"
#define musiclayer5		"../audio/umbra_test_violin.wav"

#define TestVolume	MIX_MAX_VOLUME - 20

std::unordered_map<std::string, int*>	Music::volume_vector;
Mix_Chunk* 	Music::layer[AUDIO_MAXLAYERS];

Music::Music(){
	int i;
	std::string layername 		= "";
	std::string volume_string 	= "";

	for (i = 0; i < AUDIO_MAXLAYERS; ++i)
		layer[i] = nullptr;

	//Test Sounds Loading
	//layer[0] = Resources::GetSound(musiclayer1);
	//layer[1] = Resources::GetSound(musiclayer2);
	//layer[2] = Resources::GetSound(musiclayer3);
	//layer[3] = Resources::GetSound(musiclayer4);
	//layer[4] = Resources::GetSound(musiclayer5);

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

		volume[i] = 0;
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
/*
	//Volume Setting
	if (In.keyPress(NUMKEY_1)) {
		if (volume[0] == 0)
			volume[0] = TestVolume;
		else volume[0] = 0;
	}

	if (In.keyPress(NUMKEY_2)) {
		if (volume[1] == 0)
			volume[1] = TestVolume;
		else volume[1] = 0;
	}

	if (In.keyPress(NUMKEY_3)) {
		if (volume[2] == 0)
			volume[2] = TestVolume;
		else volume[2] = 0;
	}

	if (In.keyPress(NUMKEY_4)) {
		if (volume[3] == 0)
			volume[3] = TestVolume;
		else volume[3] = 0;
	}

	if (In.keyPress(NUMKEY_5)) {
		if (volume[4] == 0)
			volume[4] = TestVolume;
		else volume[4] = 0;
	}

	if (In.keyPress(NUMKEY_6)) {
		if (volume[5] == 0)
			volume[5] = TestVolume;
		else volume[5] = 0;
	}

	if (In.keyPress(NUMKEY_7)) {
		if (volume[6] == 0)
			volume[6] = TestVolume;
		else volume[6] = 0;
	}

	if (In.keyPress(NUMKEY_8)) {
		if (volume[7] == 0)
			volume[7] = TestVolume;
		else volume[7] = 0;
	}
*/

	if (In.keyPress(NUMKEY_1)) {
		if (volume[0] == 0)
			SetVolumes("default");
		else SetVolumes("walking");
	}

	//Fading Loop
	for (i = 0; i < AUDIO_MAXLAYERS; i++){
		volume_diff = volume[i] - volumeCurrent[i];

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

//---------------------------------------------------------------------------------------

void Music::ReadVolumes(_node source){
	if (source == nullptr)	return;

	int 	counter;
	int*	volumeArray;

	_node assetsNode;
	_node layerAsset;

	_node volumeNode;
	_node layerVolume;

	volume_vector.clear();

	//Setando Arquivos de áudio a serem tocados
	assetsNode = source.child("assets");
	if (assetsNode != nullptr){
		for (counter = 0; counter < AUDIO_MAXLAYERS; counter++){
			layer[counter] = nullptr;
		}

		for (_node layerAsset = source.child("assets"); layerAsset; layerAsset = layerAsset.next_sibling()){
			if (layerAsset.attribute("file").as_string() == "null")
				layer[layerAsset.attribute("channel").as_int()] = nullptr;
			else layer[layerAsset.attribute("channel").as_int()] = Resources::GetSound(layerAsset.attribute("file").as_string());
		}
	}


	/*
	for (_node assetsNode = source.child("assets"); assetsNode; assetsNode = assetsNode.next_sibling("assets")){
		
		//Inserção de novo padrão de volume
		volumeArray = volume_vector[assetsNode.attribute("state").as_string()];
		counter = 0;

		//Preenchimento do vetor de volumes
		for(_node layerVolume = assetsNode.child("layer"); layerVolume; layerVolume = layerVolume.next_sibling()){
			volumeArray[counter] = layerVolume.attribute("value").as_int();
			counter++;
		}
	}*/

	//Iterando através de padrões de volume
	for (_node volumeNode = source.child("volume"); volumeNode; volumeNode = volumeNode.next_sibling("volume")){
		
		//Inserção de novo padrão de volume
		volume_vector.emplace(volumeNode.attribute("state").as_string(), new int[AUDIO_MAXLAYERS]);
		volumeArray = volume_vector[volumeNode.attribute("state").as_string()];
		counter = 0;

		//Preenchimento do vetor de volumes
		for(_node layerVolume = volumeNode.child("layer"); layerVolume; layerVolume = layerVolume.next_sibling()){
			volumeArray[counter] = layerVolume.attribute("value").as_int();
			counter++;
		}
	}

	if (true){
		for (auto it = volume_vector.begin(); it != volume_vector.end(); it++){
			std::cout << "Acquired State: " << it->first << std::endl;

			for (counter = 0; counter < AUDIO_MAXLAYERS; counter++){
				std::cout << "\t Channel " << counter + 1 << ": " << it->second[counter] << std::endl;
			}
		}
		std::cout << std::endl;
	}
}

void Music::SetVolumes(std::string state){
	int counter;
	int* targetVolume;

	if ((targetVolume = volume_vector[state]) != nullptr)
		for (counter = 0; counter < AUDIO_MAXLAYERS; counter++)
			volume[counter] = targetVolume[counter];
}
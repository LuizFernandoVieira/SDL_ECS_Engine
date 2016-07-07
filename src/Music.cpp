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

#define MUSIC_FADE_TIME 	100
#define VOLUME_THRESHOLD	10
#define VOLUME_SLIDE		5
#define PRINTITALL			false

#define TestVolume	MIX_MAX_VOLUME - 20

#define ROOT_DIRECTORY	"../"
#define CONFIG_XML	"../config.xml"

Music::Music(){
	int i;
	for (i = 0; i < AUDIO_MAXLAYERS; i++){
		volumeCurrent[i] 	= 0;
		volume[i] 			= 0;
		layer[i] = nullptr;
	}
}

Music::Music(std::string file){
	for (int i = 0; i < AUDIO_MAXLAYERS; i++){
		volumeCurrent[i] 	= 0;
		volume[i] 			= 0;
		layer[i]	= nullptr;
	}

	Open(file);
	Play();
}

Music::~Music(){
	Stop();

	for (int i = 0; i < AUDIO_MAXLAYERS; i++){
		volumeCurrent[i]	= 0;
		volume[i]			= 0;
		channel[i] 			= 0;
		layer[i]			= nullptr;
	}

	volume_vector.clear();
}

void Music::Play(){
	int i;
	for (i = 0; i < AUDIO_MAXLAYERS; i++){
		channel[i] = Mix_PlayChannel(-1, layer[i], -1);
		Mix_Volume(channel[i], volumeCurrent[i]);
	}
}

void Music::Stop(){
	Mix_HaltChannel(-1);
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

	if (In.keyPress(NUMKEY_1))	SetVolumes("all_on");
	if (In.keyPress(NUMKEY_2))	SetVolumes("all_off");

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

void Music::Load(_node source){
	if (source == nullptr)	return;

	int 	counter;
	int*	volumeArray;
	std::string	fileName;

	_node assetsNode;
	_node layerAsset;

	_node volumeNode;
	_node layerVolume;

	Stop();

	for (int i = 0; i < AUDIO_MAXLAYERS; i++){
		volumeCurrent[i]	= 0;
		volume[i]			= 0;
		channel[i] 			= 0;
		layer[i]			= nullptr;
	}

	volume_vector.clear();

	//Setando Arquivos de áudio a serem tocados
	assetsNode = source.child("assets");
	if (assetsNode != nullptr){
		for (counter = 0; counter < AUDIO_MAXLAYERS; counter++){
			layer[counter] = nullptr;
		}

		counter = 0;
		for (_node layerAsset = assetsNode.child("layer"); layerAsset; layerAsset = layerAsset.next_sibling()){
			//std::cout << "Filename: " << layerAsset.attribute("file").as_string() << std::endl;

			fileName = ROOT_DIRECTORY;
			fileName += layerAsset.attribute("file").as_string();
			layer[layerAsset.attribute("channel").as_int()] = Resources::GetSound(fileName);

			counter++;
		}
	}

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

	if (PRINTITALL){
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

void Music::Open(std::string file){
	_document 	doc;
	_parse		config;

	config = doc.load_file(file.c_str());
	if (config.status){
		std::cout << "[MUSIC] Error Reading CONFIG_FILE: " << config.description() << std::endl;
		std::cout << "\tStatus code: " << config.status << std::endl;
	}

	_node node = doc.first_child();

	//std::cout << "Reading State: " << node.child("state").attribute("name").as_string() << std::endl;

	//Setting Music Assets + Volume Patterns
	Load(node.child("state").child("music"));
}

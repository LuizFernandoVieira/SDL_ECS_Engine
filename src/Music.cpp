#include <iostream>

#include "../include/music.hpp"
#include "../include/inputhandler.hpp"
#include "../include/resources.hpp"

#define MUSIC_FADE_TIME 100

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


	//Test Sounds Loading
	layer[0] = Resources::GetSound(musiclayer1);
	layer[1] = Resources::GetSound(musiclayer2);
	layer[2] = Resources::GetSound(musiclayer3);
	layer[3] = Resources::GetSound(musiclayer4);
	layer[4] = Resources::GetSound(musiclayer5);


	layer[5] = Resources::GetSound(testaudiolayer);
	layer[6] = Resources::GetSound(testaudiolayer);
	layer[7] = Resources::GetSound(testaudiolayer);



	for (i = 0; i < AUDIO_MAXLAYERS; i++){
		/*
		//Carregar Layers
		layername = testaudiolayer;
		layer[i] = Resources::GetSound(layername);

		*/
		//Carregar Volumes
		volumeCurrent[i] = 0;
	}


	volumeCurrent[0] = MIX_MAX_VOLUME - 20;
	volumeCurrent[1] = MIX_MAX_VOLUME - 20;
	volumeCurrent[2] = MIX_MAX_VOLUME - 20;
	volumeCurrent[3] = MIX_MAX_VOLUME - 20;
	volumeCurrent[4] = MIX_MAX_VOLUME - 20;
	Play();
}

Music::Music(std::string file){
}


void Music::Play(){
	int i;
	for (i = 0; i < AUDIO_MAXLAYERS; i++){
		std::cout << "playing" << std::endl;
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
	//return (music != nullptr);
	return true;
}

void Music::Update(){
	//Teste de Canais
	InputHandler& In = InputHandler::getInstance();

	if (In.keyPress(NUMKEY_1)) {
		if (volumeCurrent[0] == 0)
			volumeCurrent[0] = MIX_MAX_VOLUME;
		else volumeCurrent[0] = 0;
	}

	if (In.keyPress(NUMKEY_2)) {
		if (volumeCurrent[1] == 0)
			volumeCurrent[1] = MIX_MAX_VOLUME;
		else volumeCurrent[1] = 0;
	}

	if (In.keyPress(NUMKEY_3)) {
		if (volumeCurrent[2] == 0)
			volumeCurrent[2] = MIX_MAX_VOLUME;
		else volumeCurrent[2] = 0;
	}

	if (In.keyPress(NUMKEY_4)) {
		if (volumeCurrent[3] == 0)
			volumeCurrent[3] = MIX_MAX_VOLUME;
		else volumeCurrent[3] = 0;
	}

	if (In.keyPress(NUMKEY_5)) {
		if (volumeCurrent[4] == 0)
			volumeCurrent[4] = MIX_MAX_VOLUME;
		else volumeCurrent[4] = 0;
	}

	if (In.keyPress(NUMKEY_6)) {
		if (volumeCurrent[5] == 0)
			volumeCurrent[5] = MIX_MAX_VOLUME;
		else volumeCurrent[5] = 0;
	}

	if (In.keyPress(NUMKEY_7)) {
		if (volumeCurrent[6] == 0)
			volumeCurrent[6] = MIX_MAX_VOLUME;
		else volumeCurrent[6] = 0;
	}

	if (In.keyPress(NUMKEY_8)) {
		if (volumeCurrent[7] == 0)
			volumeCurrent[7] = MIX_MAX_VOLUME;
		else volumeCurrent[7] = 0;
	}

	//Volume Setting
	int i;
	for (i = 0; i < AUDIO_MAXLAYERS; i++)
		Mix_Volume(channel[i], volumeCurrent[i]);

	/* Código Com Fades

	for ()

	*/

}

/*
#define VOLUME_THRESHOLD	10
#define VOLUME_SLIDE		10

void Music::SetVolumes(int*){
	short unsigned int i;
	short unsigned int volume_diff;

	for (i = 0; i < AUDIO_MAXLAYERS; i++){
		volume_diff = volume[i] - volumeCurrent[i];
		volumeSlide = VOLUME_SLIDE;

		//volume increase
		if (volume_diff == 0)
			continue;


private:
	SDL_Chunk* 	layer[AUDIO_MAXLAYERS];
	float 		vloume[AUDIO_MAXLAYERS];

};


		//Volume Decrease (Volume Increase is Standard Case)
		if (volume_diff < 0)
			volumeSlide * (-1);

		// ----------------------------

		//Volume Apply
		volumeCurrent[i] = Mix_Volume(channel[i], volumeCurrent[i] + volumeSlide);

		//volume lock
		if (abs(volume_diff) < AUDIO_THRESHOLD){
			volumeCurrent[i] = volume[i];
		}
	}
}
*/

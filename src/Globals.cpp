#include "../include/Globals.hpp"
/*

#define PRINTITALL false


void Globals::Read(std::string filename_){
	std::ifstream config;
	config.open(filename_, std::ifstream::in);

	//Tabelas Intermediárias
	std::unordered_map<std::string, int>		intValues;
	std::unordered_map<std::string, float>		floatValues;



	//Valores Intermediários
	int 		tempInt;
	float 		tempFloat;
	std::string	tempName;

	if(!config.is_open())
	{
		std::cout << "Erro na abertura do arquivo de globals para leitura" << std::endl;
		return;
	}

	//Aquisição de Valores
	config >> tempName;
	while(config.good())
	{
	
		//Parsing: Tipo da Variável
		if (tempName == "#INT")
		{
			config >> tempName;	//Nome da primeira variável
			while (tempName[0] != '#')
			{
				config >> tempInt;		//Valor Inteiro
				intValues.emplace(tempName, tempInt);
				if (PRINTITALL) std::cout << tempName << " = " << tempInt << std::endl;

				config >> tempName;		//Nome da próxima variável
			}
		}

		//Parsing: Tipo da Variável
		if (tempName == "#FLOAT")
		{
			config >> tempName;	//Nome da primeira variável
			while (tempName[0] != '#')
			{
				config >> tempFloat;		//Valor Inteiro
				if (PRINTITALL) std::cout << tempName << " = " << tempFloat << std::endl;
				floatValues.emplace(tempName, tempFloat);

				config >> tempName;			//Nome da próxima variável
			}
		}
		
		config >> tempName;
	}

	config.close();

	//Assossiação de Valores
	WINDOW_WIDTH 		= intValues["WINDOW_WIDTH"];
	WINDOW_HEIGHT 		= intValues["WINDOW_HEIGHT"];
	TILE_WIDTH 			= intValues["TILE_WIDTH"];
	TILE_HEIGHT 		= intValues["TILE_HEIGHT"];
	GRAVITY 			= intValues["GRAVITY"];

	PLAYER_JUMP_SPEED 	= floatValues["PLAYER_JUMP_SPEED"];
	PLAYER_WALK_SPEED 	= floatValues["PLAYER_WALK_SPEED"];
	


	//Test Printing
	if (PRINTITALL){
		std::cout << "Value WINDOW_WIDTH now equals: " 	<< intValues["WINDOW_WIDTH"] << std::endl;
		std::cout << "Value WINDOW_HEIGHT now equals: " << intValues["WINDOW_HEIGHT"] << std::endl;
		std::cout << "Value TILE_WIDTH now equals: " 	<< intValues["TILE_WIDTH"] << std::endl;
		std::cout << "Value TILE_HEIGHT now equals: " 	<< intValues["TILE_HEIGHT"] << std::endl;
		std::cout << "Value GRAVITY now equals: " 		<< intValues["GRAVITY"] << std::endl << std::endl;

		std::cout << "Value PLAYER_JUMP_SPEED now equals: " << floatValues["PLAYER_JUMP_SPEED"] << std::endl;
		std::cout << "Value PLAYER_WALK_SPEED now equals: " << floatValues["PLAYER_WALK_SPEED"] << std::endl;
	}

	intValues.clear();
	floatValues.clear();
}

*/
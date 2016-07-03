#ifndef AISYSTEM_HPP
#define AISYSTEM_HPP

#include "System.hpp"
#include "Timer.hpp"

//Apenas ignorem essa linha por enquanto
typedef const bool (*verification)();

class AISystem : public System
{
public:
	AISystem();

	~AISystem(){};
	void update(float dt, GameState& gameState);

private:

	//E essa também
	std::vector<verification> trigger_table;

	//Segunda Opção:
	//std::vector<bool>	
		//problema: sempre verifica todas as condições antes de começar a consulta

	//Available Triggers
	const bool AlwaysTrue(){
		return true;
	}
};

#endif
#ifndef AISYSTEM_HPP
#define AISYSTEM_HPP

#include "System.hpp"
#include "Timer.hpp"

#define MAX_CONDITIONS	10

//Apenas ignorem essa linha por enquanto
//typedef const bool (*verification)();


class AISystem : public System
{
public:
	AISystem();

	~AISystem(){};
	void update(float dt, GameState& gameState);

private:

	bool conditions[MAX_CONDITIONS];
	//void checkCondition[&](short int target);


	//E essa também
	//std::vector<verification> trigger_table;

	/*Available Triggers
	const bool AlwaysTrue(){
		return true;
	}
	*/
	
};

#endif
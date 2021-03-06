#ifndef AICOMPONENT_HPP
#define AICOMPONENT_HPP

#include "Timer.hpp"
#include "Component.hpp"
#include "CollisionMap.hpp"

class AIComponent : public Component{
private:

	enum EntityState
	{
		IDLE,
		WALKING,
		JUMPING,
		FALLING,
		ATTACKING,
		GRAPPLE,
		ZIPLINE,
		SHOOT,
		DEAD,
		FOLLOW,
		BLOWING,
		SUCKING,
		MOVE_RIGHT,
		MOVE_LEFT
	};

	class AIState{
		public:
			AIState(EntityState state_new, float action_hold = 0) {
				state 		= state_new;
				cooldown	= action_hold;
			};

			AIState();
			void addTrigger(short unsigned int condition_index,
			                short unsigned int target_index){

				triggers[condition_index] = target_index;
			};

			//short unsigned int state;
			EntityState state;
			std::unordered_map<short unsigned int, short unsigned int>	triggers;

			float cooldown;
	};

public:

	std::vector<bool>		conditions;
	std::vector<AIState>	states;
	short unsigned int 		state_index;
	short unsigned int		action_target;

	CollisionMap* 			terrain;
	Timer action_timer;


	//User-Defined AI
	AIComponent() : action_timer() {
		terrain = nullptr;
		AddState((int) IDLE);
		state_index = 0;
		action_target = 0;
	}

	//Template AI: Jumper
	AIComponent(int type) : action_timer(){
		terrain = nullptr;
		state_index = 0;
		action_target = 0;

		switch(type){

			case 1:
			//Follower
				AddState((int) IDLE, -0.1f);
				AddState((int) FOLLOW, 0.3f);

				states[0].addTrigger(10, 0);
				states[0].addTrigger(7, 1);

				states[1].addTrigger(10, 0);
				states[1].addTrigger(3, 0);
				states[1].addTrigger(6, 0);
			break;

			//Estátua
			case 2:
			break;

			default:
			AddState((int) IDLE);
			break;
		}
	};
	~AIComponent(){};

	void PrintAI(){
		for (auto st : states)
		{
			std::cout << "State: " << st.state << std::endl;
			for (auto trigger_it : st.triggers)
				std::cout << "\t	Trigger - Condition:  " << trigger_it.first << " Target: " << trigger_it.second << std::endl;
		}
	}
	void PrintCurrentState(){
		std::cout << "Current State: " << states[state_index].state << std::endl;
		std::cout << std::endl;
	}

	void AddState(int entityState, float action_hold = 0.0f){
		states.emplace_back(AIState((EntityState) entityState, action_hold));
	}

	void AddTrigger(short unsigned int state_index,
					short unsigned int condition_index,
					short unsigned int target_index){

		int state_ 	= state_index;
		int target_	= target_index;

		if (target_ > (int)states.size()) 	target_ = 0;
		if (state_ > (int)states.size()) 	state_ = 0;

		states[state_].addTrigger(condition_index, target_);
	}

	void SetTerrain(CollisionMap* target){terrain = target; };
};

namespace std
{
	template <>
	struct hash<AIComponent::EntityState>
	{
		std::size_t operator()(const State& k) const
		{
			using std::size_t;
			using std::hash;

			return ((hash<int>()((int)k)
					 ^ (hash<int>()((int)k) << 1)));
		}
	};
}

#endif

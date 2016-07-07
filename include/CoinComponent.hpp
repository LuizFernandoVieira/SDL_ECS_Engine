#ifndef COINCOMPONENT_HPP
#define COINCOMPONENT_HPP

#include "Component.hpp"

class CoinComponent : public Component
{
public:
	CoinComponent(): coinCounter_(0) {}
	~CoinComponent() {}

	int coinCounter_;
};

#endif

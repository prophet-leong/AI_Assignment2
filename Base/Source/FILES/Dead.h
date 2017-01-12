#pragma once
#include "States.h"
class Dead :public State
{
public:
	Dead();
	~Dead();
	virtual void update(double dt, Character* character, Character*enemy);
};


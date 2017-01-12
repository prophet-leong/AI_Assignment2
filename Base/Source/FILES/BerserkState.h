#pragma once
#include "States.h"
class BerserkState :public State
{
public:
	BerserkState();
	~BerserkState();
	virtual void update(double dt, Character* character, Character*enemy);
private:
};


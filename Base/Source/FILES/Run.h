#pragma once
#include "States.h"
class RunAway :public State
{
public:
	RunAway();
	~RunAway();
	virtual void update(double dt, Character* character, Character*enemy);
};
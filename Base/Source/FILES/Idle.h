#pragma once
#include "States.h"
class Idle:public State
{
public:
	Idle();
	~Idle();
	virtual void update(double dt, Character*enemy , Character *target);
};


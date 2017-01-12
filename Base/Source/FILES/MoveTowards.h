#pragma once
#include "States.h"
class MoveTowards:public State
{
public:
	MoveTowards();
	~MoveTowards();
	virtual void update(double dt, Character* character, Character*enemy);
};
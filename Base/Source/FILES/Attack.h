#pragma once
#include "States.h"
class Attack: public State
{
public:
	Attack();
	~Attack();
	virtual void update(double dt, Character* character, Character * enemy);
private:
	//attack cooldown
	float attackTime;
};
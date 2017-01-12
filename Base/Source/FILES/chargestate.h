#pragma once
#include "States.h"
class ChargeState :
	public State
{
public:
	ChargeState();
	~ChargeState();
	virtual void update(double dt, Character* character, Character*enemy);
private:
	float chargeTime;
	Vector2 Direction;
};


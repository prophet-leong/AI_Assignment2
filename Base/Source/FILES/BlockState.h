#pragma once
#include "States.h"
class BlockState :public State
{
public:
	BlockState();
	~BlockState();
	virtual void update(double dt, Character*enemy, Character *target);
private:
	bool RunOnce = false;
	float Timer;
	float MaxTimePerHeal;
	float timePerHeal;
};


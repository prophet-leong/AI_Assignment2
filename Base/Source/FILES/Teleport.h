#pragma once
#include "States.h"
class Teleport : public State
{
public:
	Teleport();
	~Teleport();
	virtual void update(double dt, Character* character, Character*enemy);
};

#pragma once
#include "States.h"
class Bribe : public State
{
public:
	Bribe();
	~Bribe();
	virtual void update(double dt, Character* character, Character * enemy);
private:
};
#pragma once
#include "States.h"
#include<vector>
using std::vector;
class Patrol :public State
{
public:
	Patrol();
	~Patrol();
	virtual void update(double dt, Character* character, Character*enemy);
	void MoveTo(double dt,Character* character, Vector2 pos);
protected:
};


#pragma once
#include"Character.h"
#include "States.h"
#include <vector>
using std::vector;
class Ally :public Character
{
public:
	Ally();
	Ally(Vector2 Position, int health, float moveSpeed, int attack, string Name, float attackRange, float attacksPerSecond, float detectionRange, Color color);
	virtual ~Ally();
	virtual void SetState(State* newState);
	virtual bool SetTarget(Character*Opponent);
	virtual void Update(double dt);
	virtual void UpdateFSM();
	virtual string printInfo();
	vector<Vector2*>WayPoints;
	int counter;
	string PrintStateName();
protected:
	State* currentState;
};


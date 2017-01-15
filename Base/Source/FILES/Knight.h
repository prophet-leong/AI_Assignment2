#pragma once
#include "Enemy.h"
class Knight :public Enemy
{
public:
	Knight();
	Knight(Vector2 Position, int health, float moveSpeed, int attack, string Name, float attackRange, float attacksPerSecond, 
		float detectionRange,float BlockDuration,int HealthHealed,Color color);
	Knight(Knight* other);
	~Knight();
	virtual void Update(double dt);
	virtual void UpdateFSM();
	float GetBlockBlockDuration();
	int GetTicks();
	virtual void SetMessage(Message* messsages);
	virtual void UpdateMessage();
private:
	bool chargestate = false;
	//block duration
	float BlockDuration;
	//healing ticks
	int Ticks;
};


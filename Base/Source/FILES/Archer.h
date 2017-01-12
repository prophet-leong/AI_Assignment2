#pragma once
#include "Enemy.h"
#include "Message.h"
class Archer:public Enemy
{
public:
	Archer();
	Archer(Vector2 Position, int health, float moveSpeed, int attack, float attacksPerSecond, string Name,float ShootingRange,Color color);
	~Archer();
	void setRun(bool q);
	void UpdateFSM();
	void Update(double dt);
	virtual void SetMessage(Message* messsages);
	virtual void UpdateMessage();
	bool run;
private:

};


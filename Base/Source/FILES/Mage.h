#pragma once
#include "Enemy.h"
class Mage :public Enemy
{
public:
	Mage();
	Mage(Vector2 Position, int health, float moveSpeed, int attack, float attacksPerSecond, string Name, float ShootingRange,Color color);
	Mage(Mage*others);
	~Mage();
	void Update(double dt);
	virtual void UpdateMessage();
	virtual void SetMessage(Message* messsages);
	void UpdateFSM();
	bool teleport;
private:
};

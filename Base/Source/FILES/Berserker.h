#pragma once
#include "Enemy.h"
class Berserker:public Enemy
{
public:
	Berserker();
	Berserker(Vector2 Position, int health, float moveSpeed, int attack, string Name, float attackRange, float attacksPerSecond, float detectionRange,Color color);
	~Berserker();
	
	virtual void Update(double dt);
	virtual void UpdateFSM();
	virtual void SetMessage(Message* messsages);
	virtual void UpdateMessage();
	void SetBerserkMode(bool berserkMode);
private:
	bool berserkMode = false;
};


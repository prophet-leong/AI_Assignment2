#pragma once
#include "Vector2.h"
#include "Color.h"
#include <string>
using std::string;
class Character
{
public:
	Character();
	Character(Vector2 Position, int health, float moveSpeed, int attack, string Name,Color color);
	virtual ~Character();
	virtual void Update(double dt){};
	virtual void UpdateFSM(){};
	Vector2 Position;
	Color color;
	int health;
	int maxHealth;
	float moveSpeed;
	int attack;
	float attacksPerSecond;
	//**************************Setters and Getters*******************************//
	bool GetIsDead();
	virtual void SetIsDead(bool dead);
	virtual string printInfo(){ return ""; }
	void overrideName(string name);
	string printName();
	void SetDetectionRange(float newRange);
	float GetDetectionRange();
	void SetAttackingRange(float newRange);
	float GetAttackingRange();
	virtual bool SetTarget(Character*Opponent){ return true; };
	virtual bool GetTarget(){ return (TargetedOpponent != nullptr); }
	//****************************************************************************//
protected:
	//range of dectection
	float detectionRange;
	float attackRange;
	bool isDead = false;
	string Name;
	Character *TargetedOpponent = 0;
};


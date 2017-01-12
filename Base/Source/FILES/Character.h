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
	void SetIsDead(bool dead);
	string KIMINONAWA();
	void SetDetectionRange(float newRange);
	float GetDetectionRange();
	void SetAttackingRange(float newRange);
	float GetAttackingRange();
	virtual void SetTarget(Character*Opponent){};
	//****************************************************************************//
protected:
	//range of dectection
	float detectionRange;
	float attackRange;
	bool isDead = false;
	string Name;
	Character *TargetedOpponent = 0;
};

#include "Ally.h"
#include "Patrol.h"
#include "Dead.h"
#include "MoveTowards.h"
#include "Attack.h"
#include "MessageBoard.h"
#include "Bribe.h"
#include <iostream>

Ally::Ally()
{
	counter = 0;
	currentState = new Patrol();
}
Ally::Ally(Vector2 Position, int health, float moveSpeed, int attack, string Name, float attackRange, float attacksPerSecond, float detectionRange, Color color)
{
	//TODO
	//change this to be able to set in a file
	WayPoints.push_back(new Vector2(15, -5));
	WayPoints.push_back(new Vector2(15, 5));
	WayPoints.push_back(new Vector2(5, 5));
	WayPoints.push_back(new Vector2(5, -5));
	counter = 0;
	TargetedOpponent = 0;
	currentState = new Patrol();
	this->Position = Position;
	this->health = health;
	this->maxHealth = this->health;
	this->moveSpeed = moveSpeed;
	this->attack = attack;
	this->attackRange = attackRange;
	this->attacksPerSecond = attacksPerSecond;
	this->detectionRange = detectionRange;
	this->Name = Name;
	this->color = color;
	
}
void Ally::Update(double dt)
{
	if (isDead)
		return;
	if (currentState != 0)
		currentState->update(dt, this, this->TargetedOpponent);

	if (TargetedOpponent != 0)
	{
		if (TargetedOpponent->GetIsDead() == true || (TargetedOpponent->Position - Position).LengthSquare() > detectionRange*detectionRange)
		{
			TargetedOpponent = 0;
		}
	}
	if (TargetedOpponent == 0 && currentState->stateName != "PATROL")
	{
		SetState(new Patrol());
	}

}
void Ally::UpdateFSM()
{
	static float lengthBetweenEnemy = 0.f;
	if (TargetedOpponent != 0)
	{
		lengthBetweenEnemy = (TargetedOpponent->Position - this->Position).Length();
	}
	if (health <= 0)
	{
		health = 0;
		SetState(new Dead());
		isDead = true;
	}
	else if (currentState->stateName == "PATROL" && TargetedOpponent != 0)
	{
		SetState(new MoveTowards());
	}
	else if ((currentState->stateName == "MOVETOWARDS") && (lengthBetweenEnemy < attackRange * 0.8f))
	{
		if (rand() % 10 == 0)
			SetState(new Bribe());
		else
			SetState(new Attack());
	}
	else if ((currentState->stateName == "ATTACK") && (lengthBetweenEnemy > attackRange))
	{
		SetState(new MoveTowards());
	}
}
bool Ally::SetTarget(Character *Opponent)
{
	if (TargetedOpponent == NULL || TargetedOpponent->GetIsDead())
	{
		if (Opponent->GetIsDead())
		{
			return false;
		}
		if ((Opponent->Position - Position).Length() < detectionRange)
		{
			TargetedOpponent = Opponent;
			return true;
		}
		return false;
	}
	return true;
}
void Ally::SetState(State* newState)
{
	delete currentState;
	currentState = newState;
}
Ally::~Ally()
{
	
	TargetedOpponent = NULL;
	for (unsigned int i = 0; i < WayPoints.size(); ++i)
	{
		delete WayPoints[i];
	}

	delete currentState;
	currentState = NULL;
}

string Ally::PrintStateName()
{
	return currentState->stateName;
}
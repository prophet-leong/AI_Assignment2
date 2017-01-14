#include "Ally.h"
#include "Patrol.h"
#include "Dead.h"
#include "MoveTowards.h"
#include "Attack.h"
#include "MessageBoard.h"
Ally::Ally()
{
	counter = 0;
	currentState = new Patrol();
}
Ally::Ally(Vector2 Position, int health, float moveSpeed, int attack, string Name, float attackRange, float attacksPerSecond, float detectionRange, Color color)
{
	//TODO
	//change this to be able to set in a file
	WayPoints.push_back(new Vector2(5, -5));
	WayPoints.push_back(new Vector2(5, 5));
	WayPoints.push_back(new Vector2(-5, 5));
	WayPoints.push_back(new Vector2(-5, -5));
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
		State* patrol = new Patrol();
		SetState(patrol);
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
		State *dead = new Dead();
		SetState(dead);
		isDead = true;
	}
	else if (currentState->stateName == "PATROL" && TargetedOpponent != 0)
	{
		State *moveto = new MoveTowards();
		SetState(moveto);
	}
	else if ((currentState->stateName == "MOVETOWARDS") && (lengthBetweenEnemy < attackRange * 0.8f))
	{
		State *attack = new Attack();
		SetState(attack);
	}
	else if ((currentState->stateName == "ATTACK") && (lengthBetweenEnemy > attackRange))
	{
		State *moveto = new MoveTowards();
		SetState(moveto);
	}
}
void Ally::SetTarget(Character *Opponent)
{
	if (TargetedOpponent == 0)
	{
		if (Opponent && (Opponent->Position - this->Position).Length() < detectionRange)
		{
			TargetedOpponent = Opponent;
		}
	}
}
void Ally::SetState(State* newState)
{
	if (currentState != 0)
		delete currentState;

	currentState = newState;
}
Ally::~Ally()
{

}

string Ally::PrintStateName()
{
	return currentState->stateName;
}
#include "Archer.h"
#include "Idle.h"
#include "MoveTowards.h"
#include "Attack.h"
#include "Dead.h"
#include "Run.h"
#include "MessageBoard.h"
Archer::Archer()
{
	
}
Archer::Archer(Vector2 Position, int health, float moveSpeed, int attack, float attacksPerSecond, string Name, float ShootingRange, Color color)
{
	this->Position = Position;
	this->health = health;
	this->moveSpeed = moveSpeed;
	this->attack = attack;
	this->Name = Name;
	this->attacksPerSecond = attacksPerSecond;
	this->attackRange = ShootingRange;
	this->detectionRange = ShootingRange;
	this->color = color;
	this->CurrentState = new Idle();
	this->maxHealth = health;
	messages = NULL;
	pendingRequest = false;
}
Archer::Archer(Archer* other)
{
	this->Position = other->Position;
	this->health = other->health;
	this->moveSpeed = other->moveSpeed;
	this->attack = other->attack;
	this->Name = other->Name;
	this->attacksPerSecond = other->attacksPerSecond;
	this->attackRange = other->attackRange;
	this->detectionRange = other->detectionRange;
	this->color = other->color;
	this->CurrentState = new Idle();
	this->maxHealth = other->maxHealth;
	messages = NULL;
	pendingRequest = false;
}
Archer::~Archer()
{
	Exit();
}

void Archer::Update(double dt)
{
	if (isDead)
		return;
	//just a backup check
	if (CurrentState != 0)
		CurrentState->update(dt, this, this->TargetedOpponent);
	//goes back to idle
	if (messages)
	{
		UpdateMessage();
		return;
	}
	if (TargetedOpponent == NULL)
	{
		SetState(new Idle());
	}
	//*1.2f for an offset so that the berserker wont keep losing its target 
	else if ((TargetedOpponent->Position - this->Position).Length() > detectionRange*1.2f)
	{
		TargetedOpponent = NULL;
		State* idle = new Idle();
		SetState(idle);
	}
	else if (TargetedOpponent->GetIsDead() == true)
	{
		TargetedOpponent = 0;
		State* idle = new Idle();
		SetState(idle);
	}
}
void Archer::UpdateMessage()
{
	if (TargetedOpponent->GetIsDead())
	{
		State* idle = new Idle();
		SetState(idle);
		messages = NULL;
		TargetedOpponent = NULL;
		return;
	}
	if ((TargetedOpponent->Position - this->Position).LengthSquare() < attackRange *attackRange*0.5f)
	{
		TargetedOpponent = NULL;
		State* idle = new Idle();
		SetState(idle);
		MessageBoard::GetInstance()->RemoveMessage(messages);
		messages = NULL;
	}
}
void Archer::UpdateFSM()
{
	static float lengthBetweenEnemy = 0.f;
	if (TargetedOpponent != 0)
	{
		lengthBetweenEnemy = (TargetedOpponent->Position - this->Position).Length();
	}
	if (this->health <= 0)
	{
		this->health = 0;
		isDead = true;
		delete CurrentState;
		CurrentState = 0;
		MessageBoard::GetInstance()->EnemiesAlive--;
		Exit();
		return;
	}
	else if (TargetedOpponent != NULL && (CurrentState->stateName == "IDLE") && (lengthBetweenEnemy < attackRange))
	{
		State *AttackEnemy = new Attack();
		SetState(AttackEnemy);
	}
	else if ((CurrentState->stateName == "ATTACK") && (lengthBetweenEnemy < attackRange * 0.5f))
	{
		State *run = new RunAway();
		SetState(run);
	}
	else if ((CurrentState->stateName == "RUNAWAY") && (lengthBetweenEnemy > attackRange * 0.5f))
	{
		State *AttackEnemy = new Attack();
		SetState(AttackEnemy);
	}
	else if (health < maxHealth * 0.5f)
	{
		if (!pendingRequest)
		{
			for (vector<Enemy*>::iterator i = MessageBoard::GetInstance()->GetEnemyVector().begin(); i != MessageBoard::GetInstance()->GetEnemyVector().end(); ++i)
			{
				if ((*i)->printName() == "Berserker")
				{
					pendingRequest = true;
					MessageBoard::GetInstance()->WriteToMessageBoard(new Message(MESSAGE_TYPE::NEED_HELP, AI_TYPES::BERSERKER, this));
					break;
				}
			}
		}
	}
}
void Archer::SetMessage(Message* message)
{
	messages = message;
	if (messages->message == MESSAGE_TYPE::NEED_HELP)
	{
		TargetedOpponent = message->from;
		State* MoveTowardsAlly = new MoveTowards();
		SetState(MoveTowardsAlly);
	}
	else if (messages->message == MESSAGE_TYPE::FORM_UP)
	{
		TargetedOpponent = message->from;
		State* MoveTowardsAlly = new MoveTowards();
		SetState(MoveTowardsAlly);
	}
}                                       
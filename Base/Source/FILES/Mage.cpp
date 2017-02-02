#include "Mage.h"
#include "Idle.h"
#include "MoveTowards.h"
#include "Attack.h"
#include "Dead.h"
#include "Teleport.h"
#include "MessageBoard.h"
Mage::Mage()
{

}
Mage::Mage(Vector2 Position, int health, float moveSpeed, int attack, float attacksPerSecond, string Name, float ShootingRange, Color color)
{
	this->Position = Position;
	this->health = health;
	this->moveSpeed = moveSpeed;
	this->attack = attack;
	this->attacksPerSecond = attacksPerSecond;
	this->Name = Name;
	this->attackRange = ShootingRange;
	this->detectionRange = ShootingRange;
	this->color = color;
	this->CurrentState = new Idle();
	this->maxHealth = health;
	this->teleport = false;
	messages = NULL;
	pendingRequest = false;
}
Mage::Mage(Mage*others)
{
	this->Position = others->Position;
	this->health = others->health;
	this->moveSpeed = others->moveSpeed;
	this->attack = others->attack;
	this->attacksPerSecond = others->attacksPerSecond;
	this->Name = others->Name;
	this->attackRange = others->attackRange;
	this->detectionRange = others->detectionRange;
	this->color = others->color;
	this->CurrentState = new Idle();
	this->maxHealth = others->maxHealth;
	this->teleport = others->teleport;
	messages = NULL;
	pendingRequest = false;
}
Mage::~Mage()
{
	Exit();
}

void Mage::Update(double dt)
{
	if (isDead)
		return;
	//just a backup check
	if (CurrentState != 0)
		CurrentState->update(dt, this, this->TargetedOpponent);
	if (messages)
	{
		UpdateMessage();
		return;
	}
	//goes back to idle
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
void Mage::UpdateMessage()
{
	if (TargetedOpponent->GetIsDead() || TargetedOpponent == NULL)
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
void Mage::UpdateFSM()
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
	else if ((lengthBetweenEnemy < attackRange * 0.5f) && (this->health < this->maxHealth * 0.5f) && !this->teleport)
	{
		if (!pendingRequest)
		{
			for (vector<Enemy*>::iterator i = MessageBoard::GetInstance()->GetEnemyVector().begin(); i != MessageBoard::GetInstance()->GetEnemyVector().end(); ++i)
			{
				if ((*i)->printName() == "Knight")
				{
					pendingRequest = true;
					MessageBoard::GetInstance()->WriteToMessageBoard(new Message(MESSAGE_TYPE::NEED_HELP, AI_TYPES::KNIGHT, this));
					break;
				}
			}
		}
		State *run = new Teleport();
		SetState(run);
	}
	else if ((CurrentState->stateName == "TELEPORT"))
	{
		State* idle = new Idle();
		SetState(idle);
	}
}
void Mage::SetMessage(Message* message)
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
}
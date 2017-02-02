#include "Berserker.h"
#include "Idle.h"
#include "MoveTowards.h"
#include "Attack.h"
#include "Dead.h"
#include "BerserkState.h"
#include "Run.h"
#include "MessageBoard.h"
Berserker::Berserker()
{
}
Berserker::Berserker(Vector2 Position, int health, float moveSpeed, int attack, string Name, float attackRange, float attacksPerSecond, float detectionRange,Color color)
{
	this->Position = Position;
	this->health = health;
	this->moveSpeed = moveSpeed;
	this->attack = attack;
	this->attackRange = attackRange;
	this->attacksPerSecond = attacksPerSecond;
	this->detectionRange = detectionRange;
	this->Name = Name;
	this->color = color;
	this->isDead = false;
	maxHealth = this->health;
	messages = NULL;
	pendingRequest = false;
	this->CurrentState = (rand() % 2 == 0 ? (State*)(new Idle()) : new BerserkState());

}
Berserker::Berserker(Berserker*other)
{
	this->Position = other->Position;
	this->health = other->health;
	this->moveSpeed = other->moveSpeed;
	this->attack = other->attack;
	this->attackRange = other->attackRange;
	this->attacksPerSecond = other->attacksPerSecond;
	this->detectionRange = other->detectionRange;
	this->Name = other->Name;
	this->color = other->color;
	this->isDead = false;
	maxHealth = other->maxHealth;
	messages = NULL;
	pendingRequest = false;
	this->CurrentState = (rand() % 2 == 0 ? (State*)(new Idle()) : new BerserkState());
}
void Berserker::Update(double dt)
{
	if (isDead)
		return;
	//just a backup check
	if (CurrentState != 0)
		CurrentState->update(dt, this,this->TargetedOpponent);
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
void Berserker::UpdateMessage()
{
	if (TargetedOpponent->GetIsDead())
	{
		State* idle = new Idle();
		SetState(idle);
		messages = NULL;
		TargetedOpponent = NULL;
		return;
	}
	if ((TargetedOpponent->Position - this->Position).LengthSquare() < attackRange *attackRange)
	{
		TargetedOpponent = NULL;
		State* idle;

		idle = !berserkMode ? (State*)(new BerserkState()) : new Idle;

		SetState(idle);
		MessageBoard::GetInstance()->RemoveMessage(messages);
		messages = NULL;
	}
}
void Berserker::UpdateFSM()
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
	else if (this->health < maxHealth * 0.5f)
	{
		for (vector<Enemy*>::iterator i = MessageBoard::GetInstance()->GetEnemyVector().begin(); i != MessageBoard::GetInstance()->GetEnemyVector().end(); ++i)
		{
			if ((*i)->printName() == "Mage")
			{
				if (!pendingRequest)
				{
					pendingRequest = true;
					MessageBoard::GetInstance()->WriteToMessageBoard(new Message(MESSAGE_TYPE::NEED_HELP, AI_TYPES::MAGE, this));
					break;
				}
			}
		}
		if (!berserkMode)
		{
			State* temp = (rand() % 2 == 0 ? (State*)(new BerserkState()) : new RunAway());
			SetState(temp);
			berserkMode = true;
		}
	}
	else if (TargetedOpponent != 0 && CurrentState->stateName == "IDLE")
	{
		//set state to move to enemy
		State* MoveTowardsEnemy = new MoveTowards();
		SetState(MoveTowardsEnemy);
	}
	else if ((CurrentState->stateName == "MOVETOWARDS") && (lengthBetweenEnemy < attackRange))
	{
		State *AttackEnemy = new Attack();
		SetState(AttackEnemy);
	}
	else if ((CurrentState->stateName == "ATTACK") && (lengthBetweenEnemy > attackRange))
	{
		State* MoveTowardsEnemy = new MoveTowards();
		SetState(MoveTowardsEnemy);
	}
}
void Berserker::SetMessage(Message* message)
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
void Berserker::SetBerserkMode(bool Mode)
{
	berserkMode = Mode;
}

Berserker::~Berserker()
{
}

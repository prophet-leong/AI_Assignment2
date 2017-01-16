#include "Knight.h"
#include "Idle.h"
#include "MoveTowards.h"
#include "Attack.h"
#include "Dead.h"
#include "BlockState.h"
#include "ChargeState.h"
#include "MessageBoard.h"
Knight::Knight()
{
}
Knight::Knight(Vector2 Position, int health, float moveSpeed, int attack, string Name, 
	float attackRange, float attacksPerSecond, float detectionRange, float BlockDuration, int HealthHealed,
	Color color
	)
{
	this->Position = Position;
	this->health = health;
	this->moveSpeed = moveSpeed;
	this->attack = attack;
	this->attackRange = attackRange;
	this->attacksPerSecond = attacksPerSecond;
	this->detectionRange = detectionRange;
	this->Name = Name;
	this->BlockDuration = BlockDuration;
	this->Ticks = HealthHealed;
	this->color = color;
	this->CurrentState = new Idle();
	this->maxHealth = health;
	this->isDead = false;
	messages = NULL;
	pendingRequest = false;
}
Knight::Knight(Knight* others)
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
	this->BlockDuration = others->BlockDuration;
	this->Ticks = others->Ticks;
	this->isDead = false;
	messages = NULL;
	pendingRequest = false;
}
void Knight::Update(double dt)
{
	if (isDead)
		return;
	if (TargetedOpponent == NULL)
	{
		SetState(new Idle);
		return;
	}
	//just a backup check
	if (CurrentState != 0)
		CurrentState->update(dt, this, this->TargetedOpponent);
	//skips distance checks
	if (messages)
	{
		UpdateMessage();
		return;
	}
	//goes back to idle
	if (TargetedOpponent != NULL)
	{
		//*1.2f for an offset so that the berserker wont keep losing its target 
		if ((TargetedOpponent->Position - this->Position).Length() > detectionRange*1.2f)
		{
			TargetedOpponent = NULL;
			State* idle = new Idle();
			SetState(idle);
		}
	}
}
void Knight::UpdateMessage()
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
		State* idle = new Idle();
		SetState(idle);
		MessageBoard::GetInstance()->RemoveMessage(messages);
		messages = NULL;
	}
}

void Knight::UpdateFSM()
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
		MessageBoard::GetInstance()->EnemiesAlive--;
		SetState(new Dead());
		return;
	}
	else if (this->health < maxHealth*0.3f && CurrentState->stateName != "BLOCKSTATE" && CurrentState->stateName != "CHARGESTATE")
	{
		if (pendingRequest == false)
		{
			pendingRequest = true;
	/*		if (rand() % 2 == 1)
				MessageBoard::GetInstance()->WriteToMessageBoard(new Message(MESSAGE_TYPE::NEED_HELP, AI_TYPES::ARCHER, this));
			else*/
			int temp = MessageBoard::GetInstance()->GetEnemiesAlive();
				MessageBoard::GetInstance()->WriteToMessageBoard(new MassMessage(MESSAGE_TYPE::FORM_UP, AI_TYPES::ALL, this,temp-1));

		}
		if (rand() % 2 == 1)
		{
			State* Block = new BlockState();
			SetState(Block);
		}
		else if (!chargestate)
		{
			State* charge = new ChargeState();
			SetState(charge);
			chargestate = true;
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
void Knight::SetMessage(Message* message)
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
float Knight::GetBlockBlockDuration()
{
	return BlockDuration;
}
int Knight::GetTicks()
{
	return Ticks;
}
Knight::~Knight()
{
	Exit();
}
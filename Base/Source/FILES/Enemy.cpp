#include "Enemy.h"
#include "MessageBoard.h"

Enemy::Enemy()
{
}
void Enemy::SetState(State* newState)
{
	if (CurrentState)
		delete CurrentState;
	CurrentState = newState;
}
string Enemy::PrintStateName()
{
	return CurrentState->stateName;
}
//setters and getters
bool Enemy::SetTarget(Character*Opponent)
{
	if (!TargetedOpponent|| TargetedOpponent->GetIsDead())
	{
		if (Opponent->GetIsDead())
		{
			return false;
		}
		if ((Opponent->Position - this->Position).Length() < detectionRange)
		{
			TargetedOpponent = Opponent;
			return true;
		}
		return false;
	}
	return true;
}
void Enemy::SetMessage(Message* messsages)
{
	this->messages = messages;
	TargetedOpponent = messsages->from;
}
Message* Enemy::GetMessage()
{
	return messages;
}
void Enemy::Exit()
{
	delete CurrentState;
	CurrentState = NULL;
	if (pendingRequest)
	{
		Message* temp = MessageBoard::GetInstance()->GetMessageFrom(this);
		MessageBoard::GetInstance()->RemoveMessage(temp);
	}
	if (messages != NULL)
	{
		switch (messages->message)
		{
			case MESSAGE_TYPE::NEED_HELP:
			{
				MessageBoard::GetInstance()->RemoveMessage(messages);
				break;
			}
			case MESSAGE_TYPE::FORM_UP:
			{
				MassMessage* temp = (MassMessage*)messages;
				temp->SentTo--;
				if (temp->SentTo <= 0)
					MessageBoard::GetInstance()->RemoveMessage(messages);
				break;
			}
		}
	}
}

string Enemy::printInfo()
{
	string temp = Name;
	if (CurrentState)
		temp += ":" + CurrentState->stateName;
	return temp;
}
void Enemy::SetIsDead(bool dead)
{
	isDead = dead;
}
Enemy::~Enemy()
{
	Exit();
}

#include "Enemy.h"
#include "MessageBoard.h"

Enemy::Enemy()
{
}
void Enemy::SetState(State* newState)
{
	if (CurrentState != 0)
		delete CurrentState;

	CurrentState = newState;
}
string Enemy::PrintStateName()
{
	return CurrentState->stateName;
}
//setters and getters
void Enemy::SetTarget(Character*Opponent)
{
	if (Opponent->GetIsDead() == false && (Opponent->Position - this->Position).Length() < detectionRange)
	{
		TargetedOpponent = Opponent;
	}
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
	if (CurrentState != NULL)
		delete CurrentState;
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
Enemy::~Enemy()
{
}

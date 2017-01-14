#include "MessageBoard.h"
#include "Archer.h"
#include "Berserker.h"
#include "Mage.h"
#include "Knight.h"
#include <iostream>
MessageBoard* MessageBoard::mb = new MessageBoard();
MessageBoard::MessageBoard()
{
	EnemiesAlive = 0;
	mb = nullptr;
}

MessageBoard::~MessageBoard()
{
}
MessageBoard* MessageBoard::GetInstance()
{
	if (!mb)
		mb = new MessageBoard();
	return mb;
}
void MessageBoard::Destroy()
{
	if (mb)
	{
		delete mb;
		mb = nullptr;
	}
}
void MessageBoard::UpdateAI(double dt)
{
	for (unsigned int i = 0; i < enemies.size(); ++i)
	{
		if (!enemies[i]->GetIsDead())
		{
			enemies[i]->Update(dt);
			enemies[i]->UpdateFSM();
			for (unsigned int a = 0; a < Allies.size(); ++a)
			{
				if (!Allies[a]->GetIsDead())
				enemies[i]->SetTarget(Allies[a]);
			}
		}
	}
	for (unsigned int i = 0; i < Allies.size(); ++i)
	{
		if (!Allies[i]->GetIsDead())
		{
			Allies[i]->Update(dt);
			Allies[i]->UpdateFSM();
			for (unsigned int a = 0; a <enemies.size(); ++a)
			{
				if (!enemies[a]->GetIsDead())
					Allies[i]->SetTarget(enemies[a]);
			}
		}
	}
}

void MessageBoard::WriteToMessageBoard(Message * newMessage)
{
	for (unsigned int i = 0; i < messages.size(); ++i)
	{
		if (messages[i] == NULL)
		{
			messages[i] = newMessage;
			SendMessageTo(newMessage);
			return;
		}
	}
	messages.push_back(newMessage);
	SendMessageTo(newMessage);
}
void MessageBoard::SendMessageTo(Message* message)
{
	string name;
	//set a name to check against from the enum
	switch (message->to)
	{
	case AI_TYPES::ARCHER:
		name = "Archer"; break;
	case AI_TYPES::BERSERKER:
		name = "Berserker"; break;
	case AI_TYPES::KNIGHT:
		name = "Knight"; break;
	case AI_TYPES::MAGE:
		name = "Mage"; break;
	case AI_TYPES::ALL:
		name = ""; break;
	}
	//if name = "" means all will recive
	if (name == "")
	{
		for (unsigned int i = 0; i < enemies.size(); ++i)
		{
			if (enemies[i] != message->from && enemies[i])
			{
				enemies[i]->SetMessage(message);
			}
		}
	}
	else
	{
		for (unsigned int i = 0; i < enemies.size(); ++i)
		{
			if (enemies[i] && enemies[i]->KIMINONAWA() == name)
			{
				if (enemies[i]->GetMessage() == NULL)
				{
					enemies[i]->SetMessage(message);
					return;
				}
			}
		}
		RemoveMessage(message);
	}

}
void MessageBoard::RemoveMessage(Message* oldMessage)
{
	if (oldMessage->message == MESSAGE_TYPE::FORM_UP)
	{
		MassMessage*temp = (MassMessage*)oldMessage;
		--temp->SentTo;
		if (temp->SentTo > 0)	//if this is not met it will continue downwards and delete the message
			return;				//end the function when condition met
	}
	for (unsigned int i = 0; i < messages.size(); ++i)
	{
		if (messages[i] == oldMessage)
		{
			((Enemy*)oldMessage->from)->pendingRequest = false;	//allows the enemy to send another help message
			delete messages[i];		//remove the actual data
			messages[i] = NULL;		//set the vector[i] to NULL so i can reuse
			return;					//end the function if condition met
		}
	}
}
Message* MessageBoard::GetMessageFrom(Character* Sender)
{
	for (unsigned int i = 0; i < messages.size(); ++i)
	{
		if (messages[i] == NULL)
			continue;
		if (messages[i]->from == Sender)
		{
			return messages[i];
		}
	}
	return NULL;
}
void MessageBoard::AddEnemy(Enemy* enemy)
{
	for (unsigned int i = 0; i < enemies.size(); ++i)
	{
		if (enemies[i]->GetIsDead())
		{
			delete enemies[i];
			enemies[i] = enemy;
			EnemiesAlive++;
			return;
		}
	}
	enemies.push_back(enemy);
}
void MessageBoard::RemoveEnemy(Enemy*enemy)
{
	//for (unsigned int i = 0; i < enemies.size(); ++i)
	//{
	//	if (enemies[i] == enemy)
	//	{
	//		enemies[i] = NULL;
	//		EnemiesAlive--;
	//		delete enemy;
	//		return;
	//	}
	//}
}
void MessageBoard::AddAlly(Ally* ally)
{
	for (unsigned int i = 0; i < Allies.size(); ++i)
	{
		if (Allies[i]->GetIsDead() == true)
		{
			delete Allies[i];
			Allies[i] = ally;
			return;
		}
	}
	Allies.push_back(ally);
}
void MessageBoard::RemoveAlly(Ally*ally)
{
	for (unsigned int i = 0; i < Allies.size(); ++i)
	{
		if (Allies[i] == ally)
		{
			Allies[i] = NULL;
			delete ally;
			return;
		}
	}
}
Enemy* MessageBoard::GetEnemy(int i)
{
	return enemies[i];
}
vector<Enemy*> MessageBoard::GetEnemyVector()
{
	return enemies;
}
Ally* MessageBoard::GetAlly(int i)
{
	return Allies[i];
}
vector<Ally*> MessageBoard::GetAllyVector()
{
	return Allies;
}
int MessageBoard::GetEnemiesAlive()
{
	return EnemiesAlive;
}
void MessageBoard::ClearAllAllies()
{
	Allies.clear();
}
void MessageBoard::ClearAllEnemies()
{
	enemies.clear();
}
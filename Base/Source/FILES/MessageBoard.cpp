#include "MessageBoard.h"
#include "Archer.h"
#include "Berserker.h"
#include "Mage.h"
#include "Knight.h"
#include <iostream>
using std::cout;
using std::endl;
MessageBoard* MessageBoard::mb = new MessageBoard();
MessageBoard::MessageBoard()
{
	EnemiesAlive = 0;
	mb = nullptr;
}

MessageBoard::~MessageBoard()
{
}

vector<Message*> & MessageBoard::getMessageVector()
{
	return messages;
}

void MessageBoard::getMessage()
{
	for (unsigned int i = 0; i < messages.size(); ++i)
	{
		if (messages[i] != NULL)
			cout << messages[i]->printMessage() << endl;
	}
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
		mb->ClearAllAllies();
		mb->ClearAllEnemies();
		for (unsigned int i = 0; i < mb->messages.size(); ++i)
		{
			delete mb->messages[i];
		}
		mb->messages.clear();
		delete mb;
		mb = NULL;
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
				if (enemies[i]->SetTarget(Allies[a]))
					break;
			}
		}
		else
		{
			std::swap(enemies[i], enemies[enemies.size() - 1]);
			delete enemies[enemies.size() - 1];
			enemies[enemies.size() - 1] = NULL;
			enemies.pop_back();
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
				if (Allies[i]->SetTarget(enemies[a]))
					break;
			}
		}
		else
		{
			std::swap(Allies[i], Allies[Allies.size() - 1]);
			delete Allies[Allies.size() - 1];
			Allies[Allies.size() - 1] = NULL;
			Allies.pop_back();
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
			getMessage();
			return;
		}
	}
	messages.push_back(newMessage);
	SendMessageTo(newMessage);
	getMessage();
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
			if (enemies[i] != message->from && !enemies[i]->GetIsDead())
			{
				enemies[i]->SetMessage(message);
			}
		}
	}
	else
	{
		for (unsigned int i = 0; i < enemies.size(); ++i)
		{
			if (!enemies[i]->GetIsDead() && enemies[i]->printName() == name)
			{
				if (enemies[i]->GetMessage() == NULL)
				{
					enemies[i]->SetMessage(message);
					return;
				}
			}
		}
	}
}
void MessageBoard::RemoveMessage(Message* oldMessage)
{
	if (!oldMessage)
		return;
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
			std::swap(messages[i], messages[messages.size() - 1]);
			delete messages[messages.size() - 1];
			messages[messages.size() - 1] = NULL;
			messages.pop_back();
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
	if (enemies.size() > (unsigned)(EnemiesAlive + 1))
	{
		for (unsigned int i = 0; i < enemies.size(); ++i)
		{
			if (enemies[i]->GetIsDead())
			{
				delete enemies[i];
				enemies[i] = enemy;
				EnemiesAlive++;
				break;
			}
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
			break;
		}
	}
	Allies.push_back(ally);
}
void MessageBoard::RemoveAlly(Ally* ally)
{
	for (unsigned int i = 0; i < Allies.size(); ++i)
	{
		if (Allies[i] == ally)
		{
			std::swap(Allies[i], Allies[Allies.size() - 1]);
			delete Allies[Allies.size() - 1];
			Allies[Allies.size() - 1] = NULL;
			Allies.pop_back();
			break;
		}
	}
}
Enemy* MessageBoard::GetEnemy(int i)
{
	return enemies[i];
}
vector<Enemy*> & MessageBoard::GetEnemyVector()
{
	return enemies;
}
Character* MessageBoard::GetAlly(int i)
{
	return Allies[i];
}
vector<Ally*> & MessageBoard::GetAllyVector()
{
	return Allies;
}
int MessageBoard::GetEnemiesAlive()
{
	return EnemiesAlive;
}
void MessageBoard::ClearAllAllies()
{
	for (unsigned int i = 0; i < Allies.size(); ++i)
	{
		delete Allies[i];
		Allies[i] = NULL;
	}
	Allies.clear();
}
void MessageBoard::ClearAllEnemies()
{
	for (unsigned int i = 0; i < enemies.size(); ++i)
	{
		delete enemies[i];
		enemies[i] = NULL;
	}
	enemies.clear();
}
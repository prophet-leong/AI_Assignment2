#ifndef MESSAGEBOARD_H
#define MESSAGEBOARD_H
#include "Enemy.h"
#include "Message.h"
#include "MassMessage.h"
#include "Ally.h"
#include <vector>
using std::vector;
class MessageBoard
{
public:
	static MessageBoard* GetInstance();
	static void Destroy();
	void WriteToMessageBoard(Message * newMessage);
	void RemoveMessage(Message* oldMessage);
	void SendMessageTo(Message* message);
	Message* GetMessageFrom(Character* Sender);
	void AddEnemy(Enemy* enemy);
	void RemoveEnemy(Enemy*enemy);
	void AddAlly(Ally* ally);
	void RemoveAlly(Ally*ally);
	void UpdateAI(double dt);
	Enemy* GetEnemy(int i);
	vector<Enemy*> GetEnemyVector();
	Ally* GetAlly(int i);
	vector<Ally*> GetAllyVector();
	int GetEnemiesAlive();
	void ClearAllEnemies();
	void ClearAllAllies();
protected:
	int EnemiesAlive;
	vector<Ally*>Allies;
	vector<Enemy*>enemies;
	vector<Message*>messages;
private:
	MessageBoard();
	virtual ~MessageBoard();
	static MessageBoard* mb;
};
#endif // !MESSAGEBOARD_H


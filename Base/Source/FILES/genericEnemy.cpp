#include "genericEnemy.h"

genericEnemy::genericEnemy()
{
}

genericEnemy::~genericEnemy()
{
	delete this;
}

void genericEnemy::Init(MyVector pos, string name, int hp)
{
	this->pos = pos;
	this->name = name;
	this->health = hp;
}

void genericEnemy::Update()
{
}

bool genericEnemy::checkPlayer(MyVector playerPos, float radius1, float radius2)
{
	bool detect = false;
	float totalRadius = radius1 + radius2;
	float distance = GetDistance(pos.x, pos.y, playerPos.x, playerPos.y);
	if (distance <= totalRadius) detect = true;
	return detect;
}

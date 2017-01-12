#include "Character.h"


Character::Character()
{
}
Character::Character(Vector2 Position, int health, float moveSpeed, int attack, string Name,Color color)
{
	this->Position = Position;
	this->health = health;
	this->moveSpeed = moveSpeed;
	this->attack = attack;
	this->Name = Name;
	this->color = color;
}
string Character::KIMINONAWA()
{
	return Name;
}
void Character::SetIsDead(bool dead)
{
	isDead = dead;
}
bool Character::GetIsDead()
{
	return isDead;
}
void Character::SetDetectionRange(float newDetectionRange)
{
	detectionRange = newDetectionRange;
}
float Character::GetDetectionRange()
{
	return detectionRange;
}
void Character::SetAttackingRange(float newAttackRange)
{
	attackRange = newAttackRange;
}
float Character::GetAttackingRange()
{
	return attackRange;
}
Character::~Character()
{
}

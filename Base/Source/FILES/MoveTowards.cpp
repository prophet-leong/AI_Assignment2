#include "MoveTowards.h"
MoveTowards::MoveTowards()
{
	stateName = "MOVETOWARDS";
}
void MoveTowards::update(double dt, Character* enemy, Character* target)
{
	enemy->Position = enemy->Position + ((target->Position - enemy->Position).Normalized() * enemy->moveSpeed * (float)dt);
}
MoveTowards::~MoveTowards()
{
}

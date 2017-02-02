#include "MoveTowards.h"
MoveTowards::MoveTowards()
{
	stateName = "MOVETOWARDS";
}
void MoveTowards::update(double dt, Character* enemy, Character* target)
{
	if (!target)
		return;
	enemy->Position = enemy->Position + ((target->Position - enemy->Position).Normalized() * enemy->moveSpeed * (float)dt);
}
MoveTowards::~MoveTowards()
{
}

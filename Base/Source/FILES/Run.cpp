#include "Run.h"
RunAway::RunAway()
{
	stateName = "RUNAWAY";
}
void RunAway::update(double dt, Character* enemy, Character* target)
{
	enemy->Position = enemy->Position - ((target->Position - enemy->Position).Normalized() * enemy->moveSpeed * (float)dt);
}
RunAway::~RunAway()
{
}
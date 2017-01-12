#include "Attack.h"
Attack::Attack()
{
	//0.5f is a debound time for the attack so that it wont attack when it enters this state
	stateName = "ATTACK";
	attackTime = 0.1f;
}
void Attack::update(double dt, Character* character, Character* enemy)
{
	if (attackTime <= 0.0f)
	{
		if ((character->Position - enemy->Position).Length() <= character->GetAttackingRange())
		{
			enemy->health -= character->attack;
			/*if (rand() % ((int)enemy->moveSpeed) == 0)
			{
			}*/
			//set the attack time base on how many attacks per second
			attackTime = 1.0f / character->attacksPerSecond;
		}
	}
	else
	{
		attackTime -= (float)dt;
	}
}
Attack::~Attack()
{
}

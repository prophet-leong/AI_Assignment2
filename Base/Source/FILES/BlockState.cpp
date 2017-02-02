#include "BlockState.h"
#include "Idle.h"
#include "Knight.h"

BlockState::BlockState()
{
	stateName = "BLOCKSTATE";
}
void BlockState::update(double dt, Character* self, Character *target)
{
	if ((Knight*)self->GetTarget())
	{
		if (!RunOnce)
		{
			Timer = ((Knight*)self)->GetBlockBlockDuration();
			MaxTimePerHeal = Timer / ((Knight*)self)->GetTicks();
			timePerHeal = MaxTimePerHeal;
			RunOnce = true;
		}
		else
		{
			if (Timer > 0)
			{
				Timer -= (float)dt;
				if (timePerHeal > 0)
				{
					timePerHeal -= (float)dt;
				}
				else
				{
					//change this later
					self->health += 1;
					timePerHeal = MaxTimePerHeal;
				}
			}
			else
			{
				((Knight*)self)->SetState(new Idle());
			}
		}
	}
	else
	{
		((Knight*)self)->SetState(new Idle());
	}
}
BlockState::~BlockState()
{
}

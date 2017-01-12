#include "BerserkState.h"
#include "Berserker.h"
#include "Idle.h"
BerserkState::BerserkState()
{
	stateName = "BERSERKSTATE";
}
void BerserkState::update(double dt, Character* character, Character*enemy)
{
	((Berserker*)character)->SetBerserkMode(true);
	((Berserker*)character)->SetDetectionRange(100.f);
	((Berserker*)character)->attack += 1;
	((Berserker*)character)->moveSpeed *= 1.5;
	((Berserker*)character)->attacksPerSecond *= 2;
	((Berserker*)character)->color = Color(1.0f, 0, 0);
	((Berserker*)character)->SetState(new Idle());
}

BerserkState::~BerserkState()
{
}

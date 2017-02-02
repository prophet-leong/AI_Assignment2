#include "ChargeState.h"
#include "Idle.h"
#include "Enemy.h"
ChargeState::ChargeState()
{
	chargeTime = 1.0f;
	stateName = "CHARGESTATE";
}
void ChargeState::update(double dt, Character* enemy, Character* target)
{
	if (!target)
		return;
	if(chargeTime == 1.0f)
		Direction = Vector2((target->Position - enemy->Position).Normalized());
	else if (chargeTime >= 0.0f)
	{
		Vector2 ChargeSpeed = Direction * enemy->moveSpeed * (float)dt * 2;
		enemy->Position = enemy->Position + ChargeSpeed;
		target->Position = target->Position + ChargeSpeed;
	}
	else if (chargeTime <= 0.0f)
	{
		((Enemy*)enemy)->SetState(new Idle());
	}
	chargeTime -= (float)dt;
}

ChargeState::~ChargeState()
{
}

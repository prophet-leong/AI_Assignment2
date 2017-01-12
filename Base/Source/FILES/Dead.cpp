#include "Dead.h"


Dead::Dead()
{
	stateName = "DEAD";
}
void Dead::update(double dt, Character* character, Character*enemy)
{
	character->SetIsDead(true);
}

Dead::~Dead()
{
}

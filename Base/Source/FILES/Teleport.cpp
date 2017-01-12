#include "Teleport.h"
#include <random>
#include <math.h>
#include "Mage.h"
#include <iostream>

Teleport::Teleport()
{
	stateName = "TELEPORT";
}
void Teleport::update(double dt, Character* self, Character* other)
{
	if (!((Mage*)(self))->teleport)
	{
		int action = rand() % 100 + 1;
		if (action >= 50)
		{
			self->Position.x = (float)(rand() % 20) - 10;
			self->Position.y = (float)(rand() % 20) - 10;
		}
		else if (action >= 25)
		{
			other->Position.x = (float)(rand() % 20) - 10;
			other->Position.y = (float)(rand() % 20) - 10;
		}
		else
		{
			self->Position.x = (float)(rand() % 20) - 10;
			self->Position.y = (float)(rand() % 20) - 10;
			other->Position.x = (float)(rand() % 20) - 10;
			other->Position.y = (float)(rand() % 20) - 10;
		}
		((Mage*)(self))->teleport = true;
	}
}
Teleport::~Teleport()
{
}

#include "Patrol.h"
#include "Ally.h"

Patrol::Patrol()
{
	stateName = "PATROL";
}

void Patrol::update(double dt, Character* character, Character*enemy)
{
	if ((unsigned)((Ally*)character)->counter < ((Ally*)character)->WayPoints.size())
	{
		Vector2 targetLocation = *((Ally*)character)->WayPoints[((Ally*)character)->counter];
		MoveTo(dt, ((Ally*)character), targetLocation);
		if ((targetLocation - ((Ally*)character)->Position).Length() < 0.3f)
			++((Ally*)character)->counter;
	}
	else
	{
		((Ally*)character)->counter = 0;
	}
}
void Patrol::MoveTo(double dt,Character * character,Vector2 pos)
{
	Vector2 target = (pos - character->Position).Normalized();
	character->Position = character->Position + (target*character->moveSpeed * (float)dt);
}
Patrol::~Patrol()
{
}

#include "Bribe.h"
#include "MessageBoard.h"
#include "Knight.h"
#include "Mage.h"
#include "Berserker.h"
#include "Archer.h"


Bribe::Bribe()
{
}
Bribe::~Bribe()
{
}
void Bribe::update(double dt, Character* character, Character * enemy)
{
	enemy->SetIsDead(true);//make the real enemy dead first, i can't remove it as there might be other objects using it
	MessageBoard::GetInstance()->EnemiesAlive--;
	Character* BribeTarget;
	if (enemy->KIMINONAWA() == "Knight")
		BribeTarget = new Knight(((Knight*)enemy));
	else if (enemy->KIMINONAWA() == "Mage")
		BribeTarget = new Mage(((Mage*)enemy));
	else if (enemy->KIMINONAWA() == "Berserker")
		BribeTarget = new Berserker(((Berserker*)enemy));
	else if (enemy->KIMINONAWA() == "Archer")
		BribeTarget = new Archer(((Archer*)enemy));

	MessageBoard::GetInstance()->AddAlly(BribeTarget);//make an exact same copy and put into the ally vector
}

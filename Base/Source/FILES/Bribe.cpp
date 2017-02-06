#include "Bribe.h"
#include "MessageBoard.h"
#include "Knight.h"
#include "Mage.h"
#include "Berserker.h"
#include "Archer.h"


Bribe::Bribe()
{
	stateName = "BRIBE";
}
Bribe::~Bribe()
{
}
void Bribe::update(double dt, Character* character, Character * enemy)
{
	enemy->SetIsDead(true);//make the real enemy dead first, i can't remove it as there might be other objects using it
	MessageBoard::GetInstance()->EnemiesAlive--;
	Ally* BribeTarget;

	/*if (enemy->printName() == "Knight")
		BribeTarget = new Knight(((Knight*)enemy));
	else if (enemy->printName() == "Mage")
		BribeTarget = new Mage(((Mage*)enemy));
	else if (enemy->printName() == "Berserker")
		BribeTarget = new Berserker(((Berserker*)enemy));
	else if (enemy->printName() == "Archer")
		BribeTarget = new Archer(((Archer*)enemy));*/

	BribeTarget = new Ally(enemy->Position, enemy->health, enemy->moveSpeed, enemy->attack, "Ally->"+enemy->printName(), enemy->GetAttackingRange(), enemy->attacksPerSecond, enemy->GetDetectionRange(),  Color(0.0f, 0.8f, 0.0f));
	//depending on what they were, this could be some seriously strong shit

	MessageBoard::GetInstance()->AddAlly(BribeTarget);//make an exact same copy and put into the ally vector
}

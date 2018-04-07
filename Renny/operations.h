#pragma once
#include "functions.h"


namespace Operations
{


	void Init();

	void CastSpell(object* enemyChamp, int slot, bool enemyMoving);

	void IssueAttackOrder(object* enemyChamp);

	void IssueMoveOrder();

}


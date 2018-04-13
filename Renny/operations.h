#pragma once
#include "functions.h"


namespace Operations
{


	void Init();

	void CastSpell(object* enemyChamp, int slot);

	void IssueAttackOrder(object* enemyChamp);

	void IssueMoveOrder(Vector positionToMoveTo);

}


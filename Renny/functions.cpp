#include "stdafx.h"
#include "functions.h"
#include "hooks.h"

float calculateEnemyFuturePositionCenter(float distanceTravelledDuringCast, float sumSquared, float missileSpeed, float missileWidth, float moveSpeed, float direction, float castTime) {
	return (((distanceTravelledDuringCast + ((sumSquared / missileSpeed) * moveSpeed))) * direction);
}

void applyActiveCastInfo(DWORD address) {
	if (address != NULL) {
		spellCastData = (SpellCastDataBase*)(address);
	}
}

void getListOfEnemyChamps(object* myPlayer)
{
	int enemyTeam = 0;

	if (myPlayer->team == 200) {
		enemyTeam = 100;
	}
	else {
		enemyTeam = 200;
	}

	for (int i = 0; i < objMgr->ArrayHighestIndex; i++) {
		if (objMgr->objectManagerArray[i] != NULL) {
			object* TemporaryObject = objMgr->objectManagerArray[i];
			if (TemporaryObject->team == enemyTeam)
			{
				if (TemporaryObject->mIsTargetable)
				{
					if (TemporaryObject->champion == 5121)
					{
						listOfEnemyChamps.push_back(TemporaryObject);
					}
				}
			}
		}
	}
}

bool isMoving(object* targetChamp)
{
	bool isChampMoving = false;
	firstPosition = targetChamp->unitPos;
	Sleep(33);
	secondPosition = targetChamp->unitPos;
	if (firstPosition.x != secondPosition.x) {
		isChampMoving = true;
	}
	if (firstPosition.z != secondPosition.z) {
		isChampMoving = true;
	}
	return isChampMoving;
}

object* getClosestEnemy(object* myPlayer, float range) {
	object* closestEnemy = nullptr;
	float closestDistance = static_cast<float>(15000000.0);
	Vector myPos = myPlayer->unitPos;
	std::vector<object*>::iterator iter;
	for (iter = listOfEnemyChamps.begin(); iter != listOfEnemyChamps.end(); iter++) {
		Vector enemyPos = (*iter)->unitPos;
		float differenceX = myPos.x - enemyPos.x;
		differenceX = static_cast<float>(std::fabs(differenceX));
		float differenceZ = myPos.z - enemyPos.z;
		differenceZ = static_cast<float>(std::fabs(differenceZ));
		float distanceFromMe = differenceX + differenceZ;
		//((*iter)->mHP) / ((*iter)->mMaxHP)
		if (distanceFromMe < closestDistance && ((*iter)->isDead == false) && ((*iter)->isVisible) && (range >= distanceFromMe))
		{
			closestEnemy = (*iter);
			closestDistance = distanceFromMe;
		}
	}

	return closestEnemy;
}
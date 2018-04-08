#include "stdafx.h"
#include "functions.h"
#include "hooks.h"

bool isPositive(float number) {
	return (number > 0);
}
bool isNegative(float number) {
	return (number < 0);
}
bool isZero(float number) {
	return (number == 0);
}

float modifySign(float numberToCheck, float numberToModify) {
	if (isNegative(numberToCheck)) {
		return (numberToModify * -1.0f);
	}
	if (isPositive(numberToCheck)) {
		return numberToModify;
	}
	if (isZero(numberToCheck)) {
		return 0;
	}
}

float calculateEnemyFuturePosition(float distanceTravelledDuringCast, float sumSquared, float missileSpeed, float missileWidth, float moveSpeed, float direction, float castTime) {
	return (((distanceTravelledDuringCast + ((sumSquared / missileSpeed) * moveSpeed))) * direction);
}

void applyActiveCastInfo(DWORD address) {
	if (address != NULL) {
		spellCastData = (spellCastDataBase*)(address);
	}
}

void getListOfEnemyChamps(object* myPlayer)
{
	int enemyTeam = 0;

	if (myPlayer->mTeam == 200) {
		enemyTeam = 100;
	}
	else {
		enemyTeam = 200;
	}

	for (int i = 0; i < objMgr->mArrayHighestIndex; i++) {
		if (objMgr->mObjectManagerArray[i] != NULL) {
			object* TemporaryObject = objMgr->mObjectManagerArray[i];
			if (TemporaryObject->mTeam == enemyTeam)
			{
				if (TemporaryObject->mIsTargetable)
				{
					if (TemporaryObject->mUnitType == 5121)
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
	firstPosition = targetChamp->mUnitPos;
	Sleep(33);
	secondPosition = targetChamp->mUnitPos;
	secondDirectionFaced = targetChamp->mDirectionFaced;
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
	Vector myPos = myPlayer->mUnitPos;
	std::vector<object*>::iterator iter;
	for (iter = listOfEnemyChamps.begin(); iter != listOfEnemyChamps.end(); iter++) {
		Vector enemyPos = (*iter)->mUnitPos;
		float differenceX = myPos.x - enemyPos.x;
		differenceX = static_cast<float>(std::fabs(differenceX));
		float differenceZ = myPos.z - enemyPos.z;
		differenceZ = static_cast<float>(std::fabs(differenceZ));
		float distanceFromMe = differenceX + differenceZ;
		//((*iter)->mHP) / ((*iter)->mMaxHP)
		if (distanceFromMe < closestDistance && ((*iter)->mIsDead == false) && ((*iter)->isVisible) && (range >= distanceFromMe))
		{
			closestEnemy = (*iter);
			closestDistance = distanceFromMe;
		}
	}

	return closestEnemy;
}
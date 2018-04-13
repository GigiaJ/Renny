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
	return NULL;
}

float calculateEnemyFuturePosition(float distanceTravelledDuringCast, float sumSquared, float missileSpeed, float missileWidth, float moveSpeed, float direction, float castTime) {
	return (((distanceTravelledDuringCast + ((sumSquared / missileSpeed) * moveSpeed))) * direction);
}

float absVectorDistance(Vector firstVector, Vector secondVector) {
	float distanceFromEachotherX = secondVector.x - firstVector.x;
	float distanceFromEachotherZ =  secondVector.z - firstVector.z;
	float absoluteDistanceFromEachotherX = static_cast<float>(std::fabs(distanceFromEachotherX));
	float absoluteDistanceFromEachotherZ = static_cast<float>(std::fabs(distanceFromEachotherZ));
	return  absoluteDistanceFromEachotherX + absoluteDistanceFromEachotherZ;
}

float absObjectDistanceApart(object* unitOne, object*unitTwo) {
	float unitSizesAdded = (unitOne->getUnitSize() / 2) + (unitTwo->getUnitSize() / 2);
	float absoluteCentersApart = absVectorDistance(unitOne->mUnitPos, unitTwo->mUnitPos);
	return (absoluteCentersApart + unitSizesAdded);
}

void applyActiveAutoCastInfo(DWORD address) {
		spellCastData = (spellCastDataBase*)(address);
}

void applyActiveSpellCastInfo(DWORD address) {
	spellCastData = (spellCastDataBase*)(address);
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

object* getClosestEnemy(object* myPlayer, float range, float castRadius) {
	object* closestEnemy = nullptr;
	float closestDistance = static_cast<float>(15000000.0);
	std::vector<object*>::iterator iter;
	for (iter = listOfEnemyChamps.begin(); iter != listOfEnemyChamps.end(); iter++) {
		float unitSize = (*iter)->getUnitSize();
		float distanceApart = absObjectDistanceApart(myPlayer, (*iter));
		//((*iter)->mHP) / ((*iter)->mMaxHP)
		if (distanceApart < closestDistance && ((*iter)->mIsDead == false) && ((*iter)->isVisible) && (range >= distanceApart))
		{
			closestEnemy = (*iter);
			closestDistance = distanceApart;
		}
	}

	return closestEnemy;
}
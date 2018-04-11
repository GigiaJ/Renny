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

float resetDelay(float delay) {
	return (delay + vGameTime);
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
	float distanceFromEachotherX = firstVector.x - secondVector.x;
	float distanceFromEachotherZ = secondVector.z - secondVector.z;
	float absoluteDistanceFromEachotherX = static_cast<float>(std::fabs(distanceFromEachotherX));
	float absoluteDistanceFromEachotherZ = static_cast<float>(std::fabs(distanceFromEachotherZ));
	return  absoluteDistanceFromEachotherX + absoluteDistanceFromEachotherZ;
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
	Vector myPos = myPlayer->mUnitPos;
	std::vector<object*>::iterator iter;
	for (iter = listOfEnemyChamps.begin(); iter != listOfEnemyChamps.end(); iter++) {
		Vector enemyPos = (*iter)->mUnitPos;
		float unitSize = (*iter)->mEdgePos2.x - (*iter)->mEdgePos1.x;
		float distanceApart = absVectorDistance(myPos, enemyPos);
		//((*iter)->mHP) / ((*iter)->mMaxHP)
		if (distanceApart < closestDistance && ((*iter)->mIsDead == false) && ((*iter)->isVisible) && ((range + unitSize + castRadius) >= distanceApart))
		{
			closestEnemy = (*iter);
			closestDistance = distanceApart;
		}
	}

	return closestEnemy;
}
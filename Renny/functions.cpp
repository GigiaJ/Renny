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

void setEnemyTeam(object* myPlayer) {
	if (myPlayer->mTeam == 200) {
		enemyTeam = 100;
	}
	else {
		enemyTeam = 200;
	}
}

float modifySign(float numberToCheck, float numberToModify) {
	if (isNegative(numberToCheck)) {
		return (abs(numberToModify) * -1.0f);
	}
	if (isPositive(numberToCheck)) {
		return abs(numberToModify);
	}
	if (isZero(numberToCheck)) {
		return 0.0f;
	}
	return NULL;
}

float calculateEnemyFuturePosition(float distanceTravelledDuringCast, float sumSquared, float missileSpeed, float missileWidth, float moveSpeed, float direction, float castTime) {
	return (((distanceTravelledDuringCast + ((sumSquared / missileSpeed) * moveSpeed))) * direction);
}

float absVectorDistance(Vector firstVector, Vector secondVector) {
	float distanceFromEachotherX = secondVector.x - firstVector.x;
	float distanceFromEachotherZ =  secondVector.z - firstVector.z;
	float absoluteDistanceFromEachotherX = std::abs(distanceFromEachotherX);
	float absoluteDistanceFromEachotherZ = std::abs(distanceFromEachotherZ);
	return  absoluteDistanceFromEachotherX + absoluteDistanceFromEachotherZ;
}

float absObjectDistanceApart(object* unitOne, object*unitTwo) {
	float unitSizesAdded = (unitOne->getUnitSize() / 2) + (unitTwo->getUnitSize() / 2);
	float absoluteCentersApart = absVectorDistance(unitOne->mUnitPos, unitTwo->mUnitPos);
	return (absoluteCentersApart - unitSizesAdded);
}

void getListOfEnemyChamps(object* myPlayer)
{
	std::ofstream myfile;
	myfile.open("C:\\Users\\gigia\\Desktop\\Script Development\\output.txt");
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
	myfile.close();
}

object* getClosestEnemy(object* myPlayer, float range, float castRadius) {
	object* closestEnemy = nullptr;
	float closestDistance = static_cast<float>(15000000.0);
	std::vector<object*>::iterator iter;
	for (iter = listOfEnemyChamps.begin(); iter != listOfEnemyChamps.end(); iter++) {
		float unitSize = (*iter)->getUnitSize();
		float distanceApart = absObjectDistanceApart(myPlayer, (*iter));
		//((*iter)->mHP) / ((*iter)->mMaxHP)
		float edgeDistance = distanceApart - ((*iter)->getUnitSize() + (myPlayer->getUnitSize())) - castRadius;
		if (distanceApart < closestDistance && ((*iter)->mIsDead == false) && ((*iter)->isVisible) && (range >= edgeDistance))
		{
			closestEnemy = (*iter);
			closestDistance = distanceApart;
		}
	}

	return closestEnemy;
}
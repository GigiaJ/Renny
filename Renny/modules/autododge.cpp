#include "../stdafx.h"
#include "modules.h"

float signOfXDifference(Vector firstVector, Vector secondVector) {
	float numberToCheck = secondVector.x - firstVector.x;
	if (isNegative(numberToCheck)) {
		return -1.0f;
	}
	if (isPositive(numberToCheck)) {
		return 1.0f;
	}
	if (isZero(numberToCheck)) {
		return 0.0f;
	}
	return NULL;
}

Vector findClosestPoint(float slope, float xPos, float targetXPos, Vector targetObjPos) {
	Vector closestPoint;
	float closestDistance = 1500000.0f;
	while (xPos < targetXPos) {
		Vector positionToTest = {};
		positionToTest.x = xPos;
		positionToTest.y = 0.0f;
		positionToTest.z = xPos * slope;

		float distance = absVectorDistance(targetObjPos, positionToTest);

		if (distance < closestDistance) {
			closestDistance = distance;
			closestPoint = positionToTest;
		}
		xPos++;
	}
	return closestPoint;
}

void autododge(object* myPlayer) {
	if (spellCastData != NULL) {
		int enemyTeam = setEnemyTeam(myPlayer);
		float distanceApart = absVectorDistance(myPlayer->mUnitPos, objMgr->mObjectManagerArray[spellCastData->casterIndex]->mUnitPos);
		if (enemyTeam == objMgr->mObjectManagerArray[spellCastData->casterIndex]->mTeam) {
			if (spellCastData->mSpellData->mSpellInfo->mMissileSpeed > 0.0f) {
				if (spellCastData->mSpellData->mSpellInfo->mMaxRange < distanceApart) {
					float slope = (spellCastData->mTargetPosition.z - objMgr->mObjectManagerArray[spellCastData->casterIndex]->mUnitPos.z) / (spellCastData->mTargetPosition.x - objMgr->mObjectManagerArray[spellCastData->casterIndex]->mUnitPos.x);
					float xSign = signOfXDifference(myPlayer->mUnitPos, objMgr->mObjectManagerArray[spellCastData->casterIndex]->mUnitPos);
					float targetXPos = spellCastData->mTargetPosition.x;
					float xPos = objMgr->mObjectManagerArray[spellCastData->casterIndex]->mUnitPos.x;

					Vector closestPoint = findClosestPoint(slope, xPos, targetXPos, myPlayer->mUnitPos);

					float distanceFromProjectile = absVectorDistance(closestPoint, myPlayer->mUnitPos);
					float distanceFromProjectileEdge = distanceFromProjectile + (spellCastData->mSpellData->mSpellInfo->mMissileWidth / 2);
					if (distanceFromProjectileEdge <= myPlayer->getUnitSize()) {

						Vector positionToMoveTo = {};
						positionToMoveTo.x = myPlayer->mUnitPos.x + (distanceFromProjectile * xSign);
						positionToMoveTo.y = 0.0f;
						positionToMoveTo.x = (myPlayer->mUnitPos.z * slope) + (distanceFromProjectile * xSign);
						Operations::IssueMoveOrder(positionToMoveTo);
					}

					//Check the points on the slope minus the missile width to see what points are closest to the center of the object being aimed at
					//Run through the slope 
						//spellCastData->mSpellData->mSpellInfo->mMissileWidth
				}
			}
		}
	}
}


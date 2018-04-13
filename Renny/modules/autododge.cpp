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

float findClosestPoint(float slope, float xPos, float targetXPos, Vector targetObjPos) {
	float closestPoint = 1500000.0f;
	while (xPos < targetXPos) {
		

	}
}

void autododge(object* myPlayer) {
	if (spellCastData != NULL) {
		float distanceApart = absVectorDistance(myPlayer->mUnitPos, objMgr->mObjectManagerArray[spellCastData->casterIndex]->mUnitPos);
		if (spellCastData->mSpellData->mSpellInfo->mMaxRange < distanceApart) {
			float slope = (spellCastData->mTargetPosition.z - objMgr->mObjectManagerArray[spellCastData->casterIndex]->mUnitPos.z) / (spellCastData->mTargetPosition.x - objMgr->mObjectManagerArray[spellCastData->casterIndex]->mUnitPos.x);
			float distance = signOfXDifference(myPlayer->mUnitPos, objMgr->mObjectManagerArray[spellCastData->casterIndex]->mUnitPos);
			float xPos = objMgr->mObjectManagerArray[spellCastData->casterIndex]->mUnitPos.x + distance;
			float zPos = (xPos) * slope;
			
			
			//Check the points on the slope minus the missile width to see what points are closest to the center of the object being aimed at
			//Run through the slope 
				//spellCastData->mSpellData->mSpellInfo->mMissileWidth
		}
	}
}


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

void autododge(object* myPlayer) {
	if (spellCastData != NULL) {
		float distanceApart = absVectorDistance(myPlayer->mUnitPos, objMgr->mObjectManagerArray[spellCastData->casterIndex]->mUnitPos);
		if (spellCastData->mSpellData->mSpellInfo->mMaxRange < distanceApart) {
			float slope = (spellCastData->mTargetPosition.z - objMgr->mObjectManagerArray[spellCastData->casterIndex]->mUnitPos.z) / (spellCastData->mTargetPosition.x - objMgr->mObjectManagerArray[spellCastData->casterIndex]->mUnitPos.x);
			float distance = signOfXDifference(myPlayer->mUnitPos, objMgr->mObjectManagerArray[spellCastData->casterIndex]->mUnitPos);
			float xPos = objMgr->mObjectManagerArray[spellCastData->casterIndex]->mUnitPos.x + distance;
			float zPos = (objMgr->mObjectManagerArray[spellCastData->casterIndex]->mUnitPos.x + distance) * slope;
			
			//Check the points on the slope minus the missile width to see what points are closest to the center of the object being aimed at

				//spellCastData->mSpellData->mSpellInfo->mMissileWidth
		}
	}
}


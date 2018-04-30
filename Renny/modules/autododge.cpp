#include "../stdafx.h"
#include "modules.h"

Vector empty = {};

float signOfPointDifference(float firstPoint, float secondPoint) {
	float numberToCheck = abs(secondPoint) - abs(firstPoint);
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

Vector findClosestPoint(Slope slope, Vector castPosition, Vector targetPosition, Vector targetObjPos) {
	
	int xDifference = static_cast<int>(abs(castPosition.x - targetPosition.x));
	int xPos = static_cast<int>(castPosition.x);
	float zPos = castPosition.z;
	int targetXPos = static_cast<int>(targetPosition.x);
	Vector closestPoint;
	float closestDistance = 1500000.0f;
	int counter = 0;
	while (xPos != targetXPos && counter < xDifference + 1) {
		Vector positionToTest = {};
		positionToTest.x = static_cast<float>(xPos);
		positionToTest.y = 0.0f;
		positionToTest.z = zPos;

		float distance = absVectorDistance(targetObjPos, positionToTest);

		if (distance < closestDistance) {
			closestDistance = distance;
			closestPoint = positionToTest;
		}
		if (slope.denominator != 0.0f) {
			xPos++;
		}
		if (slope.numerator != 0.0f) {
			zPos = zPos + slope.gradient;
		}
		counter++;
	}
	counter = 0;

	if (xPos != targetXPos) {
		xPos = static_cast<int>(castPosition.x);
		zPos = castPosition.z;
		while (xPos != targetXPos && counter < xDifference + 1) {
			Vector positionToTest = {};
			positionToTest.x = static_cast<float>(xPos);
			positionToTest.y = 0.0f;
			positionToTest.z = zPos;

			float distance = absVectorDistance(targetObjPos, positionToTest);

			if (distance < closestDistance) {
				closestDistance = distance;
				closestPoint = positionToTest;
			}
			if (slope.denominator != 0.0f) {
				xPos--;
			}
			if (slope.numerator != 0.0f) {
				zPos = zPos - slope.gradient;
			}
			counter++;
		}
	}

	if (absVectorDistance(closestPoint, targetPosition) < absVectorDistance(castPosition, targetPosition)) {
		return closestPoint;
	}
	else {
		return empty;
	}
}

Vector sideStepPosition(Slope slope, Vector positionToSideStepFrom, object* myPlayer) {
	Vector positionToSideStepTo = {};
	positionToSideStepTo.x = positionToSideStepFrom.x;
	positionToSideStepTo.y = positionToSideStepFrom.y;
	positionToSideStepTo.z = positionToSideStepFrom.z;
	float perpendicularSlope = -(pow(slope.gradient, -1));
	float distanceToMoveBy = (spellCastData->mSpellData->mSpellInfo->mMissileWidth * 1.05f);
	int counter = 0;
	while (counter < distanceToMoveBy) {
		if (slope.denominator != 0.0f) {
			if (isNegative(perpendicularSlope)) {
				positionToSideStepTo.x = positionToSideStepTo.x - 1;
			}
			else {
				positionToSideStepTo.x = positionToSideStepTo.x + 1;
			}
		}
		if (slope.numerator != 0.0f) {
			positionToSideStepTo.z = positionToSideStepTo.z + perpendicularSlope;
		}
		counter++;
	}
	
	return positionToSideStepTo;
}

Vector sideStepPositionReverse(Slope slope, Vector positionToSideStepFrom, object* myPlayer) {
	Vector positionToSideStepTo = {};
	positionToSideStepTo.x = positionToSideStepFrom.x;
	positionToSideStepTo.y = positionToSideStepFrom.y;
	positionToSideStepTo.z = positionToSideStepFrom.z;
	float perpendicularSlope = -(pow(slope.gradient, -1));
	float distanceToMoveBy = (spellCastData->mSpellData->mSpellInfo->mMissileWidth * 1.05f);
	int counter = 0;
	while (counter < distanceToMoveBy) {
		if (slope.denominator != 0.0f) {
			if (isNegative(perpendicularSlope)) {
				positionToSideStepTo.x = positionToSideStepTo.x + 1;
			}
			else {
				positionToSideStepTo.x = positionToSideStepTo.x - 1;
			}
		}
		if (slope.numerator != 0.0f) {
			positionToSideStepTo.z = positionToSideStepTo.z + perpendicularSlope;
		}
		counter++;
	}

	return positionToSideStepTo;
}

void autododge(object* myPlayer) {
	if (spellCastData != NULL && spellCastData != nullptr) {
		if (spellCastData->mIsSpellCast == 1) {
			int enemyTeam = setEnemyTeam(myPlayer);
			float distanceApart = absObjectDistanceApart(myPlayer, objMgr->mObjectManagerArray[spellCastData->mCasterIndex]) - (spellCastData->mSpellData->mSpellInfo->mCastRadius[spellCastData->getSpellRank()].value);
			if (enemyTeam == objMgr->mObjectManagerArray[spellCastData->mCasterIndex]->mTeam) {
				if (spellCastData->mSpellData->mSpellInfo->mMissileSpeed > 0.0f) {
					Vector castTargetPosition = spellCastData->mTargetPosition;
					Vector castStartPosition = objMgr->mObjectManagerArray[spellCastData->mCasterIndex]->mUnitPos;
					if (spellCastData->mSpellData->mSpellInfo->mMaxRange[spellCastData->getSpellRank()].value > distanceApart) {
						
						Slope projectileSlope = {};
						projectileSlope.numerator = (castTargetPosition.z - objMgr->mObjectManagerArray[spellCastData->mCasterIndex]->mUnitPos.z);
						projectileSlope.denominator = (castTargetPosition.x - objMgr->mObjectManagerArray[spellCastData->mCasterIndex]->mUnitPos.x);
						projectileSlope.gradient = projectileSlope.numerator / projectileSlope.denominator;

						Vector closestPoint = findClosestPoint(projectileSlope, castStartPosition, castTargetPosition, myPlayer->mUnitPos);
						if (closestPoint != empty) {
							float xSign = signOfPointDifference(myPlayer->mUnitPos.x, closestPoint.x);
							float zSign = signOfPointDifference(myPlayer->mUnitPos.z, closestPoint.z);

							float distanceFromProjectile = absVectorDistance(closestPoint, myPlayer->mUnitPos);
							float distanceFromProjectileEdge = distanceFromProjectile - (spellCastData->mSpellData->mSpellInfo->mMissileWidth / 2);
							if (distanceFromProjectileEdge <= myPlayer->getUnitSize()) {
								Vector positionToMoveTo = sideStepPosition(projectileSlope, closestPoint, myPlayer);
								isWall = 0x0;
								Operations::IssueMoveOrder(positionToMoveTo);
								if (isWall == 0x00000001) {
									positionToMoveTo = sideStepPositionReverse(projectileSlope, closestPoint, myPlayer);
									Operations::IssueMoveOrder(positionToMoveTo);
								}
							}
						}
					}
				}
				else {
					float xSign = signOfPointDifference(myPlayer->mUnitPos.x, spellCastData->mTargetPosition.x);
					float zSign = signOfPointDifference(myPlayer->mUnitPos.z, spellCastData->mTargetPosition.z);
					float distanceFromProjectile = absVectorDistance(spellCastData->mTargetPosition, myPlayer->mUnitPos);
					float distanceFromProjectileEdge = distanceFromProjectile + (spellCastData->mSpellData->mSpellInfo->mMissileWidth / 2);

					if (distanceFromProjectileEdge <= myPlayer->getUnitSize()) {
						Vector positionToMoveTo = {};

						positionToMoveTo.x = myPlayer->mUnitPos.x + ((myPlayer->getUnitSize() + spellCastData->mSpellData->mSpellInfo->mMissileWidth) * xSign);
						positionToMoveTo.y = myPlayer->mUnitPos.y;
						positionToMoveTo.z = myPlayer->mUnitPos.z + ((myPlayer->getUnitSize() + spellCastData->mSpellData->mSpellInfo->mMissileWidth) * zSign);
						Operations::IssueMoveOrder(positionToMoveTo);
					}
				}
			}
		}
		spellCastData = NULL;
	}
}


#include "../stdafx.h"
#include "modules.h"

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
	int distanceBetweenCastAndTarget = static_cast<int>(absVectorDistance(castPosition, targetPosition));
	int xPos = static_cast<int>(castPosition.x);
	float zPos = castPosition.z;
	int targetXPos = static_cast<int>(targetPosition.x);
	Vector closestPoint;
	float closestDistance = 1500000.0f;
	int counter = 0;
	while (xPos != targetXPos && counter < distanceBetweenCastAndTarget) {
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
			if (isPositive(slope.denominator)) {
				xPos++;
			}
			if (isNegative(slope.denominator)) {
				xPos--;
			}
		}
		if (slope.numerator != 0.0f) {
			if (isPositive(slope.numerator)) {
				zPos = zPos + abs(slope.getGradient());
			}
			if (isNegative(slope.numerator)) {
				zPos = zPos - abs(slope.getGradient());
			}
			
		}
		counter++;
	}
	/*
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
				zPos = zPos + slope.getGradient();
			}
			counter++;
		}
	}
	*/
	if (absVectorDistance(closestPoint, targetPosition) <= absVectorDistance(castPosition, targetPosition)) {
		closestPoint.y = targetPosition.y;
		return closestPoint;
	}
	else {
		return EMPTYVECTOR;
	}
}

Vector sideStepPosition(Slope slope, Vector positionToSideStepFrom, object* myPlayer) {
	Vector positionToSideStepTo = {};
	positionToSideStepTo.x = positionToSideStepFrom.x;
	positionToSideStepTo.y = positionToSideStepFrom.y;
	positionToSideStepTo.z = positionToSideStepFrom.z;

	float distanceApart = absVectorDistance(positionToSideStepFrom, myPlayer->mUnitPos);

	Slope dodgeSlope = {};
	dodgeSlope.numerator = (myPlayer->mUnitPos.z - positionToSideStepFrom.z);
	dodgeSlope.denominator = (myPlayer->mUnitPos.x - positionToSideStepFrom.x);

	Vector differential = (positionToSideStepFrom - myPlayer->mUnitPos);

	float perpendicularSlope = -(pow(slope.getGradient(), -1));
	float distanceToMoveBy = ((spellCastData->mSpellData->mSpellInfo->mMissileWidth) - distanceApart) + (spellCastData->mSpellData->mSpellInfo->mMissileWidth);

	int counter = 0;
	while (counter < distanceToMoveBy) {
		if (slope.denominator != 0.0f) {
			if (isPositive(differential.x)) {
				positionToSideStepTo.x = positionToSideStepTo.x + 1;
			}
			if (isNegative(differential.x)) {
				positionToSideStepTo.x = positionToSideStepTo.x - 1;
			}
			if (isZero(differential.x)) {
				//Don't move
			}
		}
		if (slope.numerator != 0.0f) {
				if (isPositive(differential.z)) {
					positionToSideStepTo.z = positionToSideStepTo.z + abs(perpendicularSlope);
				}
				if (isNegative(differential.z)) {
					positionToSideStepTo.z = positionToSideStepTo.z - abs(perpendicularSlope);
				}
				if (isZero(differential.z)) {
					//Don't move
				}
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
	float distanceApart = absVectorDistance(positionToSideStepFrom, myPlayer->mUnitPos);

	Slope dodgeSlope = {};
	dodgeSlope.numerator = (myPlayer->mUnitPos.z - positionToSideStepFrom.z);
	dodgeSlope.denominator = (myPlayer->mUnitPos.x - positionToSideStepFrom.x);

	Vector differential = (positionToSideStepFrom - myPlayer->mUnitPos);

	float perpendicularSlope = -(pow(slope.getGradient(), -1));
	float distanceToMoveBy = ((spellCastData->mSpellData->mSpellInfo->mMissileWidth) - distanceApart) + (spellCastData->mSpellData->mSpellInfo->mMissileWidth);

	int counter = 0;
	while (counter < distanceToMoveBy) {
		if (slope.denominator != 0.0f) {
			if (isPositive(differential.x)) {
				positionToSideStepTo.x = positionToSideStepTo.x - 1;
			}
			if (isNegative(differential.x)) {
				positionToSideStepTo.x = positionToSideStepTo.x + 1;
			}
			if (isZero(differential.x)) {
				//Don't move
			}
		}
		if (slope.numerator != 0.0f) {
			if (isPositive(differential.z)) {
				positionToSideStepTo.z = positionToSideStepTo.z - abs(perpendicularSlope);
			}
			if (isNegative(differential.z)) {
					positionToSideStepTo.z = positionToSideStepTo.z + abs(perpendicularSlope);
			
			}
			if (isZero(differential.z)) {
				//Don't move
			}
		}
		counter++;
	}

	return positionToSideStepTo;
}

void autododge(object* myPlayer) {
	if (spellCastData != NULL && spellCastData != nullptr) {
		if (spellCastData->mIsSpellCast == 1) {
			int enemyTeam = setEnemyTeam(myPlayer);
			float distanceApart = absObjectDistanceApart(myPlayer, objMgr->mObjectManagerArray[spellCastData->mCasterIndex]) - (spellCastData->mSpellData->mSpellInfo->mCastRadius[spellCastData->getSpellRank()].value + (myPlayer->getUnitSize() / 2.0f) + (objMgr->mObjectManagerArray[spellCastData->mCasterIndex]->getUnitSize() / 2.0f));
			if (enemyTeam == objMgr->mObjectManagerArray[spellCastData->mCasterIndex]->mTeam) {
				if (spellCastData->mSpellData->mSpellInfo->mMissileSpeed > 0.0f) {
					if (spellCastData->mSpellData->mSpellInfo->mMaxRange[spellCastData->getSpellRank()].value > distanceApart) {
						Vector castTargetPosition = spellCastData->mTargetPosition;
						Slope projectileSlope = { (castTargetPosition.z - objMgr->mObjectManagerArray[spellCastData->mCasterIndex]->mUnitPos.z), (castTargetPosition.x - objMgr->mObjectManagerArray[spellCastData->mCasterIndex]->mUnitPos.x)};

						object* casterOfSpell = objMgr->mObjectManagerArray[spellCastData->mCasterIndex];
						float amountToAddToCastPosX = (spellCastData->mSpellData->mSpellInfo->mCastRadius[spellCastData->getSpellRank()].value / 2) * (atan(projectileSlope.getReciprocalGradient()) / static_cast<float>(M_PI_2)); //Divided by half so it can be distributed to two values
						float amountToAddToCastPosZ = (spellCastData->mSpellData->mSpellInfo->mCastRadius[spellCastData->getSpellRank()].value / 2) * (atan(projectileSlope.getGradient()) / static_cast<float>(M_PI_2)); //If left whole then it will multiply say 1.9 by 200 instead of 1.9 by 100 and .1 by 100
						Vector castStartPosition = casterOfSpell->mUnitPos;
						
						castStartPosition.x = castStartPosition.x + (modifySign(projectileSlope.denominator, amountToAddToCastPosX));
						castStartPosition.z = castStartPosition.z + (modifySign(projectileSlope.numerator, amountToAddToCastPosZ));
						
						Vector closestPoint = findClosestPoint(projectileSlope, castStartPosition, castTargetPosition, myPlayer->mUnitPos);
						if (closestPoint != EMPTYVECTOR) {
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


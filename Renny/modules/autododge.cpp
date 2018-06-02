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

float calculateAngleBetweenTwoSlopes(Slope m1, Slope m2) {
	return atan(abs((m2.getGradient() - m1.getGradient()) / (1.0f + (m2.getGradient() * m1.getGradient()))));
}

float calculateAdjacentSideLength(float hypotenuse, float angle) {
	return hypotenuse * cos(angle);
}

Triangle triangulate(float hypotenuse, Slope slope1, Slope slope2) {
	//Line modifier should be zero unless needed
	float adjacent = calculateAdjacentSideLength(hypotenuse, calculateAngleBetweenTwoSlopes(slope1, slope2));
	float opposite = sqrt((hypotenuse * hypotenuse) - (adjacent * adjacent));
	return Triangle{ hypotenuse, opposite, adjacent };
}


Vector findClosestPoint(Slope slope, Vector castPosition, Vector targetPosition, Vector targetObjPos) {
	int distanceBetweenCastAndTarget = static_cast<int>(absVectorDistance(castPosition, targetPosition));
	int xPos = static_cast<int>(castPosition.x);
	float zPos = castPosition.z;
	int targetXPos = static_cast<int>(targetPosition.x);
	Vector closestPoint;
	float closestDistance = 1500000.0f;

	Vector differential = (targetPosition - castPosition);

	int counter = 0;
	while (xPos != targetXPos  && counter < distanceBetweenCastAndTarget) {
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
			if (isPositive(differential.x)) {
				xPos++;
			}
			if (isNegative(differential.x)) {
				xPos--;
			}
		}
		if (slope.numerator != 0.0f) {
			if (isPositive(differential.z)) {
				zPos = zPos + abs(slope.getGradient());
			}
			if (isNegative(differential.z)) {
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

Vector sideStepPosition(Slope slope, Vector myLocation, float distanceApart, float missileWidth, float xSign, float zSign) {
	Vector positionToSideStepTo = {};
	positionToSideStepTo = myLocation;

	Slope perpendicularSlope = { -abs(slope.denominator), abs(slope.numerator) };
	float distanceToMoveBy = (missileWidth + distanceApart) + missileWidth;

	positionToSideStepTo.x = positionToSideStepTo.x + modifySign(xSign, (distanceToMoveBy * abs(atan(perpendicularSlope.getReciprocalGradient()) / static_cast<float>(M_PI_2))));
	positionToSideStepTo.z = positionToSideStepTo.z + modifySign(zSign, (distanceToMoveBy * abs(atan(perpendicularSlope.getGradient()) / static_cast<float>(M_PI_2))));

	return positionToSideStepTo;
}

Vector sideStepPositionReverse(Slope slope, Vector myLocation, float distanceApart, float missileWidth, float xSign, float zSign) {
	Vector positionToSideStepTo = {};
	positionToSideStepTo = myLocation;

	Slope perpendicularSlope = { -abs(slope.denominator), abs(slope.numerator) };
	float distanceToMoveBy = (missileWidth + distanceApart) + missileWidth;

	positionToSideStepTo.x = positionToSideStepTo.x + modifySign(xSign, (distanceToMoveBy * abs(atan(perpendicularSlope.getReciprocalGradient()) / static_cast<float>(M_PI_2))));
	positionToSideStepTo.z = positionToSideStepTo.z + modifySign(zSign, (distanceToMoveBy * abs(atan(perpendicularSlope.getGradient()) / static_cast<float>(M_PI_2))));

	return positionToSideStepTo;
}

void autododge(object* myPlayer, const spellCastDataBase* currentCastData) {
	if (currentCastData != nullptr && (DWORD) currentCastData != 0x3) {
		if (currentCastData->mSpellRank < 10 && currentCastData->mSpellData != nullptr && currentCastData->mSpellData->mSpellInfo != nullptr && (DWORD)currentCastData->mSpellData->mSpellInfo != 0xCCCCCCFF) {
			if (currentCastData->mIsSpellCast == 1) {
				int spellRank = currentCastData->mSpellRank + 1;
				float missileWidth = currentCastData->mSpellData->mSpellInfo->mMissileWidth;
				float missileSpeed = currentCastData->mSpellData->mSpellInfo->mMissileSpeed;
				float castRadius = currentCastData->mSpellData->mSpellInfo->mCastRadius[spellRank].value;
				float maxRange = currentCastData->mSpellData->mSpellInfo->mMaxRange[spellRank].value;
				short casterIndex = currentCastData->mCasterIndex;
				Vector castStartPosition = currentCastData->mStartPosition;
				Vector castTargetPosition = currentCastData->mTargetPosition;
				float distanceApart = absVectorDistance(castStartPosition, myPlayer->mUnitPos) - castRadius - (myPlayer->getUnitSize() / 2);
				if (enemyTeam == objMgr->mObjectManagerArray[casterIndex]->mTeam) {
					if (missileSpeed > 0.0f) {
						if (maxRange > distanceApart) {
							distanceApart = distanceApart + castRadius + (myPlayer->getUnitSize() / 2);
							if (absVectorDistance(castTargetPosition, myPlayer->mUnitPos) < distanceApart) {
								Slope casterToUnitSlope = { (myPlayer->mUnitPos.z - castStartPosition.z), (myPlayer->mUnitPos.x - castStartPosition.x) };
								Slope projectileSlope = { (castTargetPosition.z - castStartPosition.z), (castTargetPosition.x - castStartPosition.x) };
								Triangle triangulatedData = triangulate(distanceApart, casterToUnitSlope, projectileSlope);
								Vector closestPoint = castStartPosition;
								Vector differential = {};

								if ((triangulatedData.opposite - missileWidth) <= (myPlayer->getUnitSize() / 2)) {
									float amountToAddToX = triangulatedData.adjacent * abs(atan(projectileSlope.getReciprocalGradient()) / static_cast<float>(M_PI_2));
									float amountToAddToZ = triangulatedData.adjacent * abs(atan(projectileSlope.getGradient()) / static_cast<float>(M_PI_2));

									closestPoint.x = castStartPosition.x + (modifySign(projectileSlope.denominator, amountToAddToX));
									closestPoint.z = castStartPosition.z + (modifySign(projectileSlope.numerator, amountToAddToZ));

									differential = myPlayer->mUnitPos - closestPoint;

									float xSign = 1.0f, zSign = 1.0f;

									xSign = modifySign(differential.x, xSign);
									zSign = modifySign(differential.z, zSign);

									Vector positionToMoveTo = sideStepPosition(projectileSlope, myPlayer->mUnitPos, triangulatedData.opposite, missileWidth, xSign, zSign);
									isWall = 0x0;
									Operations::IssueMoveOrder(positionToMoveTo);
									if (isWall == 0x00000001) {
										positionToMoveTo = sideStepPositionReverse(projectileSlope, myPlayer->mUnitPos, triangulatedData.opposite, missileWidth, xSign, zSign);
										Operations::IssueMoveOrder(positionToMoveTo);
									}
								}
							}
						}
					}
					/*
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
					*/
				}
			}
			spellCastData = NULL;
		}
	}
}


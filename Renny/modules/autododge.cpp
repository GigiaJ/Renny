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

Vector sideStepPosition(Slope slope, Vector myLocation, float distanceApart, float missileWidth, float xSign, float zSign) {
	Vector positionToSideStepTo = {};
	positionToSideStepTo = myLocation;

	//Obviously with limits in precision from the floating points this is probably too small to correctly dodge sometimes and would result in a hit because the script doesn't move enough
	if (distanceApart < 20.0f) {
		distanceApart = missileWidth;
	}

	Slope perpendicularSlope = { -abs(slope.denominator), abs(slope.numerator) };
	float distanceToMoveBy = (missileWidth + distanceApart) + missileWidth;


	positionToSideStepTo.x = positionToSideStepTo.x + modifySign(xSign, static_cast<float>(static_cast<double>(distanceToMoveBy) * abs(atan(static_cast<double>(perpendicularSlope.getReciprocalGradient())) / M_PI_2)));
	positionToSideStepTo.z = positionToSideStepTo.z + modifySign(zSign, static_cast<float>(static_cast<double>(distanceToMoveBy) * abs(atan(static_cast<double>(perpendicularSlope.getGradient())) / M_PI_2)));

	return positionToSideStepTo;
}

bool checkForUnitCollision(object* myPlayer, Vector castStartPosition, Vector castTargetPosition, float castRadius, float maxRange, float missileWidth, float distanceBetweenCastAndSelf) {
	//Will check if another object would be struck before you by the projectile
	std::vector<object*> objectsAbleToBlock = {};
	for (int i = 0; i < objMgr->mArrayHighestIndex; i++) {
		if (objMgr->mObjectManagerArray[i] != NULL) {
			object* TemporaryObject = objMgr->mObjectManagerArray[i];
			if (TemporaryObject->mTeam == static_cast<int>(UnitTeam::NEUTRAL_TEAM))
			{
				if (TemporaryObject->mIsTargetable)
				{
					if (TemporaryObject->mUnitType == static_cast<int>(UnitType::MINION_UNIT))
					{
						if (TemporaryObject->mMaxHP > 1) {
							objectsAbleToBlock.push_back(TemporaryObject);
						}
					}
				}
			}
			if (TemporaryObject->mTeam == myPlayer->mTeam)
			{
				if (TemporaryObject->mIsTargetable)
				{
					if (TemporaryObject->mUnitType == static_cast<int>(UnitType::MINION_UNIT))
					{
						objectsAbleToBlock.push_back(TemporaryObject);
					}
				}
			}
			if (TemporaryObject->mTeam == myPlayer->mTeam)
			{
				if (TemporaryObject->mIsTargetable)
				{
					if (TemporaryObject->mUnitType == static_cast<int>(UnitType::HERO_UNIT))
					{
						objectsAbleToBlock.push_back(TemporaryObject);
					}
				}
			}
		}
	}

	std::vector<object*>::iterator iter;
	for (iter = objectsAbleToBlock.begin(); iter != objectsAbleToBlock.end(); iter++) {
		float distanceApart = absVectorDistance(castStartPosition, (*iter)->mUnitPos) - castRadius - ((*iter)->getUnitSize() / 2);
		if (distanceApart < maxRange) {
			if (distanceApart < distanceBetweenCastAndSelf) {
				distanceApart = distanceApart + castRadius + ((*iter)->getUnitSize() / 2);
				if (absVectorDistance(castTargetPosition, (*iter)->mUnitPos) < distanceApart) {
					Slope casterToUnitSlope = { ((*iter)->mUnitPos.z - castStartPosition.z), ((*iter)->mUnitPos.x - castStartPosition.x) };
					Slope projectileSlope = { (castTargetPosition.z - castStartPosition.z), (castTargetPosition.x - castStartPosition.x) };
					Triangle triangulatedData = triangulate(distanceApart, casterToUnitSlope, projectileSlope);

					if ((triangulatedData.opposite - (missileWidth / 2)) <= ((*iter)->getUnitSize() / 2)) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

void checkForFogOfWarProjectile(object* missileObject, object* myPlayer) {
	//Checks if a projectile is shot from fog of war that would hit you
	if (missileObject != nullptr) {
		if (missileObject->mTeam != 0) {
			if (missileObject->mUnitType == static_cast<int>(UnitType::MISSILE_UNIT)) {
				if (objMgr->mObjectManagerArray[missileObject->mCasterIndex]->mUnitType == static_cast<int>(UnitType::HERO_UNIT)) {
					int spellRank = 0;

					int i = 0;
					for (int q = 0; q < 4; q++) {
						if (strstr(missileObject->mSpellData->mSpellName, objMgr->mObjectManagerArray[missileObject->mCasterIndex]->mSpellInstArray[q]->mSpellData->mSpellName)) {
							spellRank = objMgr->mObjectManagerArray[missileObject->mCasterIndex]->mSpellInstArray[q]->mCurrentRank;
							i = q;
						}
					}

					float missileWidth = objMgr->mObjectManagerArray[missileObject->mCasterIndex]->mSpellInstArray[i]->mSpellData->mSpellInfo->mMissileWidth;
					float missileSpeed = objMgr->mObjectManagerArray[missileObject->mCasterIndex]->mSpellInstArray[i]->mSpellData->mSpellInfo->mMissileSpeed;
					float castRadius = objMgr->mObjectManagerArray[missileObject->mCasterIndex]->mSpellInstArray[i]->mSpellData->mSpellInfo->mCastRadius[spellRank].value;
					float maxRange = objMgr->mObjectManagerArray[missileObject->mCasterIndex]->mSpellInstArray[i]->mSpellData->mSpellInfo->mMaxRange[spellRank].value;
					short casterIndex = missileObject->mCasterIndex;
					Vector castStartPosition = missileObject->mStartPosition;
					Vector currentPosition = missileObject->mEdgePos2 + missileObject->mEdgePos1;
					currentPosition.x = currentPosition.x / 2.0f;
					currentPosition.y = currentPosition.y / 2.0f;
					currentPosition.z = currentPosition.z / 2.0f;
					Vector castTargetPosition = missileObject->mTargetPosition;

					float distanceApart = absVectorDistance(castStartPosition, myPlayer->mUnitPos) - castRadius - (myPlayer->getUnitSize() / 2);
					if (enemyTeam == objMgr->mObjectManagerArray[casterIndex]->mTeam) {
						if (missileSpeed > 0.0f) {
							if (checkForUnitCollision(myPlayer, castStartPosition, castTargetPosition, castRadius, maxRange, missileWidth, distanceApart) == true) {
								return;
							}
							else {
								distanceApart = distanceApart + castRadius + (myPlayer->getUnitSize() / 2);
								Slope casterToUnitSlope = { (myPlayer->mUnitPos.z - castStartPosition.z), (myPlayer->mUnitPos.x - castStartPosition.x) };
								Slope projectileSlope = { (castTargetPosition.z - castStartPosition.z), (castTargetPosition.x - castStartPosition.x) };
								Triangle triangulatedData = triangulate(distanceApart, casterToUnitSlope, projectileSlope);
								Vector closestPoint = castStartPosition;
								Vector differential = {};

								if ((triangulatedData.opposite - (missileWidth / 2)) <= (myPlayer->getUnitSize() / 2)) {
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
										positionToMoveTo = sideStepPosition(projectileSlope, myPlayer->mUnitPos, triangulatedData.opposite, missileWidth, -xSign, -zSign);
										Operations::IssueMoveOrder(positionToMoveTo);
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void autododge(object* myPlayer, const spellCastDataBase* currentCastData) {
	if (currentCastData != nullptr && (DWORD) currentCastData != 0x3) {
		if (currentCastData->mSpellRank < 10 && currentCastData->mSpellData != nullptr && currentCastData->mSpellData->mSpellInfo != nullptr && (DWORD)currentCastData->mSpellData->mSpellInfo != 0xCCCCCCFF) {
			if (currentCastData->mIsSpellCast == 1 && currentCastData->mIsAutoAttack == 0) {
				checkForFogOfWarProjectile(latestObject, myPlayer);
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
						if (maxRange >= distanceApart) {
							if (checkForUnitCollision(myPlayer, castStartPosition, castTargetPosition, castRadius, maxRange, missileWidth, distanceApart) == true) {
								return;
							}
							else {
								distanceApart = distanceApart + castRadius + (myPlayer->getUnitSize() / 2);
								if (absVectorDistance(castTargetPosition, myPlayer->mUnitPos) < distanceApart) {
									Slope casterToUnitSlope = { (myPlayer->mUnitPos.z - castStartPosition.z), (myPlayer->mUnitPos.x - castStartPosition.x) };
									Slope projectileSlope = { (castTargetPosition.z - castStartPosition.z), (castTargetPosition.x - castStartPosition.x) };
									Triangle triangulatedData = triangulate(distanceApart, casterToUnitSlope, projectileSlope);
									Vector closestPoint = castStartPosition;
									Vector differential = {};

									if ((triangulatedData.opposite - (missileWidth / 2)) <= (myPlayer->getUnitSize() / 2)) {
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
											positionToMoveTo = sideStepPosition(projectileSlope, myPlayer->mUnitPos, triangulatedData.opposite, missileWidth, -xSign, -zSign);
											Operations::IssueMoveOrder(positionToMoveTo);
										}
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


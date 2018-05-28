#include "stdafx.h"
#include "operations.h"

namespace Operations {
	typedef void(__thiscall *tCastSpell)(void* SpellBookPtr, spellInst* SpellDataPtr, signed int SlotNumber, Vector* StartPosition, Vector* EndPosition, int NetworkId);
	typedef int*(__thiscall *tIssueOrder)(object* myPlayer, int orderType, Vector* targetPosition, object* targetObject, bool isAttackMove, bool isMinion, int networkID);
	typedef int(__cdecl  *tOnProcessSpell)(void* SpellBookPtr, signed int SlotNumber, int negativeOne, void* SpellDataPtr, char isAutoAttack, char isMinion);
	typedef float(__cdecl *tGetAttackCastDelay)(object* unit, int attackID); //attackID can be found in the second called subroutine of castdelay that uses the attackID as a parameter currently 65
	typedef signed int(__thiscall *tGetSpellData)(DWORD* unitSpellBook, int slot, int a3);
	typedef char(__thiscall* tOnProcessSpellW)(DWORD* SpellBookPtr, DWORD* pSpellInfo);

	tCastSpell mCastSpell;
	tIssueOrder mIssueOrder;
	tGetAttackCastDelay mGetAttackCastDelay;
	tGetSpellData  mGetSpellData;
	tOnProcessSpell  mOnProcessSpell;
	tOnProcessSpellW  mOnProcessSpellW;


	void Init()
	{
		 mCastSpell = (tCastSpell)(base + fnCastSpell);
		 mIssueOrder = (tIssueOrder)(base + fnIssueOrder);
		 mGetAttackCastDelay = (tGetAttackCastDelay)(base + fnGetAttackCastDelay);
		 mGetSpellData = (tGetSpellData)(base + fnGetSpellData);
		 mOnProcessSpell = (tOnProcessSpell)(base + fnOnProcessSpell);
		//fnOnProcessSpellW = (tOnProcessSpellW)(base + 0x54D140);
	}

	void CastSpell(object* enemyChamp, int slot) {
		DWORD SpellBook;
		spellInst* SpellPtr;
		Vector Empty = EMPTYVECTOR;

		Vector predictedLocation = enemyChamp->mUnitPos;
		//Empty.x = 0;
		//Empty.y = 0;
		//Empty.z = 0;
		Vector* pEmpty = &Empty;
		object* myPlayer = (object*)lPlayer;
		Vector myPos = myPlayer->mUnitPos;
		float ping = 0.024f * 2.0f;
		SpellBook = (lPlayer + pSpellBookPtr);
		SpellPtr = myPlayer->mSpellInstArray[slot];
		float missileSpeed = (myPlayer->mSpellInstArray[slot]->mSpellData->mSpellInfo->mMissileSpeed);
		float missileWidth = (myPlayer->mSpellInstArray[slot]->mSpellData->mSpellInfo->mMissileWidth);
		float castTime = (myPlayer->mSpellInstArray[slot]->mSpellData->mSpellInfo->mCastTime);
		float castRadius = (myPlayer->mSpellInstArray[slot]->mSpellData->mSpellInfo->mCastRadius[myPlayer->mSpellInstArray[slot]->mCurrentRank + 1].value);
		float myUnitSize = myPlayer->mEdgePos2.x - myPlayer->mEdgePos1.x;
		float moveSpeed = enemyChamp->mMoveSpeed;

		if (missileSpeed > 0.0f) {
			if (enemyChamp->mCharData->AIHeroClient->mIsMoving || enemyChamp->mCharData->AIHeroClient->mIsDashing) {

				Vector enemyPos = {};

				if (enemyChamp->mCharData->AIHeroClient->mIsMoving) {
					enemyPos = enemyChamp->mUnitPos;
				}

				if (enemyChamp->mCharData->AIHeroClient->mIsDashing) {
					enemyPos = enemyChamp->mCharData->AIHeroClient->mDashEndPosition;
				}

				float enemyHitBoxSize = enemyChamp->getUnitSize();
				float absoluteUnitDistanceApart = absObjectDistanceApart(myPlayer, enemyChamp);//absVectorDistance(myPos, enemyPos);

				float distanceTravelledDuringCast = castTime * moveSpeed;
				float distTrav = static_cast<float>(std::pow(static_cast<double>(distanceTravelledDuringCast), static_cast<double>(2)));
				float distFromEach = static_cast<float>(std::pow(static_cast<double>(absoluteUnitDistanceApart), static_cast<double>(2)));
				float sumOfDistances = distTrav + distFromEach;
				float sumSquared = static_cast<float>(std::sqrt(sumOfDistances));

				float futurePositionX = calculateEnemyFuturePosition(distanceTravelledDuringCast, sumSquared, missileSpeed, missileWidth, moveSpeed, enemyChamp->mDirectionFaced.x, castTime);
				float futurePositionZ = calculateEnemyFuturePosition(distanceTravelledDuringCast, sumSquared, missileSpeed, missileWidth, moveSpeed, enemyChamp->mDirectionFaced.z, castTime);

				float clipTowardsX = (enemyChamp->mDirectionFaced.x * enemyHitBoxSize) / 2.0f;// modifySign(futurePositionX, enemyHitBoxSize) / 2.0f;
				float  clipTowardsZ = (enemyChamp->mDirectionFaced.z * enemyHitBoxSize) / 2.0f;//modifySign(futurePositionZ, enemyHitBoxSize) / 2.0f;

				clipTowardsX = -clipTowardsX;
				clipTowardsZ = -clipTowardsZ;

				float removeMissileWidthX = missileWidth / 2.0f;
				float removeMissileWidthZ = missileWidth / 2.0f;


				if (castRadius < absoluteUnitDistanceApart) {
					predictedLocation.x = enemyPos.x + futurePositionX + clipTowardsX + removeMissileWidthX;
					predictedLocation.y = enemyPos.y;
					predictedLocation.z = enemyPos.z + futurePositionZ + clipTowardsZ + removeMissileWidthZ;
				}
			}
		}
		 mCastSpell((void*)SpellBook, SpellPtr, slot, &predictedLocation, pEmpty, 0);
	}

	void IssueAttackOrder(object* enemyChamp) {
		int orderType = 3; //AttackType
		object* myPlayer = (object*)lPlayer;
		Vector myPos = myPlayer->mUnitPos;
		Vector enemyPos = enemyChamp->mUnitPos;
		float moveSpeed = myPlayer->mMoveSpeed;
		float directionX = myPlayer->mDirectionFaced.x;
		float directionZ = myPlayer->mDirectionFaced.x;
		Vector targetPosition = {};

		if (enemyChamp != nullptr) {
			targetPosition = enemyPos;
		}

		 mIssueOrder(myPlayer, orderType, &targetPosition, enemyChamp, 0, 0, 0);
	}

	void IssueMoveOrder(Vector positionToMoveTo) {
		int orderType = 2; //MoveType
		object* myPlayer = (object*)lPlayer;
		 mIssueOrder(myPlayer, orderType, &positionToMoveTo, nullptr, 0, 0, 0);
	}
}
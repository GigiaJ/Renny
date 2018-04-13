#include "stdafx.h"
#include "operations.h"

namespace Operations {
	typedef int*(__thiscall *tCastSpell)(DWORD SpellBookPtr, DWORD SpellDataPtr, int SlotNumber, Vector* startPosition, Vector* EndPosition, int networkId);
	typedef int*(__thiscall *tIssueOrder)(object* myPlayer, int orderType, Vector* targetPosition, object* targetObject, bool isAttackMove, bool isMinion, int networkID);
	typedef int(__cdecl  *tOnProcessSpell)(void* SpellBookPtr, signed int SlotNumber, int negativeOne, void* SpellDataPtr, char isAutoAttack, char isMinion);
	typedef float(__cdecl *tGetAttackCastDelay)(object* unit, int attackID); //attackID can be found in the second called subroutine of castdelay that uses the attackID as a parameter currently 65
	typedef signed int(__thiscall *tGetSpellData)(DWORD* unitSpellBook, int slot, int a3);
	typedef char(__thiscall* tOnProcessSpellW)(DWORD* SpellBookPtr, DWORD* pSpellInfo);

	tCastSpell fnCastSpell;
	tIssueOrder fnIssueOrder;
	tGetAttackCastDelay fnGetAttackCastDelay;
	tGetSpellData fnGetSpellData;
	tOnProcessSpell fnOnProcessSpell;
	tOnProcessSpellW fnOnProcessSpellW;

	void Init()
	{
		fnCastSpell = (tCastSpell)(base + 0x548D90);
		fnIssueOrder = (tIssueOrder)(base + 0x1C9780);
		fnGetAttackCastDelay = (tGetAttackCastDelay)(base + 0x54C980);
		fnGetSpellData = (tGetSpellData)(base + 0x53E150);
		fnOnProcessSpell = (tOnProcessSpell)(base + 0x53EC10);
		//fnOnProcessSpellW = (tOnProcessSpellW)(base + 0x54D140);
	}

	void CastSpell(object* enemyChamp, int slot) {
		DWORD SpellBook;
		DWORD SpellPtr;
		Vector Empty;

		Vector predictedLocation = enemyChamp->mUnitPos;
		Empty.x = 0;
		Empty.y = 0;
		Empty.z = 0;
		Vector* pEmpty = &Empty;
		object* myPlayer = (object*)lPlayer;
		Vector myPos = myPlayer->mUnitPos;
		float ping = 0.024f * 2.0f;
		SpellBook = (lPlayer + 0x1B90);
		SpellPtr = *(DWORD*)myPlayer->mSpellInstArray[slot];
		float missileSpeed = (myPlayer->mSpellInstArray[slot]->mSpellData->mSpellInfo->mMissileSpeed);
		float missileWidth = (myPlayer->mSpellInstArray[slot]->mSpellData->mSpellInfo->mMissileWidth);
		float castTime = (myPlayer->mSpellInstArray[slot]->mSpellData->mSpellInfo->mCastTime);
		float castRadius = (myPlayer->mSpellInstArray[slot]->mSpellData->mSpellInfo->mCastRadius);
		float myUnitSize = myPlayer->mEdgePos2.x - myPlayer->mEdgePos1.x;
		float moveSpeed = enemyChamp->mMoveSpeed;

		if (missileSpeed > 0) {
			if (enemyChamp->mAIManager->mIsMoving || enemyChamp->mAIManager->mIsDashing) {

				Vector enemyPos = {};

				if (enemyChamp->mAIManager->mIsMoving) {
					enemyPos = enemyChamp->mUnitPos;
				}

				if (enemyChamp->mAIManager->mIsDashing) {
					enemyPos = enemyChamp->mAIManager->mDashEndPosition;
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
		fnCastSpell(SpellBook, SpellPtr, slot, &predictedLocation, pEmpty, 0);
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

		fnIssueOrder(myPlayer, orderType, &targetPosition, enemyChamp, 0, 0, 0);
	}

	void IssueMoveOrder() {
		int orderType = 2; //AttackType
		object* myPlayer = (object*)lPlayer;
		Vector myPos = myPlayer->mUnitPos;
		oCursor* myMouse = (oCursor*)oMouse;
		Vector mousePos = myMouse->mMousePos;

		fnIssueOrder(myPlayer, orderType, &mousePos, nullptr, 0, 0, 0);
	}
}
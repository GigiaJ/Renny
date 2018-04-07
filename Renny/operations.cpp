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

	void CastSpell(object* enemyChamp, int slot, bool enemyMoving) {
		DWORD SpellBook;
		DWORD SpellPtr;
		Vector Empty;

		Vector predictedLocation = enemyChamp->unitPos;
		Empty.x = 0;
		Empty.y = 0;
		Empty.z = 0;
		Vector* pEmpty = &Empty;
		object* myPlayer = (object*)lPlayer;
		Vector myPos = myPlayer->unitPos;
		float ping = 0.024f * 2.0f;
		SpellBook = (lPlayer + 0x1B90);
		SpellPtr = *(DWORD*)myPlayer->SpellInstArray[slot];
		float missileSpeed = (myPlayer->SpellInstArray[slot]->SpellData->SpellInfo->MissileSpeed);
		float missileWidth = (myPlayer->SpellInstArray[slot]->SpellData->SpellInfo->MissileWidth);
		float castTime = (myPlayer->SpellInstArray[slot]->SpellData->SpellInfo->CastTime);
		float moveSpeed = enemyChamp->mMoveSpeed;
		float directionX = enemyChamp->FacingX;
		float directionZ = enemyChamp->FacingZ;

		if (missileSpeed > 0) {
			if (enemyMoving) {
				float distanceFromEachotherX = static_cast<float>(std::fabs(myPos.x - secondPosition.x));
				float distanceFromEachotherZ = static_cast<float>(std::fabs(myPos.z - secondPosition.z));
				float distanceFromEachother = distanceFromEachotherX + distanceFromEachotherZ;
				float distanceTravelledDuringCast = castTime * moveSpeed;
				float distTrav = static_cast<float>(std::pow(static_cast<double>(distanceTravelledDuringCast), static_cast<double>(2)));
				float distFromEach = static_cast<float>(std::pow(static_cast<double>(std::fabs(distanceFromEachotherX)), static_cast<double>(2)));
				float sumOfDistances = distTrav + distFromEach;
				float sumSquared = static_cast<float>(std::sqrt(sumOfDistances));

				predictedLocation.x = secondPosition.x + calculateEnemyFuturePositionCenter(distanceTravelledDuringCast, sumSquared, missileSpeed, missileWidth, moveSpeed, directionX, castTime);
				predictedLocation.y = secondPosition.y;
				predictedLocation.z = secondPosition.z + calculateEnemyFuturePositionCenter(distanceTravelledDuringCast, sumSquared, missileSpeed, missileWidth, moveSpeed, directionZ, castTime);

			}
		}
		fnCastSpell(SpellBook, SpellPtr, slot, &predictedLocation, pEmpty, 0);
	}

	void IssueAttackOrder(object* enemyChamp) {
		int orderType = 3; //AttackType
		object* myPlayer = (object*)lPlayer;
		Vector myPos = myPlayer->unitPos;
		Vector enemyPos = enemyChamp->unitPos;
		float moveSpeed = myPlayer->mMoveSpeed;
		float directionX = myPlayer->FacingX;
		float directionZ = myPlayer->FacingZ;
		Vector targetPosition = {};

		if (enemyChamp != nullptr) {
			targetPosition = enemyPos;
		}

		fnIssueOrder(myPlayer, orderType, &targetPosition, enemyChamp, 0, 0, 0);
	}

	void IssueMoveOrder() {
		int orderType = 2; //AttackType
		object* myPlayer = (object*)lPlayer;
		Vector myPos = myPlayer->unitPos;
		oCursor* myMouse = (oCursor*)oMouse;
		Vector mousePos = myMouse->mousePos;

		fnIssueOrder(myPlayer, orderType, &mousePos, nullptr, 0, 0, 0);
	}
}
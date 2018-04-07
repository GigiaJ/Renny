#include "stdafx.h"
#include "modules.h"

void autododge(object* myPlayer) {

}

void autoComboer(object* myPlayer) {

	object* champToCombo = getClosestEnemy(myPlayer, myPlayer->mSpellInstArray[firstSpell]->mSpellData->mSpellInfo->mMaxRange);
	if (champToCombo != nullptr) {

		//Test::IssueAttackOrder(champToCombo);

		if (firstSpell != -1) {
			Operations::CastSpell(champToCombo, firstSpell, isMoving(champToCombo));
			Sleep(static_cast<int>(myPlayer->mSpellInstArray[firstSpell]->mSpellData->mSpellInfo->mCastTime));
		}

		if (secondSpell != -1) {
			Operations::CastSpell(champToCombo, secondSpell, isMoving(champToCombo));
			Sleep(static_cast<int>(myPlayer->mSpellInstArray[secondSpell]->mSpellData->mSpellInfo->mCastTime));
		}
		if (thirdSpell != -1) {
			Operations::CastSpell(champToCombo, thirdSpell, isMoving(champToCombo));
			Sleep(static_cast<int>(myPlayer->mSpellInstArray[thirdSpell]->mSpellData->mSpellInfo->mCastTime));
		}

		Sleep(static_cast<int>(myPlayer->mSpellInstArray[firstSpell]->mCurrentCDR));
	}
}

void orbwalker(object* myPlayer) {
	float windUpTime;
	float animationTime;
	float myAttackRange = myPlayer->mAttackRange;
	int dwDelay1 = 0;
	int dwDelay2 = 0;
	object* champToOrbWalk = getClosestEnemy(myPlayer, myAttackRange);
	if (champToOrbWalk != nullptr) {
		Operations::IssueAttackOrder(champToOrbWalk);
		Vector spellPos = spellCastData->mStartPosition;
		Vector myPos = myPlayer->mUnitPos;
		float ping = 0.025f;
		float difference = (spellPos.x - myPos.x) + (spellPos.z - myPos.z);
		float modifier = myPlayer->mAttackSpeedMod;

		if (difference == 0) {
			windUpTime = spellCastData->mWindUpTime;
			animationTime = spellCastData->mAnimationTime;
		}

		dwDelay1 = static_cast<int>(((windUpTime * 2) + ping) * 1000.00f);
		dwDelay2 = static_cast<int>(((animationTime / modifier) + windUpTime) * 1000.00f);
		//Attack (orderType 3


		std::chrono::milliseconds dura(dwDelay1);
		std::this_thread::sleep_for(dura);

		Operations::IssueMoveOrder();
		std::chrono::milliseconds dura2(dwDelay2);
		std::this_thread::sleep_for(dura2);
		/*
		Move (orderType 2)
		Test::IssueOrder(nullptr, 2);
		Auto-dodge use
		*/
	}

}
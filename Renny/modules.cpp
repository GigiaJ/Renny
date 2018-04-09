#include "stdafx.h"
#include "modules.h"

float comboerDelay = 0.0f;
float secondSpellDelay = 0.0f;
float thirdSpellDelay = 0.0f;
float fourthSpellDelay = 0.0f;

float attackDelay = 0;
float moveDelay = 0;

bool firstSpellAwaitingReset = true;
bool secondSpellAwaitingReset = true;


void autododge(object* myPlayer) {

}

void autoComboer(object* myPlayer) {
	if ((comboerDelay - myPlayer->mSpellInstArray[firstSpell]->mCurrentCDR + 1) <= vGameTime) {
		object* champToCombo = getClosestEnemy(myPlayer, myPlayer->mSpellInstArray[firstSpell]->mSpellData->mSpellInfo->mMaxRange);
		if (champToCombo != nullptr) {
			//Test::IssueAttackOrder(champToCombo);

			if (firstSpell != -1 && firstSpellAwaitingReset == true) {
				Operations::CastSpell(champToCombo, firstSpell);
				secondSpellDelay = resetDelay(myPlayer->mSpellInstArray[firstSpell]->mSpellData->mSpellInfo->mCastTime);
				firstSpellAwaitingReset = false;
				if (secondSpell == -1) {
					firstSpellAwaitingReset = true;
					comboerDelay = resetDelay(myPlayer->mSpellInstArray[firstSpell]->mCurrentCDR);
				}
			}

			if (secondSpell != -1 && secondSpellDelay <= vGameTime && secondSpellAwaitingReset == true) {
				Operations::CastSpell(champToCombo, secondSpell);
				thirdSpellDelay = resetDelay(myPlayer->mSpellInstArray[secondSpell]->mSpellData->mSpellInfo->mCastTime);
				secondSpellAwaitingReset = false;
				if (thirdSpell == -1) {
					firstSpellAwaitingReset = true;
					secondSpellAwaitingReset = true;
					comboerDelay = resetDelay(myPlayer->mSpellInstArray[firstSpell]->mCurrentCDR);
				}
			}
			if (thirdSpell != -1 && thirdSpellDelay <= vGameTime) {
				Operations::CastSpell(champToCombo, thirdSpell);
				firstSpellAwaitingReset = true;
				secondSpellAwaitingReset = true;
				comboerDelay = resetDelay(myPlayer->mSpellInstArray[firstSpell]->mCurrentCDR);
			}
		}
	}
}

void orbwalker(object* myPlayer) {
	float windUpTime;
	float animationTime;
	float myAttackRange = myPlayer->mAttackRange;

	object* champToOrbWalk = getClosestEnemy(myPlayer, myAttackRange);
	if (attackDelay <= vGameTime) {
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

			attackDelay = resetDelay((windUpTime * 2) + ping);
			moveDelay = resetDelay((animationTime / modifier) + windUpTime);
			//Attack (orderType 3
			//resetAndCountFor(dwDelay1);
			/*
			Move (orderType 2)
			Test::IssueOrder(nullptr, 2);
			Auto-dodge use
			*/
		}
		else {
			moveDelay = .250f;
		}
	}
	if (moveDelay <= vGameTime) {
		Operations::IssueMoveOrder();
	}

}
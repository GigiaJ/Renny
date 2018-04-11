#include "stdafx.h"
#include "modules.h"

float comboerDelay = 0.0f;
float secondSpellDelay = 0.0f;
float thirdSpellDelay = 0.0f;
float fourthSpellDelay = 0.0f;

float attackDelay = 0.0f; //Delay before you can attack again
float moveDelay = 0.0f; //Time it takes auto to end

float windUpTime = 0.0f;
float animationTime = 0.0f;

bool firstSpellAwaitingReset = true;
bool secondSpellAwaitingReset = true;


void autododge(object* myPlayer) {
	float distanceApart = absVectorDistance(myPlayer->mUnitPos, objMgr->mObjectManagerArray[spellCastData->casterIndex]->mUnitPos);
	if (spellCastData->mSpellData->mSpellInfo->mMaxRange < distanceApart) {

	}
}

void autoComboer(object* myPlayer) {
	if ((comboerDelay - myPlayer->mSpellInstArray[firstSpell]->mCurrentCDR + 1) <= vGameTime) {
		object* champToCombo = getClosestEnemy(myPlayer, myPlayer->mSpellInstArray[firstSpell]->mSpellData->mSpellInfo->mMaxRange, myPlayer->mSpellInstArray[firstSpell]->mSpellData->mSpellInfo->mCastRadius);
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
	if (autoAttackData != NULL) {
		Vector spellPos = autoAttackData->mStartPosition;
		Vector myPos = myPlayer->mUnitPos;
		float difference = (spellPos.x - myPos.x) + (spellPos.z - myPos.z);
		if (difference == 0) {
			windUpTime = autoAttackData->mWindUpTime;
			animationTime = autoAttackData->mAnimationTime;
		}
	}
	object* champToOrbWalk = getClosestEnemy(myPlayer, myPlayer->mAttackRange, (myPlayer->mEdgePos2.x - myPlayer->mEdgePos1.x));
	if (champToOrbWalk != nullptr) {
		if (attackDelay <= vGameTime) {
			Operations::IssueAttackOrder(champToOrbWalk);


			float ping = 0.050f;

			float modifier = myPlayer->mAttackSpeedMod;

			moveDelay = resetDelay(windUpTime + ping);
			attackDelay = resetDelay(animationTime);
		}
	}
	if (moveDelay <= vGameTime) {
		Operations::IssueMoveOrder();
		moveDelay = resetDelay(0.200f);
	}
}
#include "../stdafx.h"
#include "modules.h"

float attackDelay = 0.0f; //Delay before you can attack again
float moveDelay = 0.0f; //Time it takes auto to end

float windUpTime = 0.0f;
float animationTime = 0.0f;

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
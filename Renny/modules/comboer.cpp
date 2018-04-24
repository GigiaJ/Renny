#include "../stdafx.h"
#include "modules.h"

float comboerDelay = 0.0f;
float secondSpellDelay = 0.0f;
float thirdSpellDelay = 0.0f;
float fourthSpellDelay = 0.0f;

bool firstSpellAwaitingReset = true;
bool secondSpellAwaitingReset = true;

void autoComboer(object* myPlayer) {
	if ((comboerDelay - myPlayer->mSpellInstArray[firstSpell]->getCoolDown(myPlayer)) <= vGameTime) {
		int firstSpellRank = myPlayer->mSpellInstArray[firstSpell]->mCurrentRank;
		object* champToCombo = getClosestEnemy(myPlayer, myPlayer->mSpellInstArray[firstSpell]->mSpellData->mSpellInfo->mMaxRange[firstSpellRank + 1].value, myPlayer->mSpellInstArray[firstSpell]->mSpellData->mSpellInfo->mCastRadius[firstSpellRank + 1].value);
		if (champToCombo != nullptr) {
			//Test::IssueAttackOrder(champToCombo);

			if (firstSpell != -1 && firstSpellAwaitingReset == true) {
				Operations::CastSpell(champToCombo, firstSpell);
				secondSpellDelay = resetDelay(spellCastData->mWindUpTime);
				firstSpellAwaitingReset = false;
				if (secondSpell == -1) {
					firstSpellAwaitingReset = true;
					comboerDelay = resetDelay(myPlayer->mSpellInstArray[firstSpell]->getCoolDown(myPlayer));
				}
			}

			if (secondSpell != -1 && secondSpellDelay <= vGameTime && secondSpellAwaitingReset == true) {
				Operations::CastSpell(champToCombo, secondSpell);
				thirdSpellDelay = resetDelay(spellCastData->mWindUpTime);
				secondSpellAwaitingReset = false;
				if (thirdSpell == -1) {
					firstSpellAwaitingReset = true;
					secondSpellAwaitingReset = true;
					comboerDelay = resetDelay(myPlayer->mSpellInstArray[firstSpell]->getCoolDown(myPlayer));
				}
			}
			if (thirdSpell != -1 && thirdSpellDelay <= vGameTime) {
				Operations::CastSpell(champToCombo, thirdSpell);
				firstSpellAwaitingReset = true;
				secondSpellAwaitingReset = true;
				comboerDelay = resetDelay(myPlayer->mSpellInstArray[firstSpell]->getCoolDown(myPlayer));
			}
		}
	}
}
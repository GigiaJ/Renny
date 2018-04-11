#pragma once
#include "globals.h"

bool isPositive(float number);

bool isNegative(float number);

bool isZero(float number);

float resetDelay(float delay);

float modifySign(float numberToCheck, float numberToModify);

float calculateEnemyFuturePosition(float arg1, float arg2, float arg3, float arg4, float arg5, float arg6, float arg7);

float absVectorDistance(Vector arg1, Vector arg2);

void applyActiveAutoCastInfo(DWORD arg1);

void applyActiveSpellCastInfo(DWORD arg1);

void getListOfEnemyChamps(object* myPlayer);

object* getClosestEnemy(object* myPlayer, float range, float castRadius);
#pragma once
#include "globals.h"

bool isPositive(float number);

bool isNegative(float number);

bool isZero(float number);

float modifySign(float numberToCheck, float numberToModify);

float calculateEnemyFuturePosition(float arg1, float arg2, float arg3, float arg4, float arg5, float arg6, float arg7);

void applyActiveCastInfo(DWORD arg1);

void getListOfEnemyChamps(object* myPlayer);

bool isMoving(object* targetChamp);

object* getClosestEnemy(object* myPlayer, float range);
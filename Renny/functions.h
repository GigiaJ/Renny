#pragma once
#include "globals.h"

bool isPositive(float number);

bool isNegative(float number);

bool isZero(float number);

void setEnemyTeam(object* myPlayer);

float modifySign(float numberToCheck, float numberToModify);

float calculateEnemyFuturePosition(float arg1, float arg2, float arg3, float arg4, float arg5, float arg6, float arg7);

float absVectorDistance(Vector arg1, Vector arg2);

float absObjectDistanceApart(object* unitOne, object*unitTwo);

void applyActiveAutoCastInfo(DWORD arg1);

void applyActiveSpellCastInfo(DWORD arg1);

void applyCastInfo(DWORD arg1);

void getListOfEnemyChamps(object* myPlayer);

object* getClosestEnemy(object* myPlayer, float range, float castRadius);
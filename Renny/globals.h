#pragma once

#include "offsets.h"
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <future>

extern DWORD base;
extern objectManager* objMgr;
extern DWORD lPlayer;
extern DWORD Mouse;
extern spellCastDataBase* autoAttackData;
extern spellCastDataBase* spellCastData;
extern float vGameTime;

extern std::vector<object*> listOfEnemyChamps;
extern volatile DWORD isWall;

extern int firstSpell;
extern int secondSpell;
extern int thirdSpell;

extern DWORD comboerKey;
extern DWORD orbwalkKey;
#pragma once

#include "offsets.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

extern DWORD base;
extern objectManager* objMgr;
extern DWORD lPlayer;
extern DWORD oMouse;
extern spellCastDataBase* spellCastData;
extern Vector firstPosition;
extern Vector secondPosition;
extern std::vector<object*> listOfEnemyChamps;

extern int firstSpell;
extern int secondSpell;
extern int thirdSpell;

extern DWORD comboerKey;
extern DWORD orbwalkKey;
#include "stdafx.h"
#include "operations.h"

DWORD base = (DWORD)(GetModuleHandleA(NULL));
objectManager* objMgr = (objectManager*)(base + 0x2E30EA0);
DWORD lPlayer = *(DWORD*)(base + 0x2E31A7C);
DWORD oMouse = *(DWORD*)(base + 0x1589A94);
spellCastDataBase* spellCastData;
Vector firstPosition = {};
Vector secondPosition = {};
std::vector<object*> listOfEnemyChamps = {};

int firstSpell = 0;
int secondSpell = -1;
int thirdSpell = -1;

DWORD comboerKey = 0x57;
DWORD orbwalkKey = 0x10;
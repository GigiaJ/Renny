#include "stdafx.h"
#include "operations.h"

DWORD base = (DWORD)(GetModuleHandleA(NULL));
objectManager* objMgr = (objectManager*)(base + oObjManager);
DWORD lPlayer = *(DWORD*)(base + oLocalPlayer);
DWORD Mouse = *(DWORD*)(base + oCursor);
spellCastDataBase* autoAttackData;
spellCastDataBase* spellCastData;
float vGameTime = *(reinterpret_cast<float*> (base + oGameTime));

std::vector<object*> listOfEnemyChamps = {};

volatile DWORD isWall = 0x00000000;
object* latestObject = {};

int enemyTeam = 0;

int firstSpell = 0;
int secondSpell = 1;
int thirdSpell = -1;

DWORD comboerKey = 0x57;
DWORD orbwalkKey = 0x10;
// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "modules/modules.h"
#include "hooks.h"

DWORD WINAPI worker(LPVOID lpParam)
{
	
	object* myPlayer = (object*)lPlayer;
	getListOfEnemyChamps(myPlayer);
	applyHooks();
	
	while (true)
	{
		vGameTime = *(reinterpret_cast<float*> (base + 0x2E2E044));
		Operations::Init();

		autododge(myPlayer);

		if (GetAsyncKeyState(comboerKey) & 1) {
			autoComboer(myPlayer);
		}
		
		if (GetAsyncKeyState(orbwalkKey) & 1)
		{
			orbwalker(myPlayer);
		}
		
		if (GetAsyncKeyState(0x20) & 1) {
			oMouse* myMouse = (oMouse*)Mouse;
			Vector mousePos = myMouse->mMousePos;
			Operations::isWall(mousePos);
		}

	}

}

BOOL APIENTRY DllMain(HINSTANCE hInst, DWORD reason, LPVOID reserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(0, 0, worker, 0, 0, NULL);
		break;
	}
	return TRUE;
}
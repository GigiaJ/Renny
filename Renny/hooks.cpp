#include "stdafx.h"
#include "functions.h"
#include "hooks.h"


int hookLength = 7;
DWORD hookAddress = base + fnOnSpellCast + 0x27C;
DWORD BackAddy1 = hookAddress + hookLength;

int hookLength2 = 10;
DWORD hookAddress2 = base + fnOnAutoAttack + 0x286;
DWORD BackAddy2 = hookAddress2 + hookLength2;

int hookLength3 = 9;
DWORD hookAddress3 = base + fnOnProcessSpellW + 0x33;
DWORD BackAddy3 = hookAddress3 + hookLength3;


int hookLength4 = 5;
DWORD hookAddress4 = base + fnCreatePath + 0x2A6;
DWORD BackAddy4 = hookAddress4 + hookLength4;
DWORD callAddy4 = base + fnCheckIfInitialClickIsAvaliable;

bool Hook(void * toHook, void * ourFunct, int len) {
	if (len < 5) {
		return false;
	}

	DWORD curProtection;
	VirtualProtect(toHook, len, PAGE_EXECUTE_READWRITE, &curProtection);

	memset(toHook, 0x90, len);

	DWORD relativeAddress = ((DWORD)ourFunct - (DWORD)toHook) - 5;
	*(BYTE*)toHook = 0xE9;
	*(DWORD*)((DWORD)toHook + 1) = relativeAddress;

	DWORD temp;
	VirtualProtect(toHook, len, curProtection, &temp);

	return true;
}

void applyHooks() {
	bool doOnce = true;
	if (doOnce) {
		doOnce = false;

		//Hook((void*)hookAddress, onSpellCast, hookLength);

		//Hook((void*)hookAddress2, onAutoAttack, hookLength2);

		Hook((void*)hookAddress3, onCast, hookLength3);

		Hook((void*)hookAddress4, onWallClick, hookLength4);
	}
}

void __declspec(naked) onCast() {

	//DWORD castInfo;

	__asm {
		mov spellCastData, edi
	}

	//__asm {
	//	pushad
	//}

	//applyCastInfo(castInfo);

	__asm {
	//	popad
		mov     esi, eax
		add     esp, 18h
		mov     ecx, esi
		mov     edx, [esi]
	}

	__asm jmp BackAddy3


}

void __declspec(naked) onAutoAttack() {
	__asm {
		pushad
	}


	__asm {
		popad
		push dword ptr ss : [esp + 0Ch]
		pushad
	}

	DWORD autoAttackInfo;

	__asm {
		mov edx, ebx
		mov ebx, [esp + 10h]
		mov autoAttackInfo, ebx
		mov ebx, edx
	}

	applyActiveAutoCastInfo(autoAttackInfo);

	__asm {
		popad
		lea ecx, [ebx + pSpellBookPtr]
	}

	__asm jmp BackAddy2
}

void __declspec(naked) onSpellCast() {
	__asm {
		pushad
	}

	DWORD spellCastInfo;


	__asm {
		mov spellCastInfo, eax
	}

	if (spellCastInfo != 0x3) {
		applyActiveSpellCastInfo(spellCastInfo);
	}

	__asm {
		popad
		push eax
		lea ecx, dword ptr ss : [ebx - 1268h]
	}

	__asm jmp BackAddy1
}

void _declspec(naked) onWallClick() {
	
	_asm call callAddy4

	_asm mov isWall, eax

	_asm jmp BackAddy4
}
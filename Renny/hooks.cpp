#include "stdafx.h"
#include "functions.h"
#include "hooks.h"


int hookLength = 5;
DWORD hookAddress = base + 0x1CF81B;
DWORD BackAddy1 = hookAddress + hookLength;
int hookLength2 = 10;
DWORD hookAddress2 = base + 0x1E3CCB;
DWORD BackAddy2 = hookAddress2 + hookLength2;


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

		int hookLength = 5;
		DWORD hookAddress = base + 0x1CF81B;
		Hook((void*)hookAddress, onSpellCast, hookLength);

		int hookLength2 = 10;
		DWORD hookAddress2 = base + 0x1E3CCB;
		Hook((void*)hookAddress2, onAutoAttack, hookLength2);
	}
}

void __declspec(naked) onAutoAttack() {
	__asm {
		pushad
	}


	__asm {
		popad
		push dword ptr ss : [esp + 0Ch]
	}

	DWORD autoAttackInfo;

	__asm {
		mov edx, ebx
		mov ebx, [esp + 10h]
		mov autoAttackInfo, ebx
		mov ebx, edx
	}

	applyActiveCastInfo(autoAttackInfo);

	__asm {
		lea ecx, [ebx + 1B90h]
	}

	__asm jmp BackAddy2
}

void __declspec(naked) onSpellCast() {
	__asm {
		pushad
	}
	__asm {
		popad
		lea eax, dword ptr ss : [esp + 2Ch]
		push eax
	}

	DWORD* spellCastInfo;

	__asm {
		mov edx, ebx
		mov ebx, esp
		mov spellCastInfo, ebx
		mov ebx, edx
	}

	applyActiveCastInfo(*spellCastInfo);

	__asm jmp BackAddy1
}
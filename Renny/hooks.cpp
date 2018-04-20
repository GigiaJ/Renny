#include "stdafx.h"
#include "functions.h"
#include "hooks.h"


int hookLength = 6;
DWORD hookAddress = base + 0x1CF820;
DWORD BackAddy1 = hookAddress + hookLength;
int hookLength2 = 10;
DWORD hookAddress2 = base + 0x1E3CCB;
DWORD BackAddy2 = hookAddress2 + hookLength2;

int hookLength3 = 9;
DWORD hookAddress3 = base + 0x549910;
DWORD BackAddy3 = hookAddress3 + hookLength3;

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

	Hook((void*)hookAddress, onSpellCast, hookLength);

	Hook((void*)hookAddress2, onAutoAttack, hookLength2);

	// Hook((void*)hookAddress3, onCast, hookLength3);
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

	applyActiveAutoCastInfo(autoAttackInfo);

	__asm {
		lea ecx, [ebx + 1B90h]
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
	applyActiveSpellCastInfo(spellCastInfo);


	__asm {
		popad
		lea ecx, dword ptr ss : [ebp - 1268h]
	}

	__asm jmp BackAddy1
}

void __declspec(naked) onCast() {
	__asm {
		pushad
	}

	DWORD* spellCastInfo;

	__asm {
		mov edx, [esp + 1Ch]
		mov spellCastInfo, edx

	}

	applyActiveSpellCastInfo(*spellCastInfo);

	__asm {

		popad

		push edi
		mov edi, dword ptr ss : [esp + 8h]
		mov edx, dword ptr ds : [edi]
		test edx, edx

		jmp BackAddy3
	}

}
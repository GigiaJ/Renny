#pragma once
#include "offsets.h"

class VTABLE
{
public:
	void* m_OnProcessSpellW = (DWORD*)(base + 0x54D140);
};

class VirtualTest
{
public: 
	virtual char TwoParamVirt() {
		return 4;
	}
	virtual char TwoParamVirt2() {
		return 1;
	}
};
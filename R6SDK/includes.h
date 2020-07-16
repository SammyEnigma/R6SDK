#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include "mem.h"

class R6 {
public:
	uintptr_t base;
	DWORD pid;
	int width, size;

	Memory* mem;
	R6();
};



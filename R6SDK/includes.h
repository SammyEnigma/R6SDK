#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>

template <typename T>
struct R6Array {
	T* elements;
	DWORD size : 30;
};

#include "mem.h"
#include "offsets.h"
#include "Entity.h"
#include "GameManager.h"



class R6 {
public:
	uintptr_t base;
	DWORD pid;
	int width, size;

	Memory* mem;
	R6();


	//R6 Managers
	GameManager* gamemanager;
};



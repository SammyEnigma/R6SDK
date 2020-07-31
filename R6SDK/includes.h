#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <xmmintrin.h>
#include "math.h"
template <typename T>
struct R6Array {
	T* elements;
	DWORD size : 30;
};
#include "mem.h"
#include "offsets.h"
#include "RoundManager.h"
#include "Entity.h"
#include "GameManager.h"
#include "GameProfileManager.h"


class R6 {
public:
	uintptr_t base;
	DWORD pid;
	int width, size;

	Memory* mem;
	R6();


	//R6 Managers
	GameManager* gamemanager;
	RoundManager* roundmanager;
	GameProfileManager* gameprofilemanager;
};



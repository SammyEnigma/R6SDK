#include "includes.h"
namespace offsets {

	namespace Manager {
		DWORD GameManager = 0x605D1C0; //48 8b 05 ? ? ? ? 8b 8e ? ? ? ? 83 c1 ? 89 88 ? ? ? ? 48 89 f1 b2 ? 48 83 c4 ? 5b 5f 5e e9 ? ? ? ? 90 48 83 c4 ? 5b 5f 5e c3 cc cc cc cc cc cc cc cc cc cc cc 56 48 83 ec  
	}

	namespace GameManager {
		DWORD Entlist = 0x98;
		uintptr_t decryptionkey_entlist = 0xE60F6CF8784B5E96;
	}
}
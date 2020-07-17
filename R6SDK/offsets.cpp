#include "includes.h"
namespace offsets {

	namespace Manager {
		DWORD GameManager = 0x605D1C0; //48 8b 05 ? ? ? ? 8b 8e ? ? ? ? 83 c1 ? 89 88 ? ? ? ? 48 89 f1 b2 ? 48 83 c4 ? 5b 5f 5e e9 ? ? ? ? 90 48 83 c4 ? 5b 5f 5e c3 cc cc cc cc cc cc cc cc cc cc cc 56 48 83 ec  
	}

	namespace GameManager {
		DWORD Entlist = 0x488;
		uintptr_t decryptionkey_entlist = 0x5B27FE2BA1503866;
	}

	namespace Entity {
		DWORD maincomp = 0xAA8;
		DWORD pawn = 0x20;
		uintptr_t decryptionkey_pawn = 0xB9A25DD8A6AD943D;

		namespace npawn {
			DWORD skeleton = 0x908;
		}
	}
}
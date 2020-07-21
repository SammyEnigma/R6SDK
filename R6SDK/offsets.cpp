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
		DWORD playercomp = 0x28;
		DWORD info = 0xD0;
		DWORD weapon = 0x90;
		uintptr_t decryptionkey_pawn = 0xB9A25DD8A6AD943D;
		uintptr_t decryptionkey_main_component = 0xDC8041B6C7F86465;

		namespace ncomp {
			DWORD complist = 0xD0;
			uintptr_t decryptionkey_player_component = 0xC3868E9D7D6FCC95;
			DWORD vt_marker = 0x4c04670;
			DWORD bSpotted = 0x632; //602 if from right vtable 0x633 = showMarker
		}


		namespace ninfo {
			DWORD team = 0x1BE;
			DWORD CTU = 0x1B0;
			DWORD OP = 0x1B1;
			
		}

		namespace nweapon {
			DWORD currweapon = 0xC8;
			DWORD weaponinfo = 0x290;
			uintptr_t decryptionkey_weaponinfo = 0xD4CF9346AD08C46A;
			DWORD firetype = 0x118;
			DWORD ammo = 0x11C;
			DWORD reserved = 0x120;
			DWORD spread = 0x68;
			DWORD recoilvert = 0x174;
			DWORD recoilhoriz = 0x164;
			DWORD recoil_overwrite = 0x180;
		}

		namespace npawn {
			DWORD skeleton = 0x908;
		}
	}
}
namespace offsets {

	namespace Manager {
		extern DWORD GameManager;
	}
	
	namespace GameManager {
		extern DWORD Entlist;
		extern uintptr_t decryptionkey_entlist;
	}

	namespace Entity {
		extern DWORD entity_from_pawn;
		extern DWORD maincomp;
		extern DWORD pawn;
		extern DWORD playercomp;
		extern DWORD info;
		extern DWORD weapon;
		extern uintptr_t decryptionkey_pawn;
		extern uintptr_t decryptionkey_main_component;

		namespace ncomp {
			extern DWORD complist;
			extern uintptr_t decryptionkey_player_component;
			extern DWORD vt_marker;
			extern DWORD bSpotted;
		}

		namespace ninfo {
			extern DWORD team;
			extern DWORD CTU;
			extern DWORD OP;
		}

		namespace nweapon {
			extern DWORD currweapon;
			extern DWORD weaponinfo;
			extern uintptr_t decryptionkey_weaponinfo;
			extern DWORD firetype;
			extern DWORD ammo;
			extern DWORD reserved;
			extern DWORD spread;
			extern DWORD recoilvert;
			extern DWORD recoilhoriz;
			extern DWORD recoil_overwrite;
		}

		namespace npawn {
			extern DWORD skeleton;
		}

	}
}
namespace offsets {

	namespace Manager {
		extern DWORD GameManager;
		extern DWORD RoundManager;
		extern DWORD GameProfileManager;
	}
	
	namespace GameManager {
		extern DWORD Entlist;
		extern uintptr_t decryptionkey_entlist;
	}

	namespace RoundManager {
		extern DWORD round;
	}

	namespace GameProfileManager {
		extern DWORD _loc;
		extern DWORD locplayer;
		extern uintptr_t decryptionkey_localplayer;
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

			extern DWORD weapon_info;
			extern DWORD arry_to_single;
			extern DWORD current_weapon_preset;
			extern DWORD pull;
			extern DWORD kick;
		}

		namespace npawn {
			extern DWORD skeleton;
		}

	}
}
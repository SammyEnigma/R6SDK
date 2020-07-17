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
		extern uintptr_t decryptionkey_pawn;

		namespace npawn {
			extern DWORD skeleton;
		}

	}
}
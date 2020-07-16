#include "includes.h"
extern R6* r6;
R6Array<Entity> GameManager::get_entitylist() {
	R6Array<Entity> entarray;
	uintptr_t entlistaddress = r6->mem->read<uintptr_t>(this->address + offsets::GameManager::Entlist) + offsets::GameManager::decryptionkey_entlist;
	entarray.size = (r6->mem->read<uintptr_t>(this->address + offsets::GameManager::Entlist + sizeof(void*)) + offsets::GameManager::decryptionkey_entlist) & 0x3F;

	entarray.elements = new Entity[entarray.size];
	for (int i = 0; i < entarray.size; i++) {
		entarray.elements[i].address = r6->mem->read<uintptr_t>(entlistaddress + i * sizeof(void*));
	}

	return entarray;
}

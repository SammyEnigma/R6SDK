#include "includes.h"
extern R6* r6;
void GameProfileManager::get() {
	this->address = r6->mem->read<uintptr_t>(r6->base + offsets::Manager::GameProfileManager);
	this->address = r6->mem->read<uintptr_t>(this->address + offsets::GameProfileManager::_loc);
	this->address = r6->mem->read<uintptr_t>(this->address);
	this->address = r6->mem->read<uintptr_t>(this->address + offsets::GameProfileManager::locplayer) + offsets::GameProfileManager::decryptionkey_localplayer;
	this->LocalPlayer.get(this->address);
}
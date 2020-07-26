#include "includes.h"
extern R6* r6;
BYTE RoundManager::get_round() {
	this->address = r6->mem->read<uintptr_t>(r6->base + offsets::Manager::RoundManager);
	return r6->mem->read<BYTE>(this->address + offsets::RoundManager::round);
}
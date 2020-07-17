#include "includes.h"
extern R6* r6;
R6Array<Entity> GameManager::get_entitylist() {
	R6Array<Entity> entarray;
	uintptr_t entlistaddress = r6->mem->read<uintptr_t>(this->address + offsets::GameManager::Entlist) + offsets::GameManager::decryptionkey_entlist;
	entarray.size = (r6->mem->read<uintptr_t>(this->address + offsets::GameManager::Entlist + sizeof(void*)) + offsets::GameManager::decryptionkey_entlist) & 0x3F;
	entarray.elements = new Entity[entarray.size];
	for (int i = 0; i < entarray.size; i++) 
		entarray.elements[i] = this->get_ent(i, entlistaddress);
	return entarray;
}

Entity GameManager::get_ent(int idx, uintptr_t entlistaddress) {
	Entity newEnt;
	newEnt.maincomp.pawn.address = r6->mem->read<uintptr_t>(entlistaddress + idx * sizeof(void*));
	newEnt.maincomp.address = r6->mem->read<uintptr_t>(newEnt.maincomp.pawn.address + offsets::Entity::maincomp) ^ 0xDC8041B6C7F86465;

	newEnt.maincomp.pawn.skeleton.address = newEnt.maincomp.pawn.address + offsets::Entity::npawn::skeleton;
	math::Vec4 headpos = newEnt.maincomp.pawn.skeleton.get_bone(Skeleton::bone_ids::head);
	newEnt.maincomp.pawn.head = math::Vec3(headpos.x, headpos.y, headpos.z);
	//newEnt.maincomp.pawn.address = r6->mem->read<uintptr_t>(newEnt.maincomp.address + 0x20) + offsets::Entity::decryptionkey_pawn;
	return newEnt;
}
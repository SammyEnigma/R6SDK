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
	newEnt.maincomp.address = r6->mem->read<uintptr_t>(newEnt.maincomp.pawn.address + offsets::Entity::maincomp) ^ offsets::Entity::decryptionkey_main_component;

	//Entity PAWN 0x20
	newEnt.maincomp.pawn.skeleton.address = newEnt.maincomp.pawn.address + offsets::Entity::npawn::skeleton;
	math::Vec4 headpos = newEnt.maincomp.pawn.skeleton.get_bone(Skeleton::bone_ids::head);
	newEnt.maincomp.pawn.head = math::Vec3(headpos.x, headpos.y, headpos.z);
	math::Vec4 feetpos = newEnt.maincomp.pawn.skeleton.get_bone(Skeleton::bone_ids::foot_right);
	newEnt.maincomp.pawn.feet = math::Vec3(feetpos.x, feetpos.y, feetpos.z);

	//Entity Information 0xD0
	newEnt.maincomp.info.address = r6->mem->read<uintptr_t>(newEnt.maincomp.address + offsets::Entity::info);
	newEnt.maincomp.info.team = (r6->mem->read<BYTE>(newEnt.maincomp.info.address + offsets::Entity::ninfo::team) +0x24) & 0x3F;
	newEnt.maincomp.info.CTU = r6->mem->read<BYTE>(newEnt.maincomp.info.address + offsets::Entity::ninfo::CTU);
	newEnt.maincomp.info.OP = r6->mem->read<BYTE>(newEnt.maincomp.info.address + offsets::Entity::ninfo::OP);
	uintptr_t namepointer = r6->mem->read<uintptr_t>(newEnt.maincomp.info.address + 0x1C8);	
	r6->mem->cread(namepointer, newEnt.maincomp.info.name, 0x15);

	//Weapon 0x90
	newEnt.maincomp.weapon.address = r6->mem->read<uintptr_t>(newEnt.maincomp.address + offsets::Entity::weapon);
	newEnt.maincomp.weapon.currweapon.address = r6->mem->read<uintptr_t>(newEnt.maincomp.weapon.address + offsets::Entity::nweapon::currweapon);
	newEnt.maincomp.weapon.currweapon.info.address = r6->mem->read<uintptr_t>(newEnt.maincomp.weapon.currweapon.address + offsets::Entity::nweapon::weaponinfo) + offsets::Entity::nweapon::decryptionkey_weaponinfo;
	newEnt.maincomp.weapon.currweapon.info.address += 0x18; //Because thats how the game calls it
	newEnt.maincomp.weapon.currweapon.ammo = r6->mem->read<int>(newEnt.maincomp.weapon.currweapon.address + offsets::Entity::nweapon::ammo);
	newEnt.maincomp.weapon.currweapon.ammo_reserved = r6->mem->read<int>(newEnt.maincomp.weapon.currweapon.address + offsets::Entity::nweapon::reserved);
	newEnt.maincomp.weapon.currweapon.fire_type = r6->mem->read<int>(newEnt.maincomp.weapon.currweapon.address + offsets::Entity::nweapon::firetype);

	//WeaponInfo Weapon->0x290
	newEnt.maincomp.weapon.currweapon.info.spread = r6->mem->read<float>(newEnt.maincomp.weapon.currweapon.info.address + offsets::Entity::nweapon::spread);
	newEnt.maincomp.weapon.currweapon.info.recoilvert = r6->mem->read<float>(newEnt.maincomp.weapon.currweapon.info.address + offsets::Entity::nweapon::recoilvert);
	newEnt.maincomp.weapon.currweapon.info.recoilhoriz = r6->mem->read<float>(newEnt.maincomp.weapon.currweapon.info.address + offsets::Entity::nweapon::recoilhoriz);
	return newEnt;
}
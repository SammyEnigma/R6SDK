#include "includes.h"

class R6* r6;

R6::R6() {
	this->mem = new Memory();
	this->gamemanager = new GameManager();
}

void MainLoop(){
	while (true) {
		r6->gamemanager->address = r6->mem->read<uintptr_t>(r6->base + offsets::Manager::GameManager);
		r6->gamemanager->EntList = r6->gamemanager->get_entitylist();
		for (int i = 0; i < r6->gamemanager->EntList.size; i++) {
			Entity* current = &r6->gamemanager->EntList.elements[i];
			//Team check is invalid for BOTS (and name ofc)
			printf(
				" Entity [%i] [%s] [%s] : [%f %f %f] [%i,%i]\n",
				current->maincomp.info.team,
				current->maincomp.info.name,
				current->maincomp.info.get_operator_name(),
				current->maincomp.pawn.head.x, 
				current->maincomp.pawn.head.y, 
				current->maincomp.pawn.head.z,
				current->maincomp.weapon.currweapon.ammo,
				current->maincomp.weapon.currweapon.ammo_reserved
			);		
			//Example of weapon usage:
			current->maincomp.weapon.currweapon.set_ammo(999, 999);
			current->maincomp.weapon.currweapon.set_fire_type(CurrentWeapon::full_auto);

			current->maincomp.weapon.currweapon.info.set_spread(0.f);
			current->maincomp.weapon.currweapon.info.set_recoil(5, 5);
		}
		Sleep(1000);
		system("cls");
	}
}

int main() {
	r6 = new R6();
	r6->mem->setup();
	
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainLoop, 0, 0, 0);

	//TODO: Localplayer, Environment, Outline, DroneScan, Devices, Chat [...]

	system("pause");
	
}
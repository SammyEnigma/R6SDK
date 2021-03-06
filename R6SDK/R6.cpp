#include "includes.h"

class R6* r6;

R6::R6() {
	this->mem = new Memory();
	this->gamemanager = new GameManager();
	this->roundmanager = new RoundManager();
	this->gameprofilemanager = new GameProfileManager();
}

void MainLoop(){
	while (true) {
		BYTE round = r6->roundmanager->get_round();
		if (round == RoundManager::action) {
			r6->gameprofilemanager->get();
			r6->gamemanager->address = r6->mem->read<uintptr_t>(r6->base + offsets::Manager::GameManager);
			r6->gamemanager->EntList = r6->gamemanager->get_entitylist();
			for (int i = 0; i < r6->gamemanager->EntList.size; i++) {
				Entity* current = &r6->gamemanager->EntList.elements[i];
				//Team check is invalid for BOTS (and name ofc)
				printf(
					" Entity [%i] [%s] [%s] : [%f %f %f] [%f %f %f] [%i,%i]\n",
					current->maincomp.info.team,
					current->maincomp.info.name,
					current->maincomp.info.get_operator_name(),
					current->maincomp.pawn.head.x,
					current->maincomp.pawn.head.y,
					current->maincomp.pawn.head.z,
					current->maincomp.pawn.feet.x,
					current->maincomp.pawn.feet.y,
					current->maincomp.pawn.feet.z,
					current->maincomp.weapon.currweapon.ammo,
					current->maincomp.weapon.currweapon.ammo_reserved
				);
				//Example of weapon usage:
				r6->gameprofilemanager->LocalPlayer.maincomp.weapon.currweapon.set_ammo(900, 900);
				r6->gameprofilemanager->LocalPlayer.maincomp.weapon.currweapon.set_ammo(999, 999);
				r6->gameprofilemanager->LocalPlayer.maincomp.weapon.currweapon.set_fire_type(CurrentWeapon::full_auto);
				r6->gameprofilemanager->LocalPlayer.maincomp.weapon.currweapon.info.set_recoil_addition(0, 0); //This is for vertical horiz uses another offset :P
				r6->gameprofilemanager->LocalPlayer.maincomp.weapon.currweapon.info.set_spread(0.f);
				r6->gameprofilemanager->LocalPlayer.maincomp.weapon.currweapon.info.set_recoil(0, 0);

				//Example of marker usage:
				current->maincomp.playercomp.marker.find(&current->maincomp.playercomp.ComponentList);
				current->maincomp.playercomp.marker.set_spotted_status(true);
				
			}
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
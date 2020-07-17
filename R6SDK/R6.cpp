#include "includes.h"

class R6* r6;

R6::R6() {
	this->mem = new Memory();
	this->gamemanager = new GameManager();
}

void MainLoop(){
	while (true) {
		r6->gamemanager->EntList = r6->gamemanager->get_entitylist();
		for (int i = 0; i < r6->gamemanager->EntList.size; i++) {
			Entity* current = &r6->gamemanager->EntList.elements[i];
			printf(" Entity [%i] : %f %f %f\n",i, current->maincomp.pawn.head.x, current->maincomp.pawn.head.y, current->maincomp.pawn.head.z);
			
		}
		Sleep(1000);
		system("cls");
	}
}

int main() {
	r6 = new R6();
	r6->mem->setup();
	
	//Setup Manager addresses
	r6->gamemanager->address = r6->mem->read<uintptr_t>(r6->base + offsets::Manager::GameManager);

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainLoop, 0, 0, 0);
	system("pause");
	
}
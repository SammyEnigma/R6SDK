#include "includes.h"

class R6* r6;

R6::R6() {
	this->mem = new Memory();
}

int main() {
	r6 = new R6();
	r6->mem->setup();

}
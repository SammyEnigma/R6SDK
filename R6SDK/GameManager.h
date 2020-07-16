class GameManager {
public:
	uintptr_t address;
	R6Array<Entity> EntList;

	R6Array<Entity> get_entitylist();
};
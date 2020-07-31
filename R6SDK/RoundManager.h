class RoundManager {
public:
	uintptr_t address;
	BYTE get_round();

	enum Rounds {
		swap,
		selection,
		prep,
		action,
		end,
		mainlobby
	};

};
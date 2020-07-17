class Skeleton {
public:

    enum bone_ids : std::uint32_t
    {
        foot_left = 5,
        foot_right = 4,
        knee_left = 15,
        knee_right = 14,
        groin = 16,
        neck = 11,
        head = 6,
        max_height = 7,
        shoulder_left = 13,
        shoulder_right = 12,
        hand_left = 3,
        hand_right = 2,
    };

	uintptr_t address;

	math::Vec4 get_bone(int idx);

};

class Pawn {
public:
	uintptr_t address;
	Skeleton skeleton;

    math::Vec3 head;
    math::Vec3 feet;
};

class MainComponent {
public:
	uintptr_t address;
	Pawn pawn;
};

class Entity {
public:
	uintptr_t address;
	MainComponent maincomp;
};
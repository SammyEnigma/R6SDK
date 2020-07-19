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

class Information {
public:

    uintptr_t address;
    BYTE CTU;
    BYTE OP;
    BYTE team;

	std::string get_operator_name();
    char name[0x15];
};

class WeaponInfo {
public:
    uintptr_t address;
    float spread;
    float recoilvert;
    float recoilhoriz;
    void set_spread(float spread);
    void set_recoil(float vert, float horiz);
};

class CurrentWeapon {
public:

    enum fire_type : std::uint32_t {
        full_auto = 0,
        double_bullets = 1,
        burst = 2,
        single = 3
    };

    uintptr_t address;
    WeaponInfo info;

    void set_ammo(int curr, int reserved);
    void set_fire_type(int type);

    int fire_type;
    int ammo;
    int ammo_reserved;
};

class Weapon {
public:
    uintptr_t address;
    CurrentWeapon currweapon;
};

class MainComponent {
public:
	uintptr_t address;
	Pawn pawn;
    Information info;
    Weapon weapon;
};

class Entity {
public:
	uintptr_t address;
	MainComponent maincomp;
    void get(int idx, uintptr_t entlistaddress);
};
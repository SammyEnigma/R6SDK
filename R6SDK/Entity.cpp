#include "includes.h"
extern R6* r6;


math::Vec4 transform_bone(__int64 skeleton_info, __m128* bone_offset)
{
	__m128 v5; // xmm2
	__m128 v6; // xmm3
	__m128 v7; // xmm0
	__m128 v8; // xmm4
	__m128 v9; // xmm1

	__m128 v10 = { 0.500f, 0.500f, 0.500f, 0.500f };
	__m128 v11 = { 2.000f, 2.000f, 2.000f, 0.000f };


	__m128 v12 = r6->mem->read<__m128>(skeleton_info);
	__m128 v13 = r6->mem->read<__m128>(skeleton_info + 0x10);

	math::Vec4 result;
	v5 = v13;
	v6 = _mm_mul_ps(r6->mem->read<__m128>((std::uintptr_t)bone_offset), v5);
	v6.m128_f32[0] = v6.m128_f32[0]
		+ (float)(_mm_cvtss_f32(_mm_shuffle_ps(v6, v6, 0x55)) + _mm_cvtss_f32(_mm_shuffle_ps(v6, v6, 0xAA)));
	v7 = _mm_shuffle_ps(v13, v5, 0xFF);
	v8 = _mm_sub_ps(
		_mm_mul_ps(_mm_shuffle_ps(v5, v5, 0xD2), r6->mem->read<__m128>( (std::uintptr_t)bone_offset)),
		_mm_mul_ps(_mm_shuffle_ps(r6->mem->read<__m128>( (std::uintptr_t)bone_offset),r6->mem->read<__m128>( (std::uintptr_t)bone_offset), 0xD2), v5));
	v9 = _mm_shuffle_ps(v12, v12, 0x93);
	v9.m128_f32[0] = 0.0;
	*(__m128*)& result = _mm_add_ps(
		_mm_shuffle_ps(v9, v9, 0x39),
		_mm_mul_ps(
			_mm_add_ps(
				_mm_add_ps(
					_mm_mul_ps(_mm_shuffle_ps(v8, v8, 0xD2), v7),
					_mm_mul_ps(_mm_shuffle_ps(v6, v6, 0), v5)),
				_mm_mul_ps(
					_mm_sub_ps(_mm_mul_ps(v7, v7), (__m128)v10),
					r6->mem->read<__m128>( (std::uintptr_t)bone_offset))),
			(__m128)v11));
	return result;
}

void Entity::get(int idx, uintptr_t entlistaddress) {
	this->maincomp.pawn.address = r6->mem->read<uintptr_t>(entlistaddress + idx * sizeof(void*));
	this->maincomp.address = r6->mem->read<uintptr_t>(this->maincomp.pawn.address + offsets::Entity::maincomp) ^ offsets::Entity::decryptionkey_main_component;

	//Entity PAWN 0x20
	this->maincomp.pawn.skeleton.address = this->maincomp.pawn.address + offsets::Entity::npawn::skeleton;
	math::Vec4 headpos = this->maincomp.pawn.skeleton.get_bone(Skeleton::bone_ids::head);
	this->maincomp.pawn.head = math::Vec3(headpos.x, headpos.y, headpos.z);
	math::Vec4 feetpos = this->maincomp.pawn.skeleton.get_bone(Skeleton::bone_ids::knee_left);
	this->maincomp.pawn.feet = math::Vec3(feetpos.x, feetpos.y, feetpos.z);

	//Entity Information 0xD0
	this->maincomp.info.address = r6->mem->read<uintptr_t>(this->maincomp.address + offsets::Entity::info);
	this->maincomp.info.team = (r6->mem->read<BYTE>(this->maincomp.info.address + offsets::Entity::ninfo::team) + 0x24) & 0x3F;
	this->maincomp.info.CTU = r6->mem->read<BYTE>(this->maincomp.info.address + offsets::Entity::ninfo::CTU);
	this->maincomp.info.OP = r6->mem->read<BYTE>(this->maincomp.info.address + offsets::Entity::ninfo::OP);
	uintptr_t namepointer = r6->mem->read<uintptr_t>(this->maincomp.info.address + 0x1C8);
	r6->mem->cread(namepointer, this->maincomp.info.name, 0x15);

	//Weapon 0x90
	this->maincomp.weapon.address = r6->mem->read<uintptr_t>(this->maincomp.address + offsets::Entity::weapon);
	this->maincomp.weapon.currweapon.address = r6->mem->read<uintptr_t>(this->maincomp.weapon.address + offsets::Entity::nweapon::currweapon);
	this->maincomp.weapon.currweapon.info.address = r6->mem->read<uintptr_t>(this->maincomp.weapon.currweapon.address + offsets::Entity::nweapon::weaponinfo) + offsets::Entity::nweapon::decryptionkey_weaponinfo;
	this->maincomp.weapon.currweapon.info.address += 0x18; //Because thats how the game calls it
	this->maincomp.weapon.currweapon.ammo = r6->mem->read<int>(this->maincomp.weapon.currweapon.address + offsets::Entity::nweapon::ammo);
	this->maincomp.weapon.currweapon.ammo_reserved = r6->mem->read<int>(this->maincomp.weapon.currweapon.address + offsets::Entity::nweapon::reserved);
	this->maincomp.weapon.currweapon.fire_type = r6->mem->read<int>(this->maincomp.weapon.currweapon.address + offsets::Entity::nweapon::firetype);

	//WeaponInfo Weapon->0x290
	this->maincomp.weapon.currweapon.info.spread = r6->mem->read<float>(this->maincomp.weapon.currweapon.info.address + offsets::Entity::nweapon::spread);
	this->maincomp.weapon.currweapon.info.recoilvert = r6->mem->read<float>(this->maincomp.weapon.currweapon.info.address + offsets::Entity::nweapon::recoilvert);
	this->maincomp.weapon.currweapon.info.recoilhoriz = r6->mem->read<float>(this->maincomp.weapon.currweapon.info.address + offsets::Entity::nweapon::recoilhoriz);

	//PlayerComponent
	this->maincomp.playercomp.address = r6->mem->read<uintptr_t>(this->maincomp.address + offsets::Entity::playercomp) ^ offsets::Entity::ncomp::decryptionkey_player_component;
	this->maincomp.playercomp.ComponentList.size = r6->mem->read<DWORD>(this->maincomp.playercomp.address + 0xE0) & 0x3FFFFFFF;
	this->maincomp.playercomp.ComponentList.elements = new uintptr_t[this->maincomp.playercomp.ComponentList.size];
	uintptr_t list_address = r6->mem->read<uintptr_t>(this->maincomp.playercomp.address + 0xD8);
	for (int i = 0; i < this->maincomp.playercomp.ComponentList.size; i++) 
		this->maincomp.playercomp.ComponentList.elements[i] = r6->mem->read<uintptr_t>(list_address + i * sizeof(void*));
}

void Entity::get(uintptr_t maincomponentaddress) {
	this->maincomp.address = maincomponentaddress;
	this->maincomp.pawn.address = r6->mem->read<uintptr_t>(this->maincomp.address + offsets::Entity::pawn) + offsets::Entity::decryptionkey_pawn;
	//Entity PAWN 0x20
	this->maincomp.pawn.skeleton.address = this->maincomp.pawn.address + offsets::Entity::npawn::skeleton;
	math::Vec4 headpos = this->maincomp.pawn.skeleton.get_bone(Skeleton::bone_ids::head);
	this->maincomp.pawn.head = math::Vec3(headpos.x, headpos.y, headpos.z);
	math::Vec4 feetpos = this->maincomp.pawn.skeleton.get_bone(Skeleton::bone_ids::knee_left);
	this->maincomp.pawn.feet = math::Vec3(feetpos.x, feetpos.y, feetpos.z);

	//Entity Information 0xD0
	this->maincomp.info.address = r6->mem->read<uintptr_t>(this->maincomp.address + offsets::Entity::info);
	this->maincomp.info.team = (r6->mem->read<BYTE>(this->maincomp.info.address + offsets::Entity::ninfo::team) + 0x24) & 0x3F;
	this->maincomp.info.CTU = r6->mem->read<BYTE>(this->maincomp.info.address + offsets::Entity::ninfo::CTU);
	this->maincomp.info.OP = r6->mem->read<BYTE>(this->maincomp.info.address + offsets::Entity::ninfo::OP);
	uintptr_t namepointer = r6->mem->read<uintptr_t>(this->maincomp.info.address + 0x1C8);
	r6->mem->cread(namepointer, this->maincomp.info.name, 0x15);

	//Weapon 0x90
	this->maincomp.weapon.address = r6->mem->read<uintptr_t>(this->maincomp.address + offsets::Entity::weapon);
	this->maincomp.weapon.currweapon.address = r6->mem->read<uintptr_t>(this->maincomp.weapon.address + offsets::Entity::nweapon::currweapon);
	this->maincomp.weapon.currweapon.info.address = r6->mem->read<uintptr_t>(this->maincomp.weapon.currweapon.address + offsets::Entity::nweapon::weaponinfo) + offsets::Entity::nweapon::decryptionkey_weaponinfo;
	this->maincomp.weapon.currweapon.info.address += 0x18; //Because thats how the game calls it
	this->maincomp.weapon.currweapon.ammo = r6->mem->read<int>(this->maincomp.weapon.currweapon.address + offsets::Entity::nweapon::ammo);
	this->maincomp.weapon.currweapon.ammo_reserved = r6->mem->read<int>(this->maincomp.weapon.currweapon.address + offsets::Entity::nweapon::reserved);
	this->maincomp.weapon.currweapon.fire_type = r6->mem->read<int>(this->maincomp.weapon.currweapon.address + offsets::Entity::nweapon::firetype);

	//WeaponInfo Weapon->0x290
	this->maincomp.weapon.currweapon.info.spread = r6->mem->read<float>(this->maincomp.weapon.currweapon.info.address + offsets::Entity::nweapon::spread);
	this->maincomp.weapon.currweapon.info.recoilvert = r6->mem->read<float>(this->maincomp.weapon.currweapon.info.address + offsets::Entity::nweapon::recoilvert);
	this->maincomp.weapon.currweapon.info.recoilhoriz = r6->mem->read<float>(this->maincomp.weapon.currweapon.info.address + offsets::Entity::nweapon::recoilhoriz);

	//PlayerComponent
	this->maincomp.playercomp.address = r6->mem->read<uintptr_t>(this->maincomp.address + offsets::Entity::playercomp) ^ offsets::Entity::ncomp::decryptionkey_player_component;
	this->maincomp.playercomp.ComponentList.size = r6->mem->read<DWORD>(this->maincomp.playercomp.address + 0xE0) & 0x3FFFFFFF;
	this->maincomp.playercomp.ComponentList.elements = new uintptr_t[this->maincomp.playercomp.ComponentList.size];
	uintptr_t list_address = r6->mem->read<uintptr_t>(this->maincomp.playercomp.address + 0xD8);
	for (int i = 0; i < this->maincomp.playercomp.ComponentList.size; i++)
		this->maincomp.playercomp.ComponentList.elements[i] = r6->mem->read<uintptr_t>(list_address + i * sizeof(void*));
}

math::Vec4 Skeleton::get_bone(int idx) {
	uintptr_t bone_ptr = r6->mem->read<uintptr_t>(this->address + idx * 0x10);
	DWORD bone_index = r6->mem->read<DWORD>(bone_ptr + 0xC);
	uintptr_t bone_info_ptr = r6->mem->read<uintptr_t>(bone_ptr);
	uintptr_t bone_info = r6->mem->read<uintptr_t>(bone_info_ptr + 0x270);
	uintptr_t bone_data = r6->mem->read<uintptr_t>(bone_info + 0x58);
	const auto offset = 0x20 * idx + bone_data;
	return transform_bone(bone_info, (__m128*)offset);
}

const char* OperatorName[26][5] = {
{"BOT","SMOKE","MUTE","SLEDGE","THATCHER"},
{"RECRUIT","CASTLE","ASH","PULSE","THERMITE"},
{0,"DOC","ROOK","TWITCH","MONTAGNE"},
{0,"GLAZ","FUZE","KAPKAN","TACHANKA"},
{0,"BLITZ","IQ","JAGER","BANDIT"},
{0,"BUCK","FROST"},
{0,"BLACKBEARD","VALKYRIE"},
{0,"CAPITAO","CAVEIRA"},
{0,"HIBANA","ECHO"},
{0,"JACKAL","MIRA"},
{0,"YING","LESION"},
{0,"ELA","ZOFIA"},
{0,"DOKKAEBI","VIGIL"},
{0,0,"LION","FINKA"},
{0,"MAESTRO","ALIBI"},
{0,"MAVERICK","CLASH"},
{0,"NOMAD","KAID"},
{0,"MOZZIE","GRIDLOCK"},
{0,"NOKK"},
{0,"WARDEN"},
{0,"GOYO"},
{0,"AMARU"},
{0,"KALI","WAMAI", "ACE"},
{0,"ORYX"},
{0,"IANA"},
{0,"MELUSI"}
};

std::string Information::get_operator_name() {
	return OperatorName[this->CTU][this->OP];
}

void CurrentWeapon::set_ammo(int curr, int reserved) {
	r6->mem->write<int>(this->address + offsets::Entity::nweapon::ammo, curr);
	r6->mem->write<int>(this->address + offsets::Entity::nweapon::reserved, reserved);
}
void CurrentWeapon::set_fire_type(int type) {
	r6->mem->write<int>(this->address + offsets::Entity::nweapon::firetype, type);
}

void WeaponInfo::set_spread(float spread) {
	r6->mem->write<float>(this->address + offsets::Entity::nweapon::spread, spread);
}

void WeaponInfo::set_recoil(float vert, float horiz) {
	r6->mem->write<byte>(this->address + offsets::Entity::nweapon::recoil_overwrite, false);
	r6->mem->write<float>(this->address + offsets::Entity::nweapon::recoilvert, vert);
	r6->mem->write<float>(this->address + offsets::Entity::nweapon::recoilhoriz, horiz);
}

void MarkerComponent::find(R6Array<uintptr_t>* ComponentList) {
	for (int i = 0; i < ComponentList->size; i++) {
		uintptr_t curr_vtable_rel = r6->mem->read<uintptr_t>(ComponentList->elements[i]) - r6->base;
		if (curr_vtable_rel == offsets::Entity::ncomp::vt_marker) {
			this->address = ComponentList->elements[i];
		}
	}
}
void MarkerComponent::set_spotted_status(bool bSpotted) {
	r6->mem->write<BYTE>(this->address + offsets::Entity::ncomp::bSpotted, bSpotted);
}

void WeaponInfo::set_recoil_addition(float pull, float kick) {
	uintptr_t weapon_info = r6->mem->read<uintptr_t>(this->address + offsets::Entity::nweapon::weapon_info);
	uintptr_t arry_to_single = r6->mem->read<uintptr_t>(weapon_info + offsets::Entity::nweapon::arry_to_single);
	arry_to_single = r6->mem->read<uintptr_t>(arry_to_single);
	uintptr_t curr_weapon_preset = r6->mem->read<uintptr_t>(arry_to_single + offsets::Entity::nweapon::current_weapon_preset);
	curr_weapon_preset = r6->mem->read<uintptr_t>(curr_weapon_preset);
	r6->mem->write<float>(curr_weapon_preset + offsets::Entity::nweapon::pull, pull);
	r6->mem->write<float>(curr_weapon_preset + offsets::Entity::nweapon::kick, kick);

	/*VALUE TABLE
	uintptr_t test = r6->mem->read<uintptr_t>(curr_weapon_preset + 0x18);
	for (DWORD off = 0x0; off < 0xCD4; off += 0x4) {
		r6->mem->write<float>(test + off, 0.f);
	}
	*/
}

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

math::Vec4 Skeleton::get_bone(int idx) {
	uintptr_t bone_ptr = r6->mem->read<uintptr_t>(this->address + idx * 0x10);
	DWORD bone_index = r6->mem->read<DWORD>(bone_ptr + 0xC);
	uintptr_t bone_info_ptr = r6->mem->read<uintptr_t>(bone_ptr);
	uintptr_t bone_info = r6->mem->read<uintptr_t>(bone_info_ptr + 0x270);
	uintptr_t bone_data = r6->mem->read<uintptr_t>(bone_info + 0x58);
	const auto offset = 0x20 * bone_index + bone_data;
	return transform_bone(bone_info, (__m128*)offset);
}
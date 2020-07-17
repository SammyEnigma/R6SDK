#include "includes.h"


namespace math {

	Vec3::Vec3() {
		this->x, this->y, this->z = 0.f;
	}

	Vec3::Vec3(float _x, float _y, float _z) {
		this->x = _x; this->y = _y; this->z = _z;
	}


}
#pragma once

#include "ext/vec/vec3_float.h"

namespace Drop
{
    struct Vec3
    {
        Vec3() : v(_vec3_create(0.0f, 0.0f, 0.0f)) { }
        Vec3(float x, float y, float z) : v(_vec3_create(x, y, z)) { }

		float X() const { return _vec3_x(&v); }
        float Y() const { return _vec3_y(&v); }
		float Z() const { return _vec3_z(&v); }

		void SetX(float x) { v = _vec3_set_x(&v, x); }
		void SetY(float y) { v = _vec3_set_y(&v, y); }
		void SetZ(float z) { v = _vec3_set_z(&v, z); }

		Vec3 operator+(const Vec3& other) const {return Vec3(_vec3_add(&v, &other.v)); }
		Vec3 operator-(const Vec3& other) const {return Vec3(_vec3_sub(&v, &other.v)); }
		Vec3 operator*(float s) const {return Vec3(_vec3_mul(&v, s)); }
		Vec3 operator/(float s) const {return Vec3(_vec3_div(&v, s)); }
        bool operator==(const Vec3& other) const { return _vec3_eq(&v, &other.v); }
        bool operator!=(const Vec3& other) const { return !(*this == other); }

		float Length() const { return _vec3_length(&v); }

		static float Dot(const Vec3& v1, const Vec3& v2) { return _vec3_dot(&v1.v, &v2.v); }


    private:
        explicit Vec3(const _vec3_float& v) : v(v) { }
        _vec3_float v;
    };
} // namespace Drop
#pragma once

#include "ext/vec/vec2_float.h"

namespace Drop
{
    struct Vec2
    {
        Vec2() : v(_vec2_create(0.0f, 0.0f)) { }
        Vec2(float x, float y) : v(_vec2_create(x, y)) { }

		float X() const { return _vec2_x(&v); }
		float Y() const { return _vec2_y(&v); }

		void SetX(float x) { v = _vec2_set_x(&v, x); }
		void SetY(float y) { v = _vec2_set_y(&v, y); }

		Vec2 operator+(const Vec2& other) const { return Vec2(_vec2_add(&v, &other.v)); }
		Vec2 operator-(const Vec2& other) const { return Vec2(_vec2_sub(&v, &other.v)); }
        Vec2 operator*(float s) const { return Vec2(_vec2_mul(&v, s)); }
        Vec2 operator/(float s) const { return Vec2(_vec2_div(&v, s)); }
		bool operator==(const Vec2& other) const { return _vec2_eq(&v, &other.v); }
		bool operator!=(const Vec2& other) const { return !(*this == other); }


		float Length() const { return _vec2_length(&v); }

		static float Dot(const Vec2& v1, const Vec2& v2) { return _vec2_dot(&v1.v, &v2.v); }


    private:
        explicit Vec2(const _vec2_float& v) : v(v) { }
        _vec2_float v;
    };
} // namespace Drop
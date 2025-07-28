#pragma once

#ifndef USE_SIMD
#define USE_SIMD
#endif // !USE_SIMD

#include "DM_Vec3.h"

namespace DropMath
{
    struct alignas(16) Vec4
    {
        union
        {
            float4 v;
            struct
            {
                float x, y, z, w;
            };
            struct
            {
                float r, g, b, a;
            };
        };

		Vec4() : v(_mm_setzero_ps()) { }
        Vec4(float x, float y, float z, float w) : v(_mm_set_ps(w, z, y, x)) { }
        Vec4(const Vec3& v, float w) : v(_mm_set_ps(v.x, v.y, v.z, w)) { }
        Vec4(const Vec2& v, float z, float w) : v(_mm_set_ps(v.x, v.y, z, w)) { }

        Vec4 operator+(const Vec4& v) const { return Vec4(_mm_add_ps(this->v, v.v)); }
        Vec4 operator-(const Vec4& v) const { return Vec4(_mm_sub_ps(this->v, v.v)); }
        Vec4 operator*(float s) const { return Vec4(_mm_mul_ps(this->v, _mm_set1_ps(s))); }
        Vec4 operator/(float s) const { return Vec4(_mm_div_ps(this->v, _mm_set1_ps(s))); }
        bool operator==(const Vec4& v) const
        {
			float4 delta = _mm_sub_ps(v.v, this->v);
            float4 abs   = _mm_andnot_ps(_mm_set1_ps(-0.0f), delta);
			float4 eps   = _mm_set1_ps(DM_EPSILON);
			float4 cmp   = _mm_cmplt_ps(abs, eps);
            int mask     = _mm_movemask_ps(cmp);
			return mask == 0xF;
		}
		bool operator!=(const Vec4& v) const { return !(*this == v); }

		float Length() const
		{
			float4 dot = _mm_dp_ps(v, v, 0b11110001);
			float4 sqrt = _mm_sqrt_ps(dot);
			return _mm_cvtss_f32(sqrt);
		}
		float LengthSquared() const
		{
			float4 dot = _mm_dp_ps(v, v, 0b11110001);
			return _mm_cvtss_f32(dot);
		}

		// Normalize the length of the vector so that it is 1.
		void Normalize()
		{
			float len = Length();
			if (len > DM_EPSILON)
			{
				v = _mm_div_ps(v, _mm_set1_ps(len));
			}
		}

		// Dot product of a and b.
		static float Dot(const Vec4& a, const Vec4& b) 
		{ 
			float4 dot = _mm_dp_ps(a.v, b.v, 0b11110001);
			return _mm_cvtss_f32(dot);
		}

        // Lerp between a and b with t as the interpolation. 0 means a, 1 means b, and 0.5 means the middle.
		static Vec4 Lerp(const Vec4& a, const Vec4& b, float t) { return a * (1 - t) + b * t; }


        // Returns the zero vector (0, 0, 0, 0).
        static const Vec4 Zero() { return Vec4(_mm_setzero_ps()); }
        // Returns the one vector (1, 1, 1, 1).
        static const Vec4 One() { return Vec4(_mm_set1_ps(1.0f)); }

        explicit Vec4(const float4& v) : v(v) { }
    };

}
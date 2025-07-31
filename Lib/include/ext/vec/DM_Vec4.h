#pragma once

#include "DM_Vec3.h"

namespace DropMath
{
    struct alignas(16) Vec4
    {
        union
        {
            float4 v; // Don't ever use this directly unless you know about SSE alignment.
            struct
            {
                float x, y, z, w;
            };
            struct
            {
                float r, g, b, a;
            };
            float array[4]; // Don't use this directly. You need to use [] operator or x, y, z, w or r, g, b, a.
        };

        Vec4() : v(_mm_setzero_ps()) { }
        Vec4(float x, float y, float z, float w) : v(_mm_set_ps(w, z, y, x)) { }
        Vec4(const Vec3& v, float w) : v(_mm_set_ps(w, v.z, v.y, v.x)) { }
        Vec4(const Vec2& v, float z, float w) : v(_mm_set_ps(w, z, v.y, v.x)) { }

        float&       operator[](int i);
        const float& operator[](int i) const;
        Vec4         operator+(const Vec4& v) const { return Vec4(_mm_add_ps(this->v, v.v)); }
        Vec4         operator-(const Vec4& v) const { return Vec4(_mm_sub_ps(this->v, v.v)); }
        Vec4         operator*(float s) const { return Vec4(_mm_mul_ps(this->v, _mm_set1_ps(s))); }
        Vec4         operator/(float s) const { return Vec4(_mm_div_ps(this->v, _mm_set1_ps(s))); }
        bool         operator==(const Vec4& v) const;
        bool         operator!=(const Vec4& v) const;

        // Return vector data so you can use it directly as a float array.
        float* Data() { return &x; }
        // Return vector data so you can use it directly as a float array.
        const float* Data() const { return &x; }

        float Length() const;

        float LengthSquared() const;

        // Normalize the length of the vector so that it is 1.
        void Normalize();

        // Store the vector into array of floats.
        void Store(float* dst) const { _mm_storeu_ps(dst, v); }

        // Dot product of a and b.
        static float Dot(const Vec4& a, const Vec4& b);

        // Lerp between a and b with t as the interpolation. 0 means a, 1 means b, and 0.5 means the middle.
        static Vec4 Lerp(const Vec4& a, const Vec4& b, float t);

        // Returns the zero vector (0, 0, 0, 0).
        static Vec4 Zero() { return Vec4(_mm_setzero_ps()); }
        // Returns the one vector (1, 1, 1, 1).
        static Vec4 One() { return Vec4(_mm_set1_ps(1.0f)); }

        DM_CONSTEXPR explicit Vec4(const float4& v) : v(v) { }
    };

}

#include "DM_Vec4.inl"
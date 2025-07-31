#pragma once

#include "../utils/DM_Utils.h"

namespace DropMath
{
    struct Vec2
    {
        union
        {
            struct
            {
                float x, y;
            };
            float array[2]; // Don't use this directly. You need to use [] operator or x, y.
        };

        DM_CONSTEXPR Vec2() : x(0), y(0) { }
        DM_CONSTEXPR Vec2(float x, float y) : x(x), y(y) { }

        float&       operator[](int i);
        const float& operator[](int i) const;

        DM_CONSTEXPR Vec2 operator+(const Vec2& v) const { return Vec2(x + v.x, y + v.y); }
        DM_CONSTEXPR Vec2 operator-(const Vec2& v) const { return Vec2(x - v.x, y - v.y); }
        DM_CONSTEXPR Vec2 operator*(float s) const { return Vec2(x * s, y * s); }
        DM_CONSTEXPR Vec2 operator/(float s) const { return Vec2(x / s, y / s); }
        bool              operator==(const Vec2& v) const;
        bool              operator!=(const Vec2& v) const;

        // Return vector data so you can use it directly as a float array.
        float* Data() { return &x; }
        // Return vector data so you can use it directly as a float array.
        const float* Data() const { return &x; }

        DM_CONSTEXPR float LengthSquared() const { return x * x + y * y; }

        float Length() const;

        // Normalize the length of the vector so that it is 1.
        void Normalize();

		// Return a new normalized vector.
        Vec2 Normalized() const;

        // Store the vector into array of floats.
        void Store(float* dst) const
        {
            dst[0] = x;
            dst[1] = y;
        }

        // Dot product of a and b.
        DM_CONSTEXPR static float Dot(const Vec2& a, const Vec2& b) { return a.x * b.x + a.y * b.y; }

        // Lerp between a and b with t as the interpolation. 0 means a, 1 means b, and 0.5 means the middle.
        DM_CONSTEXPR static Vec2 Lerp(const Vec2& a, const Vec2& b, float t);

        // Returns the zero vector (0, 0).
        DM_CONSTEXPR static Vec2 Zero() { return Vec2(0, 0); }
        // Returns the one vector (1, 1).
        DM_CONSTEXPR static Vec2 One() { return Vec2(1, 1); }
        // Returns the up vector (0, 1).
        DM_CONSTEXPR static Vec2 Up() { return Vec2(0, 1); }
        // Returns the down vector (0, -1).
        DM_CONSTEXPR static Vec2 Down() { return Vec2(0, -1); }
        // Returns the left vector (-1, 0).
        DM_CONSTEXPR static Vec2 Left() { return Vec2(-1, 0); }
        // Returns the right vector (1, 0).
        DM_CONSTEXPR static Vec2 Right() { return Vec2(1, 0); }
    };

} // namespace Drop

#include "DM_Vec2.inl"
#pragma once

#include "DM_Vec2.h"

namespace DropMath
{
    struct Vec3
    {
        union
        {
            struct
            {
                float x, y, z;
            };
            float array[3]; // Don't use this directly. You need to use [] operator or x, y, z.
        };

        Vec3() : x(0), y(0), z(0) { }
        Vec3(float x, float y, float z) : x(x), y(y), z(z) { }
        Vec3(const Vec2& v, float z) : x(v.x), y(v.y), z(z) { }

        float&       operator[](int i);
        const float& operator[](int i) const;
        Vec3         operator+(const Vec3& v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
        Vec3         operator+(const Vec2& v) const { return Vec3(x + v.x, y + v.y, z); }
        Vec3         operator-(const Vec3& v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
        Vec3         operator-(const Vec2& v) const { return Vec3(x - v.x, y - v.y, z); }
        Vec3         operator*(float s) const { return Vec3(x * s, y * s, z * s); }
        Vec3         operator/(float s) const { return Vec3(x / s, y / s, z / s); }
        bool         operator==(const Vec3& v) const;
        bool         operator!=(const Vec3& v) const;

        // Return matrix data so you can use it directly as a float array.
        float* Data() { return &x; }
        // Return matrix data so you can use it directly as a float array.
        const float* Data() const { return &x; }

        float LengthSquared() const { return x * x + y * y + z * z; }

        float Length() const;

        // Normalize the length of the vector so that it is 1.
        void Normalize();

        // Store the vector into array of floats.
        void Store(float* dst) const
        {
            dst[0] = x;
            dst[1] = y;
            dst[2] = z;
        }

        // Dot product of a and b.
        static float Dot(const Vec3& a, const Vec3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

        static Vec3 Cross(const Vec3& a, const Vec3& b)
        {
            return Vec3(
                a.y * b.z - a.z * b.y,
                a.z * b.x - a.x * b.z,
                a.x * b.y - a.y * b.x);
        }

        // Lerp between a and b with t as the interpolation. 0 means a, 1 means b, and 0.5 means the middle.
        static Vec3 Lerp(const Vec3& a, const Vec3& b, float t);

        // Returns the zero vector (0, 0, 0).
        static Vec3 Zero() { return Vec3(0, 0, 0); }
        // Returns the one vector (1, 1, 1).
        static Vec3 One() { return Vec3(1, 1, 1); }
        // Returns the up vector (0, 1, 0).
        static Vec3 Up() { return Vec3(0, 1, 0); }
        // Returns the down vector (0, -1, 0).
        static Vec3 Down() { return Vec3(0, -1, 0); }
        // Returns the left vector (-1, 0, 0).
        static Vec3 Left() { return Vec3(-1, 0, 0); }
        // Returns the right vector (1, 0, 0).
        static Vec3 Right() { return Vec3(1, 0, 0); }
        // Returns the forward vector (0, 0, 1).
        static Vec3 Forward() { return Vec3(0, 0, 1); }
        // Returns the backward vector (0, 0, -1).
        static Vec3 Back() { return Vec3(0, 0, -1); }
    };

} // namespace DropMath

#include "DM_Vec3.inl"
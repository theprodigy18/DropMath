#pragma once

#include "../DM_Common.h"
#include "../DM_Constant.h"

namespace DropMath
{
    struct Vec2
    {
        float x;
        float y;

        Vec2() : x(0), y(0) { }
        Vec2(float x, float y) : x(x), y(y) { }

        Vec2 operator+(const Vec2& v) const { return Vec2(x + v.x, y + v.y); }
        Vec2 operator-(const Vec2& v) const { return Vec2(x - v.x, y - v.y); }
        Vec2 operator*(float s) const { return Vec2(x * s, y * s); }
        Vec2 operator/(float s) const { return Vec2(x / s, y / s); }
        bool operator==(const Vec2& v) const { return (fabs(x - v.x) < DM_EPSILON) && (fabs(y - v.y) < DM_EPSILON); }
        bool operator!=(const Vec2& v) const { return !(*this == v); }

        float Length() const { return sqrtf(LengthSquared()); }

        float LengthSquared() const { return x * x + y * y; }

        // Normalize the length of the vector so that it is 1.
        void Normalize()
        {
            float len = Length();
            if (len > DM_EPSILON)
            {
                x /= len;
                y /= len;
            }
        }

        // Dot product of a and b.
        static float Dot(const Vec2& a, const Vec2& b) { return a.x * b.x + a.y * b.y; }

        // Lerp between a and b with t as the interpolation. 0 means a, 1 means b, and 0.5 means the middle.
        static Vec2 Lerp(const Vec2& a, const Vec2& b, float t) { return a * (1 - t) + b * t; }

        // Returns the zero vector (0, 0).
        static Vec2 Zero() { return Vec2(0, 0); }
        // Returns the one vector (1, 1).
        static Vec2 One() { return Vec2(1, 1); }
        // Returns the up vector (0, 1).
        static Vec2 Up() { return Vec2(0, 1); }
        // Returns the down vector (0, -1).
        static Vec2 Down() { return Vec2(0, -1); }
        // Returns the left vector (-1, 0).
        static Vec2 Left() { return Vec2(-1, 0); }
        // Returns the right vector (1, 0).
        static Vec2 Right() { return Vec2(1, 0); }
    };

} // namespace Drop
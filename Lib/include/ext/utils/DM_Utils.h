#pragma once

#include "../DM_Common.h"
#include "../DM_Constant.h"

namespace DropMath
{
    // Lerp between a and b with t as the interpolation. 0 means a, 1 means b, and 0.5 means the middle.
    template <typename T>
    inline T Lerp(const T& a, const T& b, float t);

    // Return the absolute value of x(float).
    inline float AbsF(float x);
    // Return the absolute value of x(double).
    inline double AbsD(double x);
    // Return the absolute value of x(int).
    inline int AbsI(int x);

    // Return the lowest value.
    template <typename T>
    inline T Min(const T& a, const T& b);

    // Return the highest value.
    template <typename T>
    inline T Max(const T& a, const T& b);

    // Return the value clamped to the range [min, max].
    template <typename T>
    inline T Clamp(const T& value, const T& min, const T& max);

    // SqrtF will calculate the square root of x(float).
    inline float SqrtF(float x);
    // Sqrt will calculate the square root of x(double).
    inline double Sqrt(double x);

    // IsZero will do AbsF to x(float) and then check if it is less than DM_EPSILON.
    inline bool IsZero(float x);
    // IsZero will do Abs to x(double) and then check if it is less than DM_EPSILON.
    inline bool IsZero(double x);
}

#include "DM_Utils.inl"
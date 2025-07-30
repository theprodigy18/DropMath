#pragma once

#include "../DM_Common.h"
#include "../DM_Constant.h"

namespace DropMath
{
    // Return the greatest integer that is less than or equal to x(float).
    DM_CONSTEXPR_14 inline int Floor(float x);
    // Return the greatest integer that is less than or equal to x(double).
    DM_CONSTEXPR_14 inline int Floor(double x);

    // Return the smallest integer that is greater than or equal to x(float).
    DM_CONSTEXPR_14 inline int Ceil(float x);
    // Return the smallest integer that is greater than or equal to x(double).
    DM_CONSTEXPR_14 inline int Ceil(double x);

    // Return the closest integer to x(float).
    DM_CONSTEXPR_14 inline int Round(float x);
    // Return the closest integer to x(double).
    DM_CONSTEXPR_14 inline int Round(double x);

    // Return the rad(float) in the range [-pi, pi].
    DM_CONSTEXPR_14 inline float WrapPi(float rad);
    // Return the rad(double) in the range [-pi, pi].
    DM_CONSTEXPR_14 inline double WrapPi(double rad);

	// Return the degree(float) as radians.
	DM_CONSTEXPR_14 inline float ToRadians(float deg);
	// Return the degree(double) as radians.
    DM_CONSTEXPR_14 inline double ToRadians(double deg);

	// Return the rad(float) as degrees.
	DM_CONSTEXPR_14 inline float ToDegrees(float rad);
	// Return the rad(double) as degrees.
    DM_CONSTEXPR_14 inline double ToDegrees(double rad);

	// Return sin of rad(float).
    DM_CONSTEXPR_14 inline float  Sin(float rad);
	// Return sin of rad(double).
    DM_CONSTEXPR_14 inline double Sin(double rad);

	// Return cos of rad(float).
    DM_CONSTEXPR_14 inline float  Cos(float rad);
	// Return cos of rad(double).
    DM_CONSTEXPR_14 inline double Cos(double rad);

	// Return tan of rad(float).
    inline float  Tan(float rad);
	// Return tan of rad(double).
    inline double Tan(double rad);

	// Return 1 if x is greater than 0, 0 if x is 0, and -1 if x is less than 0.
	DM_CONSTEXPR_14 inline float Sign(float x);
	// Return 1 if x is greater than 0, 0 if x is 0, and -1 if x is less than 0.
	DM_CONSTEXPR_14 inline double Sign(double x);
	// Return 1 if x is greater than 0, 0 if x is 0, and -1 if x is less than 0.
	DM_CONSTEXPR_14 inline int Sign(int x);


    // Lerp between a and b with t as the interpolation. 0 means a, 1 means b, and 0.5 means the middle.
    template <typename T>
    inline T Lerp(const T& a, const T& b, float t);

    // Return the absolute value of x(float).
    inline float Abs(float x);
    // Return the absolute value of x(double).
    inline double Abs(double x);
    // Return the absolute value of x(int).
    DM_CONSTEXPR_14 inline int Abs(int x);

    // Return the lowest value. This function can be used for all data as long as they support < operator.
    template <typename T>
    inline T Min(const T& a, const T& b);

    // Return the highest value. This function can be used for all data as long as they support > operator.
    template <typename T>
    inline T Max(const T& a, const T& b);

    // Return the value clamped to the range [min, max]. This function can be used for all data as long as they support < and > operator.
    template <typename T>
    inline T Clamp(const T& value, const T& min, const T& max);

    // SqrtF will calculate the square root of x(float).
    inline float Sqrt(float x);
    // Sqrt will calculate the square root of x(double).
    inline double Sqrt(double x);

    // IsZero will do AbsF to x(float) and then check if it is less than DM_EPSILON.
    inline bool IsZero(float x);
    // IsZero will do Abs to x(double) and then check if it is less than DM_EPSILON.
    inline bool IsZero(double x);

    // Return the determinant of a matrix. This is valid as long as your data is 2x2 array and support [][] access.
    template <typename Mat>
    inline float Determinant2x2(const Mat& m);

    // Return the determinant of a matrix. This is valid as long as your data is 3x3 array and support [][] access.
    template <typename Mat>
    inline float Determinant3x3(const Mat& m);

    // Return the determinant of a matrix. This is valid as long as your data is 4x4 array and support [][] access.
    template <typename Mat>
    inline float Determinant4x4(const Mat& m);

    // Inverse a matrix. This is valid as long as your data is 2x2 array and support [][] access.
    // Return true if it is invertable(determinant != 0).
    template <typename Mat>
    inline bool TryInverse2x2(const Mat& m, Mat& out);

    // Inverse a matrix. This is valid as long as your data is 3x3 array and support [][] access.
    // Return true if it is invertable(determinant != 0).
    template <typename Mat>
    inline bool TryInverse3x3(const Mat& m, Mat& out);

    // Inverse a matrix. This is valid as long as your data is 4x4 array and support [][] access.
    // Return true if it is invertable(determinant != 0).
    template <typename Mat>
    inline bool TryInverse4x4(const Mat& m, Mat& out);
}

#include "DM_Utils.inl"
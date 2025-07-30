#pragma once

#include "../DM_Enum.h"
#include "../vec/DM_Vec2.h"

namespace DropMath
{
    struct Mat2x2
    {
        Vec2 rows[2];

        Mat2x2() : rows {Vec2(), Vec2()} { }
        Mat2x2(Vec2 r0, Vec2 r1) : rows {r0, r1} { }

        Vec2&       operator[](int i);
        const Vec2& operator[](int i) const;
        // Matrix x Vector.
        Vec2 operator*(const Vec2& v) const;
        // Matrix x Matrix.
        Mat2x2 operator*(const Mat2x2& m) const;

        // Return matrix data so you can use it directly as a float array.
        float* Data() { return reinterpret_cast<float*>(&rows[0]); }
        // Return matrix data so you can use it directly as a float array.
        const float* Data() const { return reinterpret_cast<const float*>(&rows[0]); }

		// Return the determinant of the matrix.
        float Determinant() const;

        // Return Transposed matrix.
        Mat2x2 Transposed() const;

        // Store matrix with exact alignment with original.
        void StoreRowMajor(float* dst) const;

        // Store matrix with transposed alignment.
        void StoreColMajor(float* dst) const;

        // Store the matrix with the given alignment.
        void Store(float* dst, MATRIX_ALLIGNMENT alignment) const;

		// Force inverse. This can cause an error if the determinant is 0.
        // If you don't really sure about your data, use the TryInverse that was static version with extra check.
        Mat2x2 Inverse() const;

        // Safe method for inverse. Return false if determinant is 0 and can't be inversed. Otherwise return true.
        static bool TryInverse(const Mat2x2& m, Mat2x2& out);

        // Static version to transpose matrix.
        static Mat2x2 Transpose(const Mat2x2& m);

        // Create Identity matrix.
        static Mat2x2 Identity() { return Mat2x2(Vec2(1, 0), Vec2(0, 1)); }
    };
} // namespace DropMath

#include "DM_Mat2x2.inl"
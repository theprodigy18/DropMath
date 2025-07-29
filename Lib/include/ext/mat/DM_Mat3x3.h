#pragma once

#include "../DM_Enum.h"
#include "../vec/DM_Vec3.h"

namespace DropMath
{
    struct Mat3x3
    {
        Vec3 rows[3];

        Mat3x3() : rows {Vec3(), Vec3(), Vec3()} { }
        Mat3x3(Vec3 r0, Vec3 r1, Vec3 r2) : rows {r0, r1, r2} { }

        Vec3&       operator[](int i);
        const Vec3& operator[](int i) const;
        // Matrix x Vector.
        Vec3 operator*(const Vec3& v) const;
        // Matrix x Matrix.
        Mat3x3 operator*(const Mat3x3& m) const;

        // Return matrix data so you can use it directly as a float array.
        float* Data() { return reinterpret_cast<float*>(&rows[0]); }
        // Return matrix data so you can use it directly as a float array.
        const float* Data() const { return reinterpret_cast<const float*>(&rows[0]); }

        // Return Transposed matrix.
        Mat3x3 Transposed() const;

        // Store matrix with exact alignment with original.
        void StoreRowMajor(float* dst) const;

        // Store matrix with transposed alignment.
        void StoreColMajor(float* dst) const;

        // Store the matrix with the given alignment.
        void Store(float* dst, MATRIX_ALLIGNMENT alignment) const;

        // Static version to transpose matrix.
        static Mat3x3 Transpose(const Mat3x3& m);

        // Create Identity matrix.
        static Mat3x3 Identity();
    };
} // namespace DropMath

#include "DM_Mat3x3.inl"
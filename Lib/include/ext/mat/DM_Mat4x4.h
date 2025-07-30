#pragma once

#include "../DM_Enum.h"
#include "../vec/DM_Vec4.h"

namespace DropMath
{
    struct alignas(16) Mat4x4
    {
        Vec4 rows[4];

        Mat4x4() : rows {Vec4(), Vec4(), Vec4(), Vec4()} { };
        Mat4x4(Vec4 r0, Vec4 r1, Vec4 r2, Vec4 r3) : rows {r0, r1, r2, r3} { }

        Vec4&       operator[](int i);
        const Vec4& operator[](int i) const;
        // Matrix × Vector.
        Vec4 operator*(const Vec4& v) const;
        // Matrix × Matrix.
        Mat4x4 operator*(const Mat4x4& m) const;

        // Return matrix data so you can use it directly as a float array.
        float* Data() { return reinterpret_cast<float*>(&rows[0]); }
        // Return matrix data so you can use it directly as a float array.
        const float* Data() const { return reinterpret_cast<const float*>(&rows[0]); }

		// Return the determinant of the matrix.
        float Determinant() const;

        // Return Transposed matrix.
        Mat4x4 Transposed() const;

        // Store matrix with exact alignment with original.
        void StoreRowMajor(float* dst) const;

        // Store matrix with transposed alignment.
        void StoreColMajor(float* dst) const;

        // Store the matrix with the given alignment.
        void Store(float* dst, MATRIX_ALLIGNMENT alignment) const;

		// Force inverse. This can cause an error if the determinant is 0. 
		// If you don't really sure about your data, use the TryInverse that was static version with extra check.
		Mat4x4 Inverse() const;

		// Safe method for inverse. Return false if determinant is 0 and can't be inversed. Otherwise return true.
		static bool TryInverse(const Mat4x4& m, Mat4x4& out);

        // Static version to transpose matrix.
        static Mat4x4 Transpose(const Mat4x4& m);

        // Create Identity matrix.
        static Mat4x4 Identity();
    };

} // namespace DropMath

#include "DM_Mat4x4.inl"
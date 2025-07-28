#pragma once

#include "../DM_Enum.h"
#include "../vec/DM_Vec4.h"

namespace DropMath
{
    struct alignas(16) Mat4x4
    {
        Vec4 rows[4];

        Mat4x4() : rows {Vec4::Zero(), Vec4::Zero(), Vec4::Zero(), Vec4::Zero()} { };
        Mat4x4(Vec4 r0, Vec4 r1, Vec4 r2, Vec4 r3) : rows {r0, r1, r2, r3} { }

        Vec4&       operator[](int i) { return rows[i]; }
        const Vec4& operator[](int i) const { return rows[i]; }

        // Matrix × Vector.
        Vec4 operator*(const Vec4& v) const
        {
            return Vec4(
                _mm_cvtss_f32(_mm_dp_ps(rows[0].v, v.v, 0b11110001)),
                _mm_cvtss_f32(_mm_dp_ps(rows[1].v, v.v, 0b11110001)),
                _mm_cvtss_f32(_mm_dp_ps(rows[2].v, v.v, 0b11110001)),
                _mm_cvtss_f32(_mm_dp_ps(rows[3].v, v.v, 0b11110001)));
        }

        // Matrix × Matrix.
        Mat4x4 operator*(const Mat4x4& m) const
        {
            Mat4x4 result;
            Mat4x4 t = m.Transposed(); // Column access becomes row access.

            for (int i = 0; i < 4; ++i)
            {
                result[i].v = _mm_set_ps(
                    _mm_cvtss_f32(_mm_dp_ps(rows[i].v, t[3].v, 0b11110001)),
                    _mm_cvtss_f32(_mm_dp_ps(rows[i].v, t[2].v, 0b11110001)),
                    _mm_cvtss_f32(_mm_dp_ps(rows[i].v, t[1].v, 0b11110001)),
                    _mm_cvtss_f32(_mm_dp_ps(rows[i].v, t[0].v, 0b11110001)));
            }
            return result;
        }

        // Return Transposed matrix.
        Mat4x4 Transposed() const
        {
            // Transpose 4x4 matrix using SSE.
            __m128 row0 = rows[0].v;
            __m128 row1 = rows[1].v;
            __m128 row2 = rows[2].v;
            __m128 row3 = rows[3].v;

            __m128 t0 = _mm_unpacklo_ps(row0, row1);
            __m128 t1 = _mm_unpackhi_ps(row0, row1);
            __m128 t2 = _mm_unpacklo_ps(row2, row3);
            __m128 t3 = _mm_unpackhi_ps(row2, row3);

            return Mat4x4(
                Vec4(_mm_movelh_ps(t0, t2)),
                Vec4(_mm_movehl_ps(t2, t0)),
                Vec4(_mm_movelh_ps(t1, t3)),
                Vec4(_mm_movehl_ps(t3, t1)));
        }

        // Create Identity matrix.
        static Mat4x4 Identity()
        {
            return Mat4x4(
                Vec4(1, 0, 0, 0),
                Vec4(0, 1, 0, 0),
                Vec4(0, 0, 1, 0),
                Vec4(0, 0, 0, 1));
        }

        // Store matrix with exact alignment with original.
        void StoreRowMajor(float* dst) const
        {
            _mm_storeu_ps(dst + 0, rows[0].v);
            _mm_storeu_ps(dst + 4, rows[1].v);
            _mm_storeu_ps(dst + 8, rows[2].v);
            _mm_storeu_ps(dst + 12, rows[3].v);
        }

        // Store matrix with transposed alignment.
        void StoreColMajor(float* dst) const
        {
            dst[0]  = rows[0].x;
            dst[1]  = rows[1].x;
            dst[2]  = rows[2].x;
            dst[3]  = rows[3].x;
            dst[4]  = rows[0].y;
            dst[5]  = rows[1].y;
            dst[6]  = rows[2].y;
            dst[7]  = rows[3].y;
            dst[8]  = rows[0].z;
            dst[9]  = rows[1].z;
            dst[10] = rows[2].z;
            dst[11] = rows[3].z;
            dst[12] = rows[0].w;
            dst[13] = rows[1].w;
            dst[14] = rows[2].w;
            dst[15] = rows[3].w;
        }

        void Store(float* dst, MATRIX_ALLIGNMENT alignment) const
        {
            switch (alignment)
            {
            case MATRIX_ALLIGNMENT_ROW_MAJOR:
                return StoreRowMajor(dst);
                break;
            case MATRIX_ALLIGNMENT_COLUMN_MAJOR:
                return StoreColMajor(dst);
                break;
            default:
                assert(false, "Unknown matrix allignment.");
                break;
            }
        }
    };

} // namespace DropMath
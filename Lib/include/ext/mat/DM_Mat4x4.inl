
namespace DropMath
{
    inline Vec4& Mat4x4::operator[](int i)
    {
        assert(i >= 0 && i < 4);
        return rows[i];
    }
    inline const Vec4& Mat4x4::operator[](int i) const
    {
        assert(i >= 0 && i < 4);
        return rows[i];
    }
    inline Vec4 Mat4x4::operator*(const Vec4& v) const
    {
        return Vec4(
            _mm_cvtss_f32(_mm_dp_ps(rows[0].v, v.v, 0b11110001)),
            _mm_cvtss_f32(_mm_dp_ps(rows[1].v, v.v, 0b11110001)),
            _mm_cvtss_f32(_mm_dp_ps(rows[2].v, v.v, 0b11110001)),
            _mm_cvtss_f32(_mm_dp_ps(rows[3].v, v.v, 0b11110001)));
    }
    inline Mat4x4 Mat4x4::operator*(const Mat4x4& m) const
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

    inline float Mat4x4::Determinant() const { return Determinant4x4(*this); }

    inline Mat4x4 Mat4x4::Transposed() const
    {
        // Transpose 4x4 matrix using SSE.
        float4 row0 = rows[0].v;
        float4 row1 = rows[1].v;
        float4 row2 = rows[2].v;
        float4 row3 = rows[3].v;

        float4 t0 = _mm_unpacklo_ps(row0, row1);
        float4 t1 = _mm_unpackhi_ps(row0, row1);
        float4 t2 = _mm_unpacklo_ps(row2, row3);
        float4 t3 = _mm_unpackhi_ps(row2, row3);

        return Mat4x4(
            Vec4(_mm_movelh_ps(t0, t2)),
            Vec4(_mm_movehl_ps(t2, t0)),
            Vec4(_mm_movelh_ps(t1, t3)),
            Vec4(_mm_movehl_ps(t3, t1)));
    }

    inline void Mat4x4::StoreRowMajor(float* dst) const
    {
        _mm_storeu_ps(dst + 0, rows[0].v);
        _mm_storeu_ps(dst + 4, rows[1].v);
        _mm_storeu_ps(dst + 8, rows[2].v);
        _mm_storeu_ps(dst + 12, rows[3].v);
    }

    inline void Mat4x4::StoreColMajor(float* dst) const
    {
        dst[0]  = rows[0][0];
        dst[1]  = rows[1][0];
        dst[2]  = rows[2][0];
        dst[3]  = rows[3][0];
        dst[4]  = rows[0][1];
        dst[5]  = rows[1][1];
        dst[6]  = rows[2][1];
        dst[7]  = rows[3][1];
        dst[8]  = rows[0][2];
        dst[9]  = rows[1][2];
        dst[10] = rows[2][2];
        dst[11] = rows[3][2];
        dst[12] = rows[0][3];
        dst[13] = rows[1][3];
        dst[14] = rows[2][3];
        dst[15] = rows[3][3];
    }

    inline void Mat4x4::Store(float* dst, MATRIX_ALLIGNMENT alignment) const
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

    inline Mat4x4 Mat4x4::Inverse() const
    {
        Mat4x4 out;
        bool   result = TryInverse(*this, out);
        assert(result);
        return out;
    }

    inline bool Mat4x4::TryInverse(const Mat4x4& m, Mat4x4& out)
    {
        return TryInverse4x4(m, out);
    }

    inline Mat4x4 Mat4x4::Transpose(const Mat4x4& m)
    {
        // Transpose 4x4 matrix using SSE.
        float4 row0 = m[0].v;
        float4 row1 = m[1].v;
        float4 row2 = m[2].v;
        float4 row3 = m[3].v;

        float4 t0 = _mm_unpacklo_ps(row0, row1);
        float4 t1 = _mm_unpackhi_ps(row0, row1);
        float4 t2 = _mm_unpacklo_ps(row2, row3);
        float4 t3 = _mm_unpackhi_ps(row2, row3);

        return Mat4x4(
            Vec4(_mm_movelh_ps(t0, t2)),
            Vec4(_mm_movehl_ps(t2, t0)),
            Vec4(_mm_movelh_ps(t1, t3)),
            Vec4(_mm_movehl_ps(t3, t1)));
    }

    inline Mat4x4 Mat4x4::Identity()
    {
        return Mat4x4(
            Vec4(1, 0, 0, 0),
            Vec4(0, 1, 0, 0),
            Vec4(0, 0, 1, 0),
            Vec4(0, 0, 0, 1));
    }
} // namespace DropMath
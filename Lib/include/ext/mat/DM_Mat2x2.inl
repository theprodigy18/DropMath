
namespace DropMath
{
    DM_CONSTEXPR_14 inline Vec2& Mat2x2::operator[](int i)
    {
        DM_ASSERT(i >= 0 && i < 2);
        return rows[i];
    }
    DM_CONSTEXPR_14 inline const Vec2& Mat2x2::operator[](int i) const
    {
        DM_ASSERT(i >= 0 && i < 2);
        return rows[i];
    }
    DM_CONSTEXPR inline Vec2   Mat2x2::operator*(const Vec2& v) const { return Vec2(Vec2::Dot(rows[0], v), Vec2::Dot(rows[1], v)); }
    DM_CONSTEXPR_14 inline Mat2x2 Mat2x2::operator*(const Mat2x2& m) const
    {
        Mat2x2 t = m.Transposed();

        return Mat2x2(
            Vec2(Vec2::Dot(rows[0], t[0]), Vec2::Dot(rows[0], t[1])),
            Vec2(Vec2::Dot(rows[1], t[0]), Vec2::Dot(rows[1], t[1])));
    }

    inline float Mat2x2::Determinant() const { return Determinant2x2(*this); }

    DM_CONSTEXPR inline Mat2x2 Mat2x2::Transposed() const { return Mat2x2(Vec2(rows[0].x, rows[1].x), Vec2(rows[0].y, rows[1].y)); }

    inline void Mat2x2::StoreRowMajor(float* dst) const
    {
        dst[0] = rows[0][0];
        dst[1] = rows[0][1];
        dst[2] = rows[1][0];
        dst[3] = rows[1][1];
    }

    inline void Mat2x2::StoreColMajor(float* dst) const
    {
        dst[0] = rows[0][0];
        dst[1] = rows[1][0];
        dst[2] = rows[0][1];
        dst[3] = rows[1][1];
    }

    inline void Mat2x2::Store(float* dst, MATRIX_ALLIGNMENT alignment) const
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
            DM_ASSERT(false);
            break;
        }

		return StoreRowMajor(dst);
    }

    inline Mat2x2 Mat2x2::Inverse() const
    {
        Mat2x2 out;
        bool   result = TryInverse(*this, out);
        DM_ASSERT(result);
        return out;
    }

    inline bool Mat2x2::TryInverse(const Mat2x2& m, Mat2x2& out)
    {
        return TryInverse2x2(m, out);
    }

    DM_CONSTEXPR inline Mat2x2 Mat2x2::Transpose(const Mat2x2& m) { return Mat2x2(Vec2(m[0].x, m[1].x), Vec2(m[0].y, m[1].y)); }
} // namespace Dropmath
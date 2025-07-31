
namespace DropMath
{
    DM_CONSTEXPR_14 inline Vec3& Mat3x3::operator[](int i)
    {
        DM_ASSERT(i >= 0 && i < 3);
        return rows[i];
    }
    DM_CONSTEXPR_14 inline const Vec3& Mat3x3::operator[](int i) const
    {
        DM_ASSERT(i >= 0 && i < 3);
        return rows[i];
    }
    DM_CONSTEXPR inline Vec3 Mat3x3::operator*(const Vec3& v) const
    {
        return Vec3(
            Vec3::Dot(rows[0], v),
            Vec3::Dot(rows[1], v),
            Vec3::Dot(rows[2], v));
    }
    DM_CONSTEXPR_14 inline Mat3x3 Mat3x3::operator*(const Mat3x3& m) const
    {
        Mat3x3 t = m.Transposed();

        return Mat3x3(
            Vec3(Vec3::Dot(rows[0], t[0]), Vec3::Dot(rows[0], t[1]), Vec3::Dot(rows[0], t[2])),
            Vec3(Vec3::Dot(rows[1], t[0]), Vec3::Dot(rows[1], t[1]), Vec3::Dot(rows[1], t[2])),
            Vec3(Vec3::Dot(rows[2], t[0]), Vec3::Dot(rows[2], t[1]), Vec3::Dot(rows[2], t[2])));
    }

    inline float Mat3x3::Determinant() const { return Determinant3x3(*this); }

    DM_CONSTEXPR inline Mat3x3 Mat3x3::Transposed() const
    {
        return Mat3x3(
            Vec3(rows[0].x, rows[1].x, rows[2].x),
            Vec3(rows[0].y, rows[1].y, rows[2].y),
            Vec3(rows[0].z, rows[1].z, rows[2].z));
    }

    inline void Mat3x3::StoreRowMajor(float* dst) const
    {
        dst[0] = rows[0][0];
        dst[1] = rows[0][1];
        dst[2] = rows[0][2];
        dst[3] = rows[1][0];
        dst[4] = rows[1][1];
        dst[5] = rows[1][2];
        dst[6] = rows[2][0];
        dst[7] = rows[2][1];
        dst[8] = rows[2][2];
    }

    inline void Mat3x3::StoreColMajor(float* dst) const
    {
        dst[0] = rows[0][0];
        dst[1] = rows[1][0];
        dst[2] = rows[2][0];
        dst[3] = rows[0][1];
        dst[4] = rows[1][1];
        dst[5] = rows[2][1];
        dst[6] = rows[0][2];
        dst[7] = rows[1][2];
        dst[8] = rows[2][2];
    }

    inline void Mat3x3::Store(float* dst, MATRIX_ALLIGNMENT alignment) const
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

    inline Mat3x3 Mat3x3::Inverse() const
    {
        Mat3x3 out;
        bool   result = TryInverse(*this, out);
        DM_ASSERT(result);
        return out;
    }

    inline bool Mat3x3::TryInverse(const Mat3x3& m, Mat3x3& out)
    {
        return TryInverse3x3(m, out);
    }

    DM_CONSTEXPR inline Mat3x3 Mat3x3::Transpose(const Mat3x3& m)
    {
        return Mat3x3(
            Vec3(m[0].x, m[1].x, m[2].x),
            Vec3(m[0].y, m[1].y, m[2].y),
            Vec3(m[0].z, m[1].z, m[2].z));
    }

    DM_CONSTEXPR inline Mat3x3 Mat3x3::Identity()
    {
        return Mat3x3(
            Vec3(1, 0, 0),
            Vec3(0, 1, 0),
            Vec3(0, 0, 1));
    }
} // namespace Dropmath
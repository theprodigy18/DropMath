
namespace DropMath
{
    inline Vec3& Mat3x3::operator[](int i)
    {
        assert(i >= 0 && i < 3);
        return rows[i];
    }
    inline const Vec3& Mat3x3::operator[](int i) const
    {
        assert(i >= 0 && i < 3);
        return rows[i];
    }
    inline Vec3 Mat3x3::operator*(const Vec3& v) const
    {
        return Vec3(
            Vec3::Dot(rows[0], v),
            Vec3::Dot(rows[1], v),
            Vec3::Dot(rows[2], v));
    }
    inline Mat3x3 Mat3x3::operator*(const Mat3x3& m) const
    {
        Mat3x3 t = m.Transposed();

        return Mat3x3(
            Vec3(Vec3::Dot(rows[0], t[0]), Vec3::Dot(rows[0], t[1]), Vec3::Dot(rows[0], t[2])),
            Vec3(Vec3::Dot(rows[1], t[0]), Vec3::Dot(rows[1], t[1]), Vec3::Dot(rows[1], t[2])),
            Vec3(Vec3::Dot(rows[2], t[0]), Vec3::Dot(rows[2], t[1]), Vec3::Dot(rows[2], t[2])));
    }

    inline Mat3x3 Mat3x3::Transposed() const
    {
        return Mat3x3(
            Vec3(rows[0][0], rows[1][0], rows[2][0]),
            Vec3(rows[0][1], rows[1][1], rows[2][1]),
            Vec3(rows[0][2], rows[1][2], rows[2][2]));
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
            assert(false, "Unknown matrix allignment.");
            return StoreRowMajor(dst);
            break;
        }
    }

    inline Mat3x3 Mat3x3::Transpose(const Mat3x3& m)
    {
        return Mat3x3(
            Vec3(m[0][0], m[1][0], m[2][0]),
            Vec3(m[0][1], m[1][1], m[2][1]),
            Vec3(m[0][2], m[1][2], m[2][2]));
    }

    inline Mat3x3 Mat3x3::Identity()
    {
        return Mat3x3(
            Vec3(1, 0, 0),
            Vec3(0, 1, 0),
            Vec3(0, 0, 1));
    }
} // namespace Dropmath
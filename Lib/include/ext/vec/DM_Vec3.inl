
namespace DropMath
{
    inline float& Vec3::operator[](int i)
    {
        assert(i >= 0 && i < 3);
        return array[i];
    }
    inline const float& Vec3::operator[](int i) const
    {
        assert(i >= 0 && i < 3);
        return array[i];
    }
    inline bool Vec3::operator==(const Vec3& v) const { return IsZero(x - v.x) && IsZero(y - v.y) && IsZero(z - v.z); }
    inline bool Vec3::operator!=(const Vec3& v) const { return !(*this == v); }

    inline float Vec3::Length() const { return SqrtF(LengthSquared()); }

    inline void Vec3::Normalize()
    {
        float len = Length();
        if (len > DM_EPSILON)
        {
            x /= len;
            y /= len;
            z /= len;
        }
    }

    inline Vec3 Vec3::Lerp(const Vec3& a, const Vec3& b, float t) { return DropMath::Lerp(a, b, t); }

} // namespace DropMath
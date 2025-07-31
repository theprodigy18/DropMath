
namespace DropMath
{
    inline float& Vec2::operator[](int i)
    {
		DM_ASSERT(i >= 0 && i < 2);
        return array[i];
    }
    inline const float& Vec2::operator[](int i) const
    {
        DM_ASSERT(i >= 0 && i < 2);
        return array[i];
    }
    inline bool Vec2::operator==(const Vec2& v) const { return IsZero(x - v.x) && IsZero(y - v.y); }
    inline bool Vec2::operator!=(const Vec2& v) const { return !(*this == v); }

    inline float Vec2::Length() const { return Sqrt(LengthSquared()); }

    inline void Vec2::Normalize()
    {
        float len = Length();
        if (len > F::EPSILON)
        {
            x /= len;
            y /= len;
        }
    }

	inline Vec2 Vec2::Normalized() const
	{
		Vec2 v = *this;
		v.Normalize();
		return v;
	}

    DM_CONSTEXPR inline Vec2 Vec2::Lerp(const Vec2& a, const Vec2& b, float t) { return DropMath::Lerp(a, b, t); }

} // namespace DropMath
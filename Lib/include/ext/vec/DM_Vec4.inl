
namespace DropMath
{
	namespace
	{
        const float4 g_EPSILON_F   = _mm_set1_ps(F::EPSILON);
        const float4  g_SIGN_MASK_F = _mm_castsi128_ps(_mm_set1_epi32(F::SIGN_MASK));
	} // anonymous namespace

    inline float& Vec4::operator[](int i)
    {
        DM_ASSERT(i >= 0 && i < 4);
        return array[i];
    }
    inline const float& Vec4::operator[](int i) const
    {
        DM_ASSERT(i >= 0 && i < 4);
        return array[i];
    }
    inline bool Vec4::operator==(const Vec4& v) const
    {
        float4 delta = _mm_sub_ps(v.v, this->v);
        float4 abs   = _mm_and_ps(g_SIGN_MASK_F, delta);
        float4 cmp   = _mm_cmplt_ps(abs, g_EPSILON_F);
        int    mask  = _mm_movemask_ps(cmp);
        return mask == 0xF;
    }
    inline bool Vec4::operator!=(const Vec4& v) const { return !(*this == v); }

    inline float Vec4::Length() const
    {
        float4 dot  = _mm_dp_ps(v, v, DOT_MASK);
        float4 sqrt = _mm_sqrt_ps(dot);
        return _mm_cvtss_f32(sqrt);
    }

    inline float Vec4::LengthSquared() const
    {
        float4 dot = _mm_dp_ps(v, v, DOT_MASK);
        return _mm_cvtss_f32(dot);
    }

    inline void Vec4::Normalize()
    {
        float len = Length();
        if (len > F::EPSILON)
        {
            v = _mm_div_ps(v, _mm_set1_ps(len));
        }
    }

    inline float Vec4::Dot(const Vec4& a, const Vec4& b)
    {
        float4 dot = _mm_dp_ps(a.v, b.v, DOT_MASK);
        return _mm_cvtss_f32(dot);
    }

    inline Vec4 Vec4::Lerp(const Vec4& a, const Vec4& b, float t) { return DropMath::Lerp(a, b, t); }

} // namespace DropMath
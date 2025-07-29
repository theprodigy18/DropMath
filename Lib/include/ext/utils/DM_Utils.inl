

namespace DropMath
{
    namespace
    {
        const float4  g_SIGN_MASK_F = _mm_castsi128_ps(_mm_set1_epi32(DM_SIGN_MASK_F));
        const double2 g_SIGN_MASK   = _mm_castsi128_pd(_mm_set1_epi64x(DM_SIGN_MASK));
    }

    template <typename T>
    inline T Lerp(const T& a, const T& b, float t)
    {
        return a * (1 - t) + b * t;
    }

    inline float AbsF(float x)
    {
        float4 data_x = _mm_set_ss(x);
        float4 abs_x  = _mm_and_ps(g_SIGN_MASK_F, data_x);
        return _mm_cvtss_f32(abs_x);
    }

    inline double AbsD(double x)
    {
        double2 data_x = _mm_set_sd(x);
        double2 abs_x  = _mm_and_pd(g_SIGN_MASK, data_x);
        return _mm_cvtsd_f64(abs_x);
    }

    inline int AbsI(int x)
    {
        int mask = x >> 31;
        return (x ^ mask) - mask;
    }

    template <typename T>
    inline T Min(const T& a, const T& b)
    {
        return (a < b) ? a : b;
    }

    template <typename T>
    inline T Max(const T& a, const T& b)
    {
        return (a > b) ? a : b;
    }

    template <typename T>
    inline T Clamp(const T& value, const T& min, const T& max)
    {
        return Min(Max(value, min), max);
    }

    inline float SqrtF(float x)
    {
        float4 data_x = _mm_set_ss(x);
        return _mm_cvtss_f32(_mm_sqrt_ss(data_x));
    }

    inline double Sqrt(double x)
    {
        double2 data_x = _mm_set_sd(x);
        return _mm_cvtsd_f64(_mm_sqrt_sd(data_x, data_x));
    }

    inline bool IsZero(float x)
    {
        return AbsF(x) < DM_EPSILON;
    }

    inline bool IsZero(double x)
    {
        return AbsD(x) < DM_EPSILON;
    }

} // namespace Drop
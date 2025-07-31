#pragma once

#ifdef __cplusplus
#define DM_CONSTEXPR constexpr
#if __cplusplus >= 201402L
#define DM_CONSTEXPR_14 constexpr
#else
#define DM_CONSTEXPR_14
#endif // __cplusplus >= 201402L
#if __cplusplus >= 201703L
#define DM_CONSTEXPR_17 constexpr
#else
#define DM_CONSTEXPR_17
#endif // __cplusplus >= 201703L
#else
#define DM_CONSTEXPR
#define DM_CONSTEXPR_14
#define DM_CONSTEXPR_17
#endif // __cplusplus

#if defined(_MSC_VER)
#define DM_DBG_BREAK() __debugbreak()
#elif defined(__clang__) || defined(__GNUC__)
#define DM_DBG_BREAK() __builtin_trap()
#else 
#define DM_DBG_BREAK() (*(volatile int*) 0 = 0)
#endif // 


#if !defined(DM_NO_ASSERT)
#define DM_ASSERT(x) (void)DropMath::_ASSERT_(x)
#else
#define DM_ASSERT(x)
#endif // !DM_NDBG_BREAK

namespace DropMath
{
	DM_CONSTEXPR_14 inline void _ASSERT_(bool cond)
	{
#if !defined(DM_NO_ASSERT)
        (void) (cond ? 0 : (DM_DBG_BREAK(), 0));
#endif // !DM_NO_ASSERT
	}

    DM_CONSTEXPR int DOT_MASK = 0b11110001;

    namespace F
    {
        DM_CONSTEXPR float EPSILON    = 1e-6f;
        DM_CONSTEXPR float PI         = 3.141592653589793f;
        DM_CONSTEXPR float TWO_PI     = 6.283185307179586f;
        DM_CONSTEXPR float HALF_PI    = 1.5707963267948966f;
        DM_CONSTEXPR float INV_PI     = 1.0f / PI;
        DM_CONSTEXPR float INV_TWO_PI = 1.0f / TWO_PI;
        DM_CONSTEXPR float TO_DEG     = 180.0f / PI;
        DM_CONSTEXPR float TO_RAD     = PI / 180.0f;

        DM_CONSTEXPR int SIGN_MASK = 0x7FFFFFFF;

#if defined(__GNUC__) || defined(__clang__)
        float INFINITY = __builtin_huge_valf();
#elif defined(_MSC_VER)
        const float INFINITY = (float)(1e+300 * 1e+300);
#else
#error "Unsupported compiler."
#endif

    } // namespace F

    namespace D
    {
        DM_CONSTEXPR double EPSILON    = 1e-9;
        DM_CONSTEXPR double PI         = 3.1415926535897932384626433832795;
        DM_CONSTEXPR double TWO_PI     = 6.283185307179586476925286766559;
        DM_CONSTEXPR double HALF_PI    = 1.5707963267948966192313216916398;
        DM_CONSTEXPR double INV_PI     = 1.0 / PI;
        DM_CONSTEXPR double INV_TWO_PI = 1.0 / TWO_PI;
        DM_CONSTEXPR double TO_DEG     = 180.0 / PI;
        DM_CONSTEXPR double TO_RAD     = PI / 180.0;

        DM_CONSTEXPR long long SIGN_MASK = 0x7FFFFFFFFFFFFFFF;

#if defined(__GNUC__) || defined(__clang__)
        double INFINITY = __builtin_huge_val();
#elif defined(_MSC_VER)
        const double INFINITY = (double)(1e+300 * 1e+300);
#else
#error "Unsupported compiler."
#endif
    } // namespace D

} // namespace DropMath
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

#define DM_INFINITY_F DropMath::FloatBits{0x7F800000}.f
#define DM_INFINITY DropMath::DoubleBits {0x7FF0000000000000ULL}.d

namespace DropMath
{
    union FloatBits
    {
        unsigned int u;
        float        f;
    };
    union DoubleBits
    {
        unsigned long long u;
        double             d;
    };

    namespace F
    {
        DM_CONSTEXPR float EPSILON    = 1e-6f;
        DM_CONSTEXPR float PI         = 3.14159265358979f;
        DM_CONSTEXPR float TWO_PI     = 6.28318530717959f;
        DM_CONSTEXPR float HALF_PI    = 1.57079632679489f;
        DM_CONSTEXPR float INV_PI     = 1.0f / PI; 
        DM_CONSTEXPR float INV_TWO_PI = 1.0f / TWO_PI; 
		DM_CONSTEXPR float TO_DEG     = 180.0f / PI;
		DM_CONSTEXPR float TO_RAD     = PI / 180.0f;

        DM_CONSTEXPR int SIGN_MASK = 0x7FFFFFFF;
    } // namespace F

    namespace D
    {
        DM_CONSTEXPR double EPSILON    = 1e-12;
        DM_CONSTEXPR double PI         = 3.1415926535897932384626433832795;
        DM_CONSTEXPR double TWO_PI     = 6.283185307179586476925286766559;
        DM_CONSTEXPR double HALF_PI    = 1.5707963267948966192313216916398;
        DM_CONSTEXPR double INV_PI     = 1.0 / PI;
        DM_CONSTEXPR double INV_TWO_PI = 1.0 / TWO_PI;
		DM_CONSTEXPR double TO_DEG     = 180.0 / PI;
		DM_CONSTEXPR double TO_RAD     = PI / 180.0;

        DM_CONSTEXPR long long SIGN_MASK = 0x7FFFFFFFFFFFFFFF;
    } // namespace D

} // namespace DropMath
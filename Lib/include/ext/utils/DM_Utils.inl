

namespace DropMath
{
    namespace
    {
        // Return the sign(float) and change the rad(float) that already in range [-pi, pi] to the range [-pi/2, pi/2].
        DM_CONSTEXPR_14 inline float FoldToHalfPiRef(float& wrappedRad)
        {
            float sign = 1.0f;
            if (wrappedRad > F::HALF_PI)
                wrappedRad = F::PI - wrappedRad;
            else if (wrappedRad < -F::HALF_PI)
            {
                wrappedRad = -F::PI - wrappedRad;
                sign       = -1.0f;
            }
            return sign;
        }

        // Return the sign(double) and change the rad(double) that already in range [-pi, pi] to the range [-pi/2, pi/2].
        DM_CONSTEXPR_14 inline double FoldToHalfPiRef(double& wrappedRad)
        {
            double sign = 1.0;
            if (wrappedRad > D::HALF_PI)
                wrappedRad = D::PI - wrappedRad;
            else if (wrappedRad < -D::HALF_PI)
            {
                wrappedRad = -D::PI - wrappedRad;
                sign       = -1.0;
            }
            return sign;
        }

        DM_CONSTEXPR_14 inline float SinApprox(float x)
        {
            float x2 = x * x;
            return ((((-2.3889859e-08f * x2 + 2.7525562e-06f) * x2 - 0.00019840874f) * x2 + 0.0083333310f) * x2 - 0.16666667f) * x2 * x + x;
        }

        DM_CONSTEXPR_14 inline double SinApprox(double x)
        {
            double x2 = x * x;
            return ((((((((((-1.9509019e-19 * x2 + 8.33216087e-17) * x2 - 1.95152959e-14) * x2 + 2.59230160e-12) * x2 - 2.50521084e-10) * x2 + 1.60590438e-08) * x2 - 7.64716373e-07) * x2 + 2.75573192e-05) * x2 - 0.00019841270) * x2 + 0.00833333333) * x2 - 0.16666666667) * x2 * x + x;
        }
    } // anonymous namespace

    const float4  g_SIGN_MASK_F = _mm_castsi128_ps(_mm_set1_epi32(F::SIGN_MASK));
    const double2 g_SIGN_MASK   = _mm_castsi128_pd(_mm_set1_epi64x(D::SIGN_MASK));

    DM_CONSTEXPR_14 inline int Floor(float x)
    {
        int i = (int) x;
        return (x < 0.0f && x != (float) i) ? (i - 1) : i;
    }

    DM_CONSTEXPR_14 inline int Floor(double x)
    {
        int i = (int) x;
        return (x < 0.0 && x != (double) i) ? (i - 1) : i;
    }

    DM_CONSTEXPR_14 inline int Ceil(float x)
    {
        int i = (int) x;
        return (x > 0.0f && x != (float) i) ? (i + 1) : i;
    }

    DM_CONSTEXPR_14 inline int Ceil(double x)
    {
        int i = (int) x;
        return (x > 0.0 && x != (double) i) ? (i + 1) : i;
    }

    DM_CONSTEXPR_14 inline int Round(float x)
    {
        return (x >= 0.0f) ? (int) (x + 0.5f) : (int) (x - 0.5f);
    }

    DM_CONSTEXPR_14 inline int Round(double x)
    {
        return (x >= 0.0) ? (int) (x + 0.5) : (int) (x - 0.5);
    }

    DM_CONSTEXPR_14 inline float WrapPi(float rad)
    {
        rad += F::PI;
        rad -= Floor(rad * F::INV_TWO_PI) * F::TWO_PI;
        rad -= F::PI;
        return rad;
    }

    DM_CONSTEXPR_14 inline double WrapPi(double rad)
    {
        rad += D::PI;
        rad -= Floor(rad * D::INV_TWO_PI) * D::TWO_PI;
        rad -= D::PI;
        return rad;
    }

    DM_CONSTEXPR_14 inline float ToRadians(float deg) { return deg * F::TO_RAD; }

    DM_CONSTEXPR_14 inline double ToRadians(double deg) { return deg * D::TO_RAD; }

    DM_CONSTEXPR_14 inline float ToDegrees(float rad) { return rad * F::TO_DEG; }

    DM_CONSTEXPR_14 inline double ToDegrees(double rad) { return rad * D::TO_DEG; }

    DM_CONSTEXPR_14 inline float Sin(float rad)
    {
        rad        = WrapPi(rad);
        float sign = FoldToHalfPiRef(rad);
        return sign * SinApprox(rad);
    }

    DM_CONSTEXPR_14 inline double Sin(double rad)
    {
        rad         = WrapPi(rad);
        double sign = FoldToHalfPiRef(rad);
        return sign * SinApprox(rad);
    }

    DM_CONSTEXPR_14 inline float Cos(float rad)
    {
        return Sin(F::HALF_PI - rad);
    }

    DM_CONSTEXPR_14 inline double Cos(double rad)
    {
        return Sin(D::HALF_PI - rad);
    }

    inline float Tan(float rad)
    {
        float sin = Sin(rad);
        float cos = Cos(rad);
        return IsZero(cos) ? DM_INFINITY : sin / cos;
    }

    inline double Tan(double rad)
    {
        double sin = Sin(rad);
        double cos = Cos(rad);
        return IsZero(cos) ? DM_INFINITY : sin / cos;
    }

    DM_CONSTEXPR_14 inline float Sign(float x) { return (x > 0.0f) - (x < 0.0f); }

    DM_CONSTEXPR_14 inline double Sign(double x) { return (x > 0.0) - (x < 0.0); }

    DM_CONSTEXPR_14 inline int Sign(int x) { return (x > 0) - (x < 0); }

    template <typename T>
    inline T Lerp(const T& a, const T& b, float t)
    {
        return a * (1 - t) + b * t;
    }

    inline float Abs(float x)
    {
        float4 data_x = _mm_set_ss(x);
        float4 abs_x  = _mm_and_ps(g_SIGN_MASK_F, data_x);
        return _mm_cvtss_f32(abs_x);
    }

    inline double Abs(double x)
    {
        double2 data_x = _mm_set_sd(x);
        double2 abs_x  = _mm_and_pd(g_SIGN_MASK, data_x);
        return _mm_cvtsd_f64(abs_x);
    }

    DM_CONSTEXPR_14 inline int Abs(int x)
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

    inline float Sqrt(float x)
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
        return Abs(x) < F::EPSILON;
    }

    inline bool IsZero(double x)
    {
        return Abs(x) < D::EPSILON;
    }

    template <typename Mat>
    inline float Determinant2x2(const Mat& m)
    {
        return m[0][0] * m[1][1] - m[0][1] * m[1][0];
    }

    template <typename Mat>
    inline float Determinant3x3(const Mat& m)
    {
        // Alias for faster access.
        float a10 = m[1][0], a11 = m[1][1], a12 = m[1][2];
        float a20 = m[2][0], a21 = m[2][1], a22 = m[2][2];

        return (
            m[0][0] * (a11 * a22 - a12 * a21) -
            m[0][1] * (a10 * a22 - a12 * a20) +
            m[0][2] * (a10 * a21 - a11 * a20));
    }

    template <typename Mat>
    inline float Determinant4x4(const Mat& m)
    {
        // Alias for faster access.
        float a10 = m[1][0], a11 = m[1][1], a12 = m[1][2], a13 = m[1][3];
        float a20 = m[2][0], a21 = m[2][1], a22 = m[2][2], a23 = m[2][3];
        float a30 = m[3][0], a31 = m[3][1], a32 = m[3][2], a33 = m[3][3];

        // Compute 2x2 sub-determinants (reuse as much as possible).
        float s0 = a22 * a33 - a23 * a32;
        float s1 = a21 * a33 - a23 * a31;
        float s2 = a21 * a32 - a22 * a31;
        float s3 = a20 * a33 - a23 * a30;
        float s4 = a20 * a32 - a22 * a30;
        float s5 = a20 * a31 - a21 * a30;

        // Compute cofactors of the first row.
        float c0 = a11 * s0 - a12 * s1 + a13 * s2;
        float c1 = -a10 * s0 + a12 * s3 - a13 * s4;
        float c2 = a10 * s1 - a11 * s3 + a13 * s5;
        float c3 = -a10 * s2 + a11 * s4 - a12 * s5;

        // Final determinant (dot product of row0 and cofactors).
        return m[0][0] * c0 + m[0][1] * c1 + m[0][2] * c2 + m[0][3] * c3;
    }

    template <typename Mat>
    inline bool TryInverse2x2(const Mat& m, Mat& out)
    {
        // Alias for faster access.
        float a00 = m[0][0], a01 = m[0][1];
        float a10 = m[1][0], a11 = m[1][1];

        float det = a00 * a11 - a01 * a10;

        if (IsZero(det))
            return false;

        float invDet = 1.0f / det;

        out[0][0] = a11 * invDet;
        out[0][1] = -a01 * invDet;
        out[1][0] = -a10 * invDet;
        out[1][1] = a00 * invDet;

        return true;
    }

    template <typename Mat>
    inline bool TryInverse3x3(const Mat& m, Mat& out)
    {
        // Alias for faster access.
        float a00 = m[0][0], a01 = m[0][1], a02 = m[0][2];
        float a10 = m[1][0], a11 = m[1][1], a12 = m[1][2];
        float a20 = m[2][0], a21 = m[2][1], a22 = m[2][2];

        // Cofactor matrix.
        float C00 = (a11 * a22 - a12 * a21);
        float C01 = -(a10 * a22 - a12 * a20);
        float C02 = (a10 * a21 - a11 * a20);
        float C10 = -(a01 * a22 - a02 * a21);
        float C11 = (a00 * a22 - a02 * a20);
        float C12 = -(a00 * a21 - a01 * a20);
        float C20 = (a01 * a12 - a02 * a11);
        float C21 = -(a00 * a12 - a02 * a10);
        float C22 = (a00 * a11 - a01 * a10);

        float det = a00 * C00 + a01 * C01 + a02 * C02;

        if (IsZero(det))
            return false;

        float invDet = 1.0f / det;

        // Transpose cofactor matrix(adj) x 1/det.
        out[0][0] = C00 * invDet;
        out[0][1] = C10 * invDet;
        out[0][2] = C20 * invDet;

        out[1][0] = C01 * invDet;
        out[1][1] = C11 * invDet;
        out[1][2] = C21 * invDet;

        out[2][0] = C02 * invDet;
        out[2][1] = C12 * invDet;
        out[2][2] = C22 * invDet;

        return true;
    }

    template <typename Mat>
    inline bool TryInverse4x4(const Mat& m, Mat& out)
    {
        // Alias for faster access.
        float a00 = m[0][0], a01 = m[0][1], a02 = m[0][2], a03 = m[0][3];
        float a10 = m[1][0], a11 = m[1][1], a12 = m[1][2], a13 = m[1][3];
        float a20 = m[2][0], a21 = m[2][1], a22 = m[2][2], a23 = m[2][3];
        float a30 = m[3][0], a31 = m[3][1], a32 = m[3][2], a33 = m[3][3];

        // Precompute reused 2x2 determinants (minors).
        float b00 = a00 * a11 - a01 * a10;
        float b01 = a00 * a12 - a02 * a10;
        float b02 = a00 * a13 - a03 * a10;
        float b03 = a01 * a12 - a02 * a11;
        float b04 = a01 * a13 - a03 * a11;
        float b05 = a02 * a13 - a03 * a12;
        float b06 = a20 * a31 - a21 * a30;
        float b07 = a20 * a32 - a22 * a30;
        float b08 = a20 * a33 - a23 * a30;
        float b09 = a21 * a32 - a22 * a31;
        float b10 = a21 * a33 - a23 * a31;
        float b11 = a22 * a33 - a23 * a32;

        // Compute 3x3 cofactors.
        float c00 = a11 * b11 - a12 * b10 + a13 * b09;
        float c01 = -a01 * b11 + a02 * b10 - a03 * b09;
        float c02 = a31 * b05 - a32 * b04 + a33 * b03;
        float c03 = -a21 * b05 + a22 * b04 - a23 * b03;

        float c10 = -a10 * b11 + a12 * b08 - a13 * b07;
        float c11 = a00 * b11 - a02 * b08 + a03 * b07;
        float c12 = -a30 * b05 + a32 * b02 - a33 * b01;
        float c13 = a20 * b05 - a22 * b02 + a23 * b01;

        float c20 = a10 * b10 - a11 * b08 + a13 * b06;
        float c21 = -a00 * b10 + a01 * b08 - a03 * b06;
        float c22 = a30 * b04 - a31 * b02 + a33 * b00;
        float c23 = -a20 * b04 + a21 * b02 - a23 * b00;

        float c30 = -a10 * b09 + a11 * b07 - a12 * b06;
        float c31 = a00 * b09 - a01 * b07 + a02 * b06;
        float c32 = -a30 * b03 + a31 * b01 - a32 * b00;
        float c33 = a20 * b03 - a21 * b01 + a22 * b00;

        float det = a00 * c00 + a01 * c10 + a02 * c20 + a03 * c30;

        if (IsZero(det))
            return false;

        float invDet = 1.0f / det;

        // Transpose cofactor matrix(adj) x 1/det.
        out[0][0] = c00 * invDet;
        out[0][1] = c01 * invDet;
        out[0][2] = c02 * invDet;
        out[0][3] = c03 * invDet;

        out[1][0] = c10 * invDet;
        out[1][1] = c11 * invDet;
        out[1][2] = c12 * invDet;
        out[1][3] = c13 * invDet;

        out[2][0] = c20 * invDet;
        out[2][1] = c21 * invDet;
        out[2][2] = c22 * invDet;
        out[2][3] = c23 * invDet;

        out[3][0] = c30 * invDet;
        out[3][1] = c31 * invDet;
        out[3][2] = c32 * invDet;
        out[3][3] = c33 * invDet;

        return true;
    }

} // namespace Drop
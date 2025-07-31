#include <DropMath.h>

#include <chrono>
#include <iostream>

using namespace DropMath;

// Testing Lerp<T>.
void TestUtils_Lerp()
{
    float lf = Lerp(10.0f, 20.0f, 0.5f);
    DM_ASSERT(IsZero(lf - 15.0f));

    double ld = Lerp(1.0, 3.0, 0.25);
    DM_ASSERT(IsZero(ld - 1.5));

    int li = Lerp(10, 20, 0.3f);
    DM_ASSERT(li == 13); // Integer truncation.
}

// Testing Abs overloads.
void TestUtils_Abs()
{
    DM_ASSERT(Abs(-3.5f) == 3.5f);
    DM_ASSERT(Abs(2.0f) == 2.0f);

    DM_ASSERT(Abs(-1.25) == 1.25);
    DM_ASSERT(Abs(0.5) == 0.5);

    DM_ASSERT(Abs(-7) == 7);
    DM_ASSERT(Abs(9) == 9);
}

// Testing Min<T> and Max<T>.
void TestUtils_MinMax()
{
    DM_ASSERT(Min(4, 7) == 4);
    DM_ASSERT(Max(4, 7) == 7);

    DM_ASSERT(Min(4.5f, 1.5f) == 1.5f);
    DM_ASSERT(Max(4.5, 10.0) == 10.0);
}

// Testing Clamp<T>.
void TestUtils_Clamp()
{
    DM_ASSERT(Clamp(5, 1, 10) == 5);
    DM_ASSERT(Clamp(-1, 0, 4) == 0);
    DM_ASSERT(Clamp(11, 0, 10) == 10);

    DM_ASSERT(IsZero(Clamp(0.5f, 0.0f, 1.0f) - 0.5f));
    DM_ASSERT(IsZero(Clamp(-0.5f, 0.0f, 1.0f) - 0.0f));
    DM_ASSERT(IsZero(Clamp(1.5f, 0.0f, 1.0f) - 1.0f));
}

// Testing Sqrt.
void TestUtils_Sqrt()
{
    DM_ASSERT(IsZero(Sqrt(4.0f) - 2.0f));
    DM_ASSERT(IsZero(Sqrt(9.0) - 3.0));
}

// Testing IsZero.
void TestUtils_IsZero()
{
    DM_ASSERT(IsZero(0.0000001f));
    DM_ASSERT(IsZero(-0.00000005f));
    DM_ASSERT(!IsZero(0.001f));

    DM_ASSERT(IsZero(0.0000000000001));
    DM_ASSERT(!IsZero(0.001));
}

// NEWER TESTS.

// Testing Floor, Ceil, Round.
void TestUtils_FloorCeilRound()
{
    DM_ASSERT(Floor(2.9f) == 2);
    DM_ASSERT(Floor(-2.1f) == -3);

    DM_ASSERT(Floor(3.8) == 3);
    DM_ASSERT(Floor(-3.2) == -4);

    DM_ASSERT(Ceil(2.1f) == 3);
    DM_ASSERT(Ceil(-2.9f) == -2);

    DM_ASSERT(Ceil(3.2) == 4);
    DM_ASSERT(Ceil(-3.8) == -3);

    DM_ASSERT(Round(2.4f) == 2);
    DM_ASSERT(Round(2.6f) == 3);
    DM_ASSERT(Round(-2.4f) == -2);
    DM_ASSERT(Round(-2.6f) == -3);

    DM_ASSERT(Round(2.5) == 3);
    DM_ASSERT(Round(-2.5) == -3);
}

// Testing radians <-> degrees conversion.
void TestUtils_DegRad()
{
    DM_ASSERT(IsZero(ToRadians(180.0f) - F::PI));
    DM_ASSERT(IsZero(ToRadians(90.0) - D::HALF_PI));

    DM_ASSERT(IsZero(ToDegrees(F::PI) - 180.0f));
    DM_ASSERT(IsZero(ToDegrees(D::HALF_PI) - 90.0));
}

// Testing WrapPi
void TestUtils_WrapPi()
{
    DM_ASSERT(IsZero(WrapPi(F::PI * 3.0f) + F::PI));
    DM_ASSERT(IsZero(WrapPi(-F::PI * 3.0f) + F::PI));

    DM_ASSERT(IsZero(WrapPi(D::PI * 3.0) + D::PI));
    DM_ASSERT(IsZero(WrapPi(-D::PI * 3.0) + D::PI));
}

// Testing Sign
void TestUtils_Sign()
{
    DM_ASSERT(Sign(5.0f) == 1);
    DM_ASSERT(Sign(-3.0f) == -1);
    DM_ASSERT(Sign(0.0f) == 0);

    DM_ASSERT(Sign(5.0) == 1);
    DM_ASSERT(Sign(-3.0) == -1);
    DM_ASSERT(Sign(0.0) == 0);

    DM_ASSERT(Sign(10) == 1);
    DM_ASSERT(Sign(-7) == -1);
    DM_ASSERT(Sign(0) == 0);
}

// Testing Sin, Cos, Tan.
void TestUtils_Trigonometry()
{
    DM_ASSERT(IsZero(Sin(0.0f)));
    DM_ASSERT(IsZero(Cos(F::HALF_PI)));
    DM_ASSERT(IsZero(Tan(0.0f)));

    DM_ASSERT(IsZero(Sin(0.0)));
    DM_ASSERT(IsZero(Cos(D::HALF_PI)));
    DM_ASSERT(IsZero(Tan(0.0)));
}

// Testing Determinant and Inverse.
void TestUtils_DeterminantAndInverse()
{
    // === 2x2 ===
    float m2[2][2] = {
        {4.0f, 7.0f},
        {2.0f, 6.0f}};

    float expectedDet2 = 4.0f * 6.0f - 7.0f * 2.0f; // = 10.0f
    DM_ASSERT(IsZero(Determinant2x2(m2) - expectedDet2));

    float inv2[2][2];
    DM_ASSERT(TryInverse2x2(m2, inv2));
    // Optional: test specific value or just DM_ASSERT determinant is not zero

    // === 3x3 ===
    float m3[3][3] = {
        {3.0f, 0.0f, 2.0f},
        {2.0f, 0.0f, -2.0f},
        {0.0f, 1.0f, 1.0f}};

    float det3 = Determinant3x3(m3); // Expected: 3*0*1 + 0*-2*0 + 2*2*1 - 2*0*0 - 0*0*1 - 3*-2*1 = 3*0 + 0 + 4 - 0 - 0 + 6 = 10.
    DM_ASSERT(IsZero(det3 - 10.0f));

    float inv3[3][3];
    DM_ASSERT(TryInverse3x3(m3, inv3));

    // === 4x4 ===
    float m4[4][4] = {
        {1, 0, 0, 0},
        {0, 2, 0, 0},
        {0, 0, 3, 0},
        {0, 0, 0, 4}};

    float det4 = Determinant4x4(m4); // Since diagonal: 1*2*3*4 = 24
    DM_ASSERT(IsZero(det4 - 24.0f));

    float inv4[4][4];
    DM_ASSERT(TryInverse4x4(m4, inv4));
}

int main()
{
    using Clock = std::chrono::high_resolution_clock;
    auto start  = Clock::now();

    TestUtils_Lerp();
    TestUtils_Abs();
    TestUtils_MinMax();
    TestUtils_Clamp();
    TestUtils_Sqrt();
    TestUtils_IsZero();
	// NEWER TESTS.
	TestUtils_FloorCeilRound();
	TestUtils_DegRad();
	TestUtils_WrapPi();
	TestUtils_Sign();
	TestUtils_Trigonometry();
	TestUtils_DeterminantAndInverse();

    auto                                      end     = Clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    std::cout << "[Test Utils] Passed. Time: " << elapsed.count() << "ms\n";

    return 0;
}

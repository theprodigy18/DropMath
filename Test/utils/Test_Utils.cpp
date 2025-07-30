#include <DropMath.h>

#include <chrono>
#include <iostream>

using namespace DropMath;

// Testing Lerp<T>.
void TestUtils_Lerp()
{
    float lf = Lerp(10.0f, 20.0f, 0.5f);
    assert(IsZero(lf - 15.0f));

    double ld = Lerp(1.0, 3.0, 0.25);
    assert(IsZero(ld - 1.5));

    int li = Lerp(10, 20, 0.3f);
    assert(li == 13); // Integer truncation.
}

// Testing Abs overloads.
void TestUtils_Abs()
{
    assert(Abs(-3.5f) == 3.5f);
    assert(Abs(2.0f) == 2.0f);

    assert(Abs(-1.25) == 1.25);
    assert(Abs(0.5) == 0.5);

    assert(Abs(-7) == 7);
    assert(Abs(9) == 9);
}

// Testing Min<T> and Max<T>.
void TestUtils_MinMax()
{
    assert(Min(4, 7) == 4);
    assert(Max(4, 7) == 7);

    assert(Min(4.5f, 1.5f) == 1.5f);
    assert(Max(4.5, 10.0) == 10.0);
}

// Testing Clamp<T>.
void TestUtils_Clamp()
{
    assert(Clamp(5, 1, 10) == 5);
    assert(Clamp(-1, 0, 4) == 0);
    assert(Clamp(11, 0, 10) == 10);

    assert(IsZero(Clamp(0.5f, 0.0f, 1.0f) - 0.5f));
    assert(IsZero(Clamp(-0.5f, 0.0f, 1.0f) - 0.0f));
    assert(IsZero(Clamp(1.5f, 0.0f, 1.0f) - 1.0f));
}

// Testing Sqrt.
void TestUtils_Sqrt()
{
    assert(IsZero(Sqrt(4.0f) - 2.0f));
    assert(IsZero(Sqrt(9.0) - 3.0));
}

// Testing IsZero.
void TestUtils_IsZero()
{
    assert(IsZero(0.0000001f));
    assert(IsZero(-0.00000005f));
    assert(!IsZero(0.001f));

    assert(IsZero(0.0000000000001));
    assert(!IsZero(0.001));
}

// NEWER TESTS.

// Testing Floor, Ceil, Round.
void TestUtils_FloorCeilRound()
{
    assert(Floor(2.9f) == 2);
    assert(Floor(-2.1f) == -3);

    assert(Floor(3.8) == 3);
    assert(Floor(-3.2) == -4);

    assert(Ceil(2.1f) == 3);
    assert(Ceil(-2.9f) == -2);

    assert(Ceil(3.2) == 4);
    assert(Ceil(-3.8) == -3);

    assert(Round(2.4f) == 2);
    assert(Round(2.6f) == 3);
    assert(Round(-2.4f) == -2);
    assert(Round(-2.6f) == -3);

    assert(Round(2.5) == 3);
    assert(Round(-2.5) == -3);
}

// Testing radians <-> degrees conversion.
void TestUtils_DegRad()
{
    assert(IsZero(ToRadians(180.0f) - F::PI));
    assert(IsZero(ToRadians(90.0) - D::HALF_PI));

    assert(IsZero(ToDegrees(F::PI) - 180.0f));
    assert(IsZero(ToDegrees(D::HALF_PI) - 90.0));
}

// Testing WrapPi
void TestUtils_WrapPi()
{
    assert(IsZero(WrapPi(F::PI * 3.0f) + F::PI));
    assert(IsZero(WrapPi(-F::PI * 3.0f) + F::PI));

    assert(IsZero(WrapPi(D::PI * 3.0) + D::PI));
    assert(IsZero(WrapPi(-D::PI * 3.0) + D::PI));
}

// Testing Sign
void TestUtils_Sign()
{
    assert(Sign(5.0f) == 1);
    assert(Sign(-3.0f) == -1);
    assert(Sign(0.0f) == 0);

    assert(Sign(5.0) == 1);
    assert(Sign(-3.0) == -1);
    assert(Sign(0.0) == 0);

    assert(Sign(10) == 1);
    assert(Sign(-7) == -1);
    assert(Sign(0) == 0);
}

// Testing Sin, Cos, Tan.
void TestUtils_Trigonometry()
{
    assert(IsZero(Sin(0.0f)));
    assert(IsZero(Cos(F::HALF_PI)));
    assert(IsZero(Tan(0.0f)));

    assert(IsZero(Sin(0.0)));
    assert(IsZero(Cos(D::HALF_PI)));
    assert(IsZero(Tan(0.0)));
}

// Testing Determinant and Inverse.
void TestUtils_DeterminantAndInverse()
{
    // === 2x2 ===
    float m2[2][2] = {
        {4.0f, 7.0f},
        {2.0f, 6.0f}};

    float expectedDet2 = 4.0f * 6.0f - 7.0f * 2.0f; // = 10.0f
    assert(IsZero(Determinant2x2(m2) - expectedDet2));

    float inv2[2][2];
    assert(TryInverse2x2(m2, inv2));
    // Optional: test specific value or just assert determinant is not zero

    // === 3x3 ===
    float m3[3][3] = {
        {3.0f, 0.0f, 2.0f},
        {2.0f, 0.0f, -2.0f},
        {0.0f, 1.0f, 1.0f}};

    float det3 = Determinant3x3(m3); // Expected: 3*0*1 + 0*-2*0 + 2*2*1 - 2*0*0 - 0*0*1 - 3*-2*1 = 3*0 + 0 + 4 - 0 - 0 + 6 = 10.
    assert(IsZero(det3 - 10.0f));

    float inv3[3][3];
    assert(TryInverse3x3(m3, inv3));

    // === 4x4 ===
    float m4[4][4] = {
        {1, 0, 0, 0},
        {0, 2, 0, 0},
        {0, 0, 3, 0},
        {0, 0, 0, 4}};

    float det4 = Determinant4x4(m4); // Since diagonal: 1*2*3*4 = 24
    assert(IsZero(det4 - 24.0f));

    float inv4[4][4];
    assert(TryInverse4x4(m4, inv4));
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

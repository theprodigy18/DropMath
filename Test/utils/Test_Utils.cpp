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
    assert(AbsF(-3.5f) == 3.5f);
    assert(AbsF(2.0f) == 2.0f);

    assert(AbsD(-1.25) == 1.25);
    assert(AbsD(0.5) == 0.5);

    assert(AbsI(-7) == 7);
    assert(AbsI(9) == 9);
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
    assert(IsZero(SqrtF(4.0f) - 2.0f));
    assert(IsZero(Sqrt(9.0) - 3.0));
}

// Testing IsZero.
void TestUtils_IsZero()
{
    assert(IsZero(0.0000001f));
    assert(IsZero(-0.00000005f));
    assert(!IsZero(0.001f));

    assert(IsZero(0.0000001));
    assert(!IsZero(0.001));
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

    auto                                      end     = Clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    std::cout << "[Test Utils] Passed. Time: " << elapsed.count() << "ms\n";

    return 0;
}

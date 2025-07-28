#include <DropMath.h>

#include <chrono>
#include <iostream>

using namespace DropMath;

// Testing all constructors.
void TestVec2_Constructors()
{
    Vec2 v1;
    assert(v1.x == 0.0f && v1.y == 0.0f);

    Vec2 v2(1.0f, 2.0f);
    assert(v2.x == 1.0f && v2.y == 2.0f);
}

// Testing all operators.
void TestVec2_Operators()
{
    Vec2 a(3.0f, 4.0f);
    Vec2 b(1.0f, 2.0f);

    Vec2 add = a + b;
    assert(add == Vec2(4.0f, 6.0f));

    Vec2 sub = a - b;
    assert(sub == Vec2(2.0f, 2.0f));

    Vec2 mul = a * 2.0f;
    assert(mul == Vec2(6.0f, 8.0f));

    Vec2 div = a / 2.0f;
    assert(div == Vec2(1.5f, 2.0f));

    assert(a == Vec2(3.0f, 4.0f));
    assert(a != b);
}

// Testing length and length squared.
void TestVec2_Length()
{
    Vec2 v(3.0f, 4.0f);
    assert(fabs(v.Length() - 5.0f) < DM_EPSILON);
    assert(fabs(v.LengthSquared() - 25.0f) < DM_EPSILON);
}

// Testing normalize.
void TestVec2_Normalize()
{
    Vec2 v(3.0f, 4.0f);
    v.Normalize();
    assert(fabs(v.Length() - 1.0f) < DM_EPSILON);
}

// Testing dot product.
void TestVec2_Dot()
{
    Vec2  a(1.0f, 0.0f);
    Vec2  b(0.0f, 1.0f);
    float expected = 1 * 0 + 0 * 1;
    float dot      = Vec2::Dot(a, b);
    assert(fabs(dot - expected) < DM_EPSILON);
}

// Testing lerp.
void TestVec2_Lerp()
{
    Vec2 a(1.0f, 2.0f);
    Vec2 b(4.0f, 5.0f);
    Vec2 mid = Vec2::Lerp(a, b, 0.5f);
    assert(mid == Vec2(2.5f, 3.5f));
}

// Testing all helper definition functions.
void TestVec2_StaticDefinitions()
{
    assert(Vec2::Zero() == Vec2(0.0f, 0.0f));
    assert(Vec2::One() == Vec2(1.0f, 1.0f));
    assert(Vec2::Left() == Vec2(-1.0f, 0.0f));
    assert(Vec2::Right() == Vec2(1.0f, 0.0f));
    assert(Vec2::Up() == Vec2(0.0f, 1.0f));
    assert(Vec2::Down() == Vec2(0.0f, -1.0f));
}

int main()
{
    using Clock = std::chrono::high_resolution_clock;
    auto start  = Clock::now();

    TestVec2_Constructors();
    TestVec2_Operators();
    TestVec2_Length();
    TestVec2_Normalize();
    TestVec2_Dot();
    TestVec2_Lerp();
    TestVec2_StaticDefinitions();

    auto                                      end     = Clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    std::cout << "[Test Vec2] Passed. Time: " << elapsed.count() << " ms\n";

    return 0;
}

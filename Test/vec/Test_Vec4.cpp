#include <DropMath.h>

#include <chrono>
#include <iostream>

using namespace DropMath;

// Testing all constructors.
void TestVec4_Constructors()
{
    Vec4 v1;
    assert(v1.x == 0.0f && v1.y == 0.0f && v1.z == 0.0f && v1.w == 0.0f);

    for (int i = 0; i < 4; i++)
        ;

    Vec4 v2(1.0f, 2.0f, 3.0f, 4.0f);
    assert(v2.x == 1.0f && v2.y == 2.0f && v2.z == 3.0f && v2.w == 4.0f);

    Vec3 v3d(5.0f, 6.0f, 7.0f);
    Vec4 v3(v3d, 8.0f);
    assert(v3.x == 5.0f && v3.y == 6.0f && v3.z == 7.0f && v3.w == 8.0f);

    Vec2 v2d(9.0f, 10.0f);
    Vec4 v4(v2d, 11.0f, 12.0f);
    assert(v4.x == 9.0f && v4.y == 10.0f && v4.z == 11.0f && v4.w == 12.0f);
}

// Testing all operators.
void TestVec4_Operators()
{
    Vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4 b(5.0f, 6.0f, 7.0f, 8.0f);

    Vec4 add = a + b;
    assert(add == Vec4(6.0f, 8.0f, 10.0f, 12.0f));

    Vec4 sub = b - a;
    assert(sub == Vec4(4.0f, 4.0f, 4.0f, 4.0f));

    Vec4 mul = a * 2.0f;
    assert(mul == Vec4(2.0f, 4.0f, 6.0f, 8.0f));

    Vec4 div = b / 2.0f;
    assert(div == Vec4(2.5f, 3.0f, 3.5f, 4.0f));

    assert(a == Vec4(1.0f, 2.0f, 3.0f, 4.0f));
    assert(a != b);
}

// Testing length and length squared.
void TestVec4_Length()
{
    Vec4 v(2.0f, 0.0f, 0.0f, 0.0f);
    assert(fabs(v.Length() - 2.0f) < DM_EPSILON);
    assert(fabs(v.LengthSquared() - 4.0f) < DM_EPSILON);
}

// Testing normalize.
void TestVec4_Normalize()
{
    Vec4 v(3.0f, 0.0f, 4.0f, 0.0f);
    v.Normalize();
    assert(fabs(v.Length() - 1.0f) < DM_EPSILON);
}

// Testing dot product.
void TestVec4_Dot()
{
    Vec4  a(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4  b(2.0f, 3.0f, 4.0f, 5.0f);
    float expected = 1 * 2 + 2 * 3 + 3 * 4 + 4 * 5;
    float dot      = Vec4::Dot(a, b);
    assert(fabs(dot - expected) < DM_EPSILON);
}

// Testing lerp.
void TestVec4_Lerp()
{
    Vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4 b(5.0f, 6.0f, 7.0f, 8.0f);
    Vec4 mid = Vec4::Lerp(a, b, 0.5f);
    assert(mid == Vec4(3.0f, 4.0f, 5.0f, 6.0f));
}

// Testing all helper definition functions.
void TestVec4_StaticDefinitions()
{
    assert(Vec4::Zero() == Vec4(0.0f, 0.0f, 0.0f, 0.0f));
    assert(Vec4::One() == Vec4(1.0f, 1.0f, 1.0f, 1.0f));
}

int main()
{
    using Clock = std::chrono::high_resolution_clock;
    auto start  = Clock::now();

    TestVec4_Constructors();
    TestVec4_Operators();
    TestVec4_Length();
    TestVec4_Normalize();
    TestVec4_Dot();
    TestVec4_Lerp();
    TestVec4_StaticDefinitions();

    auto                                      end     = Clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    std::cout << "[Test Vec4] Passed. Time: " << elapsed.count() << " ms\n";

    return 0;
}

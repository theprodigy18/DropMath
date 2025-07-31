#include <DropMath.h>

#include <chrono>
#include <iostream>

using namespace DropMath;

// Testing all constructors.
void TestVec2_Constructors()
{
    Vec2 v1;
    DM_ASSERT(v1.x == 0.0f && v1.y == 0.0f);

    Vec2 v2(1.0f, 2.0f);
    DM_ASSERT(v2.x == 1.0f && v2.y == 2.0f);
}

// Testing all operators.
void TestVec2_Operators()
{
    Vec2 a(3.0f, 4.0f);
    Vec2 b(1.0f, 2.0f);

    Vec2 add = a + b;
    DM_ASSERT(add == Vec2(4.0f, 6.0f));

    Vec2 sub = a - b;
    DM_ASSERT(sub == Vec2(2.0f, 2.0f));

    Vec2 mul = a * 2.0f;
    DM_ASSERT(mul == Vec2(6.0f, 8.0f));

    Vec2 div = a / 2.0f;
    DM_ASSERT(div == Vec2(1.5f, 2.0f));

    DM_ASSERT(a == Vec2(3.0f, 4.0f));
    DM_ASSERT(a != b);
}

// Testing length and length squared.
void TestVec2_Length()
{
    Vec2 v(3.0f, 4.0f);
    DM_ASSERT(IsZero(v.Length() - 5.0f));
    DM_ASSERT(IsZero(v.LengthSquared() - 25.0f));
}

// Testing normalize.
void TestVec2_Normalize()
{
    Vec2 v(3.0f, 4.0f);
    v.Normalize();
    DM_ASSERT(IsZero(v.Length() - 1.0f));
}

// Testing dot product.
void TestVec2_Dot()
{
    Vec2  a(1.0f, 0.0f);
    Vec2  b(0.0f, 1.0f);
    float expected = 1 * 0 + 0 * 1;
    float dot      = Vec2::Dot(a, b);
    DM_ASSERT(IsZero(dot - expected));
}

// Testing lerp.
void TestVec2_Lerp()
{
    Vec2 a(1.0f, 2.0f);
    Vec2 b(4.0f, 5.0f);
    Vec2 mid = Vec2::Lerp(a, b, 0.5f);
    DM_ASSERT(mid == Vec2(2.5f, 3.5f));
}

// Testing all helper definition functions.
void TestVec2_StaticDefinitions()
{
    DM_ASSERT(Vec2::Zero() == Vec2(0.0f, 0.0f));
    DM_ASSERT(Vec2::One() == Vec2(1.0f, 1.0f));
    DM_ASSERT(Vec2::Left() == Vec2(-1.0f, 0.0f));
    DM_ASSERT(Vec2::Right() == Vec2(1.0f, 0.0f));
    DM_ASSERT(Vec2::Up() == Vec2(0.0f, 1.0f));
    DM_ASSERT(Vec2::Down() == Vec2(0.0f, -1.0f));
}

// NEWER TESTS.

// Testing indexing operator.
void TestVec2_Indexing()
{
    Vec2 v(5.0f, 9.0f);
    DM_ASSERT(v[0] == 5.0f);
    DM_ASSERT(v[1] == 9.0f);

    v[0] = 2.0f;
    v[1] = 3.0f;
    DM_ASSERT(v.x == 2.0f);
    DM_ASSERT(v.y == 3.0f);

    // Test out of bounds (debug only).
    // float f = v[2]; // Uncomment this to test DM_ASSERTion fail in debug.
}

// Testing data pointer(vector as array of float).
void TestVec2_DataPointer()
{
    Vec2         v(7.0f, 8.0f);
    const float* d = v.Data();
    DM_ASSERT(IsZero(d[0] - 7.0f));
    DM_ASSERT(IsZero(d[1] - 8.0f));

    float* dp = v.Data();
    dp[0]     = 10.0f;
    dp[1]     = 11.0f;
    DM_ASSERT(v.x == 10.0f);
    DM_ASSERT(v.y == 11.0f);
}

// Testing storing vector as array of float.
void TestVec2_Store()
{
    Vec2  v(1.5f, 2.5f);
    float out[2];
    v.Store(out);
    DM_ASSERT(IsZero(out[0] - 1.5f));
    DM_ASSERT(IsZero(out[1] - 2.5f));
}

// Testing normalize zero.
void TestVec2_NormalizeZero()
{
    Vec2 v(0.0f, 0.0f);
    v.Normalize();                 // Should not crash / divide by zero.
    DM_ASSERT(v == Vec2(0.0f, 0.0f)); // Define behavior: normalize zero == zero.
}

// Testing chained operations.
void TestVec2_ChainedOps()
{
    Vec2 a(1.0f, 2.0f);
    Vec2  b(2.0f, 4.0f);
    Vec2  result = (a + b) * 2.0f - b;
    DM_ASSERT(result == Vec2(4.0f, 8.0f));
}

// Testing union alias.
void TestVec2_UnionAlias()
{
    Vec2 v;
    v.array[0] = 8.0f;
    v.array[1] = 12.0f;
    DM_ASSERT(v.x == 8.0f);
    DM_ASSERT(v.y == 12.0f);
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
	// NEWER TESTS.
	TestVec2_Indexing();
	TestVec2_DataPointer();
	TestVec2_Store();
	TestVec2_NormalizeZero();
	TestVec2_ChainedOps();
	TestVec2_UnionAlias();

    auto                                      end     = Clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    std::cout << "[Test Vec2] Passed. Time: " << elapsed.count() << " ms\n";

    return 0;
}

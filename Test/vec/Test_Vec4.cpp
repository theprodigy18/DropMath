#include <DropMath.h>

#include <chrono>
#include <iostream>

using namespace DropMath;

// Testing all constructors.
void TestVec4_Constructors()
{
    Vec4 v1;
    DM_ASSERT(v1.x == 0.0f && v1.y == 0.0f && v1.z == 0.0f && v1.w == 0.0f);

    Vec4 v2(1.0f, 2.0f, 3.0f, 4.0f);
    DM_ASSERT(v2.x == 1.0f && v2.y == 2.0f && v2.z == 3.0f && v2.w == 4.0f);

    Vec3 v3d(5.0f, 6.0f, 7.0f);
    Vec4 v3(v3d, 8.0f);
    DM_ASSERT(v3.x == 5.0f && v3.y == 6.0f && v3.z == 7.0f && v3.w == 8.0f);

    Vec2 v2d(9.0f, 10.0f);
    Vec4 v4(v2d, 11.0f, 12.0f);
    DM_ASSERT(v4.x == 9.0f && v4.y == 10.0f && v4.z == 11.0f && v4.w == 12.0f);
}

// Testing all operators.
void TestVec4_Operators()
{
    Vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4 b(5.0f, 6.0f, 7.0f, 8.0f);

    Vec4 add = a + b;
    DM_ASSERT(add == Vec4(6.0f, 8.0f, 10.0f, 12.0f));

    Vec4 sub = b - a;
    DM_ASSERT(sub == Vec4(4.0f, 4.0f, 4.0f, 4.0f));

    Vec4 mul = a * 2.0f;
    DM_ASSERT(mul == Vec4(2.0f, 4.0f, 6.0f, 8.0f));

    Vec4 div = b / 2.0f;
    DM_ASSERT(div == Vec4(2.5f, 3.0f, 3.5f, 4.0f));

    DM_ASSERT(a == Vec4(1.0f, 2.0f, 3.0f, 4.0f));
    DM_ASSERT(a != b);
}

// Testing length and length squared.
void TestVec4_Length()
{
    Vec4 v(2.0f, 0.0f, 0.0f, 0.0f);
    DM_ASSERT(IsZero(v.Length() - 2.0f));
    DM_ASSERT(IsZero(v.LengthSquared() - 4.0f));
}

// Testing normalize.
void TestVec4_Normalize()
{
    Vec4 v(3.0f, 0.0f, 4.0f, 0.0f);
    v.Normalize();
    DM_ASSERT(IsZero(v.Length() - 1.0f));
}

// Testing dot product.
void TestVec4_Dot()
{
    Vec4  a(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4  b(2.0f, 3.0f, 4.0f, 5.0f);
    float expected = 1 * 2 + 2 * 3 + 3 * 4 + 4 * 5;
    float dot      = Vec4::Dot(a, b);
    DM_ASSERT(IsZero(dot - expected));
}

// Testing lerp.
void TestVec4_Lerp()
{
    Vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4 b(5.0f, 6.0f, 7.0f, 8.0f);
    Vec4 mid = Vec4::Lerp(a, b, 0.5f);
    DM_ASSERT(mid == Vec4(3.0f, 4.0f, 5.0f, 6.0f));
}

// Testing all helper definition functions.
void TestVec4_StaticDefinitions()
{
    DM_ASSERT(Vec4::Zero() == Vec4(0.0f, 0.0f, 0.0f, 0.0f));
    DM_ASSERT(Vec4::One() == Vec4(1.0f, 1.0f, 1.0f, 1.0f));
}

// NEWER TESTS.

// Testing indexing operator.
void TestVec4_Indexing()
{
    Vec4 v(10.0f, 20.0f, 30.0f, 40.0f);
    DM_ASSERT(v[0] == 10.0f);
    DM_ASSERT(v[1] == 20.0f);
    DM_ASSERT(v[2] == 30.0f);
    DM_ASSERT(v[3] == 40.0f);

    v[0] = 1.0f;
    v[1] = 2.0f;
    v[2] = 3.0f;
    v[3] = 4.0f;
    DM_ASSERT(v.x == 1.0f);
    DM_ASSERT(v.y == 2.0f);
    DM_ASSERT(v.z == 3.0f);
    DM_ASSERT(v.w == 4.0f);

    // Test out of bounds (debug only).
    // float f = v[4]; // Uncomment this to test DM_ASSERTion fail in debug.
}

// Testing data pointer(vector as array of float).
void TestVec4_DataPointer()
{
    Vec4         v(7.0f, 8.0f, 9.0f, 10.0f);
    const float* d = v.Data();
    DM_ASSERT(IsZero(d[0] - 7.0f));
    DM_ASSERT(IsZero(d[1] - 8.0f));
    DM_ASSERT(IsZero(d[2] - 9.0f));
    DM_ASSERT(IsZero(d[3] - 10.0f));

    float* dp = v.Data();
    dp[0]     = 1.0f;
    dp[1]     = 2.0f;
    dp[2]     = 3.0f;
    dp[3]     = 4.0f;
    DM_ASSERT(v.x == 1.0f);
    DM_ASSERT(v.y == 2.0f);
    DM_ASSERT(v.z == 3.0f);
    DM_ASSERT(v.w == 4.0f);
}

// Testing storing vector as array of float.
void TestVec4_Store()
{
    Vec4  v(1.0f, 2.0f, 3.0f, 4.0f);
    float out[4];
    v.Store(out);
    DM_ASSERT(out[0] == 1.0f);
    DM_ASSERT(out[1] == 2.0f);
    DM_ASSERT(out[2] == 3.0f);
    DM_ASSERT(out[3] == 4.0f);
}

// Testing normalize zero.
void TestVec4_NormalizeZero()
{
    Vec4 v(0.0f, 0.0f, 0.0f, 0.0f);
    v.Normalize();                       // Should not crash / divide by zero.
    DM_ASSERT(v == Vec4(0.0f, 0.0f, 0.0f, 0.0f)); // Define behavior: normalize zero == zero.
}

// Testing chained operations.
void TestVec4_ChainedOps()
{
    Vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4 b(5.0f, 6.0f, 7.0f, 8.0f);
    Vec4 result = (a + b) * 2.0f - a;
    DM_ASSERT(result == Vec4(11.0f, 14.0f, 17.0f, 20.0f));
}

// Testing union alias.
void TestVec4_UnionAlias()
{
    Vec4 v;
    v.array[0] = 11.0f;
    v.array[1] = 22.0f;
    v.array[2] = 33.0f;
    v.array[3] = 44.0f;
    DM_ASSERT(v.x == 11.0f);
    DM_ASSERT(v.y == 22.0f);
    DM_ASSERT(v.z == 33.0f);
    DM_ASSERT(v.w == 44.0f);
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
	// NEWER TESTS.
	TestVec4_Indexing();
	TestVec4_DataPointer();
	TestVec4_Store();
	TestVec4_NormalizeZero();
	TestVec4_ChainedOps();
	TestVec4_UnionAlias();

    auto                                      end     = Clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    std::cout << "[Test Vec4] Passed. Time: " << elapsed.count() << " ms\n";

    return 0;
}

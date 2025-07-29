#include <DropMath.h>

#include <chrono>
#include <iostream>

using namespace DropMath;

// Testing all constructors.
void TestVec3_Constructors()
{
    Vec3 v1;
    assert(v1.x == 0.0f && v1.y == 0.0f && v1.z == 0.0f);

    Vec3 v2(1.0f, 2.0f, 3.0f);
    assert(v2.x == 1.0f && v2.y == 2.0f && v2.z == 3.0f);

    Vec2 v2d(5.0f, 6.0f);
    Vec3 v3(v2d, 7.0f);
    assert(v3 == Vec3(5.0f, 6.0f, 7.0f));
}

// Testing all operators.
void TestVec3_Operators()
{
    Vec3 a(1.0f, 2.0f, 3.0f);
    Vec3 b(4.0f, 5.0f, 6.0f);

    Vec3 add = a + b;
    assert(add == Vec3(5.0f, 7.0f, 9.0f));

    Vec3 sub = b - a;
    assert(sub == Vec3(3.0f, 3.0f, 3.0f));

    Vec3 mul = a * 2.0f;
    assert(mul == Vec3(2.0f, 4.0f, 6.0f));

    Vec3 div = b / 2.0f;
    assert(div == Vec3(2.0f, 2.5f, 3.0f));

    assert(a == Vec3(1.0f, 2.0f, 3.0f));
    assert(a != b);

    Vec3 addV2 = a + Vec2(4.0f, 5.0f);
    assert(addV2 == Vec3(5.0f, 7.0f, 3.0f));

    Vec3 subV2 = b - Vec2(4.0f, 5.0f);
    assert(subV2 == Vec3(0.0f, 0.0f, 6.0f));
}

// Testing length and length squared.
void TestVec3_Length()
{
    Vec3 v(3.0f, 4.0f, 12.0f);
    assert(IsZero(v.Length() - 13.0f));
    assert(IsZero(v.LengthSquared() - 169.0f));
}

// Testing normalize.
void TestVec3_Normalize()
{
    Vec3 v(2.0f, 0.0f, 0.0f);
    v.Normalize();
    assert(IsZero(v.Length() - 1.0f));
}

// Testing dot cross product.
void TestVec3_DotCross()
{
    Vec3  a(1.0f, 0.0f, 0.0f);
    Vec3  b(0.0f, 1.0f, 0.0f);
    float expected = 1 * 0 + 0 * 1 + 0 * 0;
    float dot      = Vec3::Dot(a, b);
    assert(IsZero(dot - expected));

    Vec3 cross = Vec3::Cross(a, b);
    assert(cross == Vec3(0.0f, 0.0f, 1.0f));
}

// Testing lerp.
void TestVec3_Lerp()
{
    Vec3 a(1.0f, 2.0f, 3.0f);
    Vec3 b(4.0f, 5.0f, 6.0f);
    Vec3 mid = Vec3::Lerp(a, b, 0.5f);
    assert(mid == Vec3(2.5f, 3.5f, 4.5f));
}

// Testing all helper definition functions.
void TestVec3_StaticDefinitions()
{
    assert(Vec3::Zero() == Vec3(0.0f, 0.0f, 0.0f));
    assert(Vec3::One() == Vec3(1.0f, 1.0f, 1.0f));
    assert(Vec3::Up() == Vec3(0.0f, 1.0f, 0.0f));
    assert(Vec3::Down() == Vec3(0.0f, -1.0f, 0.0f));
    assert(Vec3::Left() == Vec3(-1.0f, 0.0f, 0.0f));
    assert(Vec3::Right() == Vec3(1.0f, 0.0f, 0.0f));
    assert(Vec3::Forward() == Vec3(0.0f, 0.0f, 1.0f));
    assert(Vec3::Back() == Vec3(0.0f, 0.0f, -1.0f));
}

// NEWER TESTS.

// Testing indexing operator.
void TestVec3_Indexing()
{
    Vec3 v(10.0f, 20.0f, 30.0f);
    assert(v[0] == 10.0f);
    assert(v[1] == 20.0f);
    assert(v[2] == 30.0f);

    v[0] = 1.0f;
    v[1] = 2.0f;
    v[2] = 3.0f;
    assert(v.x == 1.0f);
    assert(v.y == 2.0f);
    assert(v.z == 3.0f);

    // Test out of bounds (debug only).
    // float f = v[3]; // Uncomment this to test assertion fail in debug.
}

// Testing data pointer(vector as array of float).
void TestVec3_DataPointer()
{
    Vec3         v(7.0f, 8.0f, 9.0f);
    const float* d = v.Data();
    assert(IsZero(d[0] - 7.0f));
    assert(IsZero(d[1] - 8.0f));
    assert(IsZero(d[2] - 9.0f));

    float* dp = v.Data();
    dp[0]     = 1.0f;
    dp[1]     = 2.0f;
    dp[2]     = 3.0f;
    assert(v.x == 1.0f);
    assert(v.y == 2.0f);
    assert(v.z == 3.0f);
}

// Testing storing vector as array of float.
void TestVec3_Store()
{
    Vec3  v(1.0f, 2.0f, 3.0f);
    float out[3];
    v.Store(out);
    assert(out[0] == 1.0f);
    assert(out[1] == 2.0f);
    assert(out[2] == 3.0f);
}

// Testing normalize zero.
void TestVec3_NormalizeZero()
{
    Vec3 v(0.0f, 0.0f, 0.0f);
    v.Normalize();                       // Should not crash / divide by zero.
    assert(v == Vec3(0.0f, 0.0f, 0.0f)); // Define behavior: normalize zero == zero.
}

// Testing chained operations.
void TestVec3_ChainedOps()
{
    Vec3 a(1.0f, 2.0f, 3.0f);
    Vec3 b(4.0f, 5.0f, 6.0f);
    Vec3 result = (a + b) * 2.0f - a;
    assert(result == Vec3(9.0f, 12.0f, 15.0f));
}

// Testing union alias.
void TestVec3_UnionAlias()
{
    Vec3 v;
    v.array[0] = 11.0f;
    v.array[1] = 22.0f;
    v.array[2] = 33.0f;
    assert(v.x == 11.0f);
    assert(v.y == 22.0f);
    assert(v.z == 33.0f);
}

int main()
{
    using Clock = std::chrono::high_resolution_clock;
    auto start  = Clock::now();

    TestVec3_Constructors();
    TestVec3_Operators();
    TestVec3_Length();
    TestVec3_Normalize();
    TestVec3_DotCross();
    TestVec3_Lerp();
    TestVec3_StaticDefinitions();
	// NEWER TESTS.
	TestVec3_Indexing();
	TestVec3_DataPointer();
	TestVec3_Store();
	TestVec3_NormalizeZero();
	TestVec3_ChainedOps();
	TestVec3_UnionAlias();

    auto                                      end     = Clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    std::cout << "[Test Vec3] Passed. Time: " << elapsed.count() << " ms\n";

    return 0;
}
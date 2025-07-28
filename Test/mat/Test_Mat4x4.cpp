#include <DropMath.h>

#include <chrono>
#include <iostream>

using namespace DropMath;

// Testing constructor and identity definition.
void TestMat4x4_ConstructAndIdentity()
{
    Mat4x4 identity = Mat4x4::Identity();
    Vec4   row0     = identity[0];
    Vec4   row1     = identity[1];
    Vec4   row2     = identity[2];
    Vec4   row3     = identity[3];

    assert(row0 == Vec4(1.0f, 0.0f, 0.0f, 0.0f));
    assert(row1 == Vec4(0.0f, 1.0f, 0.0f, 0.0f));
    assert(row2 == Vec4(0.0f, 0.0f, 1.0f, 0.0f));
    assert(row3 == Vec4(0.0f, 0.0f, 0.0f, 1.0f));

    Mat4x4 m = Mat4x4(row0, row1, row2, row3);
    assert(m[0] == identity[0]);
    assert(m[1] == identity[1]);
    assert(m[2] == identity[2]);
    assert(m[3] == identity[3]);
}

// Testing mul operator with Vec4 that returns Vec4.
void TestMat4x4_MultiplyVec4()
{
    Mat4x4 identity = Mat4x4::Identity();
    Vec4   v(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4   result = identity * v;
    assert(result == v);
}

// Testing mul operator with Mat4x4 that returns another Mat4x4.
void TestMat4x4_MultiplyMat4x4()
{
    Mat4x4 m1 = Mat4x4::Identity();
    Mat4x4 m2(
        Vec4(1.0f, 2.0f, 3.0f, 4.0f),
        Vec4(5.0f, 6.0f, 7.0f, 8.0f),
        Vec4(9.0f, 10.0f, 11.0f, 12.0f),
        Vec4(13.0f, 14.0f, 15.0f, 16.0f));

    Mat4x4 result = m1 * m2;

    for (int i = 0; i < 4; ++i)
        assert(result[i] == m2[i]);
}

// Testing transpose.
void TestMat4x4_Transpose()
{
    Mat4x4 m(
        Vec4(1.0f, 2.0f, 3.0f, 4.0f),
        Vec4(5.0f, 6.0f, 7.0f, 8.0f),
        Vec4(9.0f, 10.0f, 11.0f, 12.0f),
        Vec4(13.0f, 14.0f, 15.0f, 16.0f));

    Mat4x4 t = m.Transposed();

    assert(t[0] == Vec4(1.0f, 5.0f, 9.0f, 13.0f));
    assert(t[1] == Vec4(2.0f, 6.0f, 10.0f, 14.0f));
    assert(t[2] == Vec4(3.0f, 7.0f, 11.0f, 15.0f));
    assert(t[3] == Vec4(4.0f, 8.0f, 12.0f, 16.0f));
}

// Testing store Mat4x4 to float array.
void TestMat4x4_Store()
{
    Mat4x4 m(
        Vec4(1.0f, 2.0f, 3.0f, 4.0f),
        Vec4(5.0f, 6.0f, 7.0f, 8.0f),
        Vec4(9.0f, 10.0f, 11.0f, 12.0f),
        Vec4(13.0f, 14.0f, 15.0f, 16.0f));

    float rowMajor[16];
    float colMajor[16];

    m.Store(rowMajor, MATRIX_ALLIGNMENT_ROW_MAJOR);
    m.Store(colMajor, MATRIX_ALLIGNMENT_COLUMN_MAJOR);

    // Verify row-major.
    for (int i = 0; i < 16; ++i)
        assert(rowMajor[i] == (float) (i + 1));

    // Verify column-major.
    float expectedColMajor[16] = {
        1.0f, 5.0f, 9.0f, 13.0f,
        2.0f, 6.0f, 10.0f, 14.0f,
        3.0f, 7.0f, 11.0f, 15.0f,
        4.0f, 8.0f, 12.0f, 16.0f};
    for (int i = 0; i < 16; ++i)
        assert(colMajor[i] == expectedColMajor[i]);
}

int main()
{
    using Clock = std::chrono::high_resolution_clock;
    auto start  = Clock::now();

    TestMat4x4_ConstructAndIdentity();
    TestMat4x4_MultiplyVec4();
    TestMat4x4_MultiplyMat4x4();
    TestMat4x4_Transpose();
    TestMat4x4_Store();

    auto                                      end     = Clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    std::cout << "[Test Mat4x4] Passed. Time: " << elapsed.count() << "ms\n";

    return 0;
}
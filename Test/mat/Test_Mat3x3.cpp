#include <DropMath.h>

#include <chrono>
#include <iostream>

using namespace DropMath;

// Testing constructor and identity definition.
void TestMat3x3_ConstructAndIdentity()
{
    Mat3x3 identity = Mat3x3::Identity();
    Vec3   row0     = identity[0];
    Vec3   row1     = identity[1];
    Vec3   row2     = identity[2];

    assert(row0 == Vec3(1.0f, 0.0f, 0.0f));
    assert(row1 == Vec3(0.0f, 1.0f, 0.0f));
    assert(row2 == Vec3(0.0f, 0.0f, 1.0f));

    Mat3x3 m = Mat3x3(row0, row1, row2);
    assert(m[0] == identity[0]);
    assert(m[1] == identity[1]);
    assert(m[2] == identity[2]);
}

// Testing mul operator with Vec3 that returns Vec3.
void TestMat3x3_MultiplyVec3()
{
    Mat3x3 identity = Mat3x3::Identity();
    Vec3   v(1.0f, 2.0f, 3.0f);
    Vec3   result = identity * v;
    assert(result == v);
}

// Testing mul operator with Mat3x3 that returns another Mat3x3.
void TestMat3x3_MultiplyMat3x3()
{
    Mat3x3 m1 = Mat3x3::Identity();
    Mat3x3 m2(
        Vec3(1.0f, 2.0f, 3.0f),
        Vec3(4.0f, 5.0f, 6.0f),
        Vec3(7.0f, 8.0f, 9.0f));

    Mat3x3 result = m1 * m2;

    for (int i = 0; i < 3; ++i)
        assert(result[i] == m2[i]);
}

// Testing transpose.
void TestMat3x3_Transpose()
{
    Mat3x3 m(
        Vec3(1.0f, 2.0f, 3.0f),
        Vec3(4.0f, 5.0f, 6.0f),
        Vec3(7.0f, 8.0f, 9.0f));

    Mat3x3 t = m.Transposed();

    assert(t[0] == Vec3(1.0f, 4.0f, 7.0f));
    assert(t[1] == Vec3(2.0f, 5.0f, 8.0f));
    assert(t[2] == Vec3(3.0f, 6.0f, 9.0f));

    // Test static version.
    Mat3x3 t2 = Mat3x3::Transpose(t);
    assert(t2[0] == m[0]);
    assert(t2[1] == m[1]);
    assert(t2[2] == m[2]);
}

// Testing store Mat4x4 to float array.
void TestMat3x3_Store()
{
    Mat3x3 m(
        Vec3(1.0f, 2.0f, 3.0f),
        Vec3(4.0f, 5.0f, 6.0f),
        Vec3(7.0f, 8.0f, 9.0f));

    float rowMajor[9];
    float colMajor[9];

    m.Store(rowMajor, MATRIX_ALLIGNMENT_ROW_MAJOR);
    m.Store(colMajor, MATRIX_ALLIGNMENT_COLUMN_MAJOR);

    // Verify row-major.
    for (int i = 0; i < 9; ++i)
        assert(rowMajor[i] == (float) (i + 1));

    // Verify column-major.
    float expectedColMajor[9] = {
        1.0f, 4.0f, 7.0f,
        2.0f, 5.0f, 8.0f,
        3.0f, 6.0f, 9.0f};
    for (int i = 0; i < 9; ++i)
        assert(colMajor[i] == expectedColMajor[i]);
}

// NEWER TESTS.

// Testing indexing and data layout.
void TestMat3x3_Indexing()
{
    Mat3x3 m(
        Vec3(1.0f, 2.0f, 3.0f),
        Vec3(4.0f, 5.0f, 6.0f),
        Vec3(7.0f, 8.0f, 9.0f));

    // Accessing using m[i][j].
    assert(m[0][0] == 1.0f);
    assert(m[1][1] == 5.0f);
    assert(m[2][2] == 9.0f);

    // Writing using operator[].
    m[0][0] = 99.0f;
    assert(m[0].x == 99.0f);
}

// Testing pointer access via Data().
void TestMat3x3_DataPointer()
{
    Mat3x3 m(
        Vec3(1.0f, 2.0f, 3.0f),
        Vec3(4.0f, 5.0f, 6.0f),
        Vec3(7.0f, 8.0f, 9.0f));

    const float* data = m.Data();
    for (int i = 0; i < 9; ++i)
        assert(data[i] == (float) (i + 1));

    // Modify via pointer.
    float* d = m.Data();
    d[0]     = 77.0f;
    assert(m[0].x == 77.0f);
}

// Testing individual store methods.
void TestMat3x3_StoreRowColMajor()
{
    Mat3x3 m(
        Vec3(1.0f, 2.0f, 3.0f),
        Vec3(4.0f, 5.0f, 6.0f),
        Vec3(7.0f, 8.0f, 9.0f));

    float row[9];
    float col[9];

    m.StoreRowMajor(row);
    m.StoreColMajor(col);

    for (int i = 0; i < 9; ++i)
        assert(row[i] == (float) (i + 1));

    float expectedColMajor[9] = {
        1.0f, 4.0f, 7.0f,
        2.0f, 5.0f, 8.0f,
        3.0f, 6.0f, 9.0f};
    for (int i = 0; i < 9; ++i)
        assert(col[i] == expectedColMajor[i]);
}

int main()
{
    using Clock = std::chrono::high_resolution_clock;
    auto start  = Clock::now();

    TestMat3x3_ConstructAndIdentity();
    TestMat3x3_MultiplyVec3();
    TestMat3x3_MultiplyMat3x3();
    TestMat3x3_Transpose();
    TestMat3x3_Store();
    // NEWER TESTS.
    TestMat3x3_Indexing();
    TestMat3x3_DataPointer();
    TestMat3x3_StoreRowColMajor();

    auto                                      end     = Clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    std::cout << "[Test Mat3x3] Passed. Time: " << elapsed.count() << "ms\n";

    return 0;
}
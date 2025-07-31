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

    DM_ASSERT(row0 == Vec3(1.0f, 0.0f, 0.0f));
    DM_ASSERT(row1 == Vec3(0.0f, 1.0f, 0.0f));
    DM_ASSERT(row2 == Vec3(0.0f, 0.0f, 1.0f));

    Mat3x3 m = Mat3x3(row0, row1, row2);
    DM_ASSERT(m[0] == identity[0]);
    DM_ASSERT(m[1] == identity[1]);
    DM_ASSERT(m[2] == identity[2]);
}

// Testing mul operator with Vec3 that returns Vec3.
void TestMat3x3_MultiplyVec3()
{
    Mat3x3 identity = Mat3x3::Identity();
    Vec3   v(1.0f, 2.0f, 3.0f);
    Vec3   result = identity * v;
    DM_ASSERT(result == v);
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
        DM_ASSERT(result[i] == m2[i]);
}

// Testing transpose.
void TestMat3x3_Transpose()
{
    Mat3x3 m(
        Vec3(1.0f, 2.0f, 3.0f),
        Vec3(4.0f, 5.0f, 6.0f),
        Vec3(7.0f, 8.0f, 9.0f));

    Mat3x3 t = m.Transposed();

    DM_ASSERT(t[0] == Vec3(1.0f, 4.0f, 7.0f));
    DM_ASSERT(t[1] == Vec3(2.0f, 5.0f, 8.0f));
    DM_ASSERT(t[2] == Vec3(3.0f, 6.0f, 9.0f));

    // Test static version.
    Mat3x3 t2 = Mat3x3::Transpose(t);
    DM_ASSERT(t2[0] == m[0]);
    DM_ASSERT(t2[1] == m[1]);
    DM_ASSERT(t2[2] == m[2]);
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
        DM_ASSERT(rowMajor[i] == (float) (i + 1));

    // Verify column-major.
    float expectedColMajor[9] = {
        1.0f, 4.0f, 7.0f,
        2.0f, 5.0f, 8.0f,
        3.0f, 6.0f, 9.0f};
    for (int i = 0; i < 9; ++i)
        DM_ASSERT(colMajor[i] == expectedColMajor[i]);
}

// Testing indexing and data layout.
void TestMat3x3_Indexing()
{
    Mat3x3 m(
        Vec3(1.0f, 2.0f, 3.0f),
        Vec3(4.0f, 5.0f, 6.0f),
        Vec3(7.0f, 8.0f, 9.0f));

    // Accessing using m[i][j].
    DM_ASSERT(m[0][0] == 1.0f);
    DM_ASSERT(m[1][1] == 5.0f);
    DM_ASSERT(m[2][2] == 9.0f);

    // Writing using operator[].
    m[0][0] = 99.0f;
    DM_ASSERT(m[0].x == 99.0f);
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
        DM_ASSERT(data[i] == (float) (i + 1));

    // Modify via pointer.
    float* d = m.Data();
    d[0]     = 77.0f;
    DM_ASSERT(m[0].x == 77.0f);
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
        DM_ASSERT(row[i] == (float) (i + 1));

    float expectedColMajor[9] = {
        1.0f, 4.0f, 7.0f,
        2.0f, 5.0f, 8.0f,
        3.0f, 6.0f, 9.0f};
    for (int i = 0; i < 9; ++i)
        DM_ASSERT(col[i] == expectedColMajor[i]);
}

// NEWER TESTS.

// Testing Determinant computation.
void TestMat3x3_Determinant()
{
    Mat3x3 m(
        Vec3(6.0f, 1.0f, 1.0f),
        Vec3(4.0f, -2.0f, 5.0f),
        Vec3(2.0f, 8.0f, 7.0f));

    float det = m.Determinant();
    DM_ASSERT(IsZero(det - (-306.0f)));
}

// Testing Inverse and Matrix * Inverse == Identity.
void TestMat3x3_Inverse()
{
    Mat3x3 m(
        Vec3(3.0f, 0.0f, 2.0f),
        Vec3(2.0f, 0.0f, -2.0f),
        Vec3(0.0f, 1.0f, 1.0f));

    Mat3x3 inv = m.Inverse();
    Mat3x3 id  = m * inv;

    // Identity matrix check.
    DM_ASSERT(IsZero(id[0][0] - 1.0f));
    DM_ASSERT(IsZero(id[0][1] - 0.0f));
    DM_ASSERT(IsZero(id[0][2] - 0.0f));

    DM_ASSERT(IsZero(id[1][0] - 0.0f));
    DM_ASSERT(IsZero(id[1][1] - 1.0f));
    DM_ASSERT(IsZero(id[1][2] - 0.0f));

    DM_ASSERT(IsZero(id[2][0] - 0.0f));
    DM_ASSERT(IsZero(id[2][1] - 0.0f));
    DM_ASSERT(IsZero(id[2][2] - 1.0f));
}

// Testing TryInverse with success and failure cases.
void TestMat3x3_TryInverse()
{
    Mat3x3 m(
        Vec3(3.0f, 0.0f, 2.0f),
        Vec3(2.0f, 0.0f, -2.0f),
        Vec3(0.0f, 1.0f, 1.0f));

    Mat3x3 out;
    bool   success = Mat3x3::TryInverse(m, out);
    DM_ASSERT(success);

    Mat3x3 id = m * out;
    DM_ASSERT(IsZero(id[0][0] - 1.0f));
    DM_ASSERT(IsZero(id[0][1] - 0.0f));
    DM_ASSERT(IsZero(id[0][2] - 0.0f));
    DM_ASSERT(IsZero(id[1][0] - 0.0f));
    DM_ASSERT(IsZero(id[1][1] - 1.0f));
    DM_ASSERT(IsZero(id[1][2] - 0.0f));
    DM_ASSERT(IsZero(id[2][0] - 0.0f));
    DM_ASSERT(IsZero(id[2][1] - 0.0f));
    DM_ASSERT(IsZero(id[2][2] - 1.0f));

    // Singular matrix (det = 0), second row is multiple of the first.
    Mat3x3 singular(
        Vec3(1.0f, 2.0f, 3.0f),
        Vec3(2.0f, 4.0f, 6.0f),
        Vec3(7.0f, 8.0f, 9.0f));

    success = Mat3x3::TryInverse(singular, out);
    DM_ASSERT(!success);
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
    TestMat3x3_Indexing();
    TestMat3x3_DataPointer();
    TestMat3x3_StoreRowColMajor();
    // NEWER TESTS.
	TestMat3x3_Determinant();
	TestMat3x3_Inverse();
	TestMat3x3_TryInverse();

    auto                                      end     = Clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    std::cout << "[Test Mat3x3] Passed. Time: " << elapsed.count() << "ms\n";

    return 0;
}
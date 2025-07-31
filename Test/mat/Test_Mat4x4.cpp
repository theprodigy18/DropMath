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

    DM_ASSERT(row0 == Vec4(1.0f, 0.0f, 0.0f, 0.0f));
    DM_ASSERT(row1 == Vec4(0.0f, 1.0f, 0.0f, 0.0f));
    DM_ASSERT(row2 == Vec4(0.0f, 0.0f, 1.0f, 0.0f));
    DM_ASSERT(row3 == Vec4(0.0f, 0.0f, 0.0f, 1.0f));

    Mat4x4 m = Mat4x4(row0, row1, row2, row3);
    DM_ASSERT(m[0] == identity[0]);
    DM_ASSERT(m[1] == identity[1]);
    DM_ASSERT(m[2] == identity[2]);
    DM_ASSERT(m[3] == identity[3]);
}

// Testing mul operator with Vec4 that returns Vec4.
void TestMat4x4_MultiplyVec4()
{
    Mat4x4 identity = Mat4x4::Identity();
    Vec4   v(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4   result = identity * v;
    DM_ASSERT(result == v);
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
        DM_ASSERT(result[i] == m2[i]);
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

    DM_ASSERT(t[0] == Vec4(1.0f, 5.0f, 9.0f, 13.0f));
    DM_ASSERT(t[1] == Vec4(2.0f, 6.0f, 10.0f, 14.0f));
    DM_ASSERT(t[2] == Vec4(3.0f, 7.0f, 11.0f, 15.0f));
    DM_ASSERT(t[3] == Vec4(4.0f, 8.0f, 12.0f, 16.0f));

	// Test static version.
	Mat4x4 t2 = Mat4x4::Transpose(t);
    DM_ASSERT(t2[0] == m[0]);
	DM_ASSERT(t2[1] == m[1]);
	DM_ASSERT(t2[2] == m[2]);
	DM_ASSERT(t2[3] == m[3]);
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
        DM_ASSERT(rowMajor[i] == (float) (i + 1));

    // Verify column-major.
    float expectedColMajor[16] = {
        1.0f, 5.0f, 9.0f, 13.0f,
        2.0f, 6.0f, 10.0f, 14.0f,
        3.0f, 7.0f, 11.0f, 15.0f,
        4.0f, 8.0f, 12.0f, 16.0f};
    for (int i = 0; i < 16; ++i)
        DM_ASSERT(colMajor[i] == expectedColMajor[i]);
}

// Testing indexing and data layout.
void TestMat4x4_Indexing()
{
    Mat4x4 m(
        Vec4(1.0f, 2.0f, 3.0f, 4.0f),
        Vec4(5.0f, 6.0f, 7.0f, 8.0f),
        Vec4(9.0f, 10.0f, 11.0f, 12.0f),
        Vec4(13.0f, 14.0f, 15.0f, 16.0f));

    // Accessing using m[i][j].
    DM_ASSERT(m[0][0] == 1.0f);
    DM_ASSERT(m[1][1] == 6.0f);
    DM_ASSERT(m[2][2] == 11.0f);
    DM_ASSERT(m[3][3] == 16.0f);

    // Writing using operator[].
    m[0][0] = 100.0f;
    DM_ASSERT(m[0].x == 100.0f);
}

// Testing pointer access via Data().
void TestMat4x4_DataPointer()
{
    Mat4x4 m(
        Vec4(1.0f, 2.0f, 3.0f, 4.0f),
        Vec4(5.0f, 6.0f, 7.0f, 8.0f),
        Vec4(9.0f, 10.0f, 11.0f, 12.0f),
        Vec4(13.0f, 14.0f, 15.0f, 16.0f));

    const float* data = m.Data();
    for (int i = 0; i < 16; ++i)
    {
        DM_ASSERT(data[i] == (float) (i + 1));
    }

    // Modify via pointer.
    float* d = m.Data();
    d[0]     = 99.0f;
    DM_ASSERT(m[0].x == 99.0f);
}

// Testing individual store methods.
void TestMat4x4_StoreRowColMajor()
{
    Mat4x4 m(
        Vec4(1.0f, 2.0f, 3.0f, 4.0f),
        Vec4(5.0f, 6.0f, 7.0f, 8.0f),
        Vec4(9.0f, 10.0f, 11.0f, 12.0f),
        Vec4(13.0f, 14.0f, 15.0f, 16.0f));

    float row[16];
    float col[16];

    m.StoreRowMajor(row);
    m.StoreColMajor(col);

    for (int i = 0; i < 16; ++i)
    {
        DM_ASSERT(row[i] == (float) (i + 1));
    }

    float expectedColMajor[16] = {
        1.0f, 5.0f, 9.0f, 13.0f,
        2.0f, 6.0f, 10.0f, 14.0f,
        3.0f, 7.0f, 11.0f, 15.0f,
        4.0f, 8.0f, 12.0f, 16.0f};
    for (int i = 0; i < 16; ++i)
        DM_ASSERT(col[i] == expectedColMajor[i]);
}

// NEWER TESTS.

// Testing Determinant computation.
void TestMat4x4_Determinant()
{
    Mat4x4 m(
        Vec4(1.0f, 2.0f, 3.0f, 4.0f),
        Vec4(5.0f, 6.0f, 7.0f, 8.0f),
        Vec4(9.0f, 10.0f, 11.0f, 12.0f),
        Vec4(13.0f, 14.0f, 15.0f, 16.0f));

    float det = m.Determinant();
    DM_ASSERT(IsZero(det)); // Known singular matrix.
}

// Testing Inverse and Matrix * Inverse == Identity.
void TestMat4x4_Inverse()
{
    Mat4x4 m(
        Vec4(5.0f, 7.0f, 9.0f, 10.0f),
        Vec4(2.0f, 3.0f, 3.0f, 8.0f),
        Vec4(8.0f, 10.0f, 2.0f, 3.0f),
        Vec4(3.0f, 3.0f, 4.0f, 8.0f));

    Mat4x4 inv = m.Inverse();
    Mat4x4 id  = m * inv;

    // Identity matrix check.
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            DM_ASSERT(IsZero(id[i][j] - (i == j ? 1.0f : 0.0f)));
}

// Testing TryInverse with success and failure cases.
void TestMat4x4_TryInverse()
{
    Mat4x4 m(
        Vec4(5.0f, 7.0f, 9.0f, 10.0f),
        Vec4(2.0f, 3.0f, 3.0f, 8.0f),
        Vec4(8.0f, 10.0f, 2.0f, 3.0f),
        Vec4(3.0f, 3.0f, 4.0f, 8.0f));

    Mat4x4 out;
    bool   success = Mat4x4::TryInverse(m, out);
    DM_ASSERT(success);

    Mat4x4 id = m * out;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            DM_ASSERT(IsZero(id[i][j] - (i == j ? 1.0f : 0.0f)));

    // Singular matrix test.
    Mat4x4 singular(
        Vec4(1.0f, 2.0f, 3.0f, 4.0f),
        Vec4(5.0f, 6.0f, 7.0f, 8.0f),
        Vec4(9.0f, 10.0f, 11.0f, 12.0f),
        Vec4(13.0f, 14.0f, 15.0f, 16.0f));

    success = Mat4x4::TryInverse(singular, out);
    DM_ASSERT(!success);
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
	TestMat4x4_Indexing();
	TestMat4x4_DataPointer();
	TestMat4x4_StoreRowColMajor();
	// NEWER TESTS.
	TestMat4x4_Determinant();
	TestMat4x4_Inverse();
	TestMat4x4_TryInverse();

    auto                                      end     = Clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    std::cout << "[Test Mat4x4] Passed. Time: " << elapsed.count() << "ms\n";

    return 0;
}
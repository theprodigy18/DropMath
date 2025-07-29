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

	// Test static version.
	Mat4x4 t2 = Mat4x4::Transpose(t);
    assert(t2[0] == m[0]);
	assert(t2[1] == m[1]);
	assert(t2[2] == m[2]);
	assert(t2[3] == m[3]);
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

// NEWER TESTS.

// Testing indexing and data layout.
void TestMat4x4_Indexing()
{
    Mat4x4 m(
        Vec4(1.0f, 2.0f, 3.0f, 4.0f),
        Vec4(5.0f, 6.0f, 7.0f, 8.0f),
        Vec4(9.0f, 10.0f, 11.0f, 12.0f),
        Vec4(13.0f, 14.0f, 15.0f, 16.0f));

    // Accessing using m[i][j].
    assert(m[0][0] == 1.0f);
    assert(m[1][1] == 6.0f);
    assert(m[2][2] == 11.0f);
    assert(m[3][3] == 16.0f);

    // Writing using operator[].
    m[0][0] = 100.0f;
    assert(m[0].x == 100.0f);
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
        assert(data[i] == (float) (i + 1));
    }

    // Modify via pointer.
    float* d = m.Data();
    d[0]     = 99.0f;
    assert(m[0].x == 99.0f);
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
        assert(row[i] == (float) (i + 1));
    }

    float expectedColMajor[16] = {
        1.0f, 5.0f, 9.0f, 13.0f,
        2.0f, 6.0f, 10.0f, 14.0f,
        3.0f, 7.0f, 11.0f, 15.0f,
        4.0f, 8.0f, 12.0f, 16.0f};
    for (int i = 0; i < 16; ++i)
        assert(col[i] == expectedColMajor[i]);
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
	// NEWER TESTS.
	TestMat4x4_Indexing();
	TestMat4x4_DataPointer();
	TestMat4x4_StoreRowColMajor();

    auto                                      end     = Clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    std::cout << "[Test Mat4x4] Passed. Time: " << elapsed.count() << "ms\n";

    return 0;
}
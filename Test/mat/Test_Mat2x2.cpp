#include <DropMath.h>

#include <chrono>
#include <iostream>

using namespace DropMath;

// Testing constructor and identity definition.
void TestMat2x2_ConstructAndIdentity()
{
    Mat2x2 identity = Mat2x2::Identity();
    Vec2   row0     = identity[0];
    Vec2   row1     = identity[1];

    assert(row0 == Vec2(1.0f, 0.0f));
    assert(row1 == Vec2(0.0f, 1.0f));

    Mat2x2 m = Mat2x2(row0, row1);
    assert(m[0] == identity[0]);
    assert(m[1] == identity[1]);
}

// Testing mul operator with Vec2 that returns Vec2.
void TestMat2x2_MultiplyVec2()
{
    Mat2x2 identity = Mat2x2::Identity();
    Vec2   v(3.0f, 4.0f);
    Vec2   result = identity * v;
    assert(result == v);
}

// Testing mul operator with Mat2x2 that returns another Mat2x2.
void TestMat2x2_MultiplyMat2x2()
{
    Mat2x2 m1 = Mat2x2::Identity();
    Mat2x2 m2(
        Vec2(1.0f, 2.0f),
        Vec2(3.0f, 4.0f));

    Mat2x2 result = m1 * m2;

    for (int i = 0; i < 2; ++i)
        assert(result[i] == m2[i]);
}

// Testing transpose.
void TestMat2x2_Transpose()
{
    Mat2x2 m(
        Vec2(1.0f, 2.0f),
        Vec2(3.0f, 4.0f));

    Mat2x2 t = m.Transposed();

    assert(t[0] == Vec2(1.0f, 3.0f));
    assert(t[1] == Vec2(2.0f, 4.0f));

    // Test static version.
    Mat2x2 t2 = Mat2x2::Transpose(t);
    assert(t2[0] == m[0]);
    assert(t2[1] == m[1]);
}

// Testing store Mat2x2 to float array.
void TestMat2x2_Store()
{
    Mat2x2 m(
        Vec2(1.0f, 2.0f),
        Vec2(3.0f, 4.0f));

    float rowMajor[4];
    float colMajor[4];

    m.Store(rowMajor, MATRIX_ALLIGNMENT_ROW_MAJOR);
    m.Store(colMajor, MATRIX_ALLIGNMENT_COLUMN_MAJOR);

    // Verify row-major.
    for (int i = 0; i < 4; ++i)
        assert(rowMajor[i] == (float) (i + 1));

    // Verify column-major.
    float expectedColMajor[4] = {
        1.0f, 3.0f,
        2.0f, 4.0f};
    for (int i = 0; i < 4; ++i)
        assert(colMajor[i] == expectedColMajor[i]);
}

// Testing indexing and data layout.
void TestMat2x2_Indexing()
{
    Mat2x2 m(
        Vec2(1.0f, 2.0f),
        Vec2(3.0f, 4.0f));

    // Accessing using m[i][j].
    assert(m[0][0] == 1.0f);
    assert(m[1][1] == 4.0f);

    // Writing using operator[].
    m[0][0] = 88.0f;
    assert(m[0].x == 88.0f);
}

// Testing pointer access via Data().
void TestMat2x2_DataPointer()
{
    Mat2x2 m(
        Vec2(1.0f, 2.0f),
        Vec2(3.0f, 4.0f));

    const float* data = m.Data();
    for (int i = 0; i < 4; ++i)
        assert(data[i] == (float) (i + 1));

    // Modify via pointer.
    float* d = m.Data();
    d[0]     = 77.0f;
    assert(m[0].x == 77.0f);
}

// Testing individual store methods.
void TestMat2x2_StoreRowColMajor()
{
    Mat2x2 m(
        Vec2(1.0f, 2.0f),
        Vec2(3.0f, 4.0f));

    float row[4];
    float col[4];

    m.StoreRowMajor(row);
    m.StoreColMajor(col);

    for (int i = 0; i < 4; ++i)
        assert(row[i] == (float) (i + 1));

    float expectedColMajor[4] = {
        1.0f, 3.0f,
        2.0f, 4.0f};
    for (int i = 0; i < 4; ++i)
        assert(col[i] == expectedColMajor[i]);
}

// NEWER TESTS.

// Testing Determinant computation.
void TestMat2x2_Determinant()
{
    Mat2x2 m(
        Vec2(4.0f, 7.0f),
        Vec2(2.0f, 6.0f));

    float det = m.Determinant();
    assert(IsZero(det - (4.0f * 6.0f - 7.0f * 2.0f)));
}

// Testing Inverse and Matrix * Inverse == Identity.
void TestMat2x2_Inverse()
{
    Mat2x2 m(
        Vec2(4.0f, 7.0f),
        Vec2(2.0f, 6.0f));

    Mat2x2 inv = m.Inverse();
    Mat2x2 id  = m * inv;

    // Identity matrix check.
    assert(IsZero(id[0][0] - 1.0f));
    assert(IsZero(id[0][1] - 0.0f));
    assert(IsZero(id[1][0] - 0.0f));
    assert(IsZero(id[1][1] - 1.0f));
}

// Testing TryInverse with success and failure cases.
void TestMat2x2_TryInverse()
{
    Mat2x2 m(
        Vec2(1.0f, 2.0f),
        Vec2(3.0f, 4.0f));

    Mat2x2 out;
    bool   success = Mat2x2::TryInverse(m, out);
    assert(success);

    Mat2x2 id = m * out;
    assert(IsZero(id[0][0] - 1.0f));
    assert(IsZero(id[0][1] - 0.0f));
    assert(IsZero(id[1][0] - 0.0f));
    assert(IsZero(id[1][1] - 1.0f));

    // Singular matrix (det = 0), first row is multiple of the second.
    Mat2x2 singular(
        Vec2(2.0f, 4.0f),
        Vec2(1.0f, 2.0f));

    success = Mat2x2::TryInverse(singular, out);
    assert(!success);
}


int main()
{
    using Clock = std::chrono::high_resolution_clock;
    auto start  = Clock::now();

    TestMat2x2_ConstructAndIdentity();
    TestMat2x2_MultiplyVec2();
    TestMat2x2_MultiplyMat2x2();
    TestMat2x2_Transpose();
    TestMat2x2_Store();
    TestMat2x2_Indexing();
    TestMat2x2_DataPointer();
    TestMat2x2_StoreRowColMajor();
    // NEWER TESTS.
	TestMat2x2_Determinant();
	TestMat2x2_Inverse();
	TestMat2x2_TryInverse();

    auto                                      end     = Clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    std::cout << "[Test Mat2x2] Passed. Time: " << elapsed.count() << "ms\n";

    return 0;
}

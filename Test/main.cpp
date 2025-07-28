
#include <chrono>
#include <iostream>

#include <DM_Vector.h>

using namespace DropMath;

void BenchmarkVec4_SIMD()
{
    using Clock = std::chrono::high_resolution_clock;
    Vec4  a(1, 2, 3, 4);
    Vec4  b(4, 3, 2, 1);
    Vec4  r(0, 0, 0, 0);
    float acc = 0.0f;

    auto start = Clock::now();
    for (int i = 0; i < 1'000'000; ++i)
    {
        r = a + b;
        r = r * 0.5f;
        r = r / 1.25f;
        r.Normalize();
        acc += r.Length();
        acc += r.LengthSquared();
        acc += Vec4::Dot(a, b);
        if (r == a) acc += 1;
        if (r != b) acc += 1;
        r = Vec4::Lerp(a, b, 0.25f);
    }
    auto end = Clock::now();

    std::chrono::duration<double, std::milli> ms = end - start;
    std::cout << "[SIMD Vec4] Time: " << ms.count() << " ms | Acc: " << acc << std::endl;
}

int main()
{
	BenchmarkVec4_SIMD();

	while (true);
	return 0;
}
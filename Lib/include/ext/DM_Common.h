#pragma once

#ifdef USE_SIMD
#include <smmintrin.h>

using float4 = __m128;
#endif // USE_SIMD

#include <math.h>
#include <assert.h>

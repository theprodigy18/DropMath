#pragma once

#ifdef USE_SIMD
#include <smmintrin.h>

#define XY_LANE_MASK 0b0011
#define XYZ_LANE_MASK 0b0111

using float4 = __m128;
#endif // USE_SIMD

#include <math.h>
#include <assert.h>

#define DM_EPSILON 1e-6

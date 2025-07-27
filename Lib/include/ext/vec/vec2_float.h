#pragma once

#include "../common.h"

#define XY_LANE_MASK 0b0011

typedef struct dm_vec2_float
{
    __m128 data;
} _vec2_float;

inline _vec2_float _vec2_create(float x, float y)
{
    __m128 data = _mm_set_ps(0, 0, y, x); // [x, y, 0, 0].
    return _vec2_float {data};
}

inline float _vec2_x(const _vec2_float* v)
{
    return _mm_cvtss_f32(v->data);
}
inline float _vec2_y(const _vec2_float* v)
{
    return _mm_cvtss_f32(_mm_shuffle_ps(v->data, v->data, _MM_SHUFFLE(0, 0, 0, 1)));
}

inline _vec2_float _vec2_set_x(const _vec2_float* v, float x)
{
    __m128 data_x = _mm_set_ss(x);
    __m128 data   = _mm_blend_ps(v->data, data_x, 0b0001);
    return _vec2_float {data};
}

inline _vec2_float _vec2_set_y(const _vec2_float* v, float y)
{
    __m128 data_y = _mm_set_ps1(y);
    __m128 data   = _mm_blend_ps(v->data, data_y, 0b0010);
    return _vec2_float {data};
}

inline _vec2_float _vec2_add(const _vec2_float* v1, const _vec2_float* v2)
{
    __m128 data = _mm_add_ps(v1->data, v2->data);
    return _vec2_float {data};
}

inline _vec2_float _vec2_sub(const _vec2_float* v1, const _vec2_float* v2)
{
    __m128 data = _mm_sub_ps(v1->data, v2->data);
    return _vec2_float {data};
}

inline _vec2_float _vec2_mul(const _vec2_float* v1, float s)
{
    __m128 data_s = _mm_set_ps1(s);
    __m128 data   = _mm_mul_ps(v1->data, data_s);
    return _vec2_float {data};
}

inline _vec2_float _vec2_div(const _vec2_float* v1, float s)
{
    __m128 data_s = _mm_set_ps1(s);
    __m128 data   = _mm_div_ps(v1->data, data_s);
    return _vec2_float {data};
}

inline float _vec2_dot(const _vec2_float* v1, const _vec2_float* v2)
{
    __m128 dot = _mm_dp_ps(v1->data, v2->data, 0b00110001);
    return _mm_cvtss_f32(dot);
}

inline bool _vec2_eq(const _vec2_float* v1, const _vec2_float* v2)
{
    __m128 delta     = _mm_sub_ps(v1->data, v2->data);
    __m128 abs_delta = _mm_andnot_ps(_mm_set_ps1(-0.0f), delta); // Abs, change the sign bit to 0(31st bit).
    __m128 eps       = _mm_set_ps1(EPSILON);
    __m128 cmp       = _mm_cmplt_ps(abs_delta, eps); // Compare if a[x] < b[x]. Then the result will be 0xFFFFFFFF for true and 0x00000000 for false.

    int mask = _mm_movemask_ps(cmp) & XY_LANE_MASK; // Check sign bit (31st bit) for each lane. if 0 then the mask will 0 also if 1 then the mask will 1. And doing & operator to just take x and y bit.
    return mask == XY_LANE_MASK;
}

inline bool _vec2_length(const _vec2_float* v)
{
    __m128 dot  = _mm_dp_ps(v->data, v->data, 0b00110001);
    __m128 sqrt = _mm_sqrt_ps(dot);
    return _mm_cvtss_f32(sqrt);
}
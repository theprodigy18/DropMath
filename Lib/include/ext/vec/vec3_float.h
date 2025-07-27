#pragma once

#include "../common.h"

#define XYZ_LANE_MASK 0b0111

typedef struct dm_vec3_float
{
    __m128 data;
} _vec3_float;

inline _vec3_float _vec3_create(float x, float y, float z)
{
    __m128 data = _mm_set_ps(0, z, y, x);
	return _vec3_float{data};
}

inline float _vec3_x(const _vec3_float* v)
{
	return _mm_cvtss_f32(v->data);
}

inline float _vec3_y(const _vec3_float* v)
{
    return _mm_cvtss_f32(_mm_shuffle_ps(v->data, v->data, _MM_SHUFFLE(0, 0, 0, 1)));
}

inline float _vec3_z(const _vec3_float* v)
{
	return _mm_cvtss_f32(_mm_shuffle_ps(v->data, v->data, _MM_SHUFFLE(0, 0, 0, 2)));
}

inline _vec3_float _vec3_set_x(const _vec3_float* v, float x)
{
    __m128 data_x = _mm_set_ss(x);
    __m128 data   = _mm_blend_ps(v->data, data_x, 0b0001);
	return _vec3_float{data};
}

inline _vec3_float _vec3_set_y(const _vec3_float* v, float y)
{
    __m128 data_y = _mm_set_ps1(y);
    __m128 data   = _mm_blend_ps(v->data, data_y, 0b0010);
    return _vec3_float {data};
}

inline _vec3_float _vec3_set_z(const _vec3_float* v, float z)
{
    __m128 data_z = _mm_set_ps1(z);
    __m128 data   = _mm_blend_ps(v->data, data_z, 0b0100);
    return _vec3_float {data};
}

inline _vec3_float _vec3_add(const _vec3_float* v1, const _vec3_float* v2)
{
	__m128 data = _mm_add_ps(v1->data, v2->data);
	return _vec3_float{data};
}

inline _vec3_float _vec3_sub(const _vec3_float* v1, const _vec3_float* v2)
{
    __m128 data = _mm_sub_ps(v1->data, v2->data);
    return _vec3_float {data};
}

inline _vec3_float _vec3_mul(const _vec3_float* v1, float s)
{
    __m128 data_s = _mm_set_ps1(s);
	__m128 data = _mm_mul_ps(v1->data, data_s);
	return _vec3_float{data};
}

inline _vec3_float _vec3_div(const _vec3_float* v1, float s)
{
	__m128 data_s = _mm_set_ps1(s);
	__m128 data = _mm_div_ps(v1->data, data_s);
	return _vec3_float{data};
}

inline float _vec3_dot(const _vec3_float* v1, const _vec3_float* v2)
{
    __m128 dot = _mm_dp_ps(v1->data, v2->data, 0b01110001);
    return _mm_cvtss_f32(dot);
}

inline float _vec3_length(const _vec3_float* v)
{
    __m128 dot = _mm_dp_ps(v->data, v->data, 0b01110001);
    __m128 sqrt = _mm_sqrt_ss(dot);
    return _mm_cvtss_f32(sqrt);
}

inline bool _vec3_eq(const _vec3_float* v1, const _vec3_float* v2)
{
    __m128 delta = _mm_sub_ps(v1->data, v2->data);
    __m128 abs_delta = _mm_andnot_ps(_mm_set_ps1(-0.0f), delta);
    __m128 eps       = _mm_set_ps1(EPSILON);
    __m128 cmp       = _mm_cmplt_ps(abs_delta, eps);
    int    mask      = _mm_movemask_ps(cmp) & XYZ_LANE_MASK;
    return mask == XYZ_LANE_MASK;
}


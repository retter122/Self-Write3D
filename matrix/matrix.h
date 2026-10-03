#pragma once

#include <stdint.h>


typedef struct {
    float elems[16];
} mat4x4;


void mat4x4_mat4x4_eadd(mat4x4* dst, const mat4x4* src);
void mat4x4_mat4x4_esub(mat4x4* dst, const mat4x4* src);
void mat4x4_mat4x4_emul(mat4x4* dst, const mat4x4 *src);
void mat4x4_mat4x4_ediv(mat4x4* dst, const mat4x4 *src);

void mat4x4_mat4x4_evadd(mat4x4* dst, const mat4x4 *src1, const mat4x4* src2);
void mat4x4_mat4x4_evsub(mat4x4* dst, const mat4x4* src1, const mat4x4* src2);
void mat4x4_mat4x4_evmul(mat4x4* dst, const mat4x4* src1, const mat4x4* src2);
void mat4x4_mat4x4_evdiv(mat4x4* dst, const mat4x4* src1, const mat4x4* src2);

void mat4x4_mat4x4_mmul(mat4x4 *dst, const mat4x4 *src);

void mat4x4_mat4x4_mvmul(mat4x4* dst, const mat4x4 *src1, const mat4x4* src2);

void mat4x4_scalar_add(mat4x4* dst, float src);
void mat4x4_scalar_sub(mat4x4* dst, float src);
void mat4x4_scalar_mul(mat4x4* dst, float src);
void mat4x4_scalar_div(mat4x4* dst, float src);

void mat4x4_scalar_vadd(mat4x4* dst, const mat4x4* src1, float src2);
void mat4x4_scalar_vsub(mat4x4* dst, const mat4x4* src1, float src2);
void mat4x4_scalar_vmul(mat4x4* dst, const mat4x4* src1, float src2);
void mat4x4_scalar_vdiv(mat4x4* dst, const mat4x4* src1, float src2);

void mat4x4_identity(mat4x4* dst);
void mat4x4_scale(mat4x4* dst, float x, float y, float z);

void mat4x4_rotate_x(mat4x4* dst, float angle);
void mat4x4_rotate_y(mat4x4* dst, float angle);
void mat4x4_rotate_z(mat4x4* dst, float angle);


typedef struct {
    float elems[4];
} mat1x4;


void mat1x4_mat1x4_eadd(mat1x4 *dst, const mat1x4 *src);
void mat1x4_mat1x4_esub(mat1x4 *dst, const mat1x4 *src);
void mat1x4_mat1x4_emul(mat1x4 *dst, const mat1x4 *src);
void mat1x4_mat1x4_ediv(mat1x4 *dst, const mat1x4 *src);

void mat1x4_mat1x4_evadd(mat1x4 *dst, const mat1x4 *src1, const mat1x4 *src2);
void mat1x4_mat1x4_evsub(mat1x4 *dst, const mat1x4 *src1, const mat1x4 *src2);
void mat1x4_mat1x4_evmul(mat1x4 *dst, const mat1x4 *src1, const mat1x4 *src2);
void mat1x4_mat1x4_evdiv(mat1x4 *dst, const mat1x4 *src1, const mat1x4 *src2);

void mat1x4_scalar_add(mat1x4 *dst, float src);
void mat1x4_scalar_sub(mat1x4 *dst, float src);
void mat1x4_scalar_mul(mat1x4 *dst, float src);
void mat1x4_scalar_div(mat1x4 *dst, float src);

void mat1x4_scalar_vadd(mat1x4 *dst, const mat1x4* src1, float src2);
void mat1x4_scalar_vsub(mat1x4 *dst, const mat1x4* src1, float src2);
void mat1x4_scalar_vmul(mat1x4 *dst, const mat1x4* src1, float src2);
void mat1x4_scalar_vdiv(mat1x4 *dst, const mat1x4* src1, float src2);

float mat1x4_mat1x4_dot(const mat1x4 *src1, const mat1x4 *src2);
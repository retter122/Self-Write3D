#include <stdint.h>
#include <math.h>

#include "./matrix.h"


void mat4x4_mat4x4_eadd(mat4x4* dst, const mat4x4* src) {
    for (uint32_t i = 0; i < 16; ++i) dst->elems[i] += src->elems[i];
}


void mat4x4_mat4x4_esub(mat4x4* dst, const mat4x4* src) {
    for (uint32_t i = 0; i < 16; ++i) dst->elems[i] += src->elems[i];
}


void mat4x4_mat4x4_emul(mat4x4* dst, const mat4x4* src) {
    for (uint32_t i = 0; i < 16; ++i) dst->elems[i] *= src->elems[i];
}


void mat4x4_mat4x4_ediv(mat4x4* dst, const mat4x4* src) {
    for (uint32_t i = 0; i < 16; ++i) dst->elems[i] /= src->elems[i];
}


void mat4x4_mat4x4_evadd(mat4x4* dst, const mat4x4 *src1, const mat4x4* src2) {
    for (uint32_t i = 0; i < 16; ++i) dst->elems[i] = src1->elems[i] + src2->elems[i];
}


void mat4x4_mat4x4_evsub(mat4x4* dst, const mat4x4 *src1, const mat4x4* src2) {
    for (uint32_t i = 0; i < 16; ++i) dst->elems[i] = src1->elems[i] - src2->elems[i];
}


void mat4x4_mat4x4_evmul(mat4x4* dst, const mat4x4 *src1, const mat4x4* src2) {
    for (uint32_t i = 0; i < 16; ++i) dst->elems[i] = src1->elems[i] * src2->elems[i];
}


void mat4x4_mat4x4_evdiv(mat4x4* dst, const mat4x4 *src1, const mat4x4* src2) {
    for (uint32_t i = 0; i < 16; ++i) dst->elems[i] = src1->elems[i] / src2->elems[i];
}


void mat4x4_mat4x4_mmul(mat4x4 *dst, const mat4x4 *src) {
    mat4x4 tmp = {
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
    };

    for (uint32_t i = 0; i < 4; ++i) {
        for (uint32_t j = 0; j < 4; ++j) {
            tmp.elems[i * 4 + j] = 
                dst->elems[i * 4] * src->elems[j] +
                dst->elems[i * 4 + 1] * src->elems[j + 4] +
                dst->elems[i * 4 + 2] * src->elems[j + 8] +
                dst->elems[i * 4 + 3] * src->elems[j + 12];
        }
    }

    for (uint32_t i = 0; i < 16; ++i) dst->elems[i] = tmp.elems[i];
}


void mat4x4_mat4x4_mvmul(mat4x4* dst, const mat4x4 *src1, const mat4x4* src2) {
    for (uint32_t i = 0; i < 16; ++i) dst->elems[i] = 0;

    for (uint32_t i = 0; i < 4; ++i) {
        for (uint32_t j = 0; j < 4; ++j) {
            dst->elems[i * 4 + j] = 
                src1->elems[i * 4] * src2->elems[j] + 
                src1->elems[i * 4 + 1] * src2->elems[j + 4] +
                src1->elems[i * 4 + 2] * src2->elems[j + 8] + 
                src1->elems[i * 4 + 3] * src2->elems[j + 12];
        }
    }
}


void mat4x4_scalar_sadd(mat4x4* dst, float src) {
    for (uint32_t i = 0; i < 16; ++i) dst->elems[i] += src;
}


void mat4x4_scalar_ssub(mat4x4* dst, float src) {
    for (uint32_t i = 0; i < 16; ++i) dst->elems[i] -= src;
}


void mat4x4_scalar_smul(mat4x4* dst, float src) {
    for (uint32_t i = 0; i < 16; ++i) dst->elems[i] *= src;
}


void mat4x4_scalar_sdiv(mat4x4* dst, float src) {
    for (uint32_t i = 0; i < 16; ++i) dst->elems[i] /= src;
}


void mat4x4_scalar_svadd(mat4x4* dst, const mat4x4* src1, float src2) {
    for (uint32_t i = 0; i < 16; ++i) dst->elems[i] = src1->elems[i] + src2;
}


void mat4x4_scalar_svsub(mat4x4* dst, const mat4x4* src1, float src2) {
    for (uint32_t i = 0; i < 16; ++i) dst->elems[i] = src1->elems[i] - src2;
}


void mat4x4_scalar_svmul(mat4x4* dst, const mat4x4* src1, float src2) {
    for (uint32_t i = 0; i < 16; ++i) dst->elems[i] = src1->elems[i] * src2;
}


void mat4x4_scalar_svdiv(mat4x4* dst, const mat4x4* src1, float src2) {
    for (uint32_t i = 0; i < 16; ++i) dst->elems[i] = src1->elems[i] / src2;
}


void mat4x4_identity(mat4x4* dst) {
    dst->elems[0] = 1, dst->elems[1] = 0, dst->elems[2] = 0, dst->elems[3] = 0;
    dst->elems[4] = 0, dst->elems[5] = 1, dst->elems[6] = 0, dst->elems[7] = 0;
    dst->elems[8] = 0, dst->elems[9] = 0, dst->elems[10] = 1, dst->elems[11] = 0;
    dst->elems[12] = 0, dst->elems[13] = 0, dst->elems[14] = 0, dst->elems[15] = 1;
}


void mat4x4_scale(mat4x4 *dst, float x, float y, float z) {
    dst->elems[0] = x, dst->elems[1] = 0, dst->elems[2] = 0, dst->elems[3] = 0;
    dst->elems[4] = 0, dst->elems[5] = y, dst->elems[6] = 0, dst->elems[7] = 0;
    dst->elems[8] = 0, dst->elems[9] = 0, dst->elems[10] = z, dst->elems[11] = 0;
    dst->elems[12] = 0, dst->elems[13] = 0, dst->elems[14] = 0, dst->elems[15] = 1;
}


void mat4x4_rotate_x(mat4x4 *dst, float angle) {
    dst->elems[0] = 1, dst->elems[1] = 0, dst->elems[2] = 0, dst->elems[3] = 0;
    dst->elems[4] = 0, dst->elems[5] = cosf(angle), dst->elems[6] = sinf(angle), dst->elems[7] = 0;
    dst->elems[8] = 0, dst->elems[9] = -sinf(angle), dst->elems[10] = cosf(angle), dst->elems[11] = 0;
    dst->elems[12] = 0, dst->elems[13] = 0, dst->elems[14] = 0, dst->elems[15] = 1;
}


void mat4x4_rotate_y(mat4x4 *dst, float angle) {
    dst->elems[0] = cosf(angle), dst->elems[1] = 0, dst->elems[2] = sinf(angle), dst->elems[3] = 0;
    dst->elems[4] = 0, dst->elems[5] = 1, dst->elems[6] = 0, dst->elems[7] = 0;
    dst->elems[8] = -sinf(angle), dst->elems[9] = 0, dst->elems[10] = cosf(angle), dst->elems[11] = 0;
    dst->elems[12] = 0, dst->elems[13] = 0, dst->elems[14] = 0, dst->elems[15] = 1;
}


void mat4x4_rotate_z(mat4x4 *dst, float angle) {
    dst->elems[0] = cosf(angle), dst->elems[1] = sinf(angle), dst->elems[2] = 0, dst->elems[3] = 0;
    dst->elems[4] = -sinf(angle), dst->elems[5] = cosf(angle), dst->elems[6] = 0, dst->elems[7] = 0;
    dst->elems[8] = 0, dst->elems[9] = 0, dst->elems[10] = 1, dst->elems[11] = 0;
    dst->elems[12] = 0, dst->elems[13] = 0, dst->elems[14] = 0, dst->elems[15] = 1;
}


void mat1x4_mat1x4_eadd(mat1x4 *dst, const mat1x4 *src) {
    dst->elems[0] += src->elems[0], dst->elems[1] += src->elems[1];
    dst->elems[2] += src->elems[2], dst->elems[3] += src->elems[3];
}


void mat1x4_mat1x4_esub(mat1x4 *dst, const mat1x4 *src) {
    dst->elems[0] -= src->elems[0], dst->elems[1] -= src->elems[1];
    dst->elems[2] -= src->elems[2], dst->elems[3] -= src->elems[3];
}


void mat1x4_mat1x4_emul(mat1x4 *dst, const mat1x4 *src) {
    dst->elems[0] *= src->elems[0], dst->elems[1] *= src->elems[1];
    dst->elems[2] *= src->elems[2], dst->elems[3] *= src->elems[3];
}


void mat1x4_mat1x4_ediv(mat1x4 *dst, const mat1x4 *src) {
    dst->elems[0] /= src->elems[0], dst->elems[1] /= src->elems[1];
    dst->elems[2] /= src->elems[2], dst->elems[3] /= src->elems[3];
}


void mat1x4_mat1x4_evadd(mat1x4 *dst, const mat1x4 *src1, const mat1x4 *src2) {
    dst->elems[0] = src1->elems[0] + src2->elems[0], dst->elems[1] = src1->elems[1] + src2->elems[1];
    dst->elems[2] = src1->elems[2] + src2->elems[2], dst->elems[3] = src1->elems[3] + src2->elems[3];
}


void mat1x4_mat1x4_evsub(mat1x4 *dst, const mat1x4 *src1, const mat1x4 *src2) {
    dst->elems[0] = src1->elems[0] - src2->elems[0], dst->elems[1] = src1->elems[1] - src2->elems[1];
    dst->elems[2] = src1->elems[2] - src2->elems[2], dst->elems[3] = src1->elems[3] - src2->elems[3];
}


void mat1x4_mat1x4_evmul(mat1x4 *dst, const mat1x4 *src1, const mat1x4 *src2) {
    dst->elems[0] = src1->elems[0] * src2->elems[0], dst->elems[1] = src1->elems[1] * src2->elems[1];
    dst->elems[2] = src1->elems[2] * src2->elems[2], dst->elems[3] = src1->elems[3] * src2->elems[3];
}


void mat1x4_mat1x4_evdiv(mat1x4 *dst, const mat1x4 *src1, const mat1x4 *src2) {
    dst->elems[0] = src1->elems[0] / src2->elems[0], dst->elems[1] = src1->elems[1] / src2->elems[1];
    dst->elems[2] = src1->elems[2] / src2->elems[2], dst->elems[3] = src1->elems[3] / src2->elems[3];
}


void mat1x4_scalar_add(mat1x4 *dst, float src) {
    dst->elems[0] += src, dst->elems[1] += src;
    dst->elems[2] += src, dst->elems[3] += src;
}


void mat1x4_scalar_sub(mat1x4 *dst, float src) {
    dst->elems[0] -= src, dst->elems[1] -= src;
    dst->elems[2] -= src, dst->elems[3] -= src;
}


void mat1x4_scalar_mul(mat1x4 *dst, float src) {
    dst->elems[0] *= src, dst->elems[1] *= src;
    dst->elems[2] *= src, dst->elems[3] *= src;
}


void mat1x4_scalar_div(mat1x4 *dst, float src) {
    dst->elems[0] /= src, dst->elems[1] /= src;
    dst->elems[2] /= src, dst->elems[3] /= src;
}


void mat1x4_scalar_vadd(mat1x4 *dst, const mat1x4* src1, float src2) {
    dst->elems[0] = src1->elems[0] + src2, dst->elems[1] = src1->elems[1] + src2;
    dst->elems[2] = src1->elems[2] + src2, dst->elems[3] = src1->elems[3] + src2;
}


void mat1x4_scalar_vsub(mat1x4 *dst, const mat1x4* src1, float src2) {
    dst->elems[0] = src1->elems[0] - src2, dst->elems[1] = src1->elems[1] - src2;
    dst->elems[2] = src1->elems[2] - src2, dst->elems[3] = src1->elems[3] - src2;
}


void mat1x4_scalar_vmul(mat1x4 *dst, const mat1x4* src1, float src2) {
    dst->elems[0] = src1->elems[0] * src2, dst->elems[1] = src1->elems[1] * src2;
    dst->elems[2] = src1->elems[2] * src2, dst->elems[3] = src1->elems[3] * src2;
}


void mat1x4_scalar_vdiv(mat1x4 *dst, const mat1x4* src1, float src2) {
    dst->elems[0] = src1->elems[0] / src2, dst->elems[1] = src1->elems[1] / src2;
    dst->elems[2] = src1->elems[2] / src2, dst->elems[3] = src1->elems[3] / src2;
}

float mat1x4_mat1x4_dot(const mat1x4 *src1, const mat1x4 *src2) {
    return src1->elems[0] * src2->elems[0] + src1->elems[1] * src2->elems[1] + src1->elems[2] * src2->elems[2] + src1->elems[3] * src2->elems[3];
}
#include <stdint.h>

#include "./polygon.h"


void translate_figure(polygon* input, uint32_t num, mat1x4 *translate) {
    for (uint32_t i = 0; i < num; ++i) {
        float *elems = input[i].vertex.elems;

        elems[0] += translate->elems[0], elems[1] += translate->elems[1], elems[2] += translate->elems[2], elems[3] += translate->elems[3];
        elems[4] += translate->elems[0], elems[5] += translate->elems[1], elems[6] += translate->elems[2], elems[7] += translate->elems[3];
        elems[8] += translate->elems[0], elems[9] += translate->elems[1], elems[10] += translate->elems[2], elems[11] += translate->elems[3];
        elems[12] += translate->elems[0], elems[13] += translate->elems[1], elems[14] += translate->elems[2], elems[15] += translate->elems[3];
    }
}


void transform_figure(polygon* input, uint32_t num, mat4x4 *transform) {
    mat1x4 position = { 0, 0, 0, 0 };
    
    for (uint32_t i = 0; i < num; ++i) {
        float *elems = input[i].vertex.elems;
        
        position.elems[0] += elems[0] + elems[4] + elems[8];
        position.elems[1] += elems[1] + elems[5] + elems[9];
        position.elems[2] += elems[2] + elems[6] + elems[10];
        position.elems[3] += elems[3] + elems[7] + elems[11];
    } mat1x4_scalar_div(&position, num * 3);

    for (uint32_t i = 0; i < num; ++i) {
        float *elems = input[i].vertex.elems;

        elems[0] -= position.elems[0], elems[1] -= position.elems[1], elems[2] -= position.elems[2], elems[3] -= position.elems[3];
        elems[4] -= position.elems[0], elems[5] -= position.elems[1], elems[6] -= position.elems[2], elems[7] -= position.elems[3];
        elems[8] -= position.elems[0], elems[9] -= position.elems[1], elems[10] -= position.elems[2], elems[11] -= position.elems[3];
    
        mat4x4_mat4x4_mmul(&input[i].vertex, transform);

        elems[0] += position.elems[0], elems[1] += position.elems[1], elems[2] += position.elems[2], elems[3] += position.elems[3];
        elems[4] += position.elems[0], elems[5] += position.elems[1], elems[6] += position.elems[2], elems[7] += position.elems[3];
        elems[8] += position.elems[0], elems[9] += position.elems[1], elems[10] += position.elems[2], elems[11] += position.elems[3];
    }
}
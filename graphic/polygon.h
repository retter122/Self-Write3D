#pragma once

#include <stdint.h>

#include "../matrix/matrix.h"


typedef struct {
    mat4x4 vertex;
    mat1x4 color1, color2, color3;
} polygon;


void translate_figure(polygon* input, uint32_t num, mat1x4 *translate);


void transform_figure(polygon* input, uint32_t num, mat4x4 *transform);
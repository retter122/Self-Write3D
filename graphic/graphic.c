#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

#include "./graphic.h"

#include "../matrix/matrix.h"


void clear_screen(graphic_state* dst, uint32_t color) {
    for (uint32_t i = 0; i < dst->width * dst->height; ++i) dst->pixels[i] = color;
}


void clear_color_buffer(thread_worker* dst, float r, float g, float b) {
    for (uint32_t i = 0; i < dst->screen->width * dst->screen->height; ++i) {
        dst->colors[i].elems[0] = r, dst->colors[i].elems[1] = g, dst->colors[i].elems[2] = b;
        dst->colors[i].elems[3] = -1;
    }
}


thread_worker* create_workers(uint32_t num, graphic_state* state) {
    thread_worker* unit = malloc(sizeof(thread_worker) * num);

    uint32_t screen_size = state->width * state->height;
    for (uint32_t i = 0; i < num; ++i) {
        unit[i].screen = state;
        unit[i].colors = malloc(sizeof(mat1x4) * screen_size);
    }

    return unit;
}


void resize_workers(thread_worker* unit, uint32_t num) {
    uint32_t screen_size = unit->screen->width * unit->screen->height;
    for (uint32_t i = 0; i < num; ++i) unit[i].colors = realloc(unit[i].colors, sizeof(mat1x4) * screen_size);
}


void worker_function(thread_worker *worker) {
    float coof_x = (float)worker->screen->width / 2.f / tanf(worker->screen->fov_x / 2.f);
    float coof_y = (float)worker->screen->height / 2.f / tanf(worker->screen->fov_y / 2.f);

    for (polygon* i = worker->start; i < worker->end; ++i) {
        polygon shader_out;
        worker->screen->vertex_shader(i, &shader_out, worker->screen->transform, worker->screen->translate);

        float aspect_1 = worker->screen->screen_dst / shader_out.vertex.elems[2];
        float aspect_2 = worker->screen->screen_dst / shader_out.vertex.elems[6];
        float aspect_3 = worker->screen->screen_dst / shader_out.vertex.elems[10];

        float x1 = shader_out.vertex.elems[0] * aspect_1, y1 = shader_out.vertex.elems[1] * aspect_1;
        float x2 = shader_out.vertex.elems[4] * aspect_2, y2 = shader_out.vertex.elems[5] * aspect_2;
        float x3 = shader_out.vertex.elems[8] * aspect_3, y3 = shader_out.vertex.elems[9] * aspect_3;

        int32_t x1i = x1 * coof_x + worker->screen->width / 2, y1i = y1 * coof_y + worker->screen->height / 2;
        int32_t x2i = x2 * coof_x + worker->screen->width / 2, y2i = y2 * coof_y + worker->screen->height / 2;
        int32_t x3i = x3 * coof_x + worker->screen->width / 2, y3i = y3 * coof_y + worker->screen->height / 2;

        int32_t sx = max(min(x1i, min(x2i, x3i)), 0), ex = min(max(x1i, max(x2i, x3i)), worker->screen->width);
        int32_t sy = max(min(y1i, min(y2i, y3i)), 0), ey = min(max(y1i, max(y2i, y3i)), worker->screen->height);

        int32_t a2 = -(y3i - y2i), a3 = -(y1i - y3i);
        int32_t b2 = x3i - x2i, b3 = x1i - x3i;
        int32_t c2 = -(a2 * x2i + b2 * y2i), c3 = -(a3 * x3i + b3 * y3i);

        float max_d1 = (float)abs(a2 * x1i + b2 * y1i + c2) / sqrtf(a2 * a2 + b2 * b2);
        float max_d2 = (float)abs(a3 * x2i + b3 * y2i + c3) / sqrtf(a3 * a3 + b3 * b3);
        
        for (int32_t u = sy; u < ey; ++u) {
            for (int32_t v = sx; v < ex; ++v) {
                int32_t d1 = ((u - y1i) * (x2i - x1i)) - ((v - x1i) * (y2i - y1i));
                int32_t d2 = ((u - y2i) * (x3i - x2i)) - ((v - x2i) * (y3i - y2i));
                int32_t d3 = ((u - y3i) * (x1i - x3i)) - ((v - x3i) * (y1i - y3i));

                if ((d1 <= 0 && d2 <= 0 && d3 <= 0) || (d1 >= 0 && d2 >= 0 && d3 >= 0)) {
                    mat1x4 *pixel = &(worker->colors[v + u * worker->screen->width]);

                    float p1_d = (float)abs(a2 * v + b2 * u + c2) / sqrtf(a2 * a2 + b2 * b2) / max_d1;
                    float p2_d = (float)abs(a3 * v + b3 * u + c3) / sqrtf(a3 * a3 + b3 * b3) / max_d2;
                    float p3_d = 1.f - p1_d - p2_d;

                    float depth = shader_out.vertex.elems[2] * p1_d + shader_out.vertex.elems[6] * p2_d + shader_out.vertex.elems[10] * p3_d;

                    if (depth >= worker->screen->screen_dst && (pixel->elems[3]) == -1 || pixel->elems[3] > depth) {
                        pixel->elems[0] = shader_out.color1.elems[0] * p1_d + shader_out.color2.elems[0] * p2_d + shader_out.color3.elems[0] * p3_d;
                        pixel->elems[1] = shader_out.color1.elems[1] * p1_d + shader_out.color2.elems[1] * p2_d + shader_out.color3.elems[1] * p3_d;
                        pixel->elems[2] = shader_out.color1.elems[2] * p1_d + shader_out.color2.elems[2] * p2_d + shader_out.color3.elems[2] * p3_d;
                        pixel->elems[3] = depth;
                    }
                }
            }
        }
    }
}


void vertex_processing(thread_worker* unit, uint32_t num, polygon* start, polygon* end) {
    while (start < end && num) {
        polygon* new_end = start + max((end - start) / num, 1);
        
        unit->start = start;
        unit->end = new_end;

        worker_function(unit);

        --num;
        ++unit;
        start = new_end;
    }
}


void pixel_processing(thread_worker* unit, uint32_t num) {
    for (uint32_t i = 0; i < unit->screen->width * unit->screen->height; ++i) {
        float min_dst = -1;
        uint32_t min_j = 0;
        
        for (uint32_t j = 0; j < num; ++j) {
            if (unit[j].colors[i].elems[3] >= unit->screen->screen_dst && (min_dst > unit[j].colors[i].elems[3] || min_dst == -1)) {
                min_j = j;
                min_dst = unit[j].colors[i].elems[3];
            }
        }

        if (min_dst != -1) {
            unit->screen->pixels[i] = unit->screen->pixel_shader(&unit[min_j].colors[i], 0, 0);
        }
    }
}


void def_vertex_shader(polygon* input, polygon* output, mat4x4 *transform, mat1x4 *translate) {
    memcpy(output, input, sizeof(polygon));

    mat4x4_mat4x4_mvmul(&output->vertex, &input->vertex, transform);
    translate_figure(output, 1, translate);
}


uint32_t def_pixel_shader(mat1x4* input, mat1x4* position, mat1x4* normal) {
    return FRGB_URGB(input->elems[0], input->elems[1], input->elems[2]);
}
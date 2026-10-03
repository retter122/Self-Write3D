#pragma once

#include <stdint.h>

#include "./polygon.h"

#include "../matrix/matrix.h"


#define FRGB_URGB(r, g, b) ((((uint32_t)(r * 255.f)) << 16) | (((uint32_t)(g * 255.f)) << 8) | ((uint32_t)(b * 255.f)))


typedef struct {
    float screen_dst;
    float fov_x, fov_y;

    uint32_t* pixels;
    uint32_t width, height;

    mat4x4 *transform;
    mat1x4 *translate;

    void (*vertex_shader)(polygon *input, polygon *output, mat4x4 *transform, mat1x4 *translate);
    uint32_t (*pixel_shader)(mat1x4* input, mat1x4* position, mat1x4* normal);
} graphic_state;


typedef struct {
    graphic_state *screen;

    mat1x4 *colors;

    polygon *start, *end;
} thread_worker;


void clear_screen(graphic_state* dst, uint32_t color);
void clear_color_buffer(thread_worker* dst, float r, float g, float b);


thread_worker* create_workers(uint32_t num, graphic_state* state);
void resize_workers(thread_worker* unit, uint32_t num);


void pixel_processing(thread_worker* unit, uint32_t num);
void vertex_processing(thread_worker* unit, uint32_t num, polygon* start, polygon* end);


void def_vertex_shader(polygon* input, polygon* output, mat4x4 *transform, mat1x4 *translate);
uint32_t def_pixel_shader(mat1x4* input, mat1x4* position, mat1x4* normal);

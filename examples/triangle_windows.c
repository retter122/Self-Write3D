#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <windows.h>

#include "../graphic/graphic.h"
#include "../graphic/polygon.h"
#include "../matrix/matrix.h"


// DEFAULT PARAMS

#define EPSILON 1e-5

#define DEF_WIDTH 800
#define DEF_HEIGHT 600

#define DEF_FOVX 2.f
#define DEF_FOVY DEF_FOVX

#define DEF_SCREEN_DST 1.f


// SCENE DATA

static polygon Triangle = {
    {
         0.0f,  0.4f, DEF_SCREEN_DST + EPSILON, 0.f,  // FIRST VERTEX
        -0.4f, -0.4f, DEF_SCREEN_DST + EPSILON, 0.f,  // SECOND VERTEX
         0.4f, -0.4f, DEF_SCREEN_DST + EPSILON, 0.f,  // THIRD VERTEX
         0.f, 0.f, 0.f, 0.f                           // JUST FILL RANDOM
    },

    { 1.f, 0.f, 0.f, 1.f },                           // FIRST VERTEX COLOR
    { 0.f, 1.f, 0.f, 1.f },                           // SECOND VERTEX COLOR
    { 0.f, 0.f, 1.f, 1.f },                           // THIRD VERTEX COLOR
};

static mat4x4 Transform = {
    1.f, 0.f, 0.f, 0.f,
    0.f, (float)DEF_WIDTH / (float)DEF_HEIGHT, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f
};

static mat1x4 Translate = { 0.f, 0.f, 0.f, 0.f };

static graphic_state GState = {
    DEF_SCREEN_DST,
    DEF_FOVX, DEF_FOVY,
    0,
    DEF_WIDTH, DEF_HEIGHT,
    &Transform, &Translate,
    def_vertex_shader, def_pixel_shader
};

static BITMAPINFO GBmi = { { sizeof(BITMAPINFOHEADER), DEF_WIDTH, DEF_HEIGHT, 1, 32, BI_RGB, 0, 0, 0, 0, 0 } };

static thread_worker *GWorkers = 0;
#define GWorkersNum 4


// WINDOW DATA

LRESULT CALLBACK WProc(HWND Hwnd, UINT Msg, WPARAM Wparam, LPARAM Lparam);

static WNDCLASSA WClass = { CS_HREDRAW | CS_VREDRAW, WProc, 0, 0, 0, 0, 0, 0, 0, "Triangle" };
static char WName[] = "Triangle";

static HWND WHandle;
static HDC Dc;

static MSG Message;


int main() {
    GState.pixels = malloc(sizeof(uint32_t) * DEF_WIDTH * DEF_HEIGHT);
    GWorkers = create_workers(GWorkersNum, &GState);

    if (!RegisterClassA(&WClass)) return 1;
    WHandle = CreateWindowExA(0, WClass.lpszClassName, WName, WS_OVERLAPPEDWINDOW, 0, 0, DEF_WIDTH, DEF_HEIGHT, 0, 0, 0, 0);
    Dc = GetDC(WHandle);

    ShowWindow(WHandle, SW_SHOWNORMAL);

    mat4x4 TransformFigure;
    mat4x4_rotate_z(&TransformFigure, 0.015f);

    while (1) {
        if (PeekMessageA(&Message, 0, 0, 0, PM_REMOVE)) {
            DispatchMessageA(&Message);

            if (Message.message == WM_QUIT) break;
        }

        transform_figure(&Triangle, 1, &TransformFigure);
    }

    return 0;
}


LRESULT CALLBACK WProc(HWND Hwnd, UINT Msg, WPARAM WParam, LPARAM LParam) {
    switch (Msg) {
        case(WM_DESTROY):
            PostQuitMessage(0);
            break;

        case(WM_SIZE):
            GState.width = LParam & 0xFFFF;
            GState.height = (LParam >> 16) & 0xFFFF;

            GBmi.bmiHeader.biWidth = GState.width;
            GBmi.bmiHeader.biHeight = GState.height;

            GState.pixels = realloc(GState.pixels, sizeof(uint32_t) * GState.width * GState.height);
            resize_workers(GWorkers, GWorkersNum);

            mat4x4_scale(&Transform, 1.f, (float)GState.width / (float)GState.height, 1.f);

            break;
        
        case(WM_PAINT):
            clear_screen(&GState, 0x00000000);
            for (uint32_t i = 0; i < GWorkersNum; ++i) clear_color_buffer(GWorkers + i, 0.f, 0.f, 0.f);

            vertex_processing(GWorkers, GWorkersNum, &Triangle, &Triangle + 1);
            pixel_processing(GWorkers, GWorkersNum);
            
            SetDIBitsToDevice(Dc, 0, 0, GState.width, GState.height, 0, 0, 0, GState.height, GState.pixels, &GBmi, BI_RGB);
            break;

        default: 
            return DefWindowProcA(Hwnd, Msg, WParam, LParam);

    } return 0;
}
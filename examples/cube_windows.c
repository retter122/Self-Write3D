#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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

static polygon Cube[] = {
    {
        {
            0.f, 0.f, 1.f, 0.f,
            0.f, 1.f, 1.f, 0.f,
            1.f, 0.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 0.f
        },

        { 1.f, 0.f, 0.f, 0.f },
        { 1.f, 0.f, 0.f, 0.f },
        { 1.f, 0.f, 0.f, 0.f },
    }, {
        {
            1.f, 1.f, 1.f, 0.f,
            0.f, 1.f, 1.f, 0.f,
            1.f, 0.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 0.f,
        },

        { 1.f, 0.f, 0.f, 0.f },
        { 1.f, 0.f, 0.f, 0.f },
        { 1.f, 0.f, 0.f, 0.f }
    },

    {
        {
            0.f, 0.f, 0.f, 0.f,
            0.f, 1.f, 0.f, 0.f,
            1.f, 0.f, 0.f, 0.f,
            0.f, 0.f, 0.f, 0.f
        },

        { 1.f, 1.f, 0.f, 0.f },
        { 1.f, 1.f, 0.f, 0.f },
        { 1.f, 1.f, 0.f, 0.f },
    }, {
        {
            1.f, 1.f, 0.f, 0.f,
            0.f, 1.f, 0.f, 0.f,
            1.f, 0.f, 0.f, 0.f,
            0.f, 0.f, 0.f, 0.f,
        },

        { 1.f, 1.f, 0.f, 0.f },
        { 1.f, 1.f, 0.f, 0.f },
        { 1.f, 1.f, 0.f, 0.f }
    },

    {
        {
            0.f, 0.f, 0.f, 0.f,
            0.f, 1.f, 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 0.f,
        },

        { 0.f, 1.f, 0.f, 0.f },
        { 0.f, 1.f, 0.f, 0.f },
        { 0.f, 1.f, 0.f, 0.f }
    }, {
        {
            0.f, 1.f, 1.f, 0.f,
            0.f, 1.f, 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 0.f,
        },

        { 0.f, 1.f, 0.f, 0.f },
        { 0.f, 1.f, 0.f, 0.f },
        { 0.f, 1.f, 0.f, 0.f }
    },

    {
        {
            1.f, 1.f, 1.f, 0.f,
            1.f, 1.f, 0.f, 0.f,
            1.f, 0.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 0.f,
        },

        { 0.f, 0.f, 1.f, 0.f },
        { 0.f, 0.f, 1.f, 0.f },
        { 0.f, 0.f, 1.f, 0.f }
    }, {
        {
            1.f, 0.f, 0.f, 0.f,
            1.f, 1.f, 0.f, 0.f,
            1.f, 0.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 0.f,
        },

        { 0.f, 0.f, 1.f, 0.f },
        { 0.f, 0.f, 1.f, 0.f },
        { 0.f, 0.f, 1.f, 0.f }
    },

    {
        { 
            0.f, 0.f, 0.f, 0.f,
            1.f, 0.f, 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 0.f
        },

        { 1.f, 0.f, 1.f, 0.f },
        { 1.f, 0.f, 1.f, 0.f },
        { 1.f, 0.f, 1.f, 0.f },
    }, {
        { 
            1.f, 0.f, 1.f, 0.f,
            1.f, 0.f, 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 0.f
        },

        { 1.f, 0.f, 1.f, 0.f },
        { 1.f, 0.f, 1.f, 0.f },
        { 1.f, 0.f, 1.f, 0.f },
    },

    {
        { 
            0.f, 1.f, 0.f, 0.f,
            1.f, 1.f, 0.f, 0.f,
            0.f, 1.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 0.f
        },

        { 1.f, 0.f, 1.f, 0.f },
        { 1.f, 0.f, 1.f, 0.f },
        { 1.f, 0.f, 1.f, 0.f },
    }, {
        { 
            1.f, 1.f, 1.f, 0.f,
            1.f, 1.f, 0.f, 0.f,
            0.f, 1.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 0.f
        },

        { 1.f, 0.f, 1.f, 0.f },
        { 1.f, 0.f, 1.f, 0.f },
        { 1.f, 0.f, 1.f, 0.f },
    },
};
#define CubeSize (sizeof(Cube) / sizeof(polygon))

static mat4x4 Transform = {
    1.f, 0.f, 0.f, 0.f,
    0.f, (float)DEF_WIDTH / (float)DEF_HEIGHT, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f
};
static mat1x4 Translate = { -0.5f, -0.5f, 2.f, 0.f };

static graphic_state GState = { 
    DEF_SCREEN_DST, 
    DEF_FOVX, DEF_FOVY, 
    0,
    DEF_WIDTH, DEF_HEIGHT,
    &Transform, &Translate,
    def_vertex_shader, def_pixel_shader
};

static thread_worker *GWorkers;
#define GWorkersNum 1

static BITMAPINFO GBmi = { { sizeof(BITMAPINFOHEADER), DEF_WIDTH, DEF_HEIGHT, 1, 32, BI_RGB, 0, 0, 0, 0, 0 } };


// WINDOW DATA

LRESULT CALLBACK WProc(HWND Hwnd, UINT Msg, WPARAM WParam, LPARAM LParam);

static WNDCLASSA WClass = { CS_HREDRAW | CS_VREDRAW, WProc, 0, 0, 0, 0, 0, 0, 0, "Cube" };

static char WName[] = "Cube";

static HWND WHandle;
static HDC WDc;

static MSG Message;


int main() {
    GWorkers = create_workers(GWorkersNum, &GState);
    GState.pixels = malloc(sizeof(uint32_t) * DEF_WIDTH * DEF_HEIGHT);

    if (!RegisterClassA(&WClass)) return 1;
    WHandle = CreateWindowExA(0, WClass.lpszClassName, WName, WS_OVERLAPPEDWINDOW, 0, 0, DEF_WIDTH, DEF_HEIGHT, 0, 0, 0, 0);
    WDc = GetDC(WHandle);

    ShowWindow(WHandle, SW_SHOWNORMAL);

    mat4x4 TransformFigure, RotateX, RotateY;
    
    mat4x4_rotate_x(&RotateX, 0.01f);
    mat4x4_rotate_y(&RotateY, 0.01f);

    mat4x4_mat4x4_mvmul(&TransformFigure, &RotateX, &RotateY);

    while (1) {
        if (PeekMessageA(&Message, 0, 0, 0, PM_REMOVE)) {
            DispatchMessageA(&Message);

            if (Message.message == WM_QUIT) break;
        }

        transform_figure(Cube, CubeSize, &TransformFigure);
    }

    return 0;
}


LRESULT CALLBACK WProc(HWND Hwnd, UINT Msg, WPARAM WParam, LPARAM LParam) {
    switch (Msg) {
        case (WM_DESTROY):
            PostQuitMessage(0);
            break;

        case (WM_SIZE):
            GState.width = LParam & 0xFFFF;
            GState.height = (LParam >> 16) & 0xFFFF;
            
            GBmi.bmiHeader.biWidth = GState.width;
            GBmi.bmiHeader.biHeight = GState.height;

            GState.pixels = realloc(GState.pixels, sizeof(uint32_t) * GState.width * GState.height);
            resize_workers(GWorkers, GWorkersNum);

            mat4x4_scale(&Transform, 1.f, (float)GState.width / (float)GState.height, 1.f);

            break;

        case (WM_PAINT):
            clear_screen(&GState, 0x00000000);
            for (uint32_t i = 0; i < GWorkersNum; ++i) clear_color_buffer(GWorkers + i, 0, 0, 0);

            vertex_processing(GWorkers, GWorkersNum, Cube, Cube + CubeSize);
            pixel_processing(GWorkers, GWorkersNum);

            SetDIBitsToDevice(WDc, 0, 0, GState.width, GState.height, 0, 0, 0, GState.height, GState.pixels, &GBmi, BI_RGB);
            break;

        default:
            return DefWindowProcA(Hwnd, Msg, WParam, LParam);
    }
}
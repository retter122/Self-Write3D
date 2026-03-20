#pragma once
#include <Windows.h>
#include <stdint.h>


// PIXEL BUFFER DATA
extern uint32_t* PixelBuffer = 0;

extern BITMAPINFOHEADER Bmi = { sizeof(BITMAPINFOHEADER), 0, 0, 1, 32, BI_RGB, 0, 0, 0, 0, 0 };


// CLEAR BUFFER FUNCTION
extern void __fastcall ClearScreen(DWORD Color);


// DRAW RECT FUNCTION
extern void __fastcall DrawRectFunc(unsigned long long XSx, unsigned int Y, unsigned int Sy, DWORD Color);


// DRAW LINE FUNCTION
#define LineStep 0.707f
extern void __fastcall DrawLineFunc(long long SXY, long long EXY, int Width, DWORD Color);


// DRAW ELLIPSE FUNC
extern void __fastcall DrawEllipseFunc(long long XSx, int Y, unsigned int Sy, DWORD Color);


// DRAW TRIANGLE FUNC
extern void __fastcall DrawTriangleFunc(long long X1Y1, long long X2Y2, long long X3Y3, DWORD Color);

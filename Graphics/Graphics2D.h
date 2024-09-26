#pragma once
#include <Windows.h>
// PIXEL BUFFER DATA
extern int* PixelBuffer = 0;

extern BITMAPINFOHEADER Bmi = { sizeof(BITMAPINFOHEADER), 0, 0, 1, 32, BI_RGB, 0, 0, 0, 0, 0 };
// CLEAR BUFFER FUNCTION
extern void __fastcall ClearScreen(DWORD Color);
// C REALIZATION ClearScreen FUNCTION {
//	for (unsigned int i = 0; i < Bmi.biWidth * Bmi.biHeight; ++i) PixelBuffer[i] = Color;
// }

// DRAW RECT FUNCTION
extern void __fastcall DrawRectFunc(unsigned long long XSx, unsigned int Y, unsigned int Sy, DWORD Color);
// C REALIZATION DrawRectFunc FUNCTION {
//	unsigned int X = XSx & 0x00000000FFFFFFFF;
//	XSx >>= 32;
//	
//	for (unsigned int i = Y; i < Y + Sy; ++i) {
//		for (unsigned int j = X; j < X + XSx; ++j) PixelBuffer[i * Bmi.biWidth + j] = Color;
//	}
// }

// DRAW LINE FUNCTION
#define LineStep 0.707f
extern void __fastcall DrawLineFunc(long long SXY, long long EXY, int Width, DWORD Color);
// C REALIZATION DrawLineFunc FUNCTION {
//	int SX = SXY & 0x00000000FFFFFFFF;
//	int EX = EXY & 0x00000000FFFFFFFF;
// 
//	SXY >>= 32;
//	EXY >>= 32;
// 
//	float ln = sqrtf((EX - SX) * (EX - SX) + (EXY - SXY) * (EXY - SXY));
// 
//	float cs = (float)(EX - SX) / ln;
//	float sn = (float)(EXY - SXY) / ln;
// 
//	float WidthBuf = Width >> 1;
//	float WidthCont = Width;
// 
//	while (WidthCont > 0) {
//		float LnB = ln;
// 
//		while (LnB > 0) {
//			PixelBuffer[
//				(unsigned int)((float)SX + LnB * cs - (WidthCont - WidthBuf) * sn) +
//				(unsigned int)((float)SXY + LnB * sn + (WidthCont - WidthBuf) * cs) * Bmi.biWidth
//			] = Color;
// 
//			LnB -= LineStep;
//		}
// 
//		WidthCont -= LineStep;
//	}
//}

// DRAW ELLIPSE FUNC
extern void __fastcall DrawEllipseFunc(long long XSx, int Y, unsigned int Sy, DWORD Color);
// DRAW TRIANGLE FUNC
extern void __fastcall DrawTriangleFunc(long long X1Y1, long long X2Y2, long long X3Y3, DWORD Color);
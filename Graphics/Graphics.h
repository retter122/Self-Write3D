#pragma once
#include <math.h>
#include "Graphics2D.h"
#include "Graphics3D.h"
// MACROS TO WORK WITH GRAPHICS
#define ToRGB(r, g, b) (r << 16) | (g << 8) | b

#define DrawRect(X, SizeX, Y, SizeY, Color) DrawRectFunc(((long long)SizeX << 32) | X, Y, SizeY, Color)
#define DrawLine(StartX, StartY, EndX, EndY, Width, Color) DrawLineFunc(((long long)StartY << 32) | StartX, ((long long)EndY << 32) | EndX, Width, Color)
#define DrawEllipse(X, SizeX, Y, SizeY, Color) DrawEllipseFunc(((long long)SizeX << 32) | X, Y, SizeY, Color)
#define DrawTriangle(X1, Y1, X2, Y2, X3, Y3, Color) DrawTriangleFunc(((long long)Y1 << 32) | X1, ((long long)Y2 << 32) | X2, ((long long)Y3 << 32) | X3, Color)
// INIT GRAPHICS MODULE
static void __fastcall InitGraphics() {
	MaxSide = max(Bmi.biWidth, Bmi.biHeight);

	PixelBuffer = malloc(Bmi.biSizeImage = ((Bmi.biWidth * Bmi.biHeight + 4) << 2));
	ZBuffer = malloc(Bmi.biSizeImage);

	Bmi.biSizeImage >>= 4;
}
// RESIZE PIXEL BUFFER FUCTION
static void __fastcall ResizePixelBuffer() {
	MaxSide = max(Bmi.biWidth, Bmi.biHeight);

	free(PixelBuffer);
	free(ZBuffer);

	PixelBuffer = malloc(Bmi.biSizeImage = ((Bmi.biWidth * Bmi.biHeight + 4) << 2));
	ZBuffer = malloc(Bmi.biSizeImage);

	Bmi.biSizeImage >>= 4;

	NearSize = (float)MaxSide / ((1.f * tanf(FOVX / 2.f)) * 2.f);
}
// ROTATE FIGURE FUNCTIONS
static void __fastcall RotateFigureX(float* Figure, unsigned int NumVertex, float Rot) {
	float YTr = 0.f, ZTr = 0.f;
	for (unsigned int i = 0; i < NumVertex; i += 3) {
		YTr += Figure[i + 1];
		ZTr += Figure[i + 2];
	}
	YTr /= (float)(NumVertex / 3); ZTr /= (float)(NumVertex / 3);

	for (unsigned int i = 0; i < NumVertex; i += 3) {
		float VerY = Figure[i + 1] - YTr, VerZ = Figure[i + 2] - ZTr;
		
		Figure[i + 2] = (VerZ * cosf(Rot) + VerY * -sinf(Rot)) + ZTr;
		Figure[i + 1] = (VerZ * sinf(Rot) + VerY * cosf(Rot)) + YTr;
	}
}
static void __fastcall RotateFigureY(float* Figure, unsigned int NumVertex, float Rot) {
	float ZTr = 0.f, XTr = 0.f;
	for (unsigned int i = 0; i < NumVertex; i += 3) {
		ZTr += Figure[i + 2];
		XTr += Figure[i];
	}
	ZTr /= (float)(NumVertex / 3); XTr /= (float)(NumVertex / 3);

	for (unsigned int i = 0; i < NumVertex; i += 3) {
		float VerZ = Figure[i + 2] - ZTr, VerX = Figure[i] - XTr;

		Figure[i] = (VerX * cosf(Rot) + VerZ * -sinf(Rot)) + XTr;
		Figure[i + 2] = (VerX * sinf(Rot) + VerZ * cosf(Rot)) + ZTr;
	}
}
static void __fastcall RotateFigureZ(float* Figure, unsigned int NumVertex, float Rot) {
	float YTr = 0.f, XTr = 0.f;
	for (unsigned int i = 0; i < NumVertex; i += 3) {
		YTr += Figure[i + 1];
		XTr += Figure[i];
	}
	YTr /= (float)(NumVertex / 3); XTr /= (float)(NumVertex / 3);

	for (unsigned int i = 0; i < NumVertex; i += 3) {
		float VerY = Figure[i + 1] - YTr, VerX = Figure[i] - XTr;

		Figure[i] = (VerX * cosf(Rot) + VerY * -sinf(Rot)) + XTr;
		Figure[i + 1] = (VerX * sinf(Rot) + VerY * cosf(Rot)) + YTr;
	}
}
// TRANSLATE FIGURE FUNCTION
static void __fastcall TranslateFigureX(float* Figure, unsigned int NumVertex, float Trans) {
	for (unsigned int i = 0; i < NumVertex; i += 3) Figure[i] += Trans;
}
static void __fastcall TranslateFigureY(float* Figure, unsigned int NumVertex, float Trans) {
	for (unsigned int i = 1; i < NumVertex; i += 3) Figure[i] += Trans;
}
static void __fastcall TranslateFigureZ(float* Figure, unsigned int NumVertex, float Trans) {
	for (unsigned int i = 2; i < NumVertex; i += 3) Figure[i] += Trans;
}
// SCALE FIGURE FUNCTIONS
static void __fastcall ScaleFigureX(float* Figure, unsigned int NumVertex, float Scale) {
	for (unsigned int i = 0; i < NumVertex; i += 3) Figure[i] *= Scale;
}
static void __fastcall ScaleFigureY(float* Figure, unsigned int NumVertex, float Scale) {
	for (unsigned int i = 1; i < NumVertex; i += 3) Figure[i] *= Scale;
}
static void __fastcall ScaleFigureZ(float* Figure, unsigned int NumVertex, float Scale) {
	for (unsigned int i = 2; i < NumVertex; i += 3) Figure[i] *= Scale;
}
// ROTATE FIGURE AT COORDS CENTER
static void __fastcall RotateFigureCenterX(float* Figure, unsigned int NumVertex, float Rot) {
	for (unsigned int i = 0; i < NumVertex; i += 3) {
		float VerY = Figure[i + 1], VerZ = Figure[i + 2];

		Figure[i + 2] = (VerZ * cosf(Rot) + VerY * -sinf(Rot));
		Figure[i + 1] = (VerZ * sinf(Rot) + VerY * cosf(Rot));
	}
}
static void __fastcall RotateFigureCenterY(float* Figure, unsigned int NumVertex, float Rot) {
	for (unsigned int i = 0; i < NumVertex; i += 3) {
		float VerZ = Figure[i + 2], VerX = Figure[i];

		Figure[i] = (VerX * cosf(Rot) + VerZ * -sinf(Rot));
		Figure[i + 2] = (VerX * sinf(Rot) + VerZ * cosf(Rot));
	}
}
static void __fastcall RotateFigureCenterZ(float* Figure, unsigned int NumVertex, float Rot) {
	for (unsigned int i = 0; i < NumVertex; i += 3) {
		float VerY = Figure[i + 1], VerX = Figure[i];

		Figure[i] = (VerX * cosf(Rot) + VerY * -sinf(Rot));
		Figure[i + 1] = (VerX * sinf(Rot) + VerY * cosf(Rot));
	}
}
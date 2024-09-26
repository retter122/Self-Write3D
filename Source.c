#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include "Graphics/Graphics.h"
#include "Figures.h"
// APP CONST
#define GameMenu 0
#define EscapeMenu 1
// WINDOW CONST
static const char WName[] = "3DGraph";
// WINDOW DATA
static WNDPROC WProc(HWND hWnd, UINT Mess, WPARAM w, LPARAM l);

static WNDCLASSA WClass = { CS_HREDRAW | CS_VREDRAW, WProc, 0, 0, 0, 0, 0, 0, 0, "3DGraph" };
static MSG Msg;

static HDC Dc;
// APP DATA
static POINT HalfScreen;

static float XAng = 0.f;
static float YAng = 0.f;

static float MouseSens = 0.001f;

static unsigned char Menu = GameMenu;

static float FOV = 2.f;
// MAIN FUNCTION
int main() {
// INIT APP
	Bmi.biWidth = GetSystemMetrics(SM_CXSCREEN) >> 1;
	Bmi.biHeight = GetSystemMetrics(SM_CYSCREEN) >> 1;

	Bmi.biWidth += Bmi.biWidth >> 1;
	Bmi.biHeight += Bmi.biHeight >> 1;

	InitGraphics();
	SetFOV(FOV);
// INIT LIGHT
	AddNewLight(0.f, 0.f, 0.f);
// INIT WINDOW
	WClass.hCursor = LoadCursorA(0, IDC_ARROW);
// REGISTER AND SHOW WINDOW
	if (!RegisterClassA(&WClass)) return 0;

	ShowWindow(Dc = CreateWindowExA(0, WClass.lpszClassName, WName, WS_OVERLAPPEDWINDOW, 100, 100, Bmi.biWidth, Bmi.biHeight, 0, 0, 0, 0), SW_SHOWNORMAL);
	
	HalfScreen.x = Bmi.biWidth >> 1;
	HalfScreen.y = Bmi.biHeight >> 1;
	ClientToScreen(Dc, &HalfScreen);
	ShowCursor(NULL);
	
	Dc = GetDC(Dc);
// MAIN CYCLE
	CYC: {
		if (PeekMessageA(&Msg, 0, 0, 0, PM_REMOVE)) DispatchMessageA(&Msg);

		if (Menu == GameMenu) SetCursorPos(HalfScreen.x, HalfScreen.y);

		RotateFigureX(Cube, 108, 0.001f);
		RotateFigureCenterX(CubeNormals, 36, 0.001f);
	} goto CYC;
	return 0;
}
// WINDOW PROCEDURE
static WNDPROC WProc(HWND hWnd, UINT Mess, WPARAM w, LPARAM l) {
	switch (Mess) {
// DESTROY MESSAGE
		case (WM_DESTROY):
			ExitProcess(0);
			return 0;
// MOUSEMOVE MESSAGE
		case (WM_MOUSEMOVE):
			if (Menu == GameMenu) {
				XAng += (float)((l & 0x0000FFFF) - (Bmi.biWidth >> 1)) * MouseSens;
				YAng += (float)((l >> 16) - (Bmi.biHeight >> 1)) * MouseSens;
			}
			return 0;
// KEY UP MESSAGE
		case (WM_KEYUP):
			switch (w) {
				case (VK_ESCAPE):
					if (Menu == GameMenu) {
						Menu = EscapeMenu;
						ShowCursor(1);
					} else {
						Menu = GameMenu;
						ShowCursor(0);
					}
					break;
			}
			return 0;
// WINDOW MOVE MESSAGE
		case (WM_MOVE):
			HalfScreen.x = Bmi.biWidth >> 1;
			HalfScreen.y = Bmi.biHeight >> 1;
			ClientToScreen(hWnd, &HalfScreen);

			return 0;
// RESIZE MESSAGE
		case (WM_SIZE):
			Bmi.biWidth = l & 0x0000FFFF;
			Bmi.biHeight = l >> 16;

			HalfScreen.x = Bmi.biWidth >> 1;
			HalfScreen.y = Bmi.biHeight >> 1;
			ClientToScreen(hWnd, &HalfScreen);

			SetFOV(FOV);

			ResizePixelBuffer();
			return 0;
// PAINT MESSAGE
		case (WM_PAINT):
			ClearScreen(ToRGB(50, 50, 100));
			ClearZBuffer();

			Draw3DFigure(Cube, 36, CubeColors, CubeNormals);

			SetDIBitsToDevice(Dc, 0, 0, Bmi.biWidth, Bmi.biHeight, 0, 0, 0, Bmi.biHeight, PixelBuffer, &Bmi, BI_RGB);
			return 0;
// OTHER MESSAGES
		default: return DefWindowProcA(hWnd, Mess, w, l);
	}
}
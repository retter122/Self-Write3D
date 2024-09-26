#pragma once
#include <Windows.h>
#include "Graphics2D.h"
// COLOR MACROS
#define ToRGB(r, g, b) (r << 16) | (g << 8) | b
// LIGHT DATA
extern float* LightPos = 0;
extern unsigned int LightLen = 0;
// ADD NEW LIGHT TO SCENE FUCTION
static void AddNewLight(float X, float Y, float Z) {
	float* LightBuf = malloc(LightLen + 3);

	for (unsigned int i = 0; i < LightLen; ++i) LightBuf[i] = LightPos[i];
	LightBuf[LightLen] = X; LightBuf[LightLen + 1] = Y; LightBuf[LightLen + 2] = Z;

	free(LightPos);
	LightPos = LightBuf;

	LightLen += 3;
}
// 3D GRAPHICS DATA
extern float* ZBuffer = 0;

static int MaxSide;

static float FOVX;
static float FOVY;
extern float NearSize = 1.f;
extern float FarZone = 100.f;
// SET FOV FUNCTION
static void __fastcall SetFOV(float FOV) {
	FOVX = (float)Bmi.biWidth / (float)MaxSide * FOV;
	FOVY = (float)Bmi.biHeight / (float)MaxSide * FOV;

	NearSize = (float)MaxSide / ((1.f * tanf(FOVX / 2.f)) * 2.f);
}
// CLEAR 3D BUFFER FUNCTION
extern void __fastcall ClearZBuffer();
// C REALIZATION ClearZBuffer FUNCTION {
//	for (unsigned int i = 0; i < Bmi.biSizeImage; ++i) ZBuffer[i] = FarZone;
//}
// DRAW 3D FIGURE FUNCTION
extern void __fastcall Draw3DFigure(const float* Vertexies, unsigned int NumVertex, const float* Colors, const float* Normals) {
	for (unsigned int i = 0; i < NumVertex; i += 3) {
		float Z1 = Vertexies[i * 3 + 2], Z2 = Vertexies[(i + 1) * 3 + 2], Z3 = Vertexies[(i + 2) * 3 + 2];
	
		float X1 = Vertexies[i * 3], Y1 = Vertexies[i * 3 + 1];
		float X2 = Vertexies[(i + 1) * 3], Y2 = Vertexies[(i + 1) * 3 + 1];
		float X3 = Vertexies[(i + 2) * 3], Y3 = Vertexies[(i + 2) * 3 + 1];
	
		float Col1R = 0; float Col1G = 0; float Col1B = 0;
		float Col2R = 0; float Col2G = 0; float Col2B = 0;
		float Col3R = 0; float Col3G = 0; float Col3B = 0;
	
		float NormX = Normals[i], 
		NormY = Normals[i + 1],
		NormZ = Normals[i + 2];
	
		for (unsigned int Light = 0; Light < LightLen; Light += 3) {
			float Vec1X = LightPos[Light] - X1, Vec1Y = LightPos[Light + 1] - Y1, Vec1Z = LightPos[Light + 2] - Z1;
			float Vec2X = LightPos[Light] - X2, Vec2Y = LightPos[Light + 1] - Y2, Vec2Z = LightPos[Light + 2] - Z2;
			float Vec3X = LightPos[Light] - X3, Vec3Y = LightPos[Light + 1] - Y3, Vec3Z = LightPos[Light + 2] - Z3;
	
			float LnVec1 = sqrtf(Vec1X * Vec1X + Vec1Y * Vec1Y + Vec1Z * Vec1Z);
			float LnVec2 = sqrtf(Vec2X * Vec2X + Vec2Y * Vec2Y + Vec2Z * Vec2Z);
			float LnVec3 = sqrtf(Vec3X * Vec3X + Vec3Y * Vec3Y + Vec3Z * Vec3Z);
	
			Vec1X /= LnVec1; Vec1Y /= LnVec1; Vec1Z /= LnVec1;
			Vec2X /= LnVec2; Vec2Y /= LnVec2; Vec2Z /= LnVec2;
			Vec3X /= LnVec3; Vec3Y /= LnVec3; Vec3Z /= LnVec3;
	
			float Dot1 = Vec1X * NormX + Vec1Y * NormY + Vec1Z * NormZ;
			float Dot2 = Vec2X * NormX + Vec2Y * NormY + Vec2Z * NormZ;
			float Dot3 = Vec3X * NormX + Vec3Y * NormY + Vec3Z * NormZ;
	
			Col1R += Dot1; Col1G += Dot1; Col1B += Dot1;
			Col2R += Dot2; Col2G += Dot2; Col2B += Dot2;
			Col3R += Dot3; Col3G += Dot3; Col3B += Dot3;
		}
	
		Col1R = Col1R * Colors[i * 3]; Col1G = Col1G * Colors[i * 3 + 1]; Col1B = Col1B * Colors[i * 3 + 2];
		Col2R = Col2R * Colors[(i + 1) * 3]; Col2G = Col2G * Colors[(i + 1) * 3 + 1]; Col2B = Col2B * Colors[(i + 1) * 3 + 2];
		Col3R = Col3R * Colors[(i + 2) * 3]; Col3G = Col3G * Colors[(i + 2) * 3 + 1]; Col3B = Col3B * Colors[(i + 2) * 3 + 2];
	
		Col1R = max(min(Col1R, 1.f), 0); Col1B = max(min(Col1B, 1.f), 0); Col1G = max(min(Col1G, 1.f), 0);
		Col2R = max(min(Col2R, 1.f), 0); Col2B = max(min(Col2B, 1.f), 0); Col2G = max(min(Col2G, 1.f), 0);
		Col3R = max(min(Col3R, 1.f), 0); Col3B = max(min(Col3B, 1.f), 0); Col3G = max(min(Col3G, 1.f), 0);
	
		int U1 = (Bmi.biWidth >> 1) + (NearSize * (X1 / max(Z1, 0.25f))), V1 = (Bmi.biHeight >> 1) + (NearSize * (Y1 / max(Z1, 0.25f)));
		int U2 = (Bmi.biWidth >> 1) + (NearSize * (X2 / max(Z2, 0.25f))), V2 = (Bmi.biHeight >> 1) + (NearSize * (Y2 / max(Z2, 0.25f)));
		int U3 = (Bmi.biWidth >> 1) + (NearSize * (X3 / max(Z3, 0.25f))), V3 = (Bmi.biHeight >> 1) + (NearSize * (Y3 / max(Z3, 0.25f)));
	
		for (int Y = min(max(min(min(V1, V2), V3), 0), Bmi.biHeight - 1); Y <= min(max(max(max(V1, V2), V3), 0), Bmi.biHeight - 1); ++Y) {
			for (int X = min(max(min(min(U1, U2), U3), 0), Bmi.biWidth - 1); X <= min(max(max(max(U1, U2), U3), 0), Bmi.biWidth - 1); ++X) {
				int Vec1X = U1 - U2, Vec2X = U2 - U3, Vec3X = U3 - U1;
				int Vec1Y = V1 - V2, Vec2Y = V2 - V3, Vec3Y = V3 - V1;
	
				int Dot1 = ((U1 - X) * -Vec1Y) + ((V1 - Y) * Vec1X);
				int Dot2 = ((U2 - X) * -Vec2Y) + ((V2 - Y) * Vec2X);
				int Dot3 = ((U3 - X) * -Vec3Y) + ((V3 - Y) * Vec3X);
	
				if ((Dot1 <= 0 && Dot2 <= 0 && Dot3 <= 0) || (Dot1 >= 0 && Dot2 >= 0 && Dot3 >= 0)) {
					float W1 = (float)((V2 - V3) * (X - U3) + (U3 - U2) * (Y - V3)) /
							   (float)((V2 - V3) * (U1 - U3) + (U3 - U2) * (V1 - V3));
					float W2 = (float)((V3 - V1) * (X - U3) + (U1 - U3) * (Y - V3)) /
							   (float)((V2 - V3) * (U1 - U3) + (U3 - U2) * (V1 - V3));
					float W3 = 1.f - W1 - W2;
	
					float Z = (Z1 * W1 + Z2 * W2 + Z3 * W3) / (W1 + W2 + W3);
					
					float ColR = (Col1R * W1 + Col2R * W2 + Col3R * W3);
					float ColG = (Col1G * W1 + Col2G * W2 + Col3G * W3);
					float ColB = (Col1B * W1 + Col2B * W2 + Col3B * W3);
	
					if (Z < ZBuffer[Y * Bmi.biWidth + X] && Z > 1.f) {
						PixelBuffer[Y * Bmi.biWidth + X] = ToRGB((unsigned int)(255.f * ColR), (unsigned int)(255.f * ColG), (unsigned int)(255.f * ColB));
						ZBuffer[Y * Bmi.biWidth + X] = Z;
					}
				}
			}
		}
	}
}

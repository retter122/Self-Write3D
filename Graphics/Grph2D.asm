option casemap: none
public ClearScreen
public DrawRectFunc
public DrawEllipseFunc
public DrawTriangleFunc
public DrawLineFunc
.data
	extern PixelBuffer: QWORD
	extern Bmi: QWORD
.const
	LineStep REAL4 0.707f
.code

ClearScreen PROC
; void ClearScreen(RCX: DWORD Color)
	MOV eax, DWORD PTR [Bmi + 20]

	MOV r8, PixelBuffer

	MOVD xmm0, ecx
	SHUFPS xmm0, xmm0, 00000000b

	CYC:
		MOVNTPS [r8], xmm0;

		ADD r8, 16
		DEC eax
		JNZ CYC
	RET;
ClearScreen ENDP

DrawRectFunc PROC
; void DrawRectFunc(RCX: unsigned long long XSx, RDX: unsigned int Y, R8: unsigned int Sy, R9: DWORD Color)
	MOV r10d, DWORD PTR [Bmi + 4]

	MOV ebx, ecx;
	SHR rcx, 32;

	IMUL edx, r10d
	ADD rdx, rbx
	SHL rdx, 2;
	ADD rdx, PixelBuffer

	SUB r10d, ebx;
	SHL r10, 2;

	CYC:
		MOV ecx, ebx;

		C1:
			MOVNTI DWORD PTR [rdx], r9d;

			ADD rdx, 4;
			DEC ecx;
			JNZ C1;

		ADD rdx, r10;
		DEC r8;
		JNZ CYC
	RET;
DrawRectFunc ENDP

DrawEllipseFunc PROC
; void DrawEllipseFunc(RCX: long long XSx, RDX: int Y, R8: unsigned int Sy, R9: DWORD Color)
	MOV r10d, DWORD PTR [Bmi + 4]

	MOV ebx, ecx;
	SHR rcx, 32;

	CVTSI2SS xmm1, edx;
	CVTSI2SS xmm2, ecx;

	MOVSS xmm0, xmm2;
	CVTSI2SS xmm3, r8d;

	DIVSS xmm2, xmm3;
	MULSS xmm0, xmm0;

	SUB edx, r8d;

	MOV r11d, edx;

	IMUL edx, r10d;

	ADD ebx, edx;
	SHL rbx, 2;
	ADD rbx, PixelBuffer;

	SHL r8, 1;
	SHL r10, 2;

	CYC:
		CVTSI2SS xmm3, r11d;
		SUBSS xmm3, xmm1;
		MULSS xmm3, xmm2;
		MULSS xmm3, xmm3;
		MOVSS xmm4, xmm0;
		SUBSS xmm4, xmm3;
		SQRTSS xmm4, xmm4;

		CVTSS2SI ecx, xmm4;
		CMP ecx, 0;
		JLE NEXT;

		SHL rcx, 2;
		MOV rax, rcx;
		SUB rbx, rcx;

		C1:
			MOVNTI DWORD PTR [rbx], r9d

			ADD rbx, 4;
			SUB rcx, 2;
			JNZ C1;

		SUB rbx, rax;
		ADD rbx, r10;

		NEXT: INC r11d;
		DEC r8;
		JNZ CYC;
	RET;
DrawEllipseFunc ENDP

DrawTriangleFunc PROC
; void DrawTriangleFunc(RCX: long long X1Y1, RDX: long long X2Y2, R8: long long X3Y3, R9: DWORD Color)
	XOR r12, r12;
	MOV r12d, DWORD PTR [Bmi + 4];

	MOVQ xmm0, rcx;
	MOVQ xmm1, rdx;
	MOVQ xmm2, r8;

	MOVQ xmm5, xmm0;
	PSUBD xmm5, xmm1;

	MOVQ xmm6, xmm1;
	PSUBD xmm6, xmm2;

	MOVQ xmm7, xmm2;
	PSUBD xmm7, xmm0;

	MOVQ xmm3, xmm0;
	PMAXSD xmm3, xmm1;
	PMAXSD xmm3, xmm2;

	MOVQ xmm4, xmm0;
	PMINSD xmm4, xmm1;
	PMINSD xmm4, xmm2;

	PSUBD xmm3, xmm4;

	MOVD r10d, xmm4;
	PEXTRD r11d, xmm4, 1;

	MOVD r8d, xmm3;
	PEXTRD r13d, xmm3, 1;

	MOV rax, r12;
	MUL r11;
	ADD rax, r10;
	SHL rax, 2;
	ADD rax, PixelBuffer;

	SUB r12d, r8d;
	SHL r12, 2;

	CYC:
		MOV edx, r8d;

		C1:
			MOVD xmm4, r10d
			PINSRD xmm4, r11d, 1;

			MOVQ xmm8, xmm0;
			PSUBD xmm8, xmm4;
			PSHUFD xmm8, xmm8, 01000001b;
			PMULLD xmm8, xmm5;
			PHSUBD xmm8, xmm8;

			MOVQ xmm9, xmm1;
			PSUBD xmm9, xmm4;
			PSHUFD xmm9, xmm9, 01000001b;
			PMULLD xmm9, xmm6;
			PHSUBD xmm9, xmm9;

			MOVQ xmm10, xmm2;
			PSUBD xmm10, xmm4;
			PSHUFD xmm10, xmm10, 01000001b;
			PMULLD xmm10, xmm7;
			PHSUBD xmm10, xmm10;

			MOVD ecx, xmm8;
			CMP ecx, 0;
			JL CNTL

			MOVD ecx, xmm9;
			CMP ecx, 0;
			JL CNTC1;

			MOVD ecx, xmm10;
			CMP ecx, 0;
			JL CNTC1;

			JMP DRW;

			CNTL: MOVD ecx, xmm9;
			CMP ecx, 0;
			JG CNTC1;

			MOVD ecx, xmm10;
			CMP ecx, 0;
			JG CNTC1;

			DRW: MOVNTI [rax], r9d;

			CNTC1: INC r10d;
			ADD rax, 4;
			DEC edx;
			JNZ C1;

		SUB r10d, r8d;

		INC r11d;
		ADD rax, r12;
		DEC r13d;
		JNZ CYC;
	RET;
DrawTriangleFunc ENDP

DrawLineFunc PROC
; void DrawLineFunc(RCX: long long SXY, RDX: long long EXY, R8: int Width, R9: DWORD Color)
	MOVQ xmm0, rcx;
	CVTDQ2PS xmm0, xmm0;

	MOVQ xmm1, rdx;
	CVTDQ2PS xmm1, xmm1;
	SUBPS xmm1, xmm0;
	
	MOVQ xmm2, xmm1;
	MULPS xmm2, xmm2;
	HADDPS xmm2, xmm2;
	SQRTSS xmm2, xmm2;

	SHUFPS xmm2, xmm2, 00000000b;
	DIVPS xmm1, xmm2;

	MOVQ xmm8, xmm1;
	SHUFPS xmm8, xmm8, 01000001b;

	CVTSI2SS xmm3, r8d;
	SHR r8, 1;
	CVTSI2SS xmm4, r8d;

	MOVSS xmm5, LineStep;
	XORPS xmm6, xmm6;

	SHUFPS xmm0, xmm0, 01000001b;

	CYC:
		MOVSS xmm7, xmm2;
		C1:
			MOVSS xmm9, xmm4;
			SUBSS xmm9, xmm3;
			SHUFPS xmm9, xmm9, 00000000b;
			MULPS xmm9, xmm1;

			MOVSLDUP xmm10, xmm7;
			MULPS xmm10, xmm8;

			ADDSUBPS xmm10, xmm9;
			ADDPS xmm10, xmm0;

			CVTTPS2DQ xmm10, xmm10;
			
			XOR rcx, rcx
			XOR r8, r8;
			PEXTRD ecx, xmm10, 1;
			MOVD r8d, xmm10;

			IMUL r8d, DWORD PTR [Bmi + 4];
			ADD r8, rcx;
			SHL r8, 2;
			ADD r8, PixelBuffer;

			MOVNTI [r8], r9d;

			SUBSS xmm7, xmm5;
			COMISS xmm7, xmm6;
			JA C1;

		SUBSS xmm3, xmm5;
		COMISS xmm3, xmm6;
		JA CYC;
	RET;
DrawLineFunc ENDP

end
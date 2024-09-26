option casemap: none
public ClearZBuffer
.data
	extern ZBuffer: QWORD;

	extern Bmi: QWORD;

	extern FarZone: DWORD;
	extern NearSize: DWORD;

	extern LightLen: DWORD;
	extern LightPos: QWORD;
.code

ClearZBuffer PROC
; void ClearZBufferFunc()
	MOV ecx, DWORD PTR [Bmi + 20];

	MOVSS xmm0, FarZone
	SHUFPS xmm0, xmm0, 00000000b

	MOV rax, ZBuffer

	CYC:
		MOVNTPS [rax], xmm0;

		ADD rax, 16;
		DEC ecx;
		JNZ CYC;
	RET;
ClearZBuffer ENDP

end
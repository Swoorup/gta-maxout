#include "SJLIB/stdinc.h"

#define SECTORS_MULTIPLIER 6

DWORD dwstSectorListAddress[] = {
	0x40ce5d, 0x40cfbe, 0x40d05d, 0x40d21a, 0x40d3ba, 0x40d4fa, 0x40e669, 0x40ec72, 
	0x40f30e, 0x40f499, 0x40f6e7, 0x40f81b, 0x40f994, 0x40fad4, 0x423e56, 0x4257c4, 
	0x425a8d, 0x42e6cc, 0x4876dc, 0x487ed9, 0x488179, 0x4bb099, 0x4bb4bc, 0x4bdb78, 
	0x4c6c7a, 0x4c7446, 0x4c8f39, 0x4c945b, 0x4c9a97, 0x4d2a05, 0x4d2b75, 0x4d2d61, 
	0x4d33b7, 0x4d40cf, 0x4d4bd7, 0x4d5329, 0x4d54f9, 0x4d5689, 0x4d597a, 0x4d5d18, 
	0x4d612a, 0x4d6508, 0x4d6908, 0x4d6d28, 0x4d7464, 0x4d844a, 0x4d8c45, 0x4d960e, 
	0x4d96bc, 0x4d9769, 0x4d9844, 0x4d98e9, 0x4d9b14, 0x4d9bc4, 0x4d9cd4, 0x4d9d79, 
	0x4d9e37, 0x4d9ee4, 0x4da0d4, 0x4da184, 0x4da294, 0x4da339, 0x4da3f7, 0x4da4a4, 
	0x4da6f8, 0x4da790, 0x4da82a, 0x4da8e3, 0x4da983, 0x4daaa3, 0x4dab38, 0x4dac27, 
	0x4dacb6, 0x4dad63, 0x4dadf6, 0x4daefb, 0x4daf98, 0x4db08a, 0x4db114, 0x4db1c3, 
	0x4db256, 0x4db4cc, 0x4db595, 0x4dba23, 0x4dbb1d, 0x4ea153, 0x4f3723, 0x53d150, 
	0x54fb9d, 0x55308d, 0x56c5cf, 0x56d0fa, 0x58789a, 0x587cda, 0x5a89ce, 0x5a94e8, 
	0x5b5339, 0x61f518, 0x62034e, 0x4e9c4a, 0x51d38e, 0x50d650, 0x4661fa, 
};

DWORD dwDirectlyPatchableIndex[] = {
	0x40cd84, 0x40ce04, 0x40ce21, 0x40cf34, 0x40cf64, 0x40d117, 0x40d1a4, 0x40d1c7, 
	0x40d30b, 0x40d344, 0x40e5dc, 0x40e61c, 0x40eb78, 0x40ebba, 0x423d51, 0x423d93, 
	0x4256f6, 0x425738, 0x4259b8, 0x4259fa, 0x42e629, 0x42e669, 0x4bdab5, 0x4bdaf7, 
	0x4c7385, 0x4c740c, 0x4c8ea7, 0x4c8f21, 0x4d292b, 0x4d2946, 0x4d2983, 0x4d29a6, 
	0x4d2aa1, 0x4d2ab7, 0x4d2af5, 0x4d2b16, 0x4d2c7e, 0x4d2c96, 0x4d2cd6, 0x4d2cf6, 
	0x4d32f8, 0x4d333a, 0x4d401d, 0x4d4061, 0x4d5258, 0x4d5276, 0x4d52b3, 0x4d52d6, 
	0x4d5428, 0x4d5446, 0x4d5483, 0x4d54a6, 0x4d55bd, 0x4d55d6, 0x4d5613, 0x4d5636, 
	0x4d58ce, 0x4d590f, 0x4d5c63, 0x4d5ca5, 0x4d607e, 0x4d60bf, 0x4d6454, 0x4d6498, 
	0x4d6854, 0x4d6898, 0x4d6c74, 0x4d6cb8, 0x4d83b4, 0x4d83f8, 0x4d8b69, 0x4d8b86, 
	0x4d8bc4, 0x4d8be6, 0x4d9465, 0x4d9486, 0x4d94bf, 0x4d94d6, 0x4d950f, 0x4d9526, 
	0x4d9561, 0x4d9577, 0x4e9bbd, 0x4e9c03, 0x4ea09d, 0x4ea0e3, 0x4f368c, 0x4f36d2, 
	0x51d2ef, 0x51d33b, 0x53d073, 0x53d0b5, 0x552fdc, 0x55301c, 0x56c4e1, 0x56c523, 
	0x56d044, 0x56d086, 0x5877fb, 0x58783b, 0x587c3b, 0x587c7b, 0x5b526a, 0x5b52b1, 
};


using namespace HookSystem;
void GenerateIMULnewAssembly(DWORD dwAddrToHook, DWORD dwAddrToRetByJmp, AsmJit::GpReg reg, char bytesToEmit[], int nbytesToEmit, int index)
{
	int nIndex = 80 * SECTORS_MULTIPLIER - (80 - index);
	AsmJit::X86Assembler a;
	AsmJit::FileLogger logger(stdout);
	a.setLogger(&logger);
	
	byte* bytes = (byte*)malloc(nbytesToEmit);
	memcpy(bytes, bytesToEmit, nbytesToEmit);

	// start
	a.imul(reg, nIndex);
	for (int i = 0; i < nbytesToEmit; i++)
		a._emitByte(bytes[i]);
	a.jmp(dwAddrToRetByJmp);
	// end

	InstallFnByJump(dwAddrToHook, a.make());
	free(bytes);
	a.reset();
}

void GenerateADDnewAssembly(DWORD dwAddrToHook, DWORD dwAddrToRetByJmp, bool bIsDisplacement, sysint_t displacement, AsmJit::GpReg reg, char bytesToEmit[], int nbytesToEmit, int index)
{
	int nIndex = 80 * SECTORS_MULTIPLIER - (80 - index);
	AsmJit::X86Assembler a;
	AsmJit::FileLogger logger(stdout);
	a.setLogger(&logger);

	byte* bytes = (byte*)malloc(nbytesToEmit);
	memcpy(bytes, bytesToEmit, nbytesToEmit);

	// start
	if (bIsDisplacement)
		a.add(AsmJit::dword_ptr(AsmJit::esp, displacement), nIndex);
	else
		a.add(reg, nIndex);

	for (int i = 0; i < nbytesToEmit; i++)
		a._emitByte(bytes[i]);
	a.jmp(dwAddrToRetByJmp);
	// end

	InstallFnByJump(dwAddrToHook, a.make());
	free(bytes);
	a.reset();
}

void GenerateADDwithCMPnewAssembly(DWORD dwAddrToHook, DWORD dwAddrToRetByJmp, bool bIsAddDisplacement, sysint_t addDisplacement, AsmJit::GpReg addReg, int addindex, bool bIsCmpDisplacement, sysint_t cmpDisplacement, AsmJit::GpReg cmpReg, int cmpindex, int nCmpDeferenceSize)
{
	int naddIndex = 80 * SECTORS_MULTIPLIER - (80 - addindex);
	int ncmpIndex = 80 * SECTORS_MULTIPLIER - (80 - cmpindex);

	AsmJit::X86Assembler a;
	AsmJit::FileLogger logger(stdout);
	a.setLogger(&logger);


	// start
	if (bIsAddDisplacement)
		a.add(AsmJit::dword_ptr(AsmJit::esp, addDisplacement), naddIndex);
	else
		a.add(addReg, naddIndex);

	if (bIsCmpDisplacement)
		if (nCmpDeferenceSize == 4)
			a.cmp(AsmJit::dword_ptr(AsmJit::esp, cmpDisplacement), ncmpIndex);
		else if (nCmpDeferenceSize == 2)
			a.cmp(AsmJit::word_ptr(AsmJit::esp, cmpDisplacement), ncmpIndex);
		else
			a.cmp(AsmJit::byte_ptr(AsmJit::esp, cmpDisplacement), ncmpIndex);
	else
		a.cmp(cmpReg, ncmpIndex);

	a.jmp(dwAddrToRetByJmp);
	// end

	InstallFnByJump(dwAddrToHook, a.make());
	a.reset();
}

void GenerateSUBnewAssembly(DWORD dwAddrToHook, DWORD dwAddrToRetByJmp, bool bIsDisplacement, sysint_t displacement, AsmJit::GpReg reg, char bytesToEmit[], int nbytesToEmit, int index)
{
	int nIndex = 80 * SECTORS_MULTIPLIER - (80 - index);
	AsmJit::X86Assembler a;
	AsmJit::FileLogger logger(stdout);
	a.setLogger(&logger);

	byte* bytes = (byte*)malloc(nbytesToEmit);
	memcpy(bytes, bytesToEmit, nbytesToEmit);

	// start
	if (bIsDisplacement)
		a.sub(AsmJit::dword_ptr(AsmJit::esp, displacement), nIndex);
	else
		a.sub(reg, nIndex);

	for (int i = 0; i < nbytesToEmit; i++)
		a._emitByte(bytes[i]);
	a.jmp(dwAddrToRetByJmp);
	// end

	InstallFnByJump(dwAddrToHook, a.make());
	free(bytes);
	a.reset();
}

void GenerateCMPWithouJumpnewAssembly(DWORD dwAddrToHook, DWORD dwAddrToRetByJmp, bool bIsDisplacement, sysint_t displacement, AsmJit::GpReg reg, char bytesToEmit[], int nbytesToEmit, int index)
{
	int nIndex = 80 * SECTORS_MULTIPLIER - (80 - index);
	AsmJit::X86Assembler a;
	AsmJit::FileLogger logger(stdout);
	a.setLogger(&logger);

	byte* bytes = (byte*)malloc(nbytesToEmit);
	memcpy(bytes, bytesToEmit, nbytesToEmit);

	// start
	if (bIsDisplacement)
		a.cmp(AsmJit::dword_ptr(AsmJit::esp, displacement), nIndex);
	else
		a.cmp(reg, nIndex);

	for (int i = 0; i < nbytesToEmit; i++)
		a._emitByte(bytes[i]);
	a.jmp(dwAddrToRetByJmp);
	// end

	InstallFnByJump(dwAddrToHook, a.make());
	free(bytes);
	a.reset();
}

enum eAsmJump
{
	ASM_JGE,
	ASM_JL,
	ASM_JLE,
	ASM_JZ,
};

void GenerateCMPWithJumpnewAssembly(DWORD dwAddrToHook, DWORD dwAddrToRetByJmp, bool bIsDisplacement, sysint_t displacement, AsmJit::GpReg reg, int index, eAsmJump jumpType, DWORD dwAddrToJumpOnCondition)
{
	int nIndex = 80 * SECTORS_MULTIPLIER - (80 - index);
	AsmJit::X86Assembler a;
	AsmJit::FileLogger logger(stdout);
	AsmJit::Label L_true = a.newLabel();
	a.setLogger(&logger);


	// start
	if (bIsDisplacement)
		a.cmp(AsmJit::dword_ptr(AsmJit::esp, displacement), nIndex);
	else
		a.cmp(reg, nIndex);
	
	switch (jumpType)
	{
	case ASM_JGE:
		a.jge(L_true);
		break;
	case ASM_JL:
		a.jl(L_true);
		break;
	case ASM_JLE:
		a.jle(L_true);
		break;
	case ASM_JZ:
		a.jz(L_true);
		break;
	}

	a.jmp(dwAddrToRetByJmp);
	a.bind(L_true);
	a.jmp(dwAddrToJumpOnCondition);
	// end

	InstallFnByJump(dwAddrToHook, a.make());
	a.reset();
}

void HookSectorList(void)
{
	DWORD stNewSectorList = (DWORD)malloc(80 * 80 * 10 * 4 * SECTORS_MULTIPLIER * SECTORS_MULTIPLIER);
	memset((void*)stNewSectorList, 0, 80*80*10*4 * SECTORS_MULTIPLIER * SECTORS_MULTIPLIER);

	DWORD dwVp;
	
	VirtualProtect((void*)0x401000, 0x27CE00, PAGE_EXECUTE_READWRITE, &dwVp);

	// world borders
	*(float*)0x69135c *= (float)SECTORS_MULTIPLIER;
	*(float*)0x691360 *= (float)SECTORS_MULTIPLIER;
	*(float*)0x691364 *= (float)SECTORS_MULTIPLIER;
	*(float*)0x691368 *= (float)SECTORS_MULTIPLIER;

	//corona boarders
	*(float*)0x69592c *= (float)SECTORS_MULTIPLIER;
	*(float*)0x695930 *= (float)SECTORS_MULTIPLIER;
	*(float*)0x695934 *= (float)SECTORS_MULTIPLIER;
	*(float*)0x695938 *= (float)SECTORS_MULTIPLIER;

	//car borders
	*(float*)0x69a890 *= (float)SECTORS_MULTIPLIER;
	*(float*)0x69a894 *= (float)SECTORS_MULTIPLIER;
	*(float*)0x69a898 *= (float)SECTORS_MULTIPLIER;
	*(float*)0x69a8a0 *= (float)SECTORS_MULTIPLIER;
	
	// boat borders ??
	*(float*)0x69afec *= (float)SECTORS_MULTIPLIER;
	*(float*)0x69aff0 *= (float)SECTORS_MULTIPLIER;
	*(float*)0x69aff4 *= (float)SECTORS_MULTIPLIER;
	*(float*)0x69aff8 *= (float)SECTORS_MULTIPLIER;

	// police chopper borders ??
	*(float*)0x69c064 *= (float)SECTORS_MULTIPLIER;
	*(float*)0x69c068 *= (float)SECTORS_MULTIPLIER;
	*(float*)0x69c06c *= (float)SECTORS_MULTIPLIER;
	*(float*)0x69c070 *= (float)SECTORS_MULTIPLIER;
	
	// bullet boundaries ??
	*(float*)0x69cf4c *= (float)SECTORS_MULTIPLIER;
	*(float*)0x69cf50 *= (float)SECTORS_MULTIPLIER;
	*(float*)0x69cf54 *= (float)SECTORS_MULTIPLIER;
	*(float*)0x69cf58 *= (float)SECTORS_MULTIPLIER;
	
	// projectile borders, simply destroy the projectiles
	*(float*)0x69d1ac *= (float)SECTORS_MULTIPLIER;
	*(float*)0x69d1b0 *= (float)SECTORS_MULTIPLIER;
	*(float*)0x69d1b4 *= (float)SECTORS_MULTIPLIER;
	*(float*)0x69d1b8 *= (float)SECTORS_MULTIPLIER;

	// fix sector total indexing
	*((int*)0x4DB97A) *= SECTORS_MULTIPLIER * SECTORS_MULTIPLIER;
	*((int*)0x4DB6A9) *= SECTORS_MULTIPLIER * SECTORS_MULTIPLIER;
	*((int*)0x4D74ED) *= SECTORS_MULTIPLIER * SECTORS_MULTIPLIER;
	*((int*)0x4DB575) *= SECTORS_MULTIPLIER * SECTORS_MULTIPLIER;
	*((int*)0x4DBA12) *= SECTORS_MULTIPLIER * SECTORS_MULTIPLIER;
	*((int*)0x4DBA11) *= SECTORS_MULTIPLIER * SECTORS_MULTIPLIER;

	for (int i = 0; i < ARRLEN(dwstSectorListAddress); i++)
	{
		//if (*((DWORD*)dwstSectorListAddress[i]) <= 0x792D58)
		{
			DWORD field_offset = *((DWORD*)dwstSectorListAddress[i]) - 0x792D30;
			*((DWORD*)dwstSectorListAddress[i]) = stNewSectorList + field_offset;
		}
	}

	
	for (int i = 0; i < ARRLEN(dwDirectlyPatchableIndex); i++)
	{
		int nIndex = 80 * SECTORS_MULTIPLIER - (80 - *((DWORD*)dwDirectlyPatchableIndex[i]));
		*((DWORD*)dwDirectlyPatchableIndex[i]) = nIndex;
	}

	DWORD dwCZonesBounds[] = {
		0x4DE312,0x4DE31C,0x4DE32E,0x4DE338,
		0x4DE364,0x4DE36E,0x4DE388,0x4DE392,
		0x4DE46D,0x4DE477,0x4DE489,0x4DE493
	};

	for(int i = 0; i < ARRLEN(dwCZonesBounds); i++)
		*((float*)dwCZonesBounds[i]) *= (float)SECTORS_MULTIPLIER;

	DWORD dwVp2;
	VirtualProtect((void*)0x401000, 0x27CE00, dwVp, &dwVp2);

	GenerateIMULnewAssembly(0x40ce4e, 0x40ce55, AsmJit::esi, "\x03\x74\x24\x10", 4, 80);
	GenerateIMULnewAssembly(0x40cfaf, 0x40cfb6, AsmJit::esi, "\x03\x74\x24\x18", 4, 80);
	GenerateIMULnewAssembly(0x40d04e, 0x40d055, AsmJit::ebp, "\x03\x6C\x24\x14", 4, 80);
	GenerateIMULnewAssembly(0x40d1e2, 0x40d1e9, AsmJit::eax, "\x89\x44\x24\x24", 4, 80);
	GenerateIMULnewAssembly(0x40d1f1, 0x40d1f6, AsmJit::eax, "\xDE\xD9", 2, 80);
	GenerateIMULnewAssembly(0x40d385, 0x40d38c, AsmJit::eax, "\x89\x44\x24\x1C", 4, 80);
	GenerateIMULnewAssembly(0x40d394, 0x40d39b, AsmJit::eax, "\x89\x44\x24\x40", 4, 80);
	GenerateIMULnewAssembly(0x40d4ca, 0x40d4d1, AsmJit::eax, "\x89\x44\x24\x50", 4, 80);
	GenerateIMULnewAssembly(0x40d4d9, 0x40d4e0, AsmJit::eax, "\x89\x44\x24\x38", 4, 80);
	GenerateIMULnewAssembly(0x40e632, 0x40e637, AsmJit::eax, "\xDE\xD9", 2, 80);
	GenerateIMULnewAssembly(0x40ec02, 0x40ec09, AsmJit::eax, "\x89\x44\x24\x1C", 4, 80);
	GenerateIMULnewAssembly(0x40f6db, 0x40f6e2, AsmJit::ebx, "\x03\x5C\x24\x1C", 4, 80);
	GenerateIMULnewAssembly(0x40f80f, 0x40f816, AsmJit::ebx, "\x03\x5C\x24\x20", 4, 80);
	GenerateIMULnewAssembly(0x40f968, 0x40f96f, AsmJit::eax, "\x89\x44\x24\x14", 4, 80);
	GenerateIMULnewAssembly(0x40faa8, 0x40faaf, AsmJit::eax, "\x89\x44\x24\x18", 4, 80);
	GenerateIMULnewAssembly(0x423e0d, 0x423e12, AsmJit::eax, "\xDE\xD9", 2, 80);
	GenerateIMULnewAssembly(0x425787, 0x42578e, AsmJit::eax, "\x89\x44\x24\x08", 4, 80);
	GenerateIMULnewAssembly(0x425a4f, 0x425a56, AsmJit::eax, "\x89\x44\x24\x10", 4, 80);
	GenerateIMULnewAssembly(0x42e6a3, 0x42e6aa, AsmJit::eax, "\x89\x44\x24\x04", 4, 80);
	GenerateIMULnewAssembly(0x4876a3, 0x4876a8, AsmJit::eax, "\xDE\xD9", 2, 80);
	GenerateIMULnewAssembly(0x487ea3, 0x487ea8, AsmJit::eax, "\xDE\xD9", 2, 80);
	GenerateIMULnewAssembly(0x488143, 0x488148, AsmJit::eax, "\xDE\xD9", 2, 80);
	GenerateIMULnewAssembly(0x4bb059, 0x4bb05e, AsmJit::eax, "\xDE\xD9", 2, 80);
	GenerateIMULnewAssembly(0x4bb483, 0x4bb488, AsmJit::eax, "\xDE\xD9", 2, 80);
	GenerateIMULnewAssembly(0x4bdb33, 0x4bdb3a, AsmJit::eax, "\x89\x44\x24\x08", 4, 80);
	GenerateIMULnewAssembly(0x4c7421, 0x4c7428, AsmJit::eax, "\x89\x44\x24\x08", 4, 80);
	GenerateIMULnewAssembly(0x4c8f2c, 0x4c8f31, AsmJit::ebp, "\x01\xF5", 2, 80);
	GenerateIMULnewAssembly(0x4c9a7a, 0x4c9a81, AsmJit::eax, "\x89\x44\x24\x44", 4, 80);
	GenerateIMULnewAssembly(0x4d29fa, 0x4d2a00, AsmJit::edi, "\x50\x01\xF7", 3, 80);
	GenerateIMULnewAssembly(0x4d2b6a, 0x4d2b70, AsmJit::edi, "\x50\x01\xF7", 3, 80);
	GenerateIMULnewAssembly(0x4d2d56, 0x4d2d5c, AsmJit::esi, "\x50\x01\xFE", 3, 80);
	GenerateIMULnewAssembly(0x4d3371, 0x4d3378, AsmJit::eax, "\x89\x44\x24\x04", 4, 80);
	GenerateIMULnewAssembly(0x4d40a2, 0x4d40a9, AsmJit::eax, "\x89\x44\x24\x0C", 4, 80);
	GenerateIMULnewAssembly(0x4d531e, 0x4d5324, AsmJit::esi, "\x50\x01\xEE", 3, 80);
	GenerateIMULnewAssembly(0x4d54ee, 0x4d54f4, AsmJit::esi, "\x50\x01\xEE", 3, 80);
	GenerateIMULnewAssembly(0x4d567e, 0x4d5684, AsmJit::ebp, "\x50\x01\xDD", 3, 80);
	GenerateIMULnewAssembly(0x4d594f, 0x4d5956, AsmJit::eax, "\x89\x44\x24\x14", 4, 80);
	GenerateIMULnewAssembly(0x4d5ce5, 0x4d5cec, AsmJit::eax, "\x89\x44\x24\x18", 4, 80);
	GenerateIMULnewAssembly(0x4d60ff, 0x4d6106, AsmJit::eax, "\x89\x44\x24\x1C", 4, 80);
	GenerateIMULnewAssembly(0x4d64dd, 0x4d64e4, AsmJit::eax, "\x89\x44\x24\x1C", 4, 80);
	GenerateIMULnewAssembly(0x4d68dd, 0x4d68e4, AsmJit::eax, "\x89\x44\x24\x24", 4, 80);
	GenerateIMULnewAssembly(0x4d6cfd, 0x4d6d04, AsmJit::eax, "\x89\x44\x24\x1C", 4, 80);
	GenerateIMULnewAssembly(0x4d840e, 0x4d8413, AsmJit::eax, "\xDE\xD9", 2, 80);
	GenerateIMULnewAssembly(0x4d8c3a, 0x4d8c40, AsmJit::esi, "\x50\x01\xEE", 3, 80);
	GenerateIMULnewAssembly(0x4d9603, 0x4d9609, AsmJit::esi, "\x50\x01\xFE", 3, 80);
	GenerateIMULnewAssembly(0x4d963d, 0x4d9642, AsmJit::esi, "\xDE\xD9", 2, 80);
	GenerateIMULnewAssembly(0x4d96ea, 0x4d96ef, AsmJit::esi, "\xDE\xD9", 2, 80);
	GenerateIMULnewAssembly(0x4d97c0, 0x4d97c5, AsmJit::esi, "\xDE\xD9", 2, 80);
	GenerateIMULnewAssembly(0x4d986a, 0x4d986f, AsmJit::esi, "\xDE\xD9", 2, 80);
	GenerateIMULnewAssembly(0x4d9a93, 0x4d9a98, AsmJit::edi, "\xDE\xD9", 2, 80);
	GenerateIMULnewAssembly(0x4d9b3c, 0x4d9b41, AsmJit::edi, "\xDE\xD9", 2, 80);
	GenerateIMULnewAssembly(0x4d9c54, 0x4d9c5b, AsmJit::ebp, "\x03\x6C\x24\x04", 4, 80);
	GenerateIMULnewAssembly(0x4d9cfe, 0x4d9d05, AsmJit::edi, "\x03\x7C\x24\x04", 4, 80);
	GenerateIMULnewAssembly(0x4d9dbc, 0x4d9dc3, AsmJit::ebp, "\x03\x6C\x24\x10", 4, 80);
	GenerateIMULnewAssembly(0x4d9e65, 0x4d9e6c, AsmJit::edi, "\x03\x7C\x24\x10", 4, 80);
	GenerateIMULnewAssembly(0x4da04e, 0x4da053, AsmJit::edi, "\xDE\xD9", 2, 80);
	GenerateIMULnewAssembly(0x4da0fc, 0x4da101, AsmJit::edi, "\xDE\xD9", 2, 80);
	GenerateIMULnewAssembly(0x4da214, 0x4da21b, AsmJit::ebx, "\x03\x5C\x24\x08", 4, 80);
	GenerateIMULnewAssembly(0x4da2be, 0x4da2c5, AsmJit::edi, "\x03\x7C\x24\x08", 4, 80);
	GenerateIMULnewAssembly(0x4da37c, 0x4da383, AsmJit::ebx, "\x03\x5C\x24\x18", 4, 80);
	GenerateIMULnewAssembly(0x4da425, 0x4da42c, AsmJit::edi, "\x03\x7C\x24\x18", 4, 80);
	GenerateIMULnewAssembly(0x4da6eb, 0x4da6f3, AsmJit::ebp, "\x50\x03\x6C\x24\x30", 5, 80);
	GenerateIMULnewAssembly(0x4da736, 0x4da73b, AsmJit::esi, "\xDE\xD9", 2, 80);
	GenerateIMULnewAssembly(0x4da7cc, 0x4da7d1, AsmJit::ebp, "\xDE\xD9", 2, 80);
	GenerateIMULnewAssembly(0x4da886, 0x4da88b, AsmJit::esi, "\xDE\xD9", 2, 80);
	GenerateIMULnewAssembly(0x4da920, 0x4da925, AsmJit::ebp, "\xDE\xD9", 2, 80);
	GenerateIMULnewAssembly(0x4daa3f, 0x4daa44, AsmJit::ebx, "\xDE\xD9", 2, 80);
	GenerateIMULnewAssembly(0x4daada, 0x4daadf, AsmJit::ebx, "\xDE\xD9", 2, 80);
	GenerateIMULnewAssembly(0x4dabcd, 0x4dabd4, AsmJit::ebp, "\x03\x6C\x24\x0C", 4, 80);
	GenerateIMULnewAssembly(0x4dac5c, 0x4dac63, AsmJit::ebp, "\x03\x6C\x24\x0C", 4, 80);
	GenerateIMULnewAssembly(0x4dad06, 0x4dad0d, AsmJit::ebp, "\x03\x6C\x24\x24", 4, 80);
	GenerateIMULnewAssembly(0x4dad9c, 0x4dada3, AsmJit::ebp, "\x03\x6C\x24\x24", 4, 80);
	GenerateIMULnewAssembly(0x4dae9d, 0x4daea2, AsmJit::ebx, "\xDE\xD9", 2, 80);
	GenerateIMULnewAssembly(0x4daf3a, 0x4daf3f, AsmJit::ebx, "\xDE\xD9", 2, 80);
	GenerateIMULnewAssembly(0x4db031, 0x4db037, AsmJit::ebp, "\x03\x2C\x24", 3, 80);
	GenerateIMULnewAssembly(0x4db0bb, 0x4db0c1, AsmJit::ebp, "\x03\x2C\x24", 3, 80);
	GenerateIMULnewAssembly(0x4db162, 0x4db169, AsmJit::ebp, "\x03\x6C\x24\x24", 4, 80);
	GenerateIMULnewAssembly(0x4db1fc, 0x4db203, AsmJit::ebp, "\x03\x6C\x24\x24", 4, 80);
	GenerateIMULnewAssembly(0x4db72e, 0x4db733, AsmJit::ecx, "\x29\xC8", 2, 80);
	GenerateIMULnewAssembly(0x4db787, 0x4db78c, AsmJit::ebp, "\x29\xE8", 2, 80);
	GenerateIMULnewAssembly(0x4db7e1, 0x4db7e6, AsmJit::edi, "\x29\xF8", 2, 80);
	GenerateIMULnewAssembly(0x4db83b, 0x4db840, AsmJit::ecx, "\x29\xC8", 2, 80);
	GenerateIMULnewAssembly(0x4db895, 0x4db89a, AsmJit::ebp, "\x29\xE8", 2, 80);
	GenerateIMULnewAssembly(0x4db8ef, 0x4db8f4, AsmJit::edi, "\x29\xF8", 2, 80);
	GenerateIMULnewAssembly(0x4db949, 0x4db94e, AsmJit::ecx, "\x29\xC8", 2, 80);
	GenerateIMULnewAssembly(0x4e9c19, 0x4e9c1e, AsmJit::eax, "\xDE\xD9", 2, 80);
	GenerateIMULnewAssembly(0x4ea115, 0x4ea11a, AsmJit::eax, "\xDE\xD9", 2, 80);
	GenerateIMULnewAssembly(0x4f36de, 0x4f36e5, AsmJit::eax, "\x89\x44\x24\x3C", 4, 80);
	GenerateIMULnewAssembly(0x50d628, 0x50d62f, AsmJit::eax, "\x89\x44\x24\x20", 4, 80);
	GenerateIMULnewAssembly(0x51d35d, 0x51d362, AsmJit::eax, "\xDE\xD9", 2, 80);
	GenerateIMULnewAssembly(0x53d117, 0x53d11e, AsmJit::eax, "\x89\x44\x24\x14", 4, 80);
	GenerateIMULnewAssembly(0x55305a, 0x553061, AsmJit::eax, "\x89\x44\x24\x04", 4, 80);
	GenerateIMULnewAssembly(0x56c564, 0x56c56f, AsmJit::eax, "\xC7\x44\x24\x20\xA0\x15\x86\x00", 8, 80);
	GenerateIMULnewAssembly(0x56d0c4, 0x56d0cb, AsmJit::eax, "\x89\x44\x24\x08", 4, 80);
	GenerateIMULnewAssembly(0x587875, 0x58787c, AsmJit::eax, "\x89\x44\x24\x04", 4, 80);
	GenerateIMULnewAssembly(0x587cb9, 0x587cc0, AsmJit::eax, "\x89\x44\x24\x04", 4, 80);
	GenerateIMULnewAssembly(0x5a89c4, 0x5a89c9, AsmJit::edi, "\x01\xF7", 2, 80);
	GenerateIMULnewAssembly(0x5b52f2, 0x5b52f9, AsmJit::eax, "\x89\x44\x24\x0C", 4, 80);

	GenerateADDnewAssembly(0x40cea9, 0x40ceb0, false, 0, AsmJit::esi, "\x3B\x6C\x24\x08", 4, 80);
	GenerateADDnewAssembly(0x40d009, 0x40d010, false, 0, AsmJit::esi, "\x3B\x6C\x24\x08", 4, 80);
	GenerateADDnewAssembly(0x40d0a9, 0x40d0b0, false, 0, AsmJit::ebp, "\x3B\x74\x24\x08", 4, 80);
	GenerateADDnewAssembly(0x40e785, 0x40e78e, true, 20, AsmJit::no_reg, "\x3B\x44\x24\x20", 4, 80);
	GenerateADDnewAssembly(0x40ed5d, 0x40ed66, true, 28, AsmJit::no_reg, "\xFF\x44\x24\x14", 4, 80);
	GenerateADDnewAssembly(0x423f49, 0x423f52, true, 12, AsmJit::no_reg, "\x3B\x44\x24\x14", 4, 80);
	GenerateADDnewAssembly(0x42582b, 0x425834, true, 8, AsmJit::no_reg, "\x3B\x44\x24\x14", 4, 80);
	GenerateADDnewAssembly(0x425b7b, 0x425b84, true, 16, AsmJit::no_reg, "\x3B\x44\x24\x18", 4, 80);
	GenerateADDnewAssembly(0x42e70f, 0x42e718, true, 4, AsmJit::no_reg, "\x3B\x44\x24\x10", 4, 80);
	GenerateADDnewAssembly(0x487769, 0x487772, true, 28, AsmJit::no_reg, "\x3B\x44\x24\x20", 4, 80);
	GenerateADDnewAssembly(0x487fae, 0x487fb7, true, 28, AsmJit::no_reg, "\x3B\x44\x24\x20", 4, 80);
	GenerateADDnewAssembly(0x488229, 0x488232, true, 28, AsmJit::no_reg, "\x3B\x44\x24\x20", 4, 80);
	GenerateADDnewAssembly(0x4bb1e3, 0x4bb1ec, true, 36, AsmJit::no_reg, "\x3B\x44\x24\x28", 4, 80);
	GenerateADDnewAssembly(0x4bb596, 0x4bb59f, true, 28, AsmJit::no_reg, "\x3B\x44\x24\x20", 4, 80);
	GenerateADDnewAssembly(0x4bdbbd, 0x4bdbc6, true, 8, AsmJit::no_reg, "\x3B\x44\x24\x14", 4, 80);
	GenerateADDnewAssembly(0x4c74aa, 0x4c74b3, true, 8, AsmJit::no_reg, "\xFF\x44\x24\x0C", 4, 80);
	GenerateADDnewAssembly(0x4c8f43, 0x4c8f48, false, 0, AsmJit::ebp, "\x59\x43", 2, 80);
	GenerateADDnewAssembly(0x4c94b0, 0x4c94bd, true, 68, AsmJit::no_reg, "\x81\x44\x24\x40\x80\x0C\x00\x00", 8, 80);
	GenerateADDnewAssembly(0x4d345d, 0x4d3466, true, 4, AsmJit::no_reg, "\x3B\x44\x24\x10", 4, 80);
	GenerateADDnewAssembly(0x4d42cf, 0x4d42d8, true, 12, AsmJit::no_reg, "\x3B\x44\x24\x28", 4, 80);
	GenerateADDnewAssembly(0x4d5a6a, 0x4d5a73, true, 20, AsmJit::no_reg, "\x3B\x44\x24\x28", 4, 80);
	GenerateADDnewAssembly(0x4d5e81, 0x4d5e8a, true, 24, AsmJit::no_reg, "\x3B\x44\x24\x28", 4, 80);
	GenerateADDnewAssembly(0x4d6265, 0x4d626e, true, 28, AsmJit::no_reg, "\x3B\x44\x24\x28", 4, 80);
	GenerateADDnewAssembly(0x4d667f, 0x4d6688, true, 28, AsmJit::no_reg, "\x3B\x44\x24\x28", 4, 80);
	GenerateADDnewAssembly(0x4d6aa7, 0x4d6ab0, true, 36, AsmJit::no_reg, "\x3B\x44\x24\x28", 4, 80);
	GenerateADDnewAssembly(0x4d6e9f, 0x4d6ea8, true, 28, AsmJit::no_reg, "\x3B\x44\x24\x28", 4, 80);
	GenerateADDnewAssembly(0x4d84a8, 0x4d84b1, true, 12, AsmJit::no_reg, "\x3B\x44\x24\x18", 4, 80);
	GenerateADDnewAssembly(0x4d96ca, 0x4d96cf, false, 0, AsmJit::esi, "\x39\xEB", 2, 80);
	GenerateADDnewAssembly(0x4d9b22, 0x4d9b27, false, 0, AsmJit::edi, "\x39\xEE", 2, 80);
	GenerateADDnewAssembly(0x4d9ce2, 0x4d9ce7, false, 0, AsmJit::ebp, "\x39\xDE", 2, 80);
	GenerateADDnewAssembly(0x4d9e45, 0x4d9e4c, false, 0, AsmJit::ebp, "\x3B\x74\x24\x14", 4, 80);
	GenerateADDnewAssembly(0x4da0e2, 0x4da0e7, false, 0, AsmJit::edi, "\x39\xDE", 2, 80);
	GenerateADDnewAssembly(0x4da2a2, 0x4da2a7, false, 0, AsmJit::ebx, "\x39\xEE", 2, 80);
	GenerateADDnewAssembly(0x4da405, 0x4da40c, false, 0, AsmJit::ebx, "\x3B\x74\x24\x1C", 4, 80);
	GenerateADDnewAssembly(0x4da7b1, 0x4da7b8, false, 0, AsmJit::esi, "\x3B\x5C\x24\x08", 4, 80);
	GenerateADDnewAssembly(0x4daac2, 0x4daac7, false, 0, AsmJit::ebx, "\x39\xEE", 2, 80);
	GenerateADDnewAssembly(0x4dac46, 0x4dac4b, false, 0, AsmJit::ebp, "\x39\xDE", 2, 80);
	GenerateADDnewAssembly(0x4dad82, 0x4dad89, false, 0, AsmJit::ebp, "\x3B\x74\x24\x18", 4, 80);
	GenerateADDnewAssembly(0x4daf21, 0x4daf26, false, 0, AsmJit::ebx, "\x39\xEE", 2, 80);
	GenerateADDnewAssembly(0x4db0a9, 0x4db0ae, false, 0, AsmJit::ebp, "\x39\xDE", 2, 80);
	GenerateADDnewAssembly(0x4db1e2, 0x4db1e9, false, 0, AsmJit::ebp, "\x3B\x74\x24\x20", 4, 80);
	GenerateADDnewAssembly(0x4e9dff, 0x4e9e08, true, 20, AsmJit::no_reg, "\x3B\x44\x24\x20", 4, 80);
	GenerateADDnewAssembly(0x4ea4a6, 0x4ea4af, true, 72, AsmJit::no_reg, "\x3B\x44\x24\x4C", 4, 80);
	GenerateADDnewAssembly(0x4f3b28, 0x4f3b31, true, 60, AsmJit::no_reg, "\xFF\x44\x24\x38", 4, 80);
	GenerateADDnewAssembly(0x50d71b, 0x50d724, true, 32, AsmJit::no_reg, "\x3B\x44\x24\x24", 4, 80);
	GenerateADDnewAssembly(0x51d48d, 0x51d496, true, 36, AsmJit::no_reg, "\x3B\x44\x24\x30", 4, 80);
	GenerateADDnewAssembly(0x53d272, 0x53d27b, true, 20, AsmJit::no_reg, "\x3B\x44\x24\x1C", 4, 80);
	GenerateADDnewAssembly(0x5530cd, 0x5530d6, true, 4, AsmJit::no_reg, "\x3B\x44\x24\x10", 4, 80);
	GenerateADDnewAssembly(0x56c664, 0x56c66d, true, 12, AsmJit::no_reg, "\x3B\x44\x24\x1C", 4, 80);
	GenerateADDnewAssembly(0x56d2f3, 0x56d2fc, true, 8, AsmJit::no_reg, "\x3B\x44\x24\x1C", 4, 80);
	GenerateADDnewAssembly(0x5878c1, 0x5878ca, true, 4, AsmJit::no_reg, "\x3B\x44\x24\x10", 4, 80);
	GenerateADDnewAssembly(0x587d2f, 0x587d38, true, 4, AsmJit::no_reg, "\x3B\x44\x24\x10", 4, 80);
	GenerateADDnewAssembly(0x5b5481, 0x5b548a, true, 12, AsmJit::no_reg, "\x3B\x44\x24\x18", 4, 80);

	//add     [esp+30h+var_2C], 50h	//cmp     [esp+30h+var_30], 50h
	GenerateADDwithCMPnewAssembly(0x40f436, 0x40f43f, true, 4, AsmJit::no_reg, 80, true, 4, AsmJit::no_reg, 80, 4);
	//add     [esp+20h+var_1C], 50h	//cmp     [esp+20h+var_18], 50h
	GenerateADDwithCMPnewAssembly(0x40f5b7, 0x40f5c1, true, 4, AsmJit::no_reg, 80, true, 8, AsmJit::no_reg, 80, 4);
	//add     [esp+0C8h+var_88], 50h	//cmp     [esp+0C8h+var_84], 50h
	GenerateADDwithCMPnewAssembly(0x466a38, 0x466a42, true, 64, AsmJit::no_reg, 80, true, 68, AsmJit::no_reg, 80, 4);
	//add     [esp+20h+var_18], 50h	//cmp     [esp+20h+var_14], 50h
	GenerateADDwithCMPnewAssembly(0x4c6d4e, 0x4c6d58, true, 8, AsmJit::no_reg, 80, true, 12, AsmJit::no_reg, 80, 4);
	//add     [esp+18h+var_18], 50h	//cmp     [esp+18h+var_14], 50h
	GenerateADDwithCMPnewAssembly(0x4d4c1d, 0x4d4c26, true, 4, AsmJit::no_reg, 80, true, 4, AsmJit::no_reg, 80, 4);
	//add     edi, 50h	//cmp     [esp+30h+var_2C], 50h
	GenerateADDwithCMPnewAssembly(0x54fbc0, 0x54fbc8, false, 0, AsmJit::edi, 80, true, 4, AsmJit::no_reg, 80, 4);
	//add     ebp, 50h	//cmp     word ptr [esp+18h+var_14], 50h
	GenerateADDwithCMPnewAssembly(0x5a9552, 0x5a955b, false, 0, AsmJit::ebp, 80, true, 4, AsmJit::no_reg, 80, 2);

	GenerateSUBnewAssembly(0x4d9777, 0x4d977c, false, 0, AsmJit::esi, "\x39\xEB", 2, 80);
	GenerateSUBnewAssembly(0x4d9bd2, 0x4d9bd7, false, 0, AsmJit::edi, "\x39\xEB", 2, 80);
	GenerateSUBnewAssembly(0x4d9d87, 0x4d9d8c, false, 0, AsmJit::edi, "\x39\xDE", 2, 80);
	GenerateSUBnewAssembly(0x4d9ef2, 0x4d9ef9, false, 0, AsmJit::edi, "\x3B\x5C\x24\x14", 4, 80);
	GenerateSUBnewAssembly(0x4da192, 0x4da197, false, 0, AsmJit::edi, "\x39\xDD", 2, 80);
	GenerateSUBnewAssembly(0x4da347, 0x4da34c, false, 0, AsmJit::edi, "\x39\xEE", 2, 80);
	GenerateSUBnewAssembly(0x4da4b2, 0x4da4b9, false, 0, AsmJit::edi, "\x3B\x6C\x24\x1C", 4, 80);
	GenerateSUBnewAssembly(0x4da849, 0x4da850, false, 0, AsmJit::ebp, "\x3B\x5C\x24\x08", 4, 80);
	GenerateSUBnewAssembly(0x4dab57, 0x4dab5c, false, 0, AsmJit::ebx, "\x39\xEE", 2, 80);
	GenerateSUBnewAssembly(0x4dacd5, 0x4dacda, false, 0, AsmJit::ebp, "\x39\xDE", 2, 80);
	GenerateSUBnewAssembly(0x4dae15, 0x4dae1c, false, 0, AsmJit::ebp, "\x3B\x5C\x24\x18", 4, 80);
	GenerateSUBnewAssembly(0x4dafb7, 0x4dafbc, false, 0, AsmJit::ebx, "\x39\xEE", 2, 80);
	GenerateSUBnewAssembly(0x4db133, 0x4db138, false, 0, AsmJit::ebp, "\x39\xDE", 2, 80);
	GenerateSUBnewAssembly(0x4db275, 0x4db27c, false, 0, AsmJit::ebp, "\x3B\x5C\x24\x20", 4, 80);

	GenerateCMPWithouJumpnewAssembly(0x40e5cf, 0x40e5d6, false, 0, AsmJit::eax, "\x89\x44\x24\x10", 4, 79);
	GenerateCMPWithouJumpnewAssembly(0x40e60f, 0x40e616, false, 0, AsmJit::eax, "\x89\x44\x24\x20", 4, 79);
	GenerateCMPWithouJumpnewAssembly(0x40eb6b, 0x40eb72, false, 0, AsmJit::eax, "\x89\x44\x24\x10", 4, 79);
	GenerateCMPWithouJumpnewAssembly(0x40ebad, 0x40ebb4, false, 0, AsmJit::eax, "\x89\x44\x24\x28", 4, 79);
	GenerateCMPWithouJumpnewAssembly(0x423d44, 0x423d4b, false, 0, AsmJit::eax, "\x89\x44\x24\x04", 4, 79);
	GenerateCMPWithouJumpnewAssembly(0x423d86, 0x423d8d, false, 0, AsmJit::eax, "\x89\x44\x24\x14", 4, 79);
	GenerateCMPWithouJumpnewAssembly(0x4256e9, 0x4256f0, false, 0, AsmJit::eax, "\x89\x44\x24\x04", 4, 79);
	GenerateCMPWithouJumpnewAssembly(0x42572b, 0x425732, false, 0, AsmJit::eax, "\x89\x44\x24\x14", 4, 79);
	GenerateCMPWithouJumpnewAssembly(0x4259ab, 0x4259b2, false, 0, AsmJit::eax, "\x89\x44\x24\x08", 4, 79);
	GenerateCMPWithouJumpnewAssembly(0x4259ed, 0x4259f4, false, 0, AsmJit::eax, "\x89\x44\x24\x18", 4, 79);
	GenerateCMPWithouJumpnewAssembly(0x42e61e, 0x42e624, false, 0, AsmJit::eax, "\x89\x04\x24", 3, 79);
	GenerateCMPWithouJumpnewAssembly(0x42e65c, 0x42e663, false, 0, AsmJit::eax, "\x89\x44\x24\x10", 4, 79);
	GenerateCMPWithouJumpnewAssembly(0x4bdaa8, 0x4bdaaf, false, 0, AsmJit::eax, "\x89\x44\x24\x04", 4, 79);
	GenerateCMPWithouJumpnewAssembly(0x4bdaea, 0x4bdaf1, false, 0, AsmJit::eax, "\x89\x44\x24\x14", 4, 79);
	GenerateCMPWithouJumpnewAssembly(0x4c73fb, 0x4c7402, false, 0, AsmJit::eax, "\x89\x44\x24\x10", 4, 79);
	GenerateCMPWithouJumpnewAssembly(0x4c8e9a, 0x4c8ea1, false, 0, AsmJit::eax, "\x89\x44\x24\x04", 4, 79);
	GenerateCMPWithouJumpnewAssembly(0x4d332d, 0x4d3334, false, 0, AsmJit::eax, "\x89\x44\x24\x10", 4, 80);
	GenerateCMPWithouJumpnewAssembly(0x4d4010, 0x4d4017, false, 0, AsmJit::eax, "\x89\x44\x24\x08", 4, 80);
	GenerateCMPWithouJumpnewAssembly(0x4d4054, 0x4d405b, false, 0, AsmJit::eax, "\x89\x44\x24\x28", 4, 80);
	GenerateCMPWithouJumpnewAssembly(0x4d58c1, 0x4d58c8, false, 0, AsmJit::eax, "\x89\x44\x24\x08", 4, 80);
	GenerateCMPWithouJumpnewAssembly(0x4d5902, 0x4d5909, false, 0, AsmJit::eax, "\x89\x44\x24\x28", 4, 80);
	GenerateCMPWithouJumpnewAssembly(0x4d5c56, 0x4d5c5d, false, 0, AsmJit::eax, "\x89\x44\x24\x08", 4, 80);
	GenerateCMPWithouJumpnewAssembly(0x4d5c98, 0x4d5c9f, false, 0, AsmJit::eax, "\x89\x44\x24\x28", 4, 80);
	GenerateCMPWithouJumpnewAssembly(0x4d6071, 0x4d6078, false, 0, AsmJit::eax, "\x89\x44\x24\x08", 4, 80);
	GenerateCMPWithouJumpnewAssembly(0x4d60b2, 0x4d60b9, false, 0, AsmJit::eax, "\x89\x44\x24\x28", 4, 80);
	GenerateCMPWithouJumpnewAssembly(0x4d6447, 0x4d644e, false, 0, AsmJit::eax, "\x89\x44\x24\x08", 4, 80);
	GenerateCMPWithouJumpnewAssembly(0x4d648b, 0x4d6492, false, 0, AsmJit::eax, "\x89\x44\x24\x28", 4, 80);
	GenerateCMPWithouJumpnewAssembly(0x4d6847, 0x4d684e, false, 0, AsmJit::eax, "\x89\x44\x24\x08", 4, 80);
	GenerateCMPWithouJumpnewAssembly(0x4d688b, 0x4d6892, false, 0, AsmJit::eax, "\x89\x44\x24\x28", 4, 80);
	GenerateCMPWithouJumpnewAssembly(0x4d6c67, 0x4d6c6e, false, 0, AsmJit::eax, "\x89\x44\x24\x08", 4, 79);
	GenerateCMPWithouJumpnewAssembly(0x4d6cab, 0x4d6cb2, false, 0, AsmJit::eax, "\x89\x44\x24\x28", 4, 79);
	GenerateCMPWithouJumpnewAssembly(0x4d83a7, 0x4d83ae, false, 0, AsmJit::eax, "\x89\x44\x24\x08", 4, 79);
	GenerateCMPWithouJumpnewAssembly(0x4d83eb, 0x4d83f2, false, 0, AsmJit::eax, "\x89\x44\x24\x18", 4, 79);
	GenerateCMPWithouJumpnewAssembly(0x4e9bb0, 0x4e9bb7, false, 0, AsmJit::eax, "\x89\x44\x24\x10", 4, 79);
	GenerateCMPWithouJumpnewAssembly(0x4e9bf6, 0x4e9bfd, false, 0, AsmJit::eax, "\x89\x44\x24\x20", 4, 79);
	GenerateCMPWithouJumpnewAssembly(0x4ea090, 0x4ea097, false, 0, AsmJit::eax, "\x89\x44\x24\x3C", 4, 79);
	GenerateCMPWithouJumpnewAssembly(0x4ea0d6, 0x4ea0dd, false, 0, AsmJit::eax, "\x89\x44\x24\x4C", 4, 79);
	GenerateCMPWithouJumpnewAssembly(0x4f367f, 0x4f3686, false, 0, AsmJit::eax, "\x89\x44\x24\x30", 4, 80);
	GenerateCMPWithouJumpnewAssembly(0x4f36c5, 0x4f36cc, false, 0, AsmJit::eax, "\x89\x44\x24\x44", 4, 80);
	GenerateCMPWithouJumpnewAssembly(0x51d2e2, 0x51d2e9, false, 0, AsmJit::eax, "\x89\x44\x24\x10", 4, 79);
	GenerateCMPWithouJumpnewAssembly(0x51d32e, 0x51d335, false, 0, AsmJit::eax, "\x89\x44\x24\x30", 4, 79);
	GenerateCMPWithouJumpnewAssembly(0x53d066, 0x53d06d, false, 0, AsmJit::eax, "\x89\x44\x24\x0C", 4, 80);
	GenerateCMPWithouJumpnewAssembly(0x53d0a8, 0x53d0af, false, 0, AsmJit::eax, "\x89\x44\x24\x1C", 4, 80);
	GenerateCMPWithouJumpnewAssembly(0x55300f, 0x553016, false, 0, AsmJit::eax, "\x89\x44\x24\x10", 4, 79);
	GenerateCMPWithouJumpnewAssembly(0x56c4d4, 0x56c4db, false, 0, AsmJit::eax, "\x89\x44\x24\x08", 4, 79);
	GenerateCMPWithouJumpnewAssembly(0x56c516, 0x56c51d, false, 0, AsmJit::eax, "\x89\x44\x24\x1C", 4, 79);
	GenerateCMPWithouJumpnewAssembly(0x56d037, 0x56d03e, false, 0, AsmJit::eax, "\x89\x44\x24\x14", 4, 79);
	GenerateCMPWithouJumpnewAssembly(0x56d079, 0x56d080, false, 0, AsmJit::eax, "\x89\x44\x24\x1C", 4, 79);
	GenerateCMPWithouJumpnewAssembly(0x5877f0, 0x5877f6, false, 0, AsmJit::eax, "\x89\x04\x24", 3, 79);
	GenerateCMPWithouJumpnewAssembly(0x58782e, 0x587835, false, 0, AsmJit::eax, "\x89\x44\x24\x10", 4, 79);
	GenerateCMPWithouJumpnewAssembly(0x587c30, 0x587c36, false, 0, AsmJit::eax, "\x89\x04\x24", 3, 79);
	GenerateCMPWithouJumpnewAssembly(0x587c6e, 0x587c75, false, 0, AsmJit::eax, "\x89\x44\x24\x10", 4, 79);
	GenerateCMPWithouJumpnewAssembly(0x5b52a4, 0x5b52ab, false, 0, AsmJit::eax, "\x89\x44\x24\x18", 4, 80);

	GenerateCMPWithJumpnewAssembly(0x40cd6f, 0x40cd74, false, 0, AsmJit::eax, 79, ASM_JGE, 0x40cd80);
	GenerateCMPWithJumpnewAssembly(0x40cde9, 0x40cdee, false, 0, AsmJit::eax, 79, ASM_JGE, 0x40ce00);
	GenerateCMPWithJumpnewAssembly(0x40ce0f, 0x40ce14, false, 0, AsmJit::eax, 79, ASM_JGE, 0x40ce20);
	GenerateCMPWithJumpnewAssembly(0x40cf24, 0x40cf29, false, 0, AsmJit::eax, 79, ASM_JGE, 0x40cf30);
	GenerateCMPWithJumpnewAssembly(0x40cf49, 0x40cf4e, false, 0, AsmJit::eax, 79, ASM_JGE, 0x40cf60);
	GenerateCMPWithJumpnewAssembly(0x40d0ff, 0x40d104, false, 0, AsmJit::eax, 79, ASM_JGE, 0x40d113);
	GenerateCMPWithJumpnewAssembly(0x40d187, 0x40d18c, false, 0, AsmJit::eax, 79, ASM_JGE, 0x40d1a0);
	GenerateCMPWithJumpnewAssembly(0x40d1af, 0x40d1b4, false, 0, AsmJit::eax, 79, ASM_JGE, 0x40d1c3);
	GenerateCMPWithJumpnewAssembly(0x40d2f3, 0x40d2f8, false, 0, AsmJit::eax, 79, ASM_JGE, 0x40d307);
	GenerateCMPWithJumpnewAssembly(0x40d327, 0x40d32c, false, 0, AsmJit::eax, 79, ASM_JGE, 0x40d340);
	GenerateCMPWithJumpnewAssembly(0x40f699, 0x40f6a2, false, 0, AsmJit::eax, 80, ASM_JGE, 0x40f7a4);
	GenerateCMPWithJumpnewAssembly(0x40f6d2, 0x40f6db, false, 0, AsmJit::ebx, 80, ASM_JGE, 0x40f795);
	GenerateCMPWithJumpnewAssembly(0x40f7d1, 0x40f7da, false, 0, AsmJit::eax, 80, ASM_JGE, 0x40f8d5);
	GenerateCMPWithJumpnewAssembly(0x40f806, 0x40f80f, false, 0, AsmJit::ebx, 80, ASM_JGE, 0x40f8d5);
	GenerateCMPWithJumpnewAssembly(0x40f941, 0x40f94a, false, 0, AsmJit::eax, 80, ASM_JGE, 0x40fa54);
	GenerateCMPWithJumpnewAssembly(0x40f982, 0x40f98b, false, 0, AsmJit::ebx, 80, ASM_JGE, 0x40fa45);
	GenerateCMPWithJumpnewAssembly(0x40fa81, 0x40fa8a, false, 0, AsmJit::eax, 80, ASM_JGE, 0x40fb85);
	GenerateCMPWithJumpnewAssembly(0x40fac2, 0x40facb, false, 0, AsmJit::ebx, 80, ASM_JGE, 0x40fb85);
	GenerateCMPWithJumpnewAssembly(0x466a29, 0x466a34, true, 60, AsmJit::no_reg, 80, ASM_JL, 0x4661f0);
	GenerateCMPWithJumpnewAssembly(0x4c6d3f, 0x4c6d4a, true, 4, AsmJit::no_reg, 80, ASM_JL, 0x4c6c73);
	GenerateCMPWithJumpnewAssembly(0x4c8f1b, 0x4c8f20, false, 0, AsmJit::edi, 79, ASM_JL, 0x4c8f60);
	GenerateCMPWithJumpnewAssembly(0x4c9420, 0x4c942b, true, 32, AsmJit::no_reg, 80, ASM_JGE, 0x4c9a67);
	GenerateCMPWithJumpnewAssembly(0x4c9432, 0x4c9439, true, 8, AsmJit::no_reg, 80, ASM_JGE, 0x4c949e);
	GenerateCMPWithJumpnewAssembly(0x4c9475, 0x4c947c, true, 4, AsmJit::no_reg, 80, ASM_JZ, 0x4c949e);
	GenerateCMPWithJumpnewAssembly(0x4d2925, 0x4d292a, false, 0, AsmJit::esi, 79, ASM_JLE, 0x4d2931);
	GenerateCMPWithJumpnewAssembly(0x4d2940, 0x4d2945, false, 0, AsmJit::esi, 79, ASM_JLE, 0x4d294a);
	GenerateCMPWithJumpnewAssembly(0x4d297d, 0x4d2982, false, 0, AsmJit::edi, 79, ASM_JLE, 0x4d2990);
	GenerateCMPWithJumpnewAssembly(0x4d29a0, 0x4d29a5, false, 0, AsmJit::edi, 79, ASM_JLE, 0x4d29aa);
	GenerateCMPWithJumpnewAssembly(0x4d2a9b, 0x4d2aa0, false, 0, AsmJit::esi, 79, ASM_JLE, 0x4d2aa7);
	GenerateCMPWithJumpnewAssembly(0x4d2ab1, 0x4d2ab6, false, 0, AsmJit::esi, 79, ASM_JLE, 0x4d2abb);
	GenerateCMPWithJumpnewAssembly(0x4d2aef, 0x4d2af4, false, 0, AsmJit::edi, 79, ASM_JLE, 0x4d2b00);
	GenerateCMPWithJumpnewAssembly(0x4d2b10, 0x4d2b15, false, 0, AsmJit::edi, 79, ASM_JLE, 0x4d2b1a);
	GenerateCMPWithJumpnewAssembly(0x4d2c78, 0x4d2c7d, false, 0, AsmJit::edi, 79, ASM_JLE, 0x4d2c84);
	GenerateCMPWithJumpnewAssembly(0x4d2c90, 0x4d2c95, false, 0, AsmJit::edi, 79, ASM_JLE, 0x4d2c9a);
	GenerateCMPWithJumpnewAssembly(0x4d2cd0, 0x4d2cd5, false, 0, AsmJit::esi, 79, ASM_JLE, 0x4d2ce0);
	GenerateCMPWithJumpnewAssembly(0x4d2cf0, 0x4d2cf5, false, 0, AsmJit::esi, 79, ASM_JLE, 0x4d2cfa);
	GenerateCMPWithJumpnewAssembly(0x4d32f2, 0x4d32f7, false, 0, AsmJit::ebp, 80, ASM_JL, 0x4d32fc);
	GenerateCMPWithJumpnewAssembly(0x4d4c14, 0x4d4c19, false, 0, AsmJit::ebp, 80, ASM_JL, 0x4d4bd0);
	GenerateCMPWithJumpnewAssembly(0x4d5270, 0x4d5275, false, 0, AsmJit::ebp, 79, ASM_JLE, 0x4d527a);
	GenerateCMPWithJumpnewAssembly(0x4d52ad, 0x4d52b2, false, 0, AsmJit::esi, 79, ASM_JLE, 0x4d52c0);
	GenerateCMPWithJumpnewAssembly(0x4d52d0, 0x4d52d5, false, 0, AsmJit::esi, 79, ASM_JLE, 0x4d52da);
	GenerateCMPWithJumpnewAssembly(0x4d5422, 0x4d5427, false, 0, AsmJit::ebp, 79, ASM_JLE, 0x4d5430);
	GenerateCMPWithJumpnewAssembly(0x4d5440, 0x4d5445, false, 0, AsmJit::ebp, 79, ASM_JLE, 0x4d544a);
	GenerateCMPWithJumpnewAssembly(0x4d547d, 0x4d5482, false, 0, AsmJit::esi, 79, ASM_JLE, 0x4d5490);
	GenerateCMPWithJumpnewAssembly(0x4d54a0, 0x4d54a5, false, 0, AsmJit::esi, 79, ASM_JLE, 0x4d54aa);
	GenerateCMPWithJumpnewAssembly(0x4d55b7, 0x4d55bc, false, 0, AsmJit::ebx, 79, ASM_JLE, 0x4d55c3);
	GenerateCMPWithJumpnewAssembly(0x4d55d0, 0x4d55d5, false, 0, AsmJit::ebx, 79, ASM_JLE, 0x4d55da);
	GenerateCMPWithJumpnewAssembly(0x4d560d, 0x4d5612, false, 0, AsmJit::ebp, 79, ASM_JLE, 0x4d5620);
	GenerateCMPWithJumpnewAssembly(0x4d5630, 0x4d5635, false, 0, AsmJit::ebp, 79, ASM_JLE, 0x4d563a);
	GenerateCMPWithJumpnewAssembly(0x4d8b63, 0x4d8b68, false, 0, AsmJit::ebp, 79, ASM_JLE, 0x4d8b70);
	GenerateCMPWithJumpnewAssembly(0x4d8b80, 0x4d8b85, false, 0, AsmJit::ebp, 79, ASM_JLE, 0x4d8b8a);
	GenerateCMPWithJumpnewAssembly(0x4d8bbe, 0x4d8bc3, false, 0, AsmJit::esi, 79, ASM_JLE, 0x4d8bd0);
	GenerateCMPWithJumpnewAssembly(0x4d8be0, 0x4d8be5, false, 0, AsmJit::esi, 79, ASM_JLE, 0x4d8bea);
	GenerateCMPWithJumpnewAssembly(0x4d945f, 0x4d9464, false, 0, AsmJit::edi, 79, ASM_JLE, 0x4d9470);
	GenerateCMPWithJumpnewAssembly(0x4d9480, 0x4d9485, false, 0, AsmJit::edi, 79, ASM_JLE, 0x4d948a);
	GenerateCMPWithJumpnewAssembly(0x4d94b9, 0x4d94be, false, 0, AsmJit::esi, 79, ASM_JLE, 0x4d94c5);
	GenerateCMPWithJumpnewAssembly(0x4d94d0, 0x4d94d5, false, 0, AsmJit::esi, 79, ASM_JLE, 0x4d94da);
	GenerateCMPWithJumpnewAssembly(0x4d9509, 0x4d950e, false, 0, AsmJit::ebx, 79, ASM_JLE, 0x4d9515);
	GenerateCMPWithJumpnewAssembly(0x4d9520, 0x4d9525, false, 0, AsmJit::ebx, 79, ASM_JLE, 0x4d952a);
	GenerateCMPWithJumpnewAssembly(0x4d955b, 0x4d9560, false, 0, AsmJit::ebp, 79, ASM_JLE, 0x4d9567);
	GenerateCMPWithJumpnewAssembly(0x4d9571, 0x4d9576, false, 0, AsmJit::ebp, 79, ASM_JLE, 0x4d957b);
	GenerateCMPWithJumpnewAssembly(0x54fbb7, 0x54fbbc, false, 0, AsmJit::ebx, 80, ASM_JL, 0x54fb95);
	GenerateCMPWithJumpnewAssembly(0x5a9548, 0x5a954e, false, 0, AsmJit::si, 80, ASM_JL, 0x5a94e0);
	GenerateCMPWithJumpnewAssembly(0x5bc77d, 0x5bc782, false, 0, AsmJit::esi, 79, ASM_JL, 0x5bc786);
	GenerateCMPWithJumpnewAssembly(0x5bc78b, 0x5bc790, false, 0, AsmJit::eax, 79, ASM_JL, 0x5bc794);
}



#include "SJLIB\stdinc.h"

using namespace HookSystem;

/*
	The internal assembly has weird referencing stuff,
	Water Grids are accessed by multipliers of 32 and 16 sometimes to make things confusing,
	sometimes 4 * 32 = 128 and 2 * 32 = 64
	this makes things very confusing be warned
*/

#define WATER_BLOCK_WIDTH 64
#define WATER_FINEBLOCK_WIDTH 128
#define WATER_GRID_WIDTH 32
#define JUMPBO_MAP_WIDTH	6
BYTE	VisibleWaterGridStore[64 * 64 * JUMPBO_MAP_WIDTH * JUMPBO_MAP_WIDTH];
BYTE	PhysicalWaterGridStore[128 * 128 * JUMPBO_MAP_WIDTH * JUMPBO_MAP_WIDTH];
float	NorthSouthWaterOffset	= 0.0f;
float	XYOffset = 0.0f;
//==================================================================================
// For the patches.
DWORD	f2048		= 0x69CC54; //2048 
DWORD	f1By128		= 0x69CD8C; // 1/128
DWORD	f128		= 0x69CD18; // 128.0
DWORD	f64			= 0x69CD20;
DWORD	flt_69CC5C		= 0x69CC5C;
DWORD	REG_TEMP_EBX	= 0;

void _declspec(naked) Hook_RenderWater_GetWaterTileIndex(void) {
	_asm {
		mov REG_TEMP_EBX, ebx
		fadd NorthSouthWaterOffset
		mov ebx, f1By128 
		fmul dword ptr ds:[ebx]
		mov ebx, REG_TEMP_EBX
		ret
	}
}

void _declspec(naked) Hook_RenderTransparentWater_GetWaterTileIndex_2(void) {
	_asm {
		mov REG_TEMP_EBX, ebx
		fadd NorthSouthWaterOffset
		mov ebx, f2048
		fadd dword ptr ds:[ebx]
		mov ebx, REG_TEMP_EBX
		ret
	}
}

void _declspec(naked) Hook_RenderWater_GetWaterTileIndex_3(void) {
	_asm {
		mov REG_TEMP_EBX, ebx
		mov ebx, f2048
		fadd dword ptr ds:[ebx]
		fadd NorthSouthWaterOffset
		mov ebx, REG_TEMP_EBX
		ret
	}
}

void _declspec(naked) Hook_RenderWater_ToCoords_4(void) {
	_asm {
		mov REG_TEMP_EBX, ebx
		mov ebx, f128
		fmul dword ptr ds:[ebx]
		fsub NorthSouthWaterOffset
		mov ebx, REG_TEMP_EBX
		ret
	}
}

void _declspec(naked) Hook_BothRenderTransparentWater_GetWaterTileIndex(void) {
	_asm {
		mov REG_TEMP_EBX, ebx
		fadd NorthSouthWaterOffset
		mov ebx, f1By128
		fmul dword ptr ds:[ebx]
		mov ebx, REG_TEMP_EBX
		ret
	}
}
//==================================================================================
void _declspec(naked) Hook_RenderTransparentWater_ToCoords_2(void) {
	_asm {
		mov REG_TEMP_EBX, ebx
		fsub NorthSouthWaterOffset
		mov ebx, f64
		fadd dword ptr ds:[ebx]
		mov ebx, REG_TEMP_EBX
		ret
	}
}
//==================================================================================
void _declspec(naked) Hook_RenderTransparentWater_ToCoords_3(void) {
	_asm {
		mov REG_TEMP_EBX, ebx
		mov ebx, f64
		fmul dword ptr ds:[ebx]
		fsub NorthSouthWaterOffset
		mov ebx, REG_TEMP_EBX
		ret
	}
}
//==================================================================================
void _declspec(naked) Hook_GetWaterLevelNoWave_1(void) {
	_asm {
		mov REG_TEMP_EBX, ebx
		fadd NorthSouthWaterOffset
		mov ebx, flt_69CC5C
		fmul dword ptr ds:[ebx]
		mov ebx, REG_TEMP_EBX
		ret
	}
}
//==================================================================================
void _declspec(naked) Hook_GetWaterLevelNoWave_2(void) {
	_asm {
		mov REG_TEMP_EBX, ebx
		fadd NorthSouthWaterOffset
		mov ebx, flt_69CC5C
		fmul dword ptr ds:[ebx]
		mov ebx, REG_TEMP_EBX
		ret
	}
}
//==================================================================================
void _declspec(naked) Hook_WaterCamera_1(void) {
	_asm {
		mov REG_TEMP_EBX, ebx
		fadd NorthSouthWaterOffset
		mov ebx, f2048
		fadd dword ptr ds: [ebx]
		mov ebx, REG_TEMP_EBX
		ret
	}
}


//==================================================================================
DWORD	Func_RenderNearWater = 0x5BFF00;
DWORD	Func_SetRenderState = 0x649BA0;
DWORD	Func_RenderFarWater = 0x5C1710;
void _declspec(naked) RenderWaterAndEffects(void) {
		RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void*)TRUE);
        RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDONE);
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDZERO);
        RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDSRCALPHA);
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDINVSRCALPHA);
	_asm {
		push 1
		push 0x14
		call Func_SetRenderState
		pop ecx
		pop ecx
		call Func_RenderNearWater
		mov ecx, 4C9EF0h	// CRenderer::RenderBoats
		call ecx
		mov ecx, 4CA130h	// CRenderer::RenderFadingInUnderwaterEntities
		call ecx
		push 1
		push 0x14
		call Func_SetRenderState
		pop ecx
		pop ecx
		call Func_RenderFarWater
		ret
	}
}
//==================================================================================
// Douche Bag Justin Timberlake Functions
BYTE	TEMP_A10B36 = 0;
void _declspec(naked) RenderWaterAndEffects_OnlyWater(void) {
	_asm {
		push 1
		push 0x14
		call Func_SetRenderState
		pop ecx
		pop ecx
		call Func_RenderNearWater
		pushad
	}
	// This workaround solves the fast moving water.
	TEMP_A10B36 = *(PBYTE)0xA10B36;
	*(PBYTE)0xA10B36 = 1;
	_asm {
		popad
		push 1
		push 0x14
		call Func_SetRenderState
		pop ecx
		pop ecx
		call Func_RenderFarWater
		pushad
	}
	*(PBYTE)0xA10B36 = TEMP_A10B36;
	_asm {
		popad
		ret
	}
}

// why not have a jumbo one grid instead of thousands of grid;
/*

*/
//for every huge grids both water render calls are invoked with this
void RelocateGridDependencies(char watermapGrid) {
	// These patches relocate offset +0
    //Change references to waterpro segment 3 memory location
	CMemory::UnProtect(0x5C0618, 0x04); 
	CMemory::UnProtect(0x5C08C8, 0x04);
	CMemory::UnProtect(0x5C1232, 0x04);
	CMemory::UnProtect(0x5C1E54, 0x04);
	CMemory::UnProtect(0x5C201D, 0x04);
	CMemory::UnProtect(0x5C39AB, 0x04);
	*(PDWORD)0x5C0618 = (DWORD)&VisibleWaterGridStore[WATER_BLOCK_WIDTH * WATER_BLOCK_WIDTH * watermapGrid];
	*(PDWORD)0x5C08C8 = (DWORD)&VisibleWaterGridStore[WATER_BLOCK_WIDTH * WATER_BLOCK_WIDTH * watermapGrid];
	*(PDWORD)0x5C1232 = (DWORD)&VisibleWaterGridStore[WATER_BLOCK_WIDTH * WATER_BLOCK_WIDTH * watermapGrid];
	*(PDWORD)0x5C1E54 = (DWORD)&VisibleWaterGridStore[WATER_BLOCK_WIDTH * WATER_BLOCK_WIDTH * watermapGrid];
	*(PDWORD)0x5C201D = (DWORD)&VisibleWaterGridStore[WATER_BLOCK_WIDTH * WATER_BLOCK_WIDTH * watermapGrid];
	*(PDWORD)0x5C39AB = (DWORD)&VisibleWaterGridStore[WATER_BLOCK_WIDTH * WATER_BLOCK_WIDTH * watermapGrid];

	// These patches relocate offset +1

    //Change references to waterpro segment3 + 1
	CMemory::UnProtect(0x5C0644, 0x04);
	CMemory::UnProtect(0x5C1E78, 0x04);
	CMemory::UnProtect(0x5C205B, 0x04);
	*(PDWORD)0x5C0644 = (DWORD)&VisibleWaterGridStore[WATER_BLOCK_WIDTH * WATER_BLOCK_WIDTH * watermapGrid] + 1;
	*(PDWORD)0x5C1E78 = (DWORD)&VisibleWaterGridStore[WATER_BLOCK_WIDTH * WATER_BLOCK_WIDTH * watermapGrid] + 1;
	*(PDWORD)0x5C205B = (DWORD)&VisibleWaterGridStore[WATER_BLOCK_WIDTH * WATER_BLOCK_WIDTH * watermapGrid] + 1;

	// These patches relocate offset +64
	CMemory::UnProtect(0x5C0631, 0x04);
	CMemory::UnProtect(0x5C1E69, 0x04);
	CMemory::UnProtect(0x5C203C, 0x04);
	*(PDWORD)0x5C0631 = (DWORD)&VisibleWaterGridStore[WATER_BLOCK_WIDTH * WATER_BLOCK_WIDTH * watermapGrid] + (WATER_BLOCK_WIDTH);
	*(PDWORD)0x5C1E69 = (DWORD)&VisibleWaterGridStore[WATER_BLOCK_WIDTH * WATER_BLOCK_WIDTH * watermapGrid] + (WATER_BLOCK_WIDTH);
	*(PDWORD)0x5C203C = (DWORD)&VisibleWaterGridStore[WATER_BLOCK_WIDTH * WATER_BLOCK_WIDTH * watermapGrid] + (WATER_BLOCK_WIDTH);

	// These patches relocate offset +64 + 1
	CMemory::UnProtect(0x5C0657, 0x04);
	CMemory::UnProtect(0x5C1E87, 0x04);
	CMemory::UnProtect(0x5C207A, 0x04);
	*(PDWORD)0x5C0657 = (DWORD)&VisibleWaterGridStore[WATER_BLOCK_WIDTH * WATER_BLOCK_WIDTH * watermapGrid] + (WATER_BLOCK_WIDTH) + 1;
	*(PDWORD)0x5C1E87 = (DWORD)&VisibleWaterGridStore[WATER_BLOCK_WIDTH * WATER_BLOCK_WIDTH * watermapGrid] + (WATER_BLOCK_WIDTH) + 1;
	*(PDWORD)0x5C207A = (DWORD)&VisibleWaterGridStore[WATER_BLOCK_WIDTH * WATER_BLOCK_WIDTH * watermapGrid] + (WATER_BLOCK_WIDTH) + 1;

	// These patches relocate offset +0

    //Change references to waterpro segment4 (Physical Water Grid)
	CMemory::UnProtect(0x5BBB7C, 0x04);
	CMemory::UnProtect(0x5BBFBC, 0x04);
	CMemory::UnProtect(0x5BC6EE, 0x04);
	CMemory::UnProtect(0x5BCC2C, 0x04);
	CMemory::UnProtect(0x5BCFC6, 0x04);
	CMemory::UnProtect(0x5BF801, 0x04);
	CMemory::UnProtect(0x5C0ACC, 0x04);
	CMemory::UnProtect(0x5C2C56, 0x04);
	CMemory::UnProtect(0x5C2D03, 0x04);
	CMemory::UnProtect(0x5C39BE, 0x04);
	*(PDWORD)0x5BBB7C = (DWORD)&PhysicalWaterGridStore[WATER_FINEBLOCK_WIDTH * WATER_FINEBLOCK_WIDTH * watermapGrid];
	*(PDWORD)0x5BBFBC = (DWORD)&PhysicalWaterGridStore[WATER_FINEBLOCK_WIDTH * WATER_FINEBLOCK_WIDTH * watermapGrid];
	*(PDWORD)0x5BC6EE = (DWORD)&PhysicalWaterGridStore[WATER_FINEBLOCK_WIDTH * WATER_FINEBLOCK_WIDTH * watermapGrid];
	*(PDWORD)0x5BCC2C = (DWORD)&PhysicalWaterGridStore[WATER_FINEBLOCK_WIDTH * WATER_FINEBLOCK_WIDTH * watermapGrid];
	*(PDWORD)0x5BCFC6 = (DWORD)&PhysicalWaterGridStore[WATER_FINEBLOCK_WIDTH * WATER_FINEBLOCK_WIDTH * watermapGrid];
	*(PDWORD)0x5BF801 = (DWORD)&PhysicalWaterGridStore[WATER_FINEBLOCK_WIDTH * WATER_FINEBLOCK_WIDTH * watermapGrid];
	*(PDWORD)0x5C0ACC = (DWORD)&PhysicalWaterGridStore[WATER_FINEBLOCK_WIDTH * WATER_FINEBLOCK_WIDTH * watermapGrid];
	*(PDWORD)0x5C2C56 = (DWORD)&PhysicalWaterGridStore[WATER_FINEBLOCK_WIDTH * WATER_FINEBLOCK_WIDTH * watermapGrid];
	*(PDWORD)0x5C2D03 = (DWORD)&PhysicalWaterGridStore[WATER_FINEBLOCK_WIDTH * WATER_FINEBLOCK_WIDTH * watermapGrid];
	*(PDWORD)0x5C39BE = (DWORD)&PhysicalWaterGridStore[WATER_FINEBLOCK_WIDTH * WATER_FINEBLOCK_WIDTH * watermapGrid];

	// These patches relocate offset +1
	CMemory::UnProtect(0x5BF83E, 0x04);
	CMemory::UnProtect(0x5C0E6D, 0x04);
	*(PDWORD)0x5BF83E = (DWORD)&PhysicalWaterGridStore[WATER_FINEBLOCK_WIDTH * WATER_FINEBLOCK_WIDTH * watermapGrid] + 1;
	*(PDWORD)0x5C0E6D = (DWORD)&PhysicalWaterGridStore[WATER_FINEBLOCK_WIDTH * WATER_FINEBLOCK_WIDTH * watermapGrid] + 1;

	// These patches relocate offset +2
	CMemory::UnProtect(0x5BF877, 0x04);
	*(PDWORD)0x5BF877 = (DWORD)&PhysicalWaterGridStore[WATER_FINEBLOCK_WIDTH * WATER_FINEBLOCK_WIDTH * watermapGrid] + 2;

	// These patches relocate offset +(128)
	CMemory::UnProtect(0x5BF818, 0x04);
	CMemory::UnProtect(0x5C0C9D, 0x04);
	*(PDWORD)0x5BF818 = (DWORD)&PhysicalWaterGridStore[WATER_FINEBLOCK_WIDTH * WATER_FINEBLOCK_WIDTH * watermapGrid] + (WATER_FINEBLOCK_WIDTH );
	*(PDWORD)0x5C0C9D = (DWORD)&PhysicalWaterGridStore[WATER_FINEBLOCK_WIDTH * WATER_FINEBLOCK_WIDTH * watermapGrid] + (WATER_FINEBLOCK_WIDTH );

	// These patches relocate offset +(129)
	CMemory::UnProtect(0x5BF851, 0x04);
	CMemory::UnProtect(0x5C103F, 0x04);
	*(PDWORD)0x5BF851 = (DWORD)&PhysicalWaterGridStore[WATER_FINEBLOCK_WIDTH * WATER_FINEBLOCK_WIDTH * watermapGrid] + (WATER_FINEBLOCK_WIDTH ) + 1;
	*(PDWORD)0x5C103F = (DWORD)&PhysicalWaterGridStore[WATER_FINEBLOCK_WIDTH * WATER_FINEBLOCK_WIDTH * watermapGrid] + (WATER_FINEBLOCK_WIDTH ) + 1;

	// These patches relocate offset +130
	CMemory::UnProtect(0x5BF88A, 0x04);
	*(PDWORD)0x5BF88A = (DWORD)&PhysicalWaterGridStore[WATER_FINEBLOCK_WIDTH * WATER_FINEBLOCK_WIDTH * watermapGrid] + WATER_FINEBLOCK_WIDTH  + 2;

	// These patches relocate offset +256
	CMemory::UnProtect(0x5BF82B, 0x04);
	*(PDWORD)0x5BF82B = (DWORD)&PhysicalWaterGridStore[WATER_FINEBLOCK_WIDTH * WATER_FINEBLOCK_WIDTH * watermapGrid] + (2 * WATER_FINEBLOCK_WIDTH );

	// These patches relocate offset +257
	CMemory::UnProtect(0x5BF864, 0x04);
	*(PDWORD)0x5BF864 = (DWORD)&PhysicalWaterGridStore[WATER_FINEBLOCK_WIDTH * WATER_FINEBLOCK_WIDTH * watermapGrid] + (2 * WATER_FINEBLOCK_WIDTH ) + 1;

	// These patches relocate offset +258
	CMemory::UnProtect(0x5BF8A0, 0x04);
	*(PDWORD)0x5BF8A0 = (DWORD)&PhysicalWaterGridStore[WATER_FINEBLOCK_WIDTH * WATER_FINEBLOCK_WIDTH * watermapGrid] + (2 * WATER_FINEBLOCK_WIDTH ) + 2;
}

// water grids are 36 times bigger
void Hook_PreRenderNearWater(void) 
{
	*(float*)0x69CC58 = 400.0f;
	NorthSouthWaterOffset = 0.0f;
	RenderWaterAndEffects();
	for(BYTE i = 0; i < JUMPBO_MAP_WIDTH * JUMPBO_MAP_WIDTH; i++) {


		// These calculations render the designated water plane based off of offets in position.

		 float XPart = (float)(i % 6) - 2.0f;
		 float YPart = (float)(i / 6) - 2.0f;

		//*(float*)0x69CC58 = -4096.0f * XPart + 400.f;
		//NorthSouthWaterOffset = -4096.0f * YPart;

		RelocateGridDependencies(i);

		// : RenderWaterAndEffects_OnlyWater();
	}
}

void _hookcall_renderwater(void)
{
	*(float*)0x69CC58 = 400.0f;
	NorthSouthWaterOffset = 0.0f;
	
	for(int i = 0; i < JUMPBO_MAP_WIDTH * JUMPBO_MAP_WIDTH; i++) {
		 float XPart = (float)(i % 6) - 2.0f;
		 float YPart = (float)(i / 6) - 2.0f;

		 *(float*)0x69CC58 = -4096.0f * XPart + 400.f;
		NorthSouthWaterOffset = -4096.0f * YPart;

		RelocateGridDependencies(i);
		float fWaterSpeedtemp1 = *(float*)0x77FA74;
		float fWaterSpeedtemp2 = *(float*)0x77FA78;
		float fWaterSpeedtemp3 = *(float*)0x77FA7C;
		float fWaterSpeedtemp4 = *(float*)0x77FA80;
		float fWaterSpeedtemp5 = *(float*)0x77FA6C;
		float fWaterSpeedtemp6 = *(float*)0x77FA70;
		_asm
		{
			mov eax, 5C1710h
			call eax
		}
		*(float*)0x77FA74 = fWaterSpeedtemp1;
		*(float*)0x77FA78 = fWaterSpeedtemp2;
		*(float*)0x77FA7C = fWaterSpeedtemp3;
		*(float*)0x77FA80 = fWaterSpeedtemp4;
		*(float*)0x77FA6C = fWaterSpeedtemp5;
		*(float*)0x77FA70 = fWaterSpeedtemp6;
	}
}

void _hookcall_rendertransparentwater(void)
{
	*(float*)0x69CC58 = 400.0f;
	NorthSouthWaterOffset = 0.0f;
	
	for(int i = 0; i < JUMPBO_MAP_WIDTH * JUMPBO_MAP_WIDTH; i++) {
		 float XPart = (float)(i % 6) - 2.0f;
		 float YPart = (float)(i / 6) - 2.0f;

		*(float*)0x69CC58 = -4096.0f * XPart + 400.f;
		NorthSouthWaterOffset = -4096.0f * YPart;

		RelocateGridDependencies(i);
		float fWaterSpeedtemp = *(float*)0x77FA74;
		_asm
		{
			mov eax, 5BFF00h
			call eax
		}
		*(float*)0x77FA74 = fWaterSpeedtemp;
	}
}

void Hook__CWaterLevel_Initialize()
{
    __asm mov eax, 0x9B6CE8 //Water Levels
    __asm mov ds:[eax], 0
    RelocateGridDependencies(0);
}
//==================================================================================
//------------Needs-to-be-rechecked-and-patched-again-as-it-has-some-inconsistencies-and-seems-to-tamper-with-buoyancy-functions-----
//-----Crashes on clicking New game on the next run due to this-[THIS-ISSUE-HAS-BEEN-FIXED-BY-RESETING-RELOCATION-ON-EVERY-NEW-RUN]---
void PatchWater(void) 
{
	/*
	
    //Relocates the grid for preparation of use everytime New Game is clicked
    InstallNOPs(0x5C3940, 10);
    InstallFnByCall(0x5C3940, Hook__CWaterLevel_Initialize);

	// This patch removes the shiny area which appeared to be distorted below the player.
	//InstallNOPs(0x5C1525, 0x58);
	
	// Instantiate the references to and the new PHYSICAL water tile array itself.
	memset(&PhysicalWaterGridStore, 0x00, WATER_FINEBLOCK_WIDTH * WATER_FINEBLOCK_WIDTH * JUMPBO_MAP_WIDTH * JUMPBO_MAP_WIDTH);

	// Instantiate the references to and the new water tile array itself.
	memset(&VisibleWaterGridStore, 0x00, WATER_BLOCK_WIDTH * WATER_BLOCK_WIDTH * JUMPBO_MAP_WIDTH * JUMPBO_MAP_WIDTH);


	//CMemory::UnProtect(0x5BCF1C, 0x01);
	//CMemory::UnProtect(0x5BCF28, 0x01);
	//CMemory::UnProtect(0x5BCF74, 0x01);
	//CMemory::UnProtect(0x5BCF81, 0x01);
	//*(PBYTE)0x5BCF1C = (4 * WATER_GRID_WIDTH) - 1;
	//*(PBYTE)0x5BCF28 = (4 * WATER_GRID_WIDTH) - 1;
	//*(PBYTE)0x5BCF74 = (4 * WATER_GRID_WIDTH) - 1;
	//*(PBYTE)0x5BCF81 = (4 * WATER_GRID_WIDTH) - 1;
   
	// Install the patch for the size of the waterpro.dat area in CWaterLevel::Initialize
    // Visual Water Map
	CMemory::UnProtect(0x5C39A6, 0x04); // Inside CWaterLevel::Initialize
	*(PDWORD)0x5C39A6 = sizeof(VisibleWaterGridStore);

    // Physical Water Map
	CMemory::UnProtect(0x5C39B9, 0x04); // Inside CWaterLevel::Initialize
	*(PDWORD)0x5C39B9 = sizeof(PhysicalWaterGridStore);

	// Install the patches (water plane constructor) that allow for north/south boundary manipulation.
	//JUSTINInstallNOPs(0x5C1D03, 0x06);
	InstallNOPs(0x5C1D0D, 0x06);
	InstallFnByCall(0x5C1D0D, Hook_RenderWater_GetWaterTileIndex);

	InstallNOPs(0x5C1D45, 0x06);
	InstallFnByCall(0x5C1D45, Hook_RenderWater_GetWaterTileIndex);

	InstallNOPs(0x5C1C10, 0x06);
	InstallNOPs(0x5C1C45, 0x06);
	InstallNOPs(0x5C02F5, 0x06);
	InstallNOPs(0x5C0337, 0x06); 
	InstallFnByCall(0x5C1C10, Hook_RenderWater_GetWaterTileIndex_3);
	InstallFnByCall(0x5C1C45, Hook_RenderWater_GetWaterTileIndex_3);
	InstallFnByCall(0x5C02F5, Hook_RenderTransparentWater_GetWaterTileIndex_2);
	InstallFnByCall(0x5C0337, Hook_RenderTransparentWater_GetWaterTileIndex_2);

	InstallNOPs(0x5C1EA1, 0x06);
	InstallFnByCall(0x5C1EA1, Hook_RenderWater_ToCoords_4);

	InstallNOPs(0x5C041B, 0x06);
	InstallNOPs(0x5C0460, 0x06);
	InstallFnByCall(0x5C041B, Hook_BothRenderTransparentWater_GetWaterTileIndex);
	InstallFnByCall(0x5C0460, Hook_BothRenderTransparentWater_GetWaterTileIndex);

	InstallNOPs(0x5C0690, 0x06);
	InstallFnByCall(0x5C0690, Hook_RenderTransparentWater_ToCoords_2);

	InstallNOPs(0x5C08EE, 0x06);
	InstallFnByCall(0x5C08EE, Hook_RenderTransparentWater_ToCoords_3);

	// Install patch in GetWaterLevelNoWaves.
	InstallNOPs(0x5C2BF1, 0x06);
	InstallFnByCall(0x5C2BF1, Hook_GetWaterLevelNoWave_1);

	// Install patch in GetWaterLevel.
	InstallNOPs(0x5C2CD3, 6);
	InstallFnByCall(0x5C2CD3, Hook_GetWaterLevelNoWave_2);

	// Install patch in the camera processor.
	//InstallNOPs(0x5BCEDD, 6);
    //InstallNOPs(0x5BCF34, 6);
	//InstallFnByCall(0x5BCEDD, (DWORD)Hook_WaterCamera_1);
	//InstallFnByCall(0x5BCF34, (DWORD)Hook_WaterCamera_1);
	
	*(float*)0x69CC5C = 1.0f / (float)WATER_GRID_WIDTH;

	InstallFnByCall(0x4A6594, _hookcall_renderwater);
	InstallFnByCall(0x4A65AE, _hookcall_rendertransparentwater);*/
	RelocateGridDependencies(0);
	void HookRenderWater();
	HookRenderWater();
	void HookRenderTransparentWater();
	HookRenderTransparentWater();
	//InstallNOPs(0x5C1B8C, 1380); //RenderWaters in CWaterLevel::RenderWater
	InstallNOPs(0x5C20F0, 0x7FC);//WaterLODs
	//InstallNOPs(0x4A65AE, 5); //rendertransparentwater
	*(float*)0x69C780 += 8000.0f; // heliheight
}



//SWOOORUP's WAY START 
// Need fixing dword ptrs and things like that
#define ASMJMP(x) {_asm push x _asm retn} 
#define _NEW_CMP_MOV_OPND 191

//jmp hook at 5C1E1Ah
void _declspec(naked) _hookSHL5C1E1A()
{
	_asm
	{
		mov ebx, dword ptr [esp + 1Ch]
		mov eax, ebx
		shl eax, 1
		add eax, ebx
		shl eax, 7
		mov dword ptr [esp + 1Ch], eax
		mov eax, 5C1E1Fh
		jmp eax
	}
}

//jmp hook at 5C20DB
void _declspec(naked) _hookADD5C20DB()
{
	_asm
	{
		add dword ptr[esp+1Ch], 384
		mov ebp, 5C20E0h
		jmp ebp
	}
}

//jmp hook at 5C1E34
void _declspec(naked) _hookADDMinus165C1E34()
{
	_asm
	{
		add eax, -96
		mov [esp+68h], eax
		mov eax, 5C1E3Bh
		jmp eax
	}
}

//jmp hook at 5C1E96

void _declspec(naked) _hookLEAMinus165C1E96()
{
	_asm
	{
		lea eax, [ebp - 96]
		mov [esp+68h], eax
		mov eax, 5C1E9Dh
		jmp eax
	}
}
#pragma comment(lib,"asmjit.lib")

void* GenRoutine_CmpWaterIndexFix(AsmJit::X86Assembler& a, DWORD dwAddrConditionFalse, DWORD dwAddrConditionTrue)
{
	a.reset();
	AsmJit::Label L_true = a.newLabel();

	// start
	a.cmp(AsmJit::eax, _NEW_CMP_MOV_OPND);
	a.jge(L_true);
	a.jmp(dwAddrConditionFalse);
	a.bind(L_true);
	a.jmp(dwAddrConditionTrue);
	// end

	return a.make();
}

void HookRenderWater()
{
	DWORD dwVp;
	VirtualProtect((void*)0x401000, 0x27CE00, PAGE_EXECUTE_READWRITE, &dwVp);
	
	int nWaterGridMultiplier = 6;

	static float fnew2048forRender = 2048.0f * nWaterGridMultiplier;
	
	DWORD dwRefsTo2048f[] = {0x5c1b8e,0x5c1bcd,0x5c1c12,0x5c1c47,0x5c1c81,0x5c1cc3,0x5c1d05,0x5c1d3d,};
	for(int i = 0; i < ARRLEN(dwRefsTo2048f); i++)
	{
		*((DWORD*)dwRefsTo2048f[i]) = (DWORD)&fnew2048forRender;
	}
	
	DWORD dwMaxIndex_31s[] = {0x5c1d9c,0x5c1dcc,0x5c1de8,0x5c1e04,};
	for(int i = 0; i < ARRLEN(dwMaxIndex_31s); i++)
	{
		*((DWORD*)dwMaxIndex_31s[i]) = _NEW_CMP_MOV_OPND;
	}
	
	// Fix cmp instructions
	AsmJit::X86Assembler a;
	AsmJit::FileLogger logger(stdout);
	a.setLogger(&logger);
	InstallFnByJump(0x5c1d82, GenRoutine_CmpWaterIndexFix(a, 0x5C1D87, 0x5C1D98));
	InstallFnByJump(0x5C1DB2, GenRoutine_CmpWaterIndexFix(a, 0x5C1DB7, 0x5C1DC8));
	InstallFnByJump(0x5C1DDA, GenRoutine_CmpWaterIndexFix(a, 0x5C1DDF, 0x5C1DE7));
	InstallFnByJump(0x5C1DF6, GenRoutine_CmpWaterIndexFix(a, 0x5C1DFB, 0x5C1E03));
	a.reset();
	
	// Fix Multiplier Instruction
	InstallFnByJump(0x5C1E1A, _hookSHL5C1E1A);
	
	InstallNOPs(0x5C1E34, 7);
	InstallFnByJump(0x5C1E34, _hookADDMinus165C1E34);
	InstallNOPs(0x5C1E96, 7);
	InstallFnByJump(0x5C1E96, _hookLEAMinus165C1E96);
	
	InstallFnByJump(0x5C20DB, _hookADD5C20DB);
	
	DWORD dwVp2;
	VirtualProtect((void*)0x401000, 0x27CE00, dwVp, &dwVp2);
}


// Hooks for render transparent water

//jmp hook 5C0578
int _nTEMP;
void _declspec(naked) _hookSHL_5C0578()
{
	_asm
	{
		mov _nTEMP, eax
		mov eax, [esp + 54h]
		mov edi, eax
		shl eax, 1
		add eax, edi
		shl eax, 7
		mov [esp+54h], eax
		mov eax, 5C057Dh
		push eax
		mov eax, _nTEMP
		ret
	}
}

//jmp hook at 5C05CC
void _declspec(naked) _hookADD_minus16_5C05CC()
{
	_asm
	{
		add eax, -96
		mov [esp+0C0h],eax
		mov eax, 5C05D6h
		jmp eax
	}
}

//jmp hook at 5c0677
void _declspec(naked) _hookADD_minus16_5c0677()
{
	_asm
	{
		add eax, -96
		mov [esp+0C0h],eax
		mov eax, 5C0681h
		jmp eax
	}
}

//jmp hook at 5C0835, EBX, EAX
void _declspec(naked) _hookSHL_5C0835()
{
	_asm
	{
		mov [esp], eax
		mov eax, [esp+0Ch]
		mov ebx, eax
		shl eax, 1
		add eax, ebx
		shl eax, 8
		mov [esp+0Ch], eax
		mov eax, 5C083Dh
		jmp eax
	}
}

//jmp hook at 5C0857
void _declspec(naked) _hookSHL_5C0857()
{
	_asm
	{
		mov [esp+18h], eax
		mov eax, [esp]
		mov ebx, eax
		shl eax, 1
		add eax, ebx
		shl eax, 7
		mov [esp],eax
		mov eax, 5C085Fh
		jmp eax
	}
}

//jmp hook 5C087E
void _declspec(naked) _hookADD_minus32_5C087E()
{
	_asm
	{
		add eax, -192
		mov [esp+0C0h], eax
		mov eax, 5C0888h
		jmp eax
	}
}

//jmp hook 5C08DD
void _declspec(naked) _hookLEA_minus32_5C08DD()
{
	_asm
	{
		lea eax, [ebx - 192]
		mov [esp+0C0h],eax
		mov eax, 5C08E7h
		jmp eax
	}
}

//jmp hook 5C144E
void _declspec(naked) _hookADD64_128_5C144E()
{
	_asm
	{
		add dword ptr[esp], 384
		add dword ptr[esp+0Ch], 768
		mov eax, 5C1457h
		jmp eax
	}
}

//jmp hook 5C1496
//assume ebx free
void _declspec(naked) _hookADD64_5C1496()
{
	_asm
	{
		add dword ptr[esp+54h], 384
		mov ebp, 5C149Bh
		jmp ebp
	}
}

void HookRenderTransparentWater(void)
{
	DWORD dwVp;
	VirtualProtect((void*)0x401000, 0x27CE00, PAGE_EXECUTE_READWRITE, &dwVp);
	DWORD dwRefsTo2048f[] = {0x5c0261,0x5c02a9,0x5c02f7,0x5c0339,0x5c037d,0x5c03c5,0x5c0410,0x5c0455,};
	
	int nWaterGridMultiplier = 6;
	static float fnew2048forRender = 2048.0f * nWaterGridMultiplier;
	for(int i = 0; i < ARRLEN(dwRefsTo2048f); i++)
	{
		*((float**)dwRefsTo2048f[i]) = &fnew2048forRender;
	}
	
	// Fix cmp instructions
	AsmJit::X86Assembler a;
	FILE* fp = fopen("asmjit.txt", "w");
	AsmJit::FileLogger logger(fp);
	a.setLogger(&logger);
	InstallFnByJump(0x5C04A2, GenRoutine_CmpWaterIndexFix(a, 0x5C04A7, 0x5C04B8));
	InstallFnByJump(0x5C04D2, GenRoutine_CmpWaterIndexFix(a, 0x5C04D7, 0x5C04E8));
	InstallFnByJump(0x5C0502, GenRoutine_CmpWaterIndexFix(a, 0x5C0507, 0x5C0518));
	InstallFnByJump(0x5C0532, GenRoutine_CmpWaterIndexFix(a, 0x5C0537, 0x5C0548));
	a.reset();
	
	DWORD dw31s[] = {0x5c04bc,0x5c04ec,0x5c051c,0x5c054c,};
	
	for(int i = 0; i < ARRLEN(dw31s); i++)
	{
		*((DWORD*)dw31s[i]) = _NEW_CMP_MOV_OPND;
	}
	
	//assuming I hv control over edi
	InstallFnByJump(0x5C0578, _hookSHL_5C0578);
	
	InstallNOPs(0x5C05CC, 10);
	InstallFnByJump(0x5C05CC, _hookADD_minus16_5C05CC);
	InstallNOPs(0x5c0677, 10);
	InstallFnByJump(0x5c0677, _hookADD_minus16_5c0677);
		
	InstallFnByJump(0x5C0835, _hookSHL_5C0835);
	InstallNOPs(0x5C0857, 8);
	InstallFnByJump(0x5C0857, _hookSHL_5C0857);
	
	InstallNOPs(0x5C087E, 10);
	InstallFnByJump(0x5C087E, _hookADD_minus32_5C087E);
	
	InstallNOPs(0x5C08DD, 10);
	InstallFnByJump(0x5C08DD, _hookLEA_minus32_5C08DD);
	
	InstallNOPs(0x5C144E, 9);
	InstallFnByJump(0x5C144E, _hookADD64_128_5C144E);
	
	InstallFnByJump(0x5C1496, _hookADD64_5C1496);
	DWORD dwVp2;
	VirtualProtect((void*)0x401000, 0x27CE00, dwVp, &dwVp2);
}
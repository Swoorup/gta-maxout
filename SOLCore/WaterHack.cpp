#include "main.h"


//==================================================================================
#define WATER_GRID_WIDTH 32
#define	WaterGridWidth 32 //Is byte
float	GlobalMapShiftLR	= 3 * 4096.f; // 3 equivalents to VC to the left plus the normal VC shift
BYTE	MapTileWidth		= 6;
#define WATER_MAP_WIDTH	6
BYTE	VisibleWaterGridStore[4 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WATER_MAP_WIDTH * WATER_MAP_WIDTH];
BYTE	PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WATER_MAP_WIDTH * WATER_MAP_WIDTH];
float	NorthSouthWaterOffset	= 0.0f;
float	XYOffset = 0.0f;
//==================================================================================
// For the patches.
DWORD	NSBoundOffset	= (DWORD)&NorthSouthWaterOffset;
DWORD	flt_69CC54		= 0x69CC54; //2048 original
DWORD	flt_69CD8C		= 0x69CD8C;
DWORD	flt_69CD18		= 0x69CD18;
DWORD	flt_69CD20		= 0x69CD20;
DWORD	flt_69CC5C		= 0x69CC5C;
DWORD	REG_TEMP_EBX	= 0;
//==================================================================================
void _declspec(naked) Hook_WaterPlaneConstruct_1(void) {
	_asm {
		mov REG_TEMP_EBX, ebx
		mov ebx, NSBoundOffset
		fadd dword ptr ds:[ebx]
		mov ebx, flt_69CD8C
		fmul dword ptr ds:[ebx]
		mov ebx, REG_TEMP_EBX
		ret
	}
}
//==================================================================================
void _declspec(naked) Hook_WaterPlaneConstruct_2(void) {
	_asm {
		mov REG_TEMP_EBX, ebx
		mov ebx, NSBoundOffset
		fadd dword ptr ds:[ebx]
		mov ebx, flt_69CC54
		fadd dword ptr ds:[ebx]
		mov ebx, REG_TEMP_EBX
		ret
	}
}
//==================================================================================
void _declspec(naked) Hook_WaterPlaneConstruct_3(void) {
	_asm {
		mov REG_TEMP_EBX, ebx
		mov ebx, flt_69CC54
		fadd dword ptr ds:[ebx]
		mov ebx, NSBoundOffset
		fadd dword ptr ds:[ebx]
		mov ebx, REG_TEMP_EBX
		ret
	}
}
//==================================================================================
void _declspec(naked) Hook_WaterPlaneConstruct_4(void) {
	_asm {
		mov REG_TEMP_EBX, ebx
		mov ebx, flt_69CD18
		fmul dword ptr ds:[ebx]
		mov ebx, NSBoundOffset
		fsub dword ptr ds: [ebx]
		mov ebx, REG_TEMP_EBX
		ret
	}
}
//==================================================================================
void _declspec(naked) Hook_WaterPlaneDestruct_1(void) {
	_asm {
		mov REG_TEMP_EBX, ebx
		mov ebx, NSBoundOffset
		fadd dword ptr ds: [ebx]
		mov ebx, flt_69CD8C
		fmul dword ptr ds:[ebx]
		mov ebx, REG_TEMP_EBX
		ret
	}
}
//==================================================================================
void _declspec(naked) Hook_WaterPlaneDestruct_2(void) {
	_asm {
		mov REG_TEMP_EBX, ebx
		mov ebx, NSBoundOffset
		fsub dword ptr ds: [ebx]
		mov ebx, flt_69CD20
		fadd dword ptr ds:[ebx]
		mov ebx, REG_TEMP_EBX
		ret
	}
}
//==================================================================================
void _declspec(naked) Hook_WaterPlaneDestruct_3(void) {
	_asm {
		mov REG_TEMP_EBX, ebx
		mov ebx, flt_69CD20
		fmul dword ptr ds:[ebx]
		mov ebx, NSBoundOffset
		fsub dword ptr ds: [ebx]
		mov ebx, REG_TEMP_EBX
		ret
	}
}
//==================================================================================
void _declspec(naked) Hook_GetWaterLevelNoWave_1(void) {
	_asm {
		mov REG_TEMP_EBX, ebx
		mov ebx, NSBoundOffset
		fadd dword ptr ds: [ebx]
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
		mov ebx, NSBoundOffset
		fadd dword ptr ds: [ebx]
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
		mov ebx, NSBoundOffset
		fadd dword ptr ds: [ebx]
		mov ebx, flt_69CC54
		fadd dword ptr ds: [ebx]
		mov ebx, REG_TEMP_EBX
		ret
	}
}
//==================================================================================
// TODO: Make dynamic
void _declspec(naked) Hook_RelocateArraySizesForWater(void) {
	_asm {
		ADD DWORD PTR SS:[ESP],64
		SUB DWORD PTR SS:[ESP+0xC],128
		INC DWORD PTR SS:[ESP+0x4]
		ret
	}
}
//==================================================================================
// TODO: Make dynamic
void _declspec(naked) Hook_RelocateArraySizesForWater2(void) {
	_asm {
		add [esp+0x54], 64
		add [esp+0x58], 2
		ret
	}
}
//==================================================================================
DWORD	Func_RenderNearWater = 0x5BFF00;
DWORD	Func_SetRenderState = 0x649BA0;
DWORD	Func_RenderFarWater = 0x5C1710;
DWORD	Func_4C9EF0 = 0x4C9EF0;
DWORD	Func_4CA130 = 0x4CA130;
void _declspec(naked) RenderWaterAndEffects(void) {
	_asm {
		push 1
		push 0x14
		call Func_SetRenderState
		pop ecx
		pop ecx
		call Func_RenderNearWater
		call Func_4C9EF0	// Something with atmospheric effects (clouds, brown background, etc.)
		call Func_4CA130	// Something with alpha objects rendering
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



//==================================================================================
char	StoredWaterTileIndex = -1;
char GetCurrentWaterTileIndex(void) {
	if(FindPlayerPed()) {
		RwV3d *Position;
		Position = FindPlayerCentreOfWorld_NoSniperShift();
        
		float	InternalPlayerX = Position->x, InternalPlayerY = Position->y;
		InternalPlayerX += GlobalMapShiftLR - 1648.f;
		InternalPlayerY += GlobalMapShiftLR - 2048.f;
		char	CurrentXTile = (BYTE)(InternalPlayerX / (float)4096.f);
		char	CurrentYTile = (BYTE)(InternalPlayerY / (float)4096.f);
		if(CurrentXTile < 0) CurrentXTile = 0;
		if(CurrentXTile > (MapTileWidth - 1)) CurrentXTile = (MapTileWidth - 1);
		if(CurrentYTile < 0) CurrentYTile = 0;
		if(CurrentYTile > (MapTileWidth - 1)) CurrentYTile = (MapTileWidth - 1);
		return (CurrentXTile + MapTileWidth * CurrentYTile);
	}
	return -1;
}
//==================================================================================
void RelocateGridDependencies(char WaterTileIndex) {
	if(WaterTileIndex < 0 || WaterTileIndex >= (WaterGridWidth * WaterGridWidth)) return;

	// These patches relocate offset +0

    //Change references to waterpro segment 3 memory location
	CMemory::UnProtect(0x5C0618, 0x04); 
	CMemory::UnProtect(0x5C08C8, 0x04);
	CMemory::UnProtect(0x5C1232, 0x04);
	CMemory::UnProtect(0x5C1E54, 0x04);
	CMemory::UnProtect(0x5C201D, 0x04);
	CMemory::UnProtect(0x5C39AB, 0x04);
	*(PDWORD)0x5C0618 = (DWORD)&VisibleWaterGridStore[4 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WaterTileIndex];
	*(PDWORD)0x5C08C8 = (DWORD)&VisibleWaterGridStore[4 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WaterTileIndex];
	*(PDWORD)0x5C1232 = (DWORD)&VisibleWaterGridStore[4 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WaterTileIndex];
	*(PDWORD)0x5C1E54 = (DWORD)&VisibleWaterGridStore[4 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WaterTileIndex];
	*(PDWORD)0x5C201D = (DWORD)&VisibleWaterGridStore[4 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WaterTileIndex];
	*(PDWORD)0x5C39AB = (DWORD)&VisibleWaterGridStore[4 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WaterTileIndex];

	// These patches relocate offset +1

    //Change references to waterpro segment3 + 1
	CMemory::UnProtect(0x5C0644, 0x04);
	CMemory::UnProtect(0x5C1E78, 0x04);
	CMemory::UnProtect(0x5C205B, 0x04);
	*(PDWORD)0x5C0644 = (DWORD)&VisibleWaterGridStore[4 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WaterTileIndex] + 1;
	*(PDWORD)0x5C1E78 = (DWORD)&VisibleWaterGridStore[4 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WaterTileIndex] + 1;
	*(PDWORD)0x5C205B = (DWORD)&VisibleWaterGridStore[4 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WaterTileIndex] + 1;

	// These patches relocate offset +(2 * WaterGridWidth)
	CMemory::UnProtect(0x5C0631, 0x04);
	CMemory::UnProtect(0x5C1E69, 0x04);
	CMemory::UnProtect(0x5C203C, 0x04);
	*(PDWORD)0x5C0631 = (DWORD)&VisibleWaterGridStore[4 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WaterTileIndex] + (2 * WaterGridWidth);
	*(PDWORD)0x5C1E69 = (DWORD)&VisibleWaterGridStore[4 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WaterTileIndex] + (2 * WaterGridWidth);
	*(PDWORD)0x5C203C = (DWORD)&VisibleWaterGridStore[4 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WaterTileIndex] + (2 * WaterGridWidth);

	// These patches relocate offset +(2 * WaterGridWidth) + 1
	CMemory::UnProtect(0x5C0657, 0x04);
	CMemory::UnProtect(0x5C1E87, 0x04);
	CMemory::UnProtect(0x5C207A, 0x04);
	*(PDWORD)0x5C0657 = (DWORD)&VisibleWaterGridStore[4 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WaterTileIndex] + (2 * WaterGridWidth) + 1;
	*(PDWORD)0x5C1E87 = (DWORD)&VisibleWaterGridStore[4 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WaterTileIndex] + (2 * WaterGridWidth) + 1;
	*(PDWORD)0x5C207A = (DWORD)&VisibleWaterGridStore[4 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WaterTileIndex] + (2 * WaterGridWidth) + 1;

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
	*(PDWORD)0x5BBB7C = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WaterTileIndex];
	*(PDWORD)0x5BBFBC = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WaterTileIndex];
	*(PDWORD)0x5BC6EE = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WaterTileIndex];
	*(PDWORD)0x5BCC2C = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WaterTileIndex];
	*(PDWORD)0x5BCFC6 = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WaterTileIndex];
	*(PDWORD)0x5BF801 = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WaterTileIndex];
	*(PDWORD)0x5C0ACC = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WaterTileIndex];
	*(PDWORD)0x5C2C56 = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WaterTileIndex];
	*(PDWORD)0x5C2D03 = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WaterTileIndex];
	*(PDWORD)0x5C39BE = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WaterTileIndex];

	// These patches relocate offset +1
	CMemory::UnProtect(0x5BF83E, 0x04);
	CMemory::UnProtect(0x5C0E6D, 0x04);
	*(PDWORD)0x5BF83E = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WaterTileIndex] + 1;
	*(PDWORD)0x5C0E6D = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WaterTileIndex] + 1;

	// These patches relocate offset +2
	CMemory::UnProtect(0x5BF877, 0x04);
	*(PDWORD)0x5BF877 = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WaterTileIndex] + 2;

	// These patches relocate offset +(4 * WaterGridWidth)
	CMemory::UnProtect(0x5BF818, 0x04);
	CMemory::UnProtect(0x5C0C9D, 0x04);
	*(PDWORD)0x5BF818 = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WaterTileIndex] + (4 * WaterGridWidth);
	*(PDWORD)0x5C0C9D = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WaterTileIndex] + (4 * WaterGridWidth);

	// These patches relocate offset +(4 * WaterGridWidth) + 1
	CMemory::UnProtect(0x5BF851, 0x04);
	CMemory::UnProtect(0x5C103F, 0x04);
	*(PDWORD)0x5BF851 = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WaterTileIndex] + (4 * WaterGridWidth) + 1;
	*(PDWORD)0x5C103F = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WaterTileIndex] + (4 * WaterGridWidth) + 1;

	// These patches relocate offset +(4 * WaterGridWidth) + 2
	CMemory::UnProtect(0x5BF88A, 0x04);
	*(PDWORD)0x5BF88A = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WaterTileIndex] + (4 * WaterGridWidth) + 2;

	// These patches relocate offset +(8 * WaterGridWidth)
	CMemory::UnProtect(0x5BF82B, 0x04);
	*(PDWORD)0x5BF82B = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WaterTileIndex] + (8 * WaterGridWidth);

	// These patches relocate offset +(8 * WaterGridWidth) + 1
	CMemory::UnProtect(0x5BF864, 0x04);
	*(PDWORD)0x5BF864 = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WaterTileIndex] + (8 * WaterGridWidth) + 1;

	// These patches relocate offset +(8 * WaterGridWidth) + 2
	CMemory::UnProtect(0x5BF8A0, 0x04);
	*(PDWORD)0x5BF8A0 = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WaterTileIndex] + (8 * WaterGridWidth) + 2;
}
//==================================================================================
void Hook_PreRenderNearWater(void) {
	for(BYTE i = 0; i < MapTileWidth * MapTileWidth; i++) {

		RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void*)TRUE);
        RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDONE);
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDZERO);
        RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDSRCALPHA);
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDINVSRCALPHA);


		// These calculations render the designated water plane based off of offets in position.

		 float XPart = (float)(i % 6) - 2.0f;
		 float YPart = (float)(i / 6) - 2.0f;

		*(float*)0x69CC58 = -4096.0f * XPart + 400.f;
		NorthSouthWaterOffset = -4096.0f * YPart;

		RelocateGridDependencies(i);

		(i == 0) ? RenderWaterAndEffects() : RenderWaterAndEffects_OnlyWater(); // We only need to render the water once.

		XPart = (float)(StoredWaterTileIndex % 6) - 2.0f;
		YPart = (float)(StoredWaterTileIndex / 6) - 2.0f;

		*(float*)0x69CC58 = -4096.0f * XPart + 400.f;
		NorthSouthWaterOffset = -4096.0f * YPart;

		RelocateGridDependencies(StoredWaterTileIndex);

		char CurrentWaterTileIndex = GetCurrentWaterTileIndex();
		if(StoredWaterTileIndex != CurrentWaterTileIndex) { // They changed water "tiles"
			StoredWaterTileIndex = CurrentWaterTileIndex;
		}
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
    //Relocates the grid for preparation of use everytime New Game is clicked
    CMemory::NoOperation(0x5C3940, 10);
    CMemory::InstallCallHook(0x5C3940, (DWORD)Hook__CWaterLevel_Initialize, ASM_CALL);

	// This patch removes the shiny area which appeared to be distorted below the player.
	CMemory::NoOperation(0x5C1525, 0x58);

	// This patch removes the flickering screen issue. RenderFarWater Issue
	CMemory::NoOperation(0x5C0093, 0x05);
	
	// Instantiate the references to and the new PHYSICAL water tile array itself.
	memset(&PhysicalWaterGridStore, 0x00, 16 * WaterGridWidth * WaterGridWidth * WATER_MAP_WIDTH * WATER_MAP_WIDTH);
	CMemory::UnProtect((DWORD)&PhysicalWaterGridStore, 16 * WaterGridWidth * WaterGridWidth * WATER_MAP_WIDTH * WATER_MAP_WIDTH);

	// Instantiate the references to and the new water tile array itself.
	memset(&VisibleWaterGridStore, 0x00, 4 * WaterGridWidth * WaterGridWidth * WATER_MAP_WIDTH * WATER_MAP_WIDTH);
	CMemory::UnProtect((DWORD)&VisibleWaterGridStore, 4 * WaterGridWidth * WaterGridWidth * WATER_MAP_WIDTH * WATER_MAP_WIDTH);

	// This massive patch removes the calls to render the hardcoded useless LOD water planes past the default boundaries.
	CMemory::NoOperation(0x5C20F0, 0x7FC);

	CMemory::UnProtect(0x5C1D84, 0x01);
	CMemory::UnProtect(0x5C1D9C, 0x01);
	CMemory::UnProtect(0x5C1DB4, 0x01);
	CMemory::UnProtect(0x5C1DCC, 0x01);
	CMemory::UnProtect(0x5C1DDC, 0x01);
	CMemory::UnProtect(0x5C1DE8, 0x01);
	CMemory::UnProtect(0x5C1DF8, 0x01);
	CMemory::UnProtect(0x5C1E04, 0x01);

	CMemory::UnProtect(0x5C04A4, 0x01);
	CMemory::UnProtect(0x5C04BC, 0x01);
	CMemory::UnProtect(0x5C04D4, 0x01);
	CMemory::UnProtect(0x5C04EC, 0x01);
	CMemory::UnProtect(0x5C0504, 0x01);
	CMemory::UnProtect(0x5C051C, 0x01);
	CMemory::UnProtect(0x5C0534, 0x01);
	CMemory::UnProtect(0x5C054C, 0x01);

	*(PBYTE)0x5C1D84 = WaterGridWidth - 1;
	*(PBYTE)0x5C1D9C = WaterGridWidth - 1;
	*(PBYTE)0x5C1DB4 = WaterGridWidth - 1;
	*(PBYTE)0x5C1DCC = WaterGridWidth - 1;
	*(PBYTE)0x5C1DDC = WaterGridWidth - 1;
	*(PBYTE)0x5C1DE8 = WaterGridWidth - 1;
	*(PBYTE)0x5C1DF8 = WaterGridWidth - 1;
	*(PBYTE)0x5C1E04 = WaterGridWidth - 1;
	*(PBYTE)0x5C04A4 = WaterGridWidth - 1;
	*(PBYTE)0x5C04BC = WaterGridWidth - 1;
	*(PBYTE)0x5C04D4 = WaterGridWidth - 1;
	*(PBYTE)0x5C04EC = WaterGridWidth - 1;
	*(PBYTE)0x5C0504 = WaterGridWidth - 1;
	*(PBYTE)0x5C051C = WaterGridWidth - 1;
	*(PBYTE)0x5C0534 = WaterGridWidth - 1;
	*(PBYTE)0x5C054C = WaterGridWidth - 1;

    /*
	CMemory::UnProtect(0x5C1E36, 0x01);
	CMemory::UnProtect(0x5C1E98, 0x01);
	CMemory::UnProtect(0x5C05CE, 0x01);
	CMemory::UnProtect(0x5C0679, 0x01);
	*(PBYTE)0x5C1E36 = -WaterGridWidth / 2;
	*(PBYTE)0x5C1E98 = -WaterGridWidth / 2;
	*(PBYTE)0x5C05CE = -WaterGridWidth / 2;
	*(PBYTE)0x5C0679 = -WaterGridWidth / 2;

	CMemory::UnProtect(0x5BCF1C, 0x01);
	CMemory::UnProtect(0x5BCF28, 0x01);
	CMemory::UnProtect(0x5BCF74, 0x01);
	CMemory::UnProtect(0x5BCF81, 0x01);
	*(PBYTE)0x5BCF1C = (4 * WaterGridWidth) - 1;
	*(PBYTE)0x5BCF28 = (4 * WaterGridWidth) - 1;
	*(PBYTE)0x5BCF74 = (4 * WaterGridWidth) - 1;
	*(PBYTE)0x5BCF81 = (4 * WaterGridWidth) - 1;
    */
	// Install the patch for the size of the waterpro.dat area in CWaterLevel::Initialize
    // Visual Water Map
	CMemory::UnProtect(0x5C39A6, 0x04);
	*(PDWORD)0x5C39A6 = (4 * WaterGridWidth * WaterGridWidth * WATER_MAP_WIDTH * WATER_MAP_WIDTH);

    // Physical Water Map
	CMemory::UnProtect(0x5C39B9, 0x04);
	*(PDWORD)0x5C39B9 = (16 * WaterGridWidth * WaterGridWidth * WATER_MAP_WIDTH * WATER_MAP_WIDTH);

	// Install the patches (water plane constructor) that allow for north/south boundary manipulation.
	CMemory::NoOperation(0x5C1D03, 0x06);
	CMemory::InstallCallHook(0x5C1D03, (DWORD)Hook_WaterPlaneConstruct_1, ASM_CALL);

	CMemory::NoOperation(0x5C1D45, 0x06);
	CMemory::InstallCallHook(0x5C1D45, (DWORD)Hook_WaterPlaneConstruct_1, ASM_CALL);

	CMemory::NoOperation(0x5C1C10, 0x06); // construct
	CMemory::NoOperation(0x5C1C45, 0x06); // construct
	CMemory::NoOperation(0x5C02F5, 0x06); // destruct
	CMemory::NoOperation(0x5C0337, 0x06); // destruct
	CMemory::InstallCallHook(0x5C1C10, (DWORD)Hook_WaterPlaneConstruct_3, ASM_CALL);
	CMemory::InstallCallHook(0x5C1C45, (DWORD)Hook_WaterPlaneConstruct_3, ASM_CALL);
	CMemory::InstallCallHook(0x5C02F5, (DWORD)Hook_WaterPlaneConstruct_2, ASM_CALL);
	CMemory::InstallCallHook(0x5C0337, (DWORD)Hook_WaterPlaneConstruct_2, ASM_CALL);

	CMemory::NoOperation(0x5C1EA1, 0x06);
	CMemory::InstallCallHook(0x5C1EA1, (DWORD)Hook_WaterPlaneConstruct_4, ASM_CALL);

	CMemory::NoOperation(0x5C041B, 0x06);
	CMemory::NoOperation(0x5C0460, 0x06);
	CMemory::InstallCallHook(0x5C041B, (DWORD)Hook_WaterPlaneDestruct_1, ASM_CALL);
	CMemory::InstallCallHook(0x5C0460, (DWORD)Hook_WaterPlaneDestruct_1, ASM_CALL);

	CMemory::NoOperation(0x5C0690, 0x06);
	CMemory::InstallCallHook(0x5C0690, (DWORD)Hook_WaterPlaneDestruct_2, ASM_CALL);

	CMemory::NoOperation(0x5C08EE, 0x06);
	CMemory::InstallCallHook(0x5C08EE, (DWORD)Hook_WaterPlaneDestruct_3, ASM_CALL);

	// Install patch in GetWaterLevelNoWaves.
	CMemory::NoOperation(0x5C2BF1, 0x06);
	CMemory::InstallCallHook(0x5C2BF1, (DWORD)Hook_GetWaterLevelNoWave_1, ASM_CALL);

	// Install patch in GetWaterLevel.
	CMemory::NoOperation(0x5C2CD3, 6);
	CMemory::InstallCallHook(0x5C2CD3, (DWORD)Hook_GetWaterLevelNoWave_2, ASM_CALL);

	// Install patch in the camera processor.
	//CMemory::NoOperation(0x5BCEDD, 6);
    //CMemory::NoOperation(0x5BCF34, 6);
	//CMemory::InstallCallHook(0x5BCEDD, (DWORD)Hook_WaterCamera_1);
	//CMemory::InstallCallHook(0x5BCF34, (DWORD)Hook_WaterCamera_1);

	*(float*)0x69CC5C = 1.0f / (float)WaterGridWidth;

	// Remove calls to read from the waterpro.dat file.
	//CMemory::NoOperation(0x5C39A5, 0x13); //Stop reading visual water
	//CMemory::NoOperation(0x5C39B8, 0x13); //Stop reading physical water

	// NEW TEST MATERIALS

	CMemory::NoOperation(0x4A6589, 0x2A);
	CMemory::InstallCallHook(0x4A6589, (DWORD)Hook_PreRenderNearWater, ASM_CALL);
}
#include "main.h"

using namespace HookSystem;
//==================================================================================
#define WATER_GRID_WIDTH 32
float	GlobalMapShiftLR	= 3 * 4096.f; // 3 equivalents to VC to the left plus the normal VC shift
BYTE	MapTileWidth		= 6;
#define WATER_MAP_WIDTH	6
//BYTE	VisibleWaterGridStore[4 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WATER_MAP_WIDTH * WATER_MAP_WIDTH];
BYTE	VisibleWaterGridStore[64 * 64 * WATER_MAP_WIDTH * WATER_MAP_WIDTH];
BYTE	PhysicalWaterGridStore[128 * 128 * WATER_MAP_WIDTH * WATER_MAP_WIDTH];
//BYTE	PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WATER_MAP_WIDTH * WATER_MAP_WIDTH];
float	NorthSouthWaterOffset	= 0.0f;
float	XYOffset = 0.0f;
//==================================================================================
// For the patches.
DWORD	f2048		= 0x69CC54; //2048 
DWORD	f1By128		= 0x69CD8C; // 1/128
DWORD	f128		= 0x69CD18; // 128.0
DWORD	flt_69CD20		= 0x69CD20;
DWORD	flt_69CC5C		= 0x69CC5C;
DWORD	REG_TEMP_EBX	= 0;
//==================================================================================
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
//==================================================================================
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
//==================================================================================
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
//==================================================================================
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
//==================================================================================
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
		mov ebx, flt_69CD20
		fadd dword ptr ds:[ebx]
		mov ebx, REG_TEMP_EBX
		ret
	}
}
//==================================================================================
void _declspec(naked) Hook_RenderTransparentWater_ToCoords_3(void) {
	_asm {
		mov REG_TEMP_EBX, ebx
		mov ebx, flt_69CD20
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




char	StoredwatermapGrid = -1;
char GetCurrentwatermapGrid(void) {
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
// why not have a jumbo one grid instead of thousands of grid;
/*

*/
//for every huge grids both water render calls are invoked with this
void RelocateGridDependencies(char watermapGrid) {
	// lame Justin if(watermapGrid < 0 || watermapGrid >= (WATER_GRID_WIDTH * WATER_GRID_WIDTH)) return;


	// These patches relocate offset +0
    //Change references to waterpro segment 3 memory location
	CMemory::UnProtect(0x5C0618, 0x04); 
	CMemory::UnProtect(0x5C08C8, 0x04);
	CMemory::UnProtect(0x5C1232, 0x04);
	CMemory::UnProtect(0x5C1E54, 0x04);
	CMemory::UnProtect(0x5C201D, 0x04);
	CMemory::UnProtect(0x5C39AB, 0x04);
	*(PDWORD)0x5C0618 = (DWORD)&VisibleWaterGridStore[4 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * watermapGrid];
	*(PDWORD)0x5C08C8 = (DWORD)&VisibleWaterGridStore[4 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * watermapGrid];
	*(PDWORD)0x5C1232 = (DWORD)&VisibleWaterGridStore[4 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * watermapGrid];
	*(PDWORD)0x5C1E54 = (DWORD)&VisibleWaterGridStore[4 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * watermapGrid];
	*(PDWORD)0x5C201D = (DWORD)&VisibleWaterGridStore[4 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * watermapGrid];
	*(PDWORD)0x5C39AB = (DWORD)&VisibleWaterGridStore[4 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * watermapGrid];

	// These patches relocate offset +1

    //Change references to waterpro segment3 + 1
	CMemory::UnProtect(0x5C0644, 0x04);
	CMemory::UnProtect(0x5C1E78, 0x04);
	CMemory::UnProtect(0x5C205B, 0x04);
	*(PDWORD)0x5C0644 = (DWORD)&VisibleWaterGridStore[4 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * watermapGrid] + 1;
	*(PDWORD)0x5C1E78 = (DWORD)&VisibleWaterGridStore[4 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * watermapGrid] + 1;
	*(PDWORD)0x5C205B = (DWORD)&VisibleWaterGridStore[4 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * watermapGrid] + 1;

	// These patches relocate offset +(2 * WATER_GRID_WIDTH)
	CMemory::UnProtect(0x5C0631, 0x04);
	CMemory::UnProtect(0x5C1E69, 0x04);
	CMemory::UnProtect(0x5C203C, 0x04);
	*(PDWORD)0x5C0631 = (DWORD)&VisibleWaterGridStore[4 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * watermapGrid] + (2 * WATER_GRID_WIDTH);
	*(PDWORD)0x5C1E69 = (DWORD)&VisibleWaterGridStore[4 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * watermapGrid] + (2 * WATER_GRID_WIDTH);
	*(PDWORD)0x5C203C = (DWORD)&VisibleWaterGridStore[4 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * watermapGrid] + (2 * WATER_GRID_WIDTH);

	// These patches relocate offset +(2 * WATER_GRID_WIDTH) + 1
	CMemory::UnProtect(0x5C0657, 0x04);
	CMemory::UnProtect(0x5C1E87, 0x04);
	CMemory::UnProtect(0x5C207A, 0x04);
	*(PDWORD)0x5C0657 = (DWORD)&VisibleWaterGridStore[4 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * watermapGrid] + (2 * WATER_GRID_WIDTH) + 1;
	*(PDWORD)0x5C1E87 = (DWORD)&VisibleWaterGridStore[4 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * watermapGrid] + (2 * WATER_GRID_WIDTH) + 1;
	*(PDWORD)0x5C207A = (DWORD)&VisibleWaterGridStore[4 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * watermapGrid] + (2 * WATER_GRID_WIDTH) + 1;

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
	*(PDWORD)0x5BBB7C = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * watermapGrid];
	*(PDWORD)0x5BBFBC = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * watermapGrid];
	*(PDWORD)0x5BC6EE = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * watermapGrid];
	*(PDWORD)0x5BCC2C = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * watermapGrid];
	*(PDWORD)0x5BCFC6 = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * watermapGrid];
	*(PDWORD)0x5BF801 = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * watermapGrid];
	*(PDWORD)0x5C0ACC = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * watermapGrid];
	*(PDWORD)0x5C2C56 = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * watermapGrid];
	*(PDWORD)0x5C2D03 = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * watermapGrid];
	*(PDWORD)0x5C39BE = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * watermapGrid];

	// These patches relocate offset +1
	CMemory::UnProtect(0x5BF83E, 0x04);
	CMemory::UnProtect(0x5C0E6D, 0x04);
	*(PDWORD)0x5BF83E = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * watermapGrid] + 1;
	*(PDWORD)0x5C0E6D = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * watermapGrid] + 1;

	// These patches relocate offset +2
	CMemory::UnProtect(0x5BF877, 0x04);
	*(PDWORD)0x5BF877 = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * watermapGrid] + 2;

	// These patches relocate offset +(4 * WATER_GRID_WIDTH)
	CMemory::UnProtect(0x5BF818, 0x04);
	CMemory::UnProtect(0x5C0C9D, 0x04);
	*(PDWORD)0x5BF818 = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * watermapGrid] + (4 * WATER_GRID_WIDTH);
	*(PDWORD)0x5C0C9D = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * watermapGrid] + (4 * WATER_GRID_WIDTH);

	// These patches relocate offset +(4 * WATER_GRID_WIDTH) + 1
	CMemory::UnProtect(0x5BF851, 0x04);
	CMemory::UnProtect(0x5C103F, 0x04);
	*(PDWORD)0x5BF851 = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * watermapGrid] + (4 * WATER_GRID_WIDTH) + 1;
	*(PDWORD)0x5C103F = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * watermapGrid] + (4 * WATER_GRID_WIDTH) + 1;

	// These patches relocate offset +(4 * WATER_GRID_WIDTH) + 2
	CMemory::UnProtect(0x5BF88A, 0x04);
	*(PDWORD)0x5BF88A = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * watermapGrid] + (4 * WATER_GRID_WIDTH) + 2;

	// These patches relocate offset +(8 * WATER_GRID_WIDTH)
	CMemory::UnProtect(0x5BF82B, 0x04);
	*(PDWORD)0x5BF82B = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * watermapGrid] + (8 * WATER_GRID_WIDTH);

	// These patches relocate offset +(8 * WATER_GRID_WIDTH) + 1
	CMemory::UnProtect(0x5BF864, 0x04);
	*(PDWORD)0x5BF864 = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * watermapGrid] + (8 * WATER_GRID_WIDTH) + 1;

	// These patches relocate offset +(8 * WATER_GRID_WIDTH) + 2
	CMemory::UnProtect(0x5BF8A0, 0x04);
	*(PDWORD)0x5BF8A0 = (DWORD)&PhysicalWaterGridStore[16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * watermapGrid] + (8 * WATER_GRID_WIDTH) + 2;
}

// water grids are 36 times bigger
void Hook_PreRenderNearWater(void) 
{
	*(float*)0x69CC58 = 400.0f;
	NorthSouthWaterOffset = 0.0f;
	RenderWaterAndEffects();
	for(BYTE i = 0; i < MapTileWidth * MapTileWidth; i++) {

		


		// These calculations render the designated water plane based off of offets in position.

		 float XPart = (float)(i % 6) - 2.0f;
		 float YPart = (float)(i / 6) - 2.0f;

		//*(float*)0x69CC58 = -4096.0f * XPart + 400.f;
		//NorthSouthWaterOffset = -4096.0f * YPart;

		RelocateGridDependencies(i);

		// : RenderWaterAndEffects_OnlyWater();
		
		/*XPart = (float)(StoredwatermapGrid % 6) - 2.0f;
		YPart = (float)(StoredwatermapGrid / 6) - 2.0f;

		*(float*)0x69CC58 = -4096.0f * XPart + 400.f;
		NorthSouthWaterOffset = -4096.0f * YPart;

		RelocateGridDependencies(StoredwatermapGrid);

		char CurrentwatermapGrid = GetCurrentwatermapGrid();
		if(StoredwatermapGrid != CurrentwatermapGrid) { // They changed water "tiles"
			StoredwatermapGrid = CurrentwatermapGrid;
		}*/
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
	*(float*)0x69C780 += 8000.0f;
    //Relocates the grid for preparation of use everytime New Game is clicked
    InstallNOPs(0x5C3940, 10);
    InstallFnByCall(0x5C3940, Hook__CWaterLevel_Initialize);

	// This patch removes the shiny area which appeared to be distorted below the player.
	//InstallNOPs(0x5C1525, 0x58);

	// This patch removes the flickering screen issue. RenderFarWater Issue
	//InstallNOPs(0x5C0093, 0x05);
	
	// Instantiate the references to and the new PHYSICAL water tile array itself.
	memset(&PhysicalWaterGridStore, 0x00, 16 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WATER_MAP_WIDTH * WATER_MAP_WIDTH);

	// Instantiate the references to and the new water tile array itself.
	memset(&VisibleWaterGridStore, 0x00, 4 * WATER_GRID_WIDTH * WATER_GRID_WIDTH * WATER_MAP_WIDTH * WATER_MAP_WIDTH);

	// Static Water planes rendering codes outside the boundary, need to change it so that it changes with the player
	//InstallNOPs(0x5C20F0, 0x7FC);

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

	*(PBYTE)0x5C1D84 = WATER_GRID_WIDTH - 1;
	*(PBYTE)0x5C1D9C = WATER_GRID_WIDTH - 1;
	*(PBYTE)0x5C1DB4 = WATER_GRID_WIDTH - 1;
	*(PBYTE)0x5C1DCC = WATER_GRID_WIDTH - 1;
	*(PBYTE)0x5C1DDC = WATER_GRID_WIDTH - 1;
	*(PBYTE)0x5C1DE8 = WATER_GRID_WIDTH - 1;
	*(PBYTE)0x5C1DF8 = WATER_GRID_WIDTH - 1;
	*(PBYTE)0x5C1E04 = WATER_GRID_WIDTH - 1;
	*(PBYTE)0x5C04A4 = WATER_GRID_WIDTH - 1;
	*(PBYTE)0x5C04BC = WATER_GRID_WIDTH - 1;
	*(PBYTE)0x5C04D4 = WATER_GRID_WIDTH - 1;
	*(PBYTE)0x5C04EC = WATER_GRID_WIDTH - 1;
	*(PBYTE)0x5C0504 = WATER_GRID_WIDTH - 1;
	*(PBYTE)0x5C051C = WATER_GRID_WIDTH - 1;
	*(PBYTE)0x5C0534 = WATER_GRID_WIDTH - 1;
	*(PBYTE)0x5C054C = WATER_GRID_WIDTH - 1;

    /*
	CMemory::UnProtect(0x5C1E36, 0x01);
	CMemory::UnProtect(0x5C1E98, 0x01);
	CMemory::UnProtect(0x5C05CE, 0x01);
	CMemory::UnProtect(0x5C0679, 0x01);
	*(PBYTE)0x5C1E36 = -WATER_GRID_WIDTH / 2;
	*(PBYTE)0x5C1E98 = -WATER_GRID_WIDTH / 2;
	*(PBYTE)0x5C05CE = -WATER_GRID_WIDTH / 2;
	*(PBYTE)0x5C0679 = -WATER_GRID_WIDTH / 2;

	CMemory::UnProtect(0x5BCF1C, 0x01);
	CMemory::UnProtect(0x5BCF28, 0x01);
	CMemory::UnProtect(0x5BCF74, 0x01);
	CMemory::UnProtect(0x5BCF81, 0x01);
	*(PBYTE)0x5BCF1C = (4 * WATER_GRID_WIDTH) - 1;
	*(PBYTE)0x5BCF28 = (4 * WATER_GRID_WIDTH) - 1;
	*(PBYTE)0x5BCF74 = (4 * WATER_GRID_WIDTH) - 1;
	*(PBYTE)0x5BCF81 = (4 * WATER_GRID_WIDTH) - 1;
    */
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

	// Remove calls to read from the waterpro.dat file.
	//InstallNOPs(0x5C39A5, 0x13); //Stop reading visual water
	//InstallNOPs(0x5C39B8, 0x13); //Stop reading physical water


	// Place calls repeat each grid
	//InstallNOPs(0x4A6589, 0x2A);
	//InstallFnByCall(0x4A6589, Hook_PreRenderNearWater);
}
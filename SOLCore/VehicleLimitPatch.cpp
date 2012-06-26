#include "GamePatches.h"
#include "main.h"

// Create the vehicle model store array.
/*DWORD	IDEVehicleLimit = 1000;
BYTE	NewVehicleStore[4 + (1000 * 372)];



// Create the vehicle model store array.
DWORD	ObjectTypeLimit = 100;
#define	OBJECT_TYPE_LIMIT 100
BYTE	NewObjectTypeStore[4 + (OBJECT_TYPE_LIMIT * 100)];

DWORD	OBJ_FuncA = 0x560200, 
		OBJ_FuncB = 0x560220,
		OBJ_FuncC = (DWORD)(&NewObjectTypeStore[4]);

void _declspec(naked) Hook_AllocateObjectTypeLimitArray(void) {
	_asm {
		push ObjectTypeLimit
		push 72 // sizeof(ObjectType)
		push OBJ_FuncA
		push OBJ_FuncB
		push OBJ_FuncC
		call Func_ConstructArray
		add esp, 0x14
		ret
	}
}
void _declspec(naked) Hook_DeallocateObjectTypeLimitArray(void) {
	_asm {
		mov ebx, ecx
		lea eax, dword ptr ds: [ebx + 4]
		push ObjectTypeLimit
		push 72
		push OBJ_FuncA
		push eax
		call Func_DeconstructArray
		add esp, 10h
		mov eax, ebx
		pop ebx
		ret
	}
}


void PatchVehicleModelInfo(void) {
	// Apply the patch for the vehicle object storage.


	// Apply the patch to relocate the object type storage.
	DWORD	ObjTypeOffsets[] = {0x55FF4D};
	DWORD	ObjCountTypeOffsets[] = {0x55F692, 0x55F6AF, 0x55F6B5, 0x55F6BE, 0x55F8A9, 0x55F8B1, 0x55F8C8, 0x55F9E2, 0x55FB8C, 0x55FF5B, 0x55FF6E};

	UnProtect((DWORD)&NewObjectTypeStore, 4 + 72 * ObjectTypeLimit);
	memset(&NewObjectTypeStore, 0, 4 + 72 * ObjectTypeLimit);
	for(USHORT i = 0; i < 11; i++) {
		UnProtect(ObjCountTypeOffsets[i], 4);
		*(PDWORD)ObjCountTypeOffsets[i] = (DWORD)&NewObjectTypeStore;
	}
	for(USHORT i = 0; i < 1; i++) {
		UnProtect(ObjTypeOffsets[i], 4);
		*(PDWORD)ObjTypeOffsets[i] = (DWORD)&NewObjectTypeStore[4];
	}
	// Overwrite the code to allocate the array.
	NoOperation(0x55FF3E, 0x1B);
	CMemory::InstallCallHook(0x55FF3E, (DWORD)Hook_AllocateObjectTypeLimitArray, ASM_CALL);
	NoOperation(0x5601E1, 0x1A);
	CMemory::InstallCallHook(0x5601E1, (DWORD)Hook_DeallocateObjectTypeLimitArray, ASM_CALL);
}*/
//===============================================================================
#define MAX_VEHICLES 400
#define MAXCARS_IN_ONE_RATING 127    // VC's default is 25

#define ARRLEN(a) (sizeof(a)/sizeof(a[0]))

DWORD dwHookRet55FFBD = 0x55FFBD;
void _declspec (naked) HookConstructVehicleModelInfoArray() {
    _asm push MAX_VEHICLES
    _asm push 0x174
    _asm jmp dwHookRet55FFBD
}

DWORD dwHookRet56015D = 0x56015D;
void _declspec (naked) HookDestructVehicleModelInfoArray() {
    _asm push MAX_VEHICLES
    _asm push 0x174
    _asm jmp dwHookRet56015D
}

DWORD sVehicles = 0x68F904;
DWORD dwHookRet4C02EB = 0x4C02EB;
void _declspec (naked) HookConstructVehiclePool() {
    _asm push sVehicles
    _asm push MAX_VEHICLES
    _asm jmp dwHookRet4C02EB
}

unsigned int TotalNumOfCarsOfRating[11]; // VC has 11 vehicle AI classes distribution, -1 is used for ignore
unsigned int CarArrays[11 * MAXCARS_IN_ONE_RATING];

int _cdecl AddToCarArray(int modelID, int VehicleClass)
{
    int index = TotalNumOfCarsOfRating[VehicleClass]++ + MAXCARS_IN_ONE_RATING * VehicleClass;
    CarArrays[index] = modelID;
    return modelID;
}

int _cdecl ChooseCarModel(int VehicleClass)
{
    int (_cdecl *Random)(void) = (int(*)(void))0x6499F0;
    return CarArrays[(signed int)((double)TotalNumOfCarsOfRating[VehicleClass] /** (double)Random()*/ * 0.000030517578f) + MAXCARS_IN_ONE_RATING * VehicleClass];
}

void PatchVehicleLimits()
{
    // Code to relocate the vehicle Model Info structure in bss section
    static void* pNewVehicleModelInfoBuffer = NULL;
    
    static uint32_t dwVehicleModelInfoDataRefs[] = {
	    0x55F5D2, 0x55F5ED, 0x55F5F3, 0x55F5FE, 
        0x55F919, 0x55F921, 0x55F93B, 0x55F9D8, 
	    0x55FB62, 0x55FFD6, 0x55FFE9, 0x55FFC8
    };

    pNewVehicleModelInfoBuffer = malloc(MAX_VEHICLES * 0x174 + 4 );
    for(int i = 0; i < ARRLEN(dwVehicleModelInfoDataRefs); i++) {
        DWORD dwMod = *((uint32_t*)dwVehicleModelInfoDataRefs[i]);
        dwMod -= 0x752A88;
        dwMod += (uint32_t)pNewVehicleModelInfoBuffer;

        DWORD dwPrevProtect = CMemory::UnProtect(dwVehicleModelInfoDataRefs[i], 4);
        *((uint32_t*)dwVehicleModelInfoDataRefs[i]) = dwMod;
        CMemory::RestoreProtection(dwVehicleModelInfoDataRefs[i], 4, dwPrevProtect);
    }

    CMemory::NoOperation(0x55FFB6, 7);
    CMemory::InstallCallHook(0x55FFB6, &HookConstructVehicleModelInfoArray, ASM_JMP);

    CMemory::NoOperation(0x560156, 7);
    CMemory::InstallCallHook(0x560156, &HookDestructVehicleModelInfoArray, ASM_JMP);

    CMemory::NoOperation(0x4C02E4, 7);
    CMemory::InstallCallHook(0x4C02E4, &HookConstructVehiclePool, ASM_JMP);
    
    // Patches in CCarCtrl Car Arrays and Car Ratings
    memset(&TotalNumOfCarsOfRating, NULL, sizeof(TotalNumOfCarsOfRating));
    memset(&CarArrays, NULL, sizeof(CarArrays));

    CMemory::InstallPatch<void*>(0x4294C6, &TotalNumOfCarsOfRating);
    CMemory::InstallCallHook( 0x426A30, &ChooseCarModel, ASM_JMP);
    CMemory::InstallCallHook( 0x426820, &AddToCarArray, ASM_JMP);
}
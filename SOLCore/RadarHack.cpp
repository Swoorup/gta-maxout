#include "main.h"
#include "StdInc.h"
#include <iostream>


//============================================================================
#define RADAR_TXD_LIMIT 1296

BYTE	RadarTXDLimit = 36;

DWORD	RadarTXDStore[RADAR_TXD_LIMIT];
DWORD	ADDR_RadarTXDStore = (DWORD)&RadarTXDStore;
BYTE DisplayRadarSection_HookJmp[]				= {0xFF, 0x25, 0x61, 0x28, 0x4C, 0x00};			// 4C2861
BYTE RadarStreamTile_HookJmpCode[]				= {0xFF, 0x25, 0x11, 0x26, 0x4C, 0x00};			// 4C2611


/* Original
=============================================================================
The radar txd indexes are stored in bss segment at 0x70473C
XREFS
.text:004C1E3A 178 8B 3C 85 3C 47 70 00                   mov     edi, ds:radarsTxd[eax*4]
.text:004C28B6 010 8B 04 BD 3C 47 70 00                   mov     eax, ds:radarsTxd[edi*4]
.text:004C28FD 010 8B 04 8D 3C 47 70 00                   mov     eax, ds:radarsTxd[ecx*4]
.text:004C2952 00C 8B 04 B5 3C 47 70 00                   mov     eax, ds:radarsTxd[esi*4]
.text:004C61D6 00C 8B 04 B5 3C 47 70 00                   mov     eax, ds:radarsTxd[esi*4]
.text:004C62CD 00C 89 04 AD 3C 47 70 00                   mov     ds:radarsTxd[ebp*4], eax  CRadar::Initialize

We have to patch all this addresses to our custom allocated location ignoring the default location for TXD index storage
*/
void Patch_RadarTXDindexes_address(void) {
    memset(&RadarTXDStore, 0, RADAR_TXD_LIMIT * 4);
    CMemory::InstallPatch<DWORD>(0x4C1E3D, (DWORD)&RadarTXDStore);
    CMemory::InstallPatch<DWORD>(0x4C28B9, (DWORD)&RadarTXDStore);
    CMemory::InstallPatch<DWORD>(0x4C2900, (DWORD)&RadarTXDStore);
    CMemory::InstallPatch<DWORD>(0x4C2955, (DWORD)&RadarTXDStore);
    CMemory::InstallPatch<DWORD>(0x4C61D9, (DWORD)&RadarTXDStore);
    CMemory::InstallPatch<DWORD>(0x4C62D0, (DWORD)&RadarTXDStore);
}

void Patch_RadarGrid(void) {
    // Install the patches to increase the size of the radar grid.
    float MapWidth = 18000.0f;

    //---------------------------------------------------------------------------------------
    // SOL is 40,000 units wide from east to west and 40,000 units long from north to side.
    // 68FD00 should contain half of the wide of the map, 
    // but the SOLOteam had already adjusted their radar textures to be compatible with 18,000 wide map.
    // This might need extending in the future if more radar or map sections are to be added. 
    // So to hence to make it compatible with the current provide radar textures I am adjusting it to 9,000 (half of 18000).
    //---------------------------------------------------------------------------------------
    
    CMemory::InstallPatch<float>(0x68FD00, MapWidth/2.0f);

    // 68FD04 contains the multiplier to calculate current Radar Row and Columns.
    //This number is equal to 1/(map_width/numOfRadarTexIn_Arow)

    CMemory::InstallPatch<float>(0x68FD04, 1.0f/(MapWidth/(float)RadarTXDLimit));
    
    // Adjustment for calculation of Radar Y coords (Rows)   
    CMemory::InstallPatch<float>(0x68FD08, (float)RadarTXDLimit - 1.0f);
    
    // Patches for Relating World Cordinates to Radar Cordinates. Not needed as Map Width and TXD has been adjusted according to the original value
    //.text:004C1D82 178 69 D2 F4 01 00 00                          imul    edx, 500        ; Signed Multiply
    //UnProtect(0x4C1D84,2);
    //*(PSHORT)0x4C1D84 = (short)(MapWidth/(float)RadarTXDLimit);

    //.text:004C1D8E 178 69 C0 F4 01 00 00                          imul    eax, 500        ; Signed Multiply
    //UnProtect(0x4C1D90,2);
    //*(PSHORT)0x4C1D90 = (short)(MapWidth/(float)RadarTXDLimit);

    //.text:004C1D94 178 69 FF F4 01 00 00                          imul    edi, 500        ; Signed Multiply
    //UnProtect(0x4C1D96,2);
    //*(PSHORT)0x4C1D96 = (short)(MapWidth/(float)RadarTXDLimit);

    //.text:004C1D9A 178 69 C9 F4 01 00 00                          imul    ecx, 500        ; Signed Multiply
    //UnProtect(0x4C1D9C,2);
    //*(PSHORT)0x4C1D9C = (short)(MapWidth/(float)RadarTXDLimit);

    /*Patches done for proper calculation of Rows and Coloumns of Radar*/
    // CRadar::DrawRadarSection

    //.text:004C1E08 178 83 FE 07                                   cmp     esi, 7          ; Compare Two Operands 
	UnProtect(0x4C1E0A, 1);
    *(PBYTE)0x4C1E0A = RadarTXDLimit - 1;
    //.text:004C1E0D 178 BE 07 00 00 00                             mov     esi, 7
	UnProtect(0x4C1E0E, 1);
    *(PBYTE)0x4C1E0E = RadarTXDLimit - 1;
	//.text:004C1E18 178 83 FD 07                                   cmp     ebp, 7          ; Compare Two Operands
    UnProtect(0x4C1E1A, 1);
    *(PBYTE)0x4C1E1A = RadarTXDLimit - 1;
	//.text:004C1E1D 178 BD 07 00 00 00                             mov     ebp, 7
    UnProtect(0x4C1E1E, 1);
    *(PBYTE)0x4C1E1E = RadarTXDLimit - 1;
    //.text:004C1D7D 178 B9 03 00 00 00                             mov     ecx, 3
    UnProtect(0x4C1D7E, 1);
    *(PBYTE)0x4C1D7E = (RadarTXDLimit / 2) - 1;
	//.text:004C1F91 178 B9 08 00 00 00                             mov     ecx, 8
    UnProtect(0x4C1F92, 1);
    *(PBYTE)0x4C1F92 = RadarTXDLimit;
    //.text:004C1D71 178 8D 7E FC                                   lea     edi, [esi-4]    ; Load Effective Address
	UnProtect(0x4C1D73, 1);
	*(PBYTE)0x4C1D73 = 0x100 - (RadarTXDLimit / 2);	
    

    // CRadar::StreamRadarSection Patches

    //.text:004C28DA 010 83 FA 07                                   cmp     edx, 7          ; Compare Two Operands
    CMemory::InstallPatch <BYTE> (0x4C28DC, RadarTXDLimit - 1);
    //.text:004C28DF 010 BA 07 00 00 00                             mov     edx, 7
	UnProtect(0x4C28E0, 1);
    *(PBYTE)0x4C28E0 = RadarTXDLimit - 1;
    //.text:004C28EA 010 83 F9 07                                   cmp     ecx, 7          ; Compare Two Operands
	UnProtect(0x4C28EC, 1);
    *(PBYTE)0x4C28EC = RadarTXDLimit - 1;
    //.text:004C28EF 010 B9 07 00 00 00                             mov     ecx, 7
	UnProtect(0x4C28F0, 1);
    *(PBYTE)0x4C28F0 = RadarTXDLimit - 1;
    //.text:004C28A8 010 83 FD 07                                   cmp     ebp, 7          ; Compare Two Operands
	UnProtect(0x4C28AA, 1);
    *(PBYTE)0x4C28AA = RadarTXDLimit - 1;
	//.text:004C28B1 010 83 FE 07                                   cmp     esi, 7          ; Compare Two Operands
    UnProtect(0x4C28B3, 1);
    *(PBYTE)0x4C28B3 = RadarTXDLimit - 1;
    //.text:004C2914 010 83 C7 08                                   add     edi, 8          ; Add
	UnProtect(0x4C2916, 1);
    *(PBYTE)0x4C2916 = RadarTXDLimit;
	//.text:004C2917 010 83 FE 08                                   cmp     esi, 8          ; Compare Two Operands
    UnProtect(0x4C2919, 1);
    *(PBYTE)0x4C2919 = RadarTXDLimit;
	//.text:004C2921 010 83 FD 08                                   cmp     ebp, 8          ; Compare Two Operands
    UnProtect(0x4C2923, 1);
    *(PBYTE)0x4C2923 = RadarTXDLimit;
    
    // CRadar::RemoveRadarSection Patches
    
    //.text:004C2944 00C 83 FB 07                                   cmp     ebx, 7          ; Compare Two Operands
    UnProtect(0x4C2946, 1);
    *(PBYTE)0x4C2946 = RadarTXDLimit - 1;
    //.text:004C294D 00C 83 FD 07                                   cmp     ebp, 7          ; Compare Two Operands
    UnProtect(0x4C294F,1);
    *(PBYTE)0x4C294F = RadarTXDLimit - 1;

    //.text:004C2966 00C 83 C6 08                                   add     esi, 8          ; Add
    UnProtect(0x4C2968, 1);
    *(PBYTE)0x4C2968 = RadarTXDLimit;
    //.text:004C2969 00C 83 FD 08                                   cmp     ebp, 8          ; Compare Two Operands
    UnProtect(0x4C296B, 1);
    *(PBYTE)0x4C296B = RadarTXDLimit; 
    //.text:004C296F 00C 83 FB 08                                   cmp     ebx, 8          ; Compare Two Operands
    UnProtect(0x4C2971, 1);
    *(PBYTE)0x4C2971 = RadarTXDLimit;
}

//============================================================================
PCHAR	RadarName = (PCHAR)malloc(10);
DWORD	Func_AddTXDRef = 0x580D70;
DWORD	TXDAddress = 0;
DWORD	TextAddress = (DWORD)RadarName;
void _declspec(naked) Hook_CRadar_Init(void) {
	_asm pushad
	for(DWORD i = 0; i < (DWORD)(RadarTXDLimit * RadarTXDLimit); i++) {
		sprintf(RadarName, "radar%04d", i); 
		TextAddress = (DWORD)RadarName;
		_asm {
			push TextAddress
			call Func_AddTXDRef
			pop ecx
			mov TXDAddress, eax
		}
		RadarTXDStore[i] = TXDAddress;
	}
	_asm {
		popad
		ret
	}
}

//Myself Corrected Hooked in CRadar::DrawMapSection
//============================================================================
int	DW_TempTileID_X = 0, DW_TempTileID_Y = 0, DW_TempTileID_ID = 0;
void _declspec(naked) Hook_ChangeRadarTileFormula(void) {
	_asm {
		mov DW_TempTileID_X, esi    //esi is X
		mov DW_TempTileID_Y, ebp //ebp is Y
		pushad
	}
	DW_TempTileID_ID = RadarTXDStore[DW_TempTileID_X + RadarTXDLimit * DW_TempTileID_Y];
	_asm {
		popad
		mov edi, DW_TempTileID_ID
		ret
	}
}
//============================================================================

DWORD	JMP_StreamModelContinue = 0x4C2912;
DWORD	Func_CStreaming_RequestModel = 0x40E310;
void _declspec(naked) Hook_ChangeRadarStreamTile(void) {
	_asm {
		mov DW_TempTileID_X, edx
		mov DW_TempTileID_Y, ecx 
		pushad
	}
	DW_TempTileID_ID = RadarTXDStore[DW_TempTileID_X + RadarTXDLimit*DW_TempTileID_Y] + 32760; //TXDLIMIT HERE
	_asm {
		popad 
		push 5
		push DW_TempTileID_ID
		call Func_CStreaming_RequestModel
		pop ecx
		jmp JMP_StreamModelContinue
	}
}

//============================================================================
void _cdecl DEBUGHook_CRadar__DrawRadarMap(int radarX, int radarY) {
    wchar_t buff[90];
               
    wsprintfW(buff,L"CurrentRadar: Radar%04d.txd",radarX + RadarTXDLimit * radarY);
    CFont::SetPropOff();
	CFont::SetBackgroundOff();
	CFont::SetScale(ResolutionX / 640.0f * 0.40000001f, ResolutionY / 448.0f * 1.0f);
	CFont::SetCentreOff();
	CFont::SetRightJustifyOn();
	CFont::SetRightJustifyWrap(0.0f);
	CFont::SetBackGroundOnlyTextOff();
	CFont::SetFontStyle(2);
	CFont::SetPropOff();
	CFont::SetColor(&CRGBA(194,192,192,255));
    CFont::PrintString(ResolutionX/ 640.0f * 150.0f, ResolutionY / 448.0f * 43.0f, buff);

    _asm {
        push radarY
        push radarX
        mov ebx, 0x4C2870
        call ebx
        pop ecx
        pop ecx
    }    
}

//============================================================================
void PatchRadar(bool bdebugMsg) {
    Patch_RadarTXDindexes_address();
    Patch_RadarGrid();
	memset(RadarTXDStore, 0, RADAR_TXD_LIMIT * sizeof(DWORD));

	// Install the hook to customly allocate the array for radar images. Function is hooked at CRadar::Initialise(void)
	CMemory::NoOperation(0x4C62C0, 0x1B);
	CMemory::InstallCallHook(0x4C62C0, Hook_CRadar_Init, ASM_CALL);

	// Install the hook to Stream the radar textures. Function is hooked at CRadar::StreamRadarSections
	InstallHook(0x4C28F4, (DWORD)Hook_ChangeRadarStreamTile, 0x4C2611, RadarStreamTile_HookJmpCode, sizeof(RadarStreamTile_HookJmpCode));

    // Install the hooks to change the dimensional calls to the size of the radar grid. Function is hooked at CRadar::DrawRadarSection
    CMemory::NoOperation(0x4C1E3A, 0x07);
	CMemory::InstallCallHook(0x4C1E3A, Hook_ChangeRadarTileFormula, ASM_CALL);
    // Debugging Message for Radar(Optional)
    if(bdebugMsg == true) {
        CMemory::UnProtect(0x4C186F, 5);
        CMemory::InstallCallHook(0x4C186F,&DEBUGHook_CRadar__DrawRadarMap, ASM_CALL);
    }
}
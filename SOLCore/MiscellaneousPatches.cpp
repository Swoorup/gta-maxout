#include "main.h"
#include "StdInc.h"

//Patches of this section are loaded through PatchMiscData()


//=======================Loading Game Screen Patches By Elvis============================

/* This patches are subject to change in the future
It Patches how the loading bar should be displayed */

char* GameStateText;
char* loadingStageText;

DWORD dwHookJmp4A6A88 = 0x4A6A88;
void _declspec (naked) GetLoadingScreenMsg(){
    __asm{
        mov eax, dword ptr [esp + 0x70]
        mov GameStateText, eax
        mov eax, dword ptr [esp + 0x74]
        mov loadingStageText, eax
        cmp [esp + 0x70],0
        jmp dwHookJmp4A6A88
    }
}

wchar_t MsgBuffer[256];
void DisplayLoadingScreenMsg(){
    if (GameStateText){
        CFont::SetPropOn();
	    CFont::SetBackgroundOff();
	    CFont::SetScale(ResolutionX / 640.0f * 0.4f, ResolutionY / 448.0f * 0.8f);
	    
	    CFont::SetRightJustifyOff();
        CFont::SetJustifyOff();
	    CFont::SetRightJustifyWrap(999.0f);
	    CFont::SetBackGroundOnlyTextOff();
	    CFont::SetFontStyle(1);
        CFont::SetCentreOn();
        CFont::SetBackgroundOff();
    	CFont::SetColor(&CRGBA(255,255,255,255));
        CFont::AsciiToUnicode(GameStateText,MsgBuffer);
        CFont::PrintString(0.5f * (float)ResolutionX,335.0f/480.0f * (float)ResolutionY,MsgBuffer);
        CFont::AsciiToUnicode(loadingStageText,MsgBuffer);
        CFont::PrintString(0.5f * (float)ResolutionX,365.0f/480.0f * (float)ResolutionY,MsgBuffer);
        CFont::SetScale(ResolutionX / 640.0f * 0.2f, ResolutionY / 448.0f * 0.8f);
    }

    __asm   mov eax, 0x550250
    __asm   call eax
}


void PatchLoadingBarDisplayOnly()
{
   *(float*)0x68E70C = 550.0f;  // length (50)
   *(float*)0x68E710 = 5.0f;    // Width (25)
   *(float*)0x68E708 = 115.0f;   // distance from bottom (27)
   *(float*)0x68E704 = 275.0f;  // distance from right (1)
   *(float*)0x68E6FC = 0.65979f;//Progress Step

   //Background color

  CMemory::InstallPatch<byte>(0x4A6B7C,113); //B
  CMemory::InstallPatch<byte>(0x4A6B7E, 68); //G
  CMemory::InstallPatch<byte>(0x4A6B80, 11); //R
  

  //Foreground color (call @ 0x4A6C37)
  CMemory::InstallPatch<byte>(0x4A6C29, 171);//B
  CMemory::InstallPatch<byte>(0x4A6C2E, 113);//G
  CMemory::InstallPatch<byte>(0x4A6C33, 47); //R

  CMemory::NoOperation(0x4A6A83, 5);
  CMemory::InstallCallHook(0x4A6A83,(DWORD)&GetLoadingScreenMsg,ASM_JMP);

  CMemory::NoOperation(0x4A6D47, 5);
  CMemory::InstallCallHook(0x4A6D47, (DWORD)&DisplayLoadingScreenMsg, ASM_CALL);
}

//=======================End of Elvis's patches===================================


// This is the pointer to the new CarGenerator Store Buffer
CCarGenerator* pNewCarGeneratorBuffer = NULL;

// ----------------------------------------------------------------
// CTheCarGenerator Array Limit patches
//ToDos :
// Nothing is done for CCarGenerators::LoadAllCarGenerators() 
// Nothing is done for CCarGenerators::SaveAllCarGenerators()
// MayBe make this like SA loads from IPL?

#define ARRLEN(a) (sizeof(a)/sizeof(a[0])) 


// This is the new 4-byte counter for CTheCarGenerators
int CTheCarGenerators__ProcessCounter; 

DWORD dwHookJmp5A6CB4 = 0x005A6CB4;
void __declspec (naked) HookCTheCarGenerators4bCounter(){
    __asm{
        inc CTheCarGenerators__ProcessCounter
        cmp CTheCarGenerators__ProcessCounter, 4
        jnz Label_if_not_4
        mov CTheCarGenerators__ProcessCounter, 0
Label_if_not_4: 
        mov ebx, CTheCarGenerators__ProcessCounter
        jmp dwHookJmp5A6CB4
    }
}


void PatchCarGeneratorLimit()
{
    static uint32_t dwCarGeneratorDataRefs[] = 
    {	
        0x4537A9, 0x5A69DB, 0x5A69E6, 0x5A69F1, 0x5A69FC, 0x5A6A07, 0x5A6A14, 0x5A6A21, 
    	0x5A6A2A, 0x5A6A33, 0x5A6A3C, 0x5A6A49, 0x5A6A56, 0x5A6A61, 0x5A6A6C, 0x5A6A79, 
    	0x5A6A85, 0x5A6B16, 0x5A6B22, 0x5A6B2A, 0x5A6B35, 0x5A6B40, 0x5A6B4C, 0x5A6B5C, 
    	0x5A6B65, 0x5A6B6E, 0x5A6B77, 0x5A6B85, 0x5A6B95, 0x5A6BA1, 0x5A6BAC, 0x5A6BB8, 
    	0x5A6BC1, 0x5A6C5F, 0x5A6CC3
    };
  
    // This is the new CarGenerator Array Buffer
    pNewCarGeneratorBuffer = (CCarGenerator*)malloc(0x2C * MAXPARKEDCARS);
  
    for (int i = 0; i<ARRLEN(dwCarGeneratorDataRefs); i++){
        DWORD dwPrevProt = CMemory::UnProtect(dwCarGeneratorDataRefs[i], 4);
        *((uint32_t*)dwCarGeneratorDataRefs[i]) -= 0x00A0DC94;
        *((uint32_t*)dwCarGeneratorDataRefs[i]) += (uint32_t)pNewCarGeneratorBuffer;
        CMemory::RestoreProtection(dwCarGeneratorDataRefs[i], 4, dwPrevProt);
    }

    // Patch cmp instruction in CreateCarGenerator
    CMemory::InstallPatch<uint32_t>(0x5A6C16, MAXPARKEDCARS); 
  
    // Create a byte array of assembly instruction
    uint8_t HookCCarGeneratorsInitBuffer[] = 
    {
        0xC7, 0x05, 0x90, 0x90, 0x90, 0x90, 0x00, 0x00, 0x00, 0x00,
        0xC7, 0x05, 0xA8, 0xF2, 0x97, 0x00, 0x00, 0x00, 0x00, 0x00,
        0xC3,
    };

    // Patch the byte array to CTheCarGenerators::Init(void) section
    (*(uint32_t*)(HookCCarGeneratorsInitBuffer + 2)) = (uint32_t)&CTheCarGenerators__ProcessCounter;
    CMemory::UnProtect(0x5A6BF1, sizeof(HookCCarGeneratorsInitBuffer));
    memcpy((void*)0x005A6BF1, HookCCarGeneratorsInitBuffer, sizeof(HookCCarGeneratorsInitBuffer));
      
    CMemory::NoOperation(0x005A6C97, 6);
    CMemory::InstallCallHook(0x005A6C97, (DWORD)&HookCTheCarGenerators4bCounter, ASM_JMP);
}
//-----------------------------------------------------------------------------


void PatchMiscData(){
    PatchLoadingBarDisplayOnly();
    PatchCarGeneratorLimit();
    
    // Change the fade-out color to black upon death/busted.
	CMemory::InstallPatch<BYTE>(0x42BC1A, 0);
	CMemory::InstallPatch<BYTE>(0x42BC1F, 0);
	CMemory::InstallPatch<BYTE>(0x42BC24, 0);

    // Initialize the default limit for the detail distance.
	CMemory::InstallPatch<float>(0x69022C, 300.0f);
	CMemory::InstallPatch<float>(0x698FE0, 300.0f);
    
    // Apply the streaming memory patch.
    //CMemory::InstallPatch<DWORD>(0x94DD54, 1024 * 1024 * 1024);

    // These patches allow us to have a custom horizon, replacing the "ugly grey" color.
	//CMemory::NoOperation(0x53F4AC, 0x05);
	//CMemory::NoOperation(0x53F4DE, 0x05);
	//CMemory::NoOperation(0x53F514, 0x05);
	//CMemory::NoOperation(0x53F519, 0x07);
	//CMemory::InstallPatch<DWORD>(0x978574, 0xFF646464);
}
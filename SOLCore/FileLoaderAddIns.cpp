#include "StdInc.h"

char szSOLScenePath[] = "SOL\\Scene.dat";

void prevChange(){
    CMemory::NoOperation(0x48D95E,2);
}

void nextChange(){
    CMemory::InstallPatch<byte>(0x48D95E, 0x30);
    CMemory::InstallPatch<byte>(0x48D95F, 0xDB);
}

void __declspec (naked) Hook_CGameInitialize(){
    __asm{
        push ebx
        call CFileLoader::LoadLevel
        pop ecx

    //------------------------------------------------------------
    // The previous gta_vc.dat already loads the Collision stuffs
    // This makes changes to ensure the Collision is not loaded twice
    // When reading our dat file
    //-------------------------------------------------------------
        pushad
        call prevChange
        popad
        mov bl, 0x01

        push OFFSET szSOLScenePath
        call CFileLoader::LoadLevel
        pop ecx
    
    //------------------------------------------------------------
    // This restores the changes done to disable reading Collision
    // After CFileLoader::LoadLevel finishes reading our dat file
    //------------------------------------------------------------
        pushad
        call nextChange
        popad

        ret
    }
}

DWORD dwHookGetLine = 0x48B9F5;

DWORD dwHookJmp48B1F0 = 0x48B1F0;
void __declspec (naked) Hook_48B1C0(){
    __asm{
        cmp al, 'o'
        jnz checkCARS
        cmp byte ptr [esi + 1], 'c'
        jnz checkCARS
        cmp byte ptr [esi + 2], 'c'
        jnz checkCARS
        cmp byte ptr [esi + 3], 'l'
        jnz checkCARS
        mov ebx, 4
        jmp dwHookGetLine

checkCARS:
        cmp al, 'c'
        jnz getline
        cmp byte ptr [esi + 1], 'a'
        jnz getline
        cmp byte ptr [esi + 2], 'r'
        jnz getline
        cmp byte ptr [esi + 3], 's'
        jnz getline
        mov ebx, 7 // This is used so that the instruction goes to HookReadLineCARS
getline:
        jmp dwHookGetLine
    }
}

void LoadCarGenerators(char* currentLine){
    float fX; 
    float fY; 
    float fZ; 
    float fangle; 
    int iModelID;
    int primaryCol;
    int secondaryCol;
    unsigned char forceSpawn;
    unsigned char alarmProbability;
    char doorLockProbability;
    int minDelay;
    int maxDelay;
    
    sscanf(currentLine, "%f %f %f %f %d %d %d %d %d %d %d %d", &fX, &fY, &fZ, &fangle, &iModelID, &primaryCol, &secondaryCol, &forceSpawn, &alarmProbability, &doorLockProbability, &minDelay, &maxDelay);
    int currentIndex = CTheCarGenerators__CreateCarGenerator(fX, fY, fZ, 
                                                                fangle, 
                                                                iModelID, 
                                                                primaryCol, 
                                                                secondaryCol, 
                                                                forceSpawn, 
                                                                alarmProbability, 
                                                                doorLockProbability, 
                                                                minDelay, 
                                                                maxDelay);
    CCarGenerator__SwitchOn(currentIndex);
}

void __declspec (naked) HookReadLineCARS(){
    __asm{
        push esi
        call LoadCarGenerators
        pop esi
        jmp dwHookGetLine
    }
}

void AddIPLSections(){
    CMemory::NoOperation(0x48B1C0, 8);
    CMemory::InstallCallHook(0x48B1C0, (DWORD)&Hook_48B1C0, ASM_JMP);

    //Patch the comparision limit
    CMemory::InstallPatch<byte> (0x48B20E, 0x07);

    static DWORD jmptableForLoadLevel[] = { 
        0x0048B21C, 0x0048B228, 0x0048B29C, 
        0x0048B348, 0x0048B3DF, 0x0048B412, 
        0x00000000};

    // Add a jump table offset for Loading 'cars'
    jmptableForLoadLevel[6] = (DWORD)&HookReadLineCARS;

    CMemory::InstallPatch<DWORD>(0x48B218, (DWORD)&jmptableForLoadLevel);
}

void InstallFileLoaderHooks(void){
    // Ensure we have the SOL files
    FILE * fCheckDAT = fopen(szSOLScenePath, "rb");

	if(!fCheckDAT){
	    MessageBox(0,"You are missing the SOL scene.dat","GTA:State Of Liberty Error",MB_OK);
        SetForegroundWindow(HWND_DESKTOP);
		ExitProcess(1);			
    }
		
	fclose(fCheckDAT);
        
    CMemory::NoOperation(0x4A4C9F, 7);
    CMemory::InstallCallHook(0x4A4C9F, (DWORD)&Hook_CGameInitialize, ASM_CALL);

    // The following function adds new section called 'cars' in CFileLoader::LoadScene
    AddIPLSections();
}
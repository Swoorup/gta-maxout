#include "SJLIB/stdinc.h"

// get the pointer to new car generator buffer
extern CCarGenerator* pNewCarGeneratorBuffer;
		
DWORD dwFunc_CCarGenerator__SwitchOn  = 0x5A7650;
DWORD dwFunc_CCarGenerator__SwitchOff = 0x5A7670;
DWORD dwFunc_CTheCarGenerator__CreateCarGenerator = 0x5A6C10;

__declspec(naked) int CTheCarGenerators__CreateCarGenerator(float fX, float fY, float fZ, float fangle, int iModelID, int primaryCol, int secondaryCol, unsigned char forceSpawn, unsigned char alarmProbability, char doorLockProbability, int minDelay, int maxDelay) {
	__asm jmp dwFunc_CTheCarGenerator__CreateCarGenerator
}

void CCarGenerator__SwitchOn(int index){
    __asm{
        mov ecx, index
        imul ecx, 0x2C
        add ecx, pNewCarGeneratorBuffer
        call dwFunc_CCarGenerator__SwitchOn
    }
}

void CCarGenerator__SwitchOff(int index){
    __asm{
        mov ecx, index
        imul ecx, 0x2C
        add ecx, pNewCarGeneratorBuffer
        call dwFunc_CCarGenerator__SwitchOff
    }
}
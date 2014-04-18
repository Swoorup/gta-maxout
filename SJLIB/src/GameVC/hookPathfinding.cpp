#include "SJLIB/stdinc.h"
using namespace HookSystem;

template<> CPathFindHook * CSingleton<CPathFindHook>::m_pSingleton = NULL;
CPathFind* pThePaths = NULL;

void CPathFindHook::InitPathBuffer(void)
{
	//    pThePaths = (CPathFind*)0x9B6E5C;
	pThePaths = new CPathFind();
}

void CPathFindHook::DeletePathBuffer(void)
{
	delete pThePaths;
}

int _nHookDetachedNodeIndex;
int _nHookAttachedNodeIndex;
CPathNode* _pHookPathNode;
wchar_t* _pwszHookString;
int* _pHookEditValue;
void* _pHookReturn;
DWORD _dwIndexWithSize;
DWORD _dwHookArgOne, _dwHookArgTwo;
CPathFind* _pHookPathFind;
CCarPathLink* _pHookDetachedNode;
DWORD _dwHookLocal;
int _iHookNodeX, _iHookNodeY, _iHookNodeZ;
float _fHookFloatOne, _fHookFloatTwo;
int _nHookReturn;
int _nHookIndexOne, _nHookIndexTwo;
byte _byteHookSpawnRateOne, _byteHookSpawnRateTwo;
byte _byteHookLocal;

#define ASMJMP(x) {_asm push x _asm retn} 

// These hooks are inside CCarCtrl::GenerateOneEmergencyServicesCar.
// They make sure coordinates of Pathfind member are attached properly

//41C4F1
void _declspec(naked) HookGenEmerCarCheckVehicleType(void) {
    _asm mov _nHookAttachedNodeIndex, ecx
    _asm pushad

    if(pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].bitIsVehicleBoat) {
        _asm popad
        ASMJMP(41C531h)
    }

    _asm popad
    ASMJMP(41C4FFh)
}

//41C6A5
void _declspec(naked) HookGenEmerCarGetAttachedZCoorsOne(void) {
    _asm mov esi, [esp+68h]
    _asm mov ecx, [esp+64h]
    _asm lea edx, [esp+28h]
    _asm mov _dwHookArgOne, esi
    _asm mov _dwHookArgTwo, ecx
    _asm pushad

    _nHookReturn = pThePaths->m_AttachedPaths[_dwHookArgOne].wZ;

    _asm popad
    _asm mov eax, _nHookReturn
    _asm push 0
    _asm push 0
    _asm mov [esp+28h], eax
    _asm pushad

    _fHookFloatOne = 0.125f;
    _nHookReturn = pThePaths->m_AttachedPaths[_dwHookArgTwo].wZ;

    _asm popad
    _asm fild dword ptr [esp+28h]
    _asm fmul _fHookFloatOne
    _asm mov eax, _nHookReturn
    ASMJMP(41C6EBh)
}

//-----------------------------------------------------------------------
// This is a hook inside CCarCtrl::JoinCarWithRoadSystemGotoCoors.
// It fixes the instructions which subtracts the pathnode with the first
// pathnode element in the ThePaths and divides them by the size of
// CPathNode to get the index.
//-----------------------------------------------------------------------

//41CF52
void _declspec(naked) HookJoinCarWithRoadFixPathPointerSubtract(void) {
    _asm mov _pHookPathNode, edx
    _asm pushad

    _nHookAttachedNodeIndex = _pHookPathNode - &pThePaths->m_AttachedPaths[0];

    _asm popad
    _asm mov ecx, _nHookAttachedNodeIndex
    _asm mov [ebx+128h], ecx
    _asm lea ecx, [ebx+128h]
    _asm mov eax, 418CA0h
    _asm call eax
    _asm mov edx, [ebx+178h]
    _asm mov _pHookPathNode, edx
    _asm pushad

    _nHookAttachedNodeIndex = _pHookPathNode - &pThePaths->m_AttachedPaths[0];

    _asm popad
    _asm mov ecx, _nHookAttachedNodeIndex
    ASMJMP(41CF97h)
}

//-----------------------------------------------------------------------------
// These are hooks inside CCarCtrl::SteerAICarWithPhysicsFollowPaths. They make 
// sure that proper values with proper type for ThePaths fields are loaded in 
// CCarCtrl elements.
// To DO: Reverse entirely in the future
//-----------------------------------------------------------------------------

//41EF70
void _declspec(naked) HookSteerAICarFixDetachedNodeMultiplierOne(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _dwIndexWithSize = _nHookDetachedNodeIndex * sizeof(CCarPathLink);

    _asm popad
    _asm mov ebp, _dwIndexWithSize
    ASMJMP(41EF7Bh)
}

//41EFEB
void _declspec(naked) HookSteerAICarFixDetachedNodeMultiplierTwo(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _dwIndexWithSize = _nHookDetachedNodeIndex * sizeof(CCarPathLink);

    _asm popad
    _asm mov esi, _dwIndexWithSize
    ASMJMP(41EFF5h)
}


//41F088
void _declspec(naked) HookSteerAICarFixDetachedPreGetLaneDistanceOne(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _pHookDetachedNode = &pThePaths->m_CarPathLinks[_nHookDetachedNodeIndex];

    _asm popad
    _asm mov ecx, _pHookDetachedNode
    ASMJMP(41F09Eh)
}

//41F0C8
void _declspec(naked) HookSteerCarAIGetDetachedNodeXYCoorsOne(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _nHookReturn = pThePaths->m_CarPathLinks[_nHookDetachedNodeIndex].wX;

    _asm popad
    _asm mov eax, _nHookReturn
    _asm mov [esp+0A0h], eax
    _asm fild dword ptr [esp+0A0h]
    _asm pushad

    _nHookReturn = pThePaths->m_CarPathLinks[_nHookDetachedNodeIndex].wY;

    _asm popad
    _asm mov eax, _nHookReturn
    ASMJMP(41F0EEh)
}

//41F130
void _declspec(naked) HookSteerCarAIGetDetachedNodeXYCoorsTwo(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _nHookReturn = pThePaths->m_CarPathLinks[_nHookDetachedNodeIndex].wX;

    _asm popad
    _asm mov eax, _nHookReturn
    _asm mov [esp+0A0h], eax
    _asm fild dword ptr [esp+0A0h]
    _asm pushad

    _nHookReturn = pThePaths->m_CarPathLinks[_nHookDetachedNodeIndex].wY;

    _asm popad
    _asm mov eax, _nHookReturn
    ASMJMP(41F156h)
}

//41F346
void _declspec(naked) HookSteerCarAIFixDetachedPreGetLaneDistanceTwo(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _pHookDetachedNode = &pThePaths->m_CarPathLinks[_nHookDetachedNodeIndex];

    _asm popad
    _asm mov ecx, _pHookDetachedNode
    ASMJMP(41F35Ch)
}

//41F386
void _declspec(naked) HookSteerCarAIGetDetachedNodeXYCoorsThree(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _nHookReturn = pThePaths->m_CarPathLinks[_nHookDetachedNodeIndex].wX;

    _asm popad
    _asm mov eax, _nHookReturn
    _asm mov [esp+0A0h], eax
    _asm fild dword ptr [esp+0A0h]
    _asm pushad

    _nHookReturn = pThePaths->m_CarPathLinks[_nHookDetachedNodeIndex].wY;

    _asm popad
    _asm mov eax, _nHookReturn
    ASMJMP(41F3ACh)
}

//41F440
void _declspec(naked) HookSteerCarAIFixDetachedNodeMultiplierThree(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _dwIndexWithSize = _nHookDetachedNodeIndex * sizeof(CCarPathLink);

    _asm popad
    _asm mov ebp, _dwIndexWithSize
    ASMJMP(41F44Bh)
}

//41F4BB
void _declspec(naked) HookSteerCarAIFixDetachedNodeMultiplierFour(void){
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _dwIndexWithSize = _nHookDetachedNodeIndex * sizeof(CCarPathLink);

    _asm popad
    _asm mov edx, _dwIndexWithSize
    ASMJMP(41F4C5h)
}



//41F525
void _declspec(naked) HookSteerCarAIGetDetachedNodeXYCoorsFour(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _nHookReturn = pThePaths->m_CarPathLinks[_nHookDetachedNodeIndex].wY;

    _asm popad
    _asm mov eax, _nHookReturn
    _asm fldz
    _asm fldz
    _asm mov [esp+0A0h], eax
    _asm fldz
    _asm fldz
    _asm fldz
    _asm fldz
    _asm fild dword ptr [esp+0A0h]
    _asm pushad

    _nHookReturn = pThePaths->m_CarPathLinks[_nHookDetachedNodeIndex].wX;

    _asm popad
    _asm mov eax, _nHookReturn
    ASMJMP(41F558h)
}

//41F838
void _declspec(naked) HookSteerCarAIFixDetachedPreGetLaneDistanceThree(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _pHookDetachedNode = &pThePaths->m_CarPathLinks[_nHookDetachedNodeIndex];

    _asm popad
    _asm mov ecx, _pHookDetachedNode
    ASMJMP(41F84Eh)
}

//41F87B
void _declspec(naked) HookSteerCarAIGetDetachedNodeXYCoorsFive(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _nHookReturn = pThePaths->m_CarPathLinks[_nHookDetachedNodeIndex].wY;
    _dwIndexWithSize = _nHookDetachedNodeIndex * sizeof(CCarPathLink);
    _fHookFloatOne = 0.125f;

    _asm popad
    _asm mov ebp, _dwIndexWithSize
    _asm mov eax, _nHookReturn
    _asm mov [esp+0A0h], eax
    _asm push eax
    _asm fild dword ptr[esp+0A4h]
    _asm fmul _fHookFloatOne
    _asm fstp dword ptr[esp+94h]
    _asm fld dword ptr[esp+24h]
    _asm fmul dword ptr[esp+98h]
    _asm fsubr dword ptr[esp+94h]
    _asm fsub dword ptr[esi+4]
    _asm fstp dword ptr [esp]
    _asm pushad

    _nHookReturn = pThePaths->m_CarPathLinks[_nHookDetachedNodeIndex].wX;

    _asm popad
    _asm mov eax, _nHookReturn
    ASMJMP(41F8C8h)
}

// These hooks are inside CCarCtrl::GenerateOneRandomCar

//42733C
void _declspec(naked) HookGenOneRandomCarCompareSpawnRate(void) {
    _asm mov _nHookIndexOne, eax
    _asm mov eax, [esp+0C0h]
    _asm mov _nHookIndexTwo, eax
    _asm pushad

    _byteHookSpawnRateOne = pThePaths->m_AttachedPaths[_nHookIndexOne].byteSpawnRate;
    _byteHookSpawnRateTwo = pThePaths->m_AttachedPaths[_nHookIndexTwo].byteSpawnRate;

    if(_byteHookSpawnRateTwo >= _byteHookSpawnRateOne) {
        _asm popad
        _asm mov cl, _byteHookSpawnRateOne
        _asm mov bl, cl
        ASMJMP(427363h)
    }

    _asm popad
    _asm mov cl, _byteHookSpawnRateOne
    _asm mov bl, _byteHookSpawnRateTwo
    ASMJMP(427363h)
}

//427380h
void _declspec(naked) HookGenOneRandomCarCheckBoat(void) {
    _asm mov _nHookAttachedNodeIndex, edx
    _asm pushad

    if(pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].bitIsVehicleBoat) {
        _asm popad
        ASMJMP(427392h)
    }

    _asm popad
    ASMJMP(427581h)
}

//42752Ah
void _declspec(naked) HookGenOneRandomCarCheckVehClass(void) {
    _asm mov _nHookIndexOne, ebx
    _asm mov edx, [esp+0C4h]
    _asm mov _nHookIndexTwo, edx
    _asm pushad

    if(pThePaths->m_AttachedPaths[_nHookIndexOne].bitHaveUnrandomizedVehClass || pThePaths->m_AttachedPaths[_nHookIndexTwo].bitHaveUnrandomizedVehClass) {
        _asm popad
        ASMJMP(427551h)
    }

    _asm popad
    ASMJMP(427581h)
}

int _nHooki, _nHookCompareIndexOne, _nHookCompareIndexTwo;
int _nHookx1, _nHooky1, _nHookz1;
int _nHookx2, _nHooky2, _nHookz2;
float _fHookValueHalf = 0.5f;
float _fHookValueOne = 1.0f;
float _fHookValueOneByEight = 0.125f;

//427623h
void _declspec(naked) HookGenOneRandomCarGetProperLaneOne(void) {
    _asm mov _nHookAttachedNodeIndex, ebx
    _asm mov eax, [esp+0C4h]
    _asm mov _nHookCompareIndexOne, eax
    _asm pushad

    _byteHookLocal = pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].bitnumberOfNodesConnected;
    //_dwIndexWithSize = _nHookAttachedNodeIndex * sizeof(CPathNode);

    for(_nHooki = 0; _nHooki < _byteHookLocal && _nHookCompareIndexOne != (pThePaths->m_infoConnectedNodes[pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wRouteInfoIndex + _nHooki] & CPathFind::em_infoConnectedNodesNODEINDEXONLY); _nHooki++) {
    }

    _nHookReturn = pThePaths->m_InfoCarPathLinks[pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wRouteInfoIndex + _nHooki];

    _asm popad
    _asm mov eax, _nHookReturn
    _asm mov [esp+20h], eax
    _asm pushad

    if(pThePaths->m_CarPathLinks[_nHookReturn].nIndexToAttachedNode == _nHookCompareIndexOne) {
        _byteHookLocal = pThePaths->m_CarPathLinks[_nHookReturn].bitLeftLanes;
        _asm popad
        _asm mov dl, _byteHookLocal
        _asm movzx eax, dl
        ASMJMP(4276B7h)
    }

    _byteHookLocal = pThePaths->m_CarPathLinks[_nHookReturn].bitRightLanes;
    _asm popad
    _asm mov cl, _byteHookLocal
    _asm movzx eax, cl
    ASMJMP(4276B7h)
}


//427B07h
void _declspec(naked) HookGenOneRandomCarGetXYsOne(void) {
    _asm mov _nHookIndexOne, eax
    _asm fsub dword ptr [ecx+14h]
    _asm mov edi, [esp+0C0h]
    _asm mov _nHookIndexTwo, edi
    _asm pushad

    _nHookx1 = pThePaths->m_AttachedPaths[_nHookIndexOne].wX;
    _nHooky1 = pThePaths->m_AttachedPaths[_nHookIndexOne].wY;

    _nHookx2 = pThePaths->m_AttachedPaths[_nHookIndexTwo].wX;
    _nHooky2 = pThePaths->m_AttachedPaths[_nHookIndexTwo].wY;

    _asm popad
    _asm {
        fstp st(4)
        fld _fHookValueHalf
        fmul st, st(4)
        fadd _fHookValueOne
        mov ecx, _nHooky1
        fstp st(4)
        mov [esp+0B0h], ecx
        fild dword ptr[esp+0B0h]
        fmul _fHookValueOneByEight
        fstp dword ptr [esp+3Ch]
        mov edx, _nHooky2
        mov [esp+0B0h], edx
        fild dword ptr [esp+0B0h]
        fmul _fHookValueOneByEight
        fstp dword ptr [esp+38h]
        mov ebx, _nHooky1
        mov [esp+0B0h], ebx
        fild dword ptr [esp+0B0h]
        fmul _fHookValueOneByEight
        fstp dword ptr [esp+34h]
        mov ecx, _nHooky2
        mov [esp+0B0h], ecx
        fild dword ptr [esp+0B0h]
        fmul _fHookValueOneByEight
        fstp dword ptr [esp+30h]
        mov edx, _nHookx1
        mov [esp+0B0h], edx
        fild dword ptr [esp+0B0h]
        fmul _fHookValueOneByEight
        fstp st(2)
        fld st(1)
        fstp dword ptr [esp+28h]
        mov eax, _nHookx2
    }
    ASMJMP(427BDAh)
}

CVehicle* _pHookVehicle;

//427CC6h
void _declspec(naked) HookGenRandomCarPathsGeneric(void) {
    _asm mov _nHookAttachedNodeIndex, ecx
    _asm pushad

    _byteHookLocal = pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].bitnumberOfNodesConnected;
    if(_byteHookLocal == 1) {
        _asm popad
        ASMJMP(427CD6h)
    }
    _asm popad
    _asm mov _pHookVehicle, ebp
    _asm fldz
    _asm pushad

    for(_nHooki = _pHookVehicle->stAutopilot.m_dwNextCarLinkNode; _nHooki == _pHookVehicle->stAutopilot.m_dwNextCarLinkNode; _nHooki = pThePaths->m_InfoCarPathLinks[_dwHookLocal + pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wRouteInfoIndex]) {
        _asm fcompp
        _asm fcompp
        _asm fstp st
        _dwHookLocal = (unsigned int)rand() % _byteHookLocal;
        _asm fldz
        _asm fldz
        _asm fldz
        _asm fldz
        _asm fldz
    }
    _pHookVehicle->stAutopilot.m_dwCurrentCarLinkNode = _nHooki;
    if((pThePaths->m_infoConnectedNodes[_dwHookLocal + pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wRouteInfoIndex] & CPathFind::em_infoConnectedNodesNODEINDEXONLY) >= _nHookAttachedNodeIndex) {
        _pHookVehicle->stAutopilot.m_byteCurrentDirectionScale = 1;
    }
    else {
        _pHookVehicle->stAutopilot.m_byteCurrentDirectionScale = -1;
    }

    _asm popad
    ASMJMP(427DA7h);
}

//427DB5h
void _declspec(naked) HookGenOneRandomCarGetXYZsTwo(void) {
    _asm mov _nHookIndexOne, ecx
    _asm mov _nHookIndexTwo, ebx
    _asm pushad

    _nHookx1 = pThePaths->m_AttachedPaths[_nHookIndexOne].wX;
    _nHooky1 = pThePaths->m_AttachedPaths[_nHookIndexOne].wY;
    _nHookz1 = pThePaths->m_AttachedPaths[_nHookIndexOne].wZ;

    _nHookx2 = pThePaths->m_AttachedPaths[_nHookIndexTwo].wX;
    _nHooky2 = pThePaths->m_AttachedPaths[_nHookIndexTwo].wY;
    _nHookz2 = pThePaths->m_AttachedPaths[_nHookIndexTwo].wZ;

    _asm popad
    _asm {
        mov eax, _nHookz1
        mov [esp+0B0h], eax
        fild dword ptr [esp+0B0h]
        mov eax, _nHooky1
        fmul _fHookValueOneByEight
        mov [esp+0B0h], eax
        mov eax, _nHookx1
        fstp st(3)
        fild dword ptr [esp+0B0h]
        mov [esp+0B0h], eax
        fmul _fHookValueOneByEight
        mov eax, _nHookz2
        fstp st(4)
        fild dword ptr [esp+0B0h]
        mov [esp+0B0h], eax
        fmul _fHookValueOneByEight
        fstp st(5)
        fild dword ptr [esp+0B0h]
        fmul _fHookValueOneByEight
        fstp dword ptr [esp+2Ch]
        mov eax, _nHooky2
        mov [esp+0B0h], eax
        fild dword ptr [esp+0B0h]
        mov eax, _nHookx2
    }
    ASMJMP(427E55h)
}

//427FA4h
void _declspec(naked) HookGenOneRandomCarGetDetachedNodeOffsetOne(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _dwIndexWithSize = _nHookDetachedNodeIndex * sizeof(CCarPathLink);
    

    _asm popad
    _asm mov edi, _dwIndexWithSize
    ASMJMP(427FAEh)
}

//428026h
void _declspec(naked) HookGenOneRandomCarGetDetachedNodeOffsetTwo(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _dwIndexWithSize = _nHookDetachedNodeIndex * sizeof(CCarPathLink);

    _asm popad
    _asm mov esi, _dwIndexWithSize
    ASMJMP(428030h)
}

//4280B4h
void _declspec(naked) HookGenOneRandomCarGetDetachedNodeOne(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _pHookDetachedNode = &pThePaths->m_CarPathLinks[_nHookDetachedNodeIndex];

    _asm popad
    _asm mov ecx, _pHookDetachedNode
    ASMJMP(4280CAh)
}


//42810Ah
void _declspec(naked) HookGenOneRandomCarGetDetachedNodeXYOne(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _iHookNodeX = pThePaths->m_CarPathLinks[_nHookDetachedNodeIndex].wX;
    _iHookNodeY = pThePaths->m_CarPathLinks[_nHookDetachedNodeIndex].wY;

    _asm popad
    _asm mov eax, _iHookNodeY
    _asm mov [esp+0B0h], eax
    _asm fild dword ptr [esp+0B0h]
    _asm mov eax, _iHookNodeX
    ASMJMP(428130h)
}


//428198h
void _declspec(naked) HookGenOneRandomCarGetDetachedNodeXYTwo(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _iHookNodeX = pThePaths->m_CarPathLinks[_nHookDetachedNodeIndex].wX;
    _iHookNodeY = pThePaths->m_CarPathLinks[_nHookDetachedNodeIndex].wY;

    _asm popad
    _asm mov eax, _iHookNodeY
    _asm mov [esp+0B0h], eax
    _asm fild dword ptr [esp+0B0h]
    _asm mov eax, _iHookNodeX
    ASMJMP(4281BEh)
}


//428236h
void _declspec(naked) HookGenRandomCarGetDetachedNodeTwo(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _dwIndexWithSize = _nHookDetachedNodeIndex * sizeof(CCarPathLink);

    _asm popad
    _asm mov edi, _dwIndexWithSize
    ASMJMP(428240h)
}


//4282B0
void _declspec(naked) HookGenRandomCarGetDetachedNodeThree(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _dwIndexWithSize = _nHookDetachedNodeIndex * sizeof(CCarPathLink);

    _asm popad
    _asm mov edx, _dwIndexWithSize
    ASMJMP(4282BAh)
}


//42846Bh
void _declspec(naked) HookGenRandomCarGetDetachedNodeXYThree(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _iHookNodeX = pThePaths->m_CarPathLinks[_nHookDetachedNodeIndex].wX;
    _iHookNodeY = pThePaths->m_CarPathLinks[_nHookDetachedNodeIndex].wY;

    _asm popad
    _asm mov eax, _iHookNodeY
    _asm mov [esp+0B0h], eax
    _asm fild dword ptr [esp+0B0h]
    _asm mov eax, _iHookNodeX
    ASMJMP(428491h)
}


//4284E2h
void _declspec(naked) HookGenRandomCarGetDetachedNodeXYFour(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _iHookNodeX = pThePaths->m_CarPathLinks[_nHookDetachedNodeIndex].wX;
    _iHookNodeY = pThePaths->m_CarPathLinks[_nHookDetachedNodeIndex].wY;

    _asm popad
    _asm mov eax, _iHookNodeY
    _asm mov [esp+0B0h], eax
    _asm fild dword ptr [esp+0B0h]
    _asm mov eax, _iHookNodeX
    ASMJMP(428508h)
}

//428585
void _declspec(naked) HookGenOneRandomCarGetXYZsThree(void) {
    _asm mov _nHookIndexOne, ecx
    _asm mov _nHookIndexTwo, edx
    _asm pushad

    _nHookx1 = pThePaths->m_AttachedPaths[_nHookIndexOne].wX;
    _nHooky1 = pThePaths->m_AttachedPaths[_nHookIndexOne].wY;
    _nHookz1 = pThePaths->m_AttachedPaths[_nHookIndexOne].wZ;

    _nHookx2 = pThePaths->m_AttachedPaths[_nHookIndexTwo].wX;
    _nHooky2 = pThePaths->m_AttachedPaths[_nHookIndexTwo].wY;
    _nHookz2 = pThePaths->m_AttachedPaths[_nHookIndexTwo].wZ;

    _asm popad
    _asm {
        add esp, 20h
        mov eax, _nHookz1
        fldz
        mov [esp+0B0h], eax
        fldz
        fldz
        fldz
        fild dword ptr [esp+0B0h]
        mov eax, _nHookz2
        fmul _fHookValueOneByEight
        mov [esp+0B0h], eax
        fild dword ptr [esp+0B0h]
        mov eax, _nHooky1
        fmul _fHookValueOneByEight
        mov [esp+0B0h], eax
        mov eax, _nHooky2
        fsubrp st(1), st
        fstp st(3)
        fild dword ptr [esp+0B0h]
        mov [esp+0B0h], eax
        mov eax, _nHookx1
        fmul _fHookValueOneByEight
        fild dword ptr [esp+0B0h]
        mov [esp+0B0h], eax
        mov eax, _nHookx2
    }
    ASMJMP(42861Dh)
}

//4286C0h
void _declspec(naked) HookGenRandomCarGetNodeZsOnly(void) {
    _asm mov _nHookIndexOne, ebx
    _asm mov _nHookIndexTwo, esi
    _asm pushad

    _nHookz1 = pThePaths->m_AttachedPaths[_nHookIndexOne].wZ;
    _nHookz2 = pThePaths->m_AttachedPaths[_nHookIndexTwo].wZ;

    _asm popad
    _asm mov eax, _nHookz1
    _asm mov [esp+0B0h], eax
    _asm fild dword ptr [esp+0B0h]
    _asm cmp byte ptr [esp+1Ch], 0
    _asm fmul _fHookValueOneByEight
    _asm mov eax, _nHookz2
    ASMJMP(428701h)
}

// This hook is inside CRestart::FindClosestPoliceRestartPoint
//442BD8h
void _declspec(naked) HookRestartForPoliceGetXYZ(void) {
    _asm mov _nHookAttachedNodeIndex, eax
    _asm pushad

    _iHookNodeX = pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wX;
    _iHookNodeY = pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wY;
    _iHookNodeZ = pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wZ;

    _asm popad
    _asm mov ecx, _iHookNodeZ
    _asm fldz
    _asm fldz
    _asm mov [esp+18h], ecx
    _asm fild dword ptr [esp+18h]
    _asm mov edx, _iHookNodeY
    _asm fmul _fHookValueOneByEight
    _asm mov [esp+18h], edx
    _asm mov eax, _iHookNodeX
    ASMJMP(442C09h)
}

// This hook is inside CRestart::FindClosestHospitalRestartPoint
//442E9Ch
void _declspec(naked) HookRestartForHospitalGetXYZ(void) {
    _asm mov _nHookAttachedNodeIndex, eax
    _asm pushad

    _fHookFloatOne = 0.125f;
    _iHookNodeX = pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wX;
    _iHookNodeY = pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wY;
    _iHookNodeZ = pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wZ;

    _asm popad
    _asm mov ecx, _iHookNodeZ
    _asm fldz
    _asm fldz
    _asm mov [esp+18h], ecx
    _asm fild dword ptr [esp+18h]
    _asm mov edx, _iHookNodeY
    _asm fmul _fHookFloatOne
    _asm mov [esp+18h], edx
    _asm mov eax, _iHookNodeX
    ASMJMP(442ECDh)
}

// This hook is inside CarCheatSpawner
//4AE9DDh
void _declspec(naked) HookCarCheatSpawner(void) {
    _asm mov _nHookAttachedNodeIndex, edi
    _asm pushad

    _fHookFloatOne = 0.125f;
    _iHookNodeX = pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wX;
    _iHookNodeY = pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wY;
    _iHookNodeZ = pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wZ;

    _asm popad
    _asm mov eax, _iHookNodeX
    _asm mov [esp], eax
    _asm fild dword ptr [esp]
    _asm mov eax, _iHookNodeY
    _asm fmul _fHookFloatOne
    _asm mov [esp], eax
    _asm mov eax, _iHookNodeZ
    ASMJMP(4AEA0Bh)
}


/*
 * This hooks are inside CWorld::RemoveFallenCars. These hooks
 * make sure the coordinates are loaded right from the path
 * node
 */

//4D4966h
void _declspec(naked) HookRemoveFallenCarsGetXYZ(void) {
    _asm mov _nHookAttachedNodeIndex, eax
    _asm mov ecx, esi
    _asm pushad

    _iHookNodeX = pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wX;
    _iHookNodeY = pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wY;
    _iHookNodeZ = pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wZ;

    _asm popad
    _asm mov ebp, _iHookNodeX
    _asm mov edx, _iHookNodeY
    _asm mov eax, _iHookNodeZ
    _asm fldz
    _asm fldz
    _asm mov [esp+8], ebp
    _asm fldz
    _asm fild dword ptr [esp+8]
    ASMJMP(4D4995h)
}

/* 
 * Thes hooks are inside CWorld::RemoveFallenPeds
 */
//4D4AF2
void _declspec(naked) HookRemoveFallenPedsGetXYZ(void) {
    _asm mov _nHookAttachedNodeIndex, eax
    _asm mov ecx, ebp
    _asm pushad

    _iHookNodeX = pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wX;
    _iHookNodeY = pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wY;
    _iHookNodeZ = pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wZ;

    _asm popad
    _asm mov edi, _iHookNodeX
    _asm mov edx, _iHookNodeY
    _asm mov eax, _iHookNodeZ
    _asm fldz
    _asm fldz
    _asm mov [esp+8], edi
    _asm fldz
    _asm fild dword ptr [esp+8]
    ASMJMP(4D4B21h)
}

// These hooks are inside CPed::FollowPath
//4F7800h
void _declspec(naked) HookPedFollowPathGetXY(void) {
    _asm mov _pHookPathNode, edx
    _asm pushad

    _iHookNodeX = _pHookPathNode->wX;
    _iHookNodeY = _pHookPathNode->wY;
    _fHookFloatOne = 0.125f;

    _asm popad
    _asm mov eax, _iHookNodeX
    _asm mov [esp], eax
    _asm fild dword ptr [esp]
    _asm fmul _fHookFloatOne
    _asm fst st(1)
    _asm fstp dword ptr [ebx+398h]
    _asm mov ecx, ebx
    _asm mov eax, _iHookNodeY
    ASMJMP(4F782Ch)
}

// This hook is inside sub_4F99F0

//4F9D47h
void _declspec(naked) HookSub4F99F0GetXYZ(void) {
    _asm mov _pHookPathNode, ecx
    _asm pushad

    _iHookNodeX = _pHookPathNode->wX;
    _iHookNodeY = _pHookPathNode->wY;
    _iHookNodeZ = _pHookPathNode->wZ;
    _fHookFloatOne = 0.125f;

    _asm popad
    _asm mov eax, _iHookNodeZ
    _asm fldz
    _asm fldz
    _asm mov [esp], eax
    _asm fldz
    _asm fild dword ptr [esp]
    _asm mov eax, _iHookNodeY
    _asm fmul _fHookFloatOne
    _asm mov [esp], eax
    _asm mov eax, _iHookNodeX
    ASMJMP(4F9D68h)
}

//This hook is inside CPed::SeekFollowingPath

//4FA201h
void _declspec(naked) HookSeekFollowingPathGetXYZ(void){
    _asm mov _pHookPathNode, edx
    _asm pushad

    _iHookNodeX = _pHookPathNode->wX;
    _iHookNodeY = _pHookPathNode->wY;
    _iHookNodeZ = _pHookPathNode->wZ;

    _fHookFloatOne = 0.125f;

    _asm popad
    _asm mov eax, _iHookNodeZ
    _asm mov [esp], eax
    _asm fild dword ptr [esp]
    _asm mov eax, _iHookNodeY
    _asm fmul _fHookFloatOne
    _asm mov [esp], eax
    _asm mov eax, _iHookNodeX
    ASMJMP(4FA21Ch)
}

//These hooks are inside CPed::WanderPath

//4FA946h
void _declspec(naked) HookWanderPathGetXYZOne(void){
    _asm mov _pHookPathNode, ecx
    _asm pushad

    _fHookFloatOne = 0.125f;
    _iHookNodeX = _pHookPathNode->wX;
    _iHookNodeY = _pHookPathNode->wY;
    _iHookNodeZ = _pHookPathNode->wZ;

    _asm popad
    _asm mov eax, _iHookNodeX
    _asm lea edi, [esp+2Ch]
    _asm mov [esp+20h], eax
    _asm fild dword ptr [esp+20h]
    _asm fmul _fHookFloatOne
    _asm fstp dword ptr [esp+50h]
    _asm mov eax, _iHookNodeY
    _asm lea esi, [esp+50h]
    _asm mov [esp+20h], eax
    _asm fild dword ptr [esp+20h]
    _asm fmul _fHookFloatOne
    _asm fstp dword ptr [esp+54h]
    _asm mov eax, _iHookNodeZ
    ASMJMP(4FA97Eh)
}

void _declspec(naked) HookWanderPathGetXYZTwo(void) {
    _asm mov _pHookPathNode, edi
    _asm pushad

    _fHookFloatOne = 0.125f;
    _iHookNodeX = _pHookPathNode->wX;
    _iHookNodeY = _pHookPathNode->wY;
    _iHookNodeZ = _pHookPathNode->wZ;

    _asm popad
    _asm mov eax, _iHookNodeX
    _asm mov [esp+20h], eax
    _asm fild dword ptr [esp+20h]
    _asm fmul _fHookFloatOne
    _asm fstp dword ptr [esp+5Ch]
    _asm mov eax, _iHookNodeY
    _asm lea esi, [esp+5Ch]
    _asm mov [esp+20h], eax
    _asm fild dword ptr [esp+20h]
    _asm fmul _fHookFloatOne
    _asm fstp dword ptr [esp+60h]
    _asm mov eax, _iHookNodeZ
    ASMJMP(4FABDAh)
}


//These Hooks are inside CPed::ProcessControl

//507184h
void _declspec(naked) HookPedProcessControlGetXYZOne(void) {
    _asm mov _nHookAttachedNodeIndex, eax
    _asm pushad

    _fHookFloatOne = 0.125f;
    _iHookNodeX = pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wX;
    _iHookNodeY = pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wY;
    _iHookNodeZ = pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wZ;
    _dwIndexWithSize = _nHookAttachedNodeIndex * sizeof(CPathNode);

    _asm popad
    _asm mov ebp, _dwIndexWithSize
    _asm mov eax, _iHookNodeZ
    _asm mov [esp+0A8h], eax
    _asm push eax
    _asm fild dword ptr [esp+0ACh]
    _asm fmul _fHookFloatOne
    _asm fstp dword ptr [esp]
    _asm mov eax, _iHookNodeY
    _asm mov [esp+0ACh], eax
    _asm push eax
    _asm fild dword ptr [esp+0B0h]
    _asm fmul _fHookFloatOne
    _asm fstp dword ptr [esp]
    _asm mov eax, _iHookNodeX
    ASMJMP(5071D5h)
}


//5072D5h
void _declspec(naked) HookPedProcessControlGetPathNodeOne(void) {
    _asm mov _nHookAttachedNodeIndex, eax
    _asm pushad

    _pHookPathNode = &pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex];

    _asm popad
    _asm mov eax, _pHookPathNode
    ASMJMP(5072E4h)
}

//507347h
void _declspec(naked) HookPedProcessControlGetXYZTwo(void) {
    _asm mov _pHookPathNode, ecx
    _asm pushad

    _fHookFloatOne = 0.125f;
    _iHookNodeX = _pHookPathNode->wX;
    _iHookNodeY = _pHookPathNode->wY;
    _iHookNodeZ = _pHookPathNode->wZ;

    _asm popad
    _asm mov eax, _iHookNodeZ
    _asm mov [esp+0A8h], eax
    _asm push eax
    _asm fild dword ptr [esp+0ACh]
    _asm fmul _fHookFloatOne
    _asm fstp dword ptr [esp]
    _asm mov eax, _iHookNodeY
    _asm mov [esp+0ACh], eax
    _asm push eax
    _asm fild dword ptr [esp+0B0h]
    _asm fmul _fHookFloatOne
    _asm fstp dword ptr [esp]
    _asm mov eax, _iHookNodeX
    ASMJMP(507383h)
}

//5073D0h
void _declspec(naked) HookPedProcessControlGetXYZThree(void) {
    _asm mov _nHookAttachedNodeIndex, eax
    _asm pushad

    _fHookFloatOne = 0.125f;
    _iHookNodeX = pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wX;
    _iHookNodeY = pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wY;
    _iHookNodeZ = pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wZ;
    _dwIndexWithSize = _nHookAttachedNodeIndex * sizeof(CPathNode);

    _asm popad
    _asm mov ebp, _dwIndexWithSize
    _asm mov eax, _iHookNodeZ
    _asm mov [esp+0A8h], eax
    _asm push eax
    _asm fild dword ptr [esp+0ACh]
    _asm fmul _fHookFloatOne
    _asm fstp dword ptr [esp]
    _asm mov eax, _iHookNodeY
    _asm mov [esp+0ACh], eax
    _asm push eax
    _asm fild dword ptr [esp+0B0h]
    _asm fmul _fHookFloatOne
    _asm fstp dword ptr [esp]
    _asm mov eax, _iHookNodeX
    ASMJMP(507421h)
}

//507460h
void _declspec(naked) HookPedProcessControlGetXYZFour(void) {
    _asm mov _dwIndexWithSize, ebp
    _asm pushad

    _fHookFloatOne = 0.125f;
    _nHookAttachedNodeIndex = _dwIndexWithSize / sizeof(CPathNode);
    _iHookNodeX = pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wX;
    _iHookNodeY = pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wY;
    _iHookNodeZ = pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wZ;

    _asm popad
    _asm mov eax, _iHookNodeZ
    _asm mov [esp+0A8h], eax
    _asm push eax
    _asm fild dword ptr [esp+0ACh]
    _asm fmul _fHookFloatOne
    _asm fstp dword ptr [esp]
    _asm mov eax, _iHookNodeY
    _asm mov [esp+0ACh], eax
    _asm push eax
    _asm fild dword ptr [esp+0B0h]
    _asm fmul _fHookFloatOne
    _asm fstp dword ptr [esp]
    _asm mov eax, _iHookNodeX
    ASMJMP(5074A5h)
}

//5074E4h
void _declspec(naked) HookPedProcessControlGetXYZFive(void) {
    _asm mov _dwIndexWithSize, ebp
    _asm pushad

    _fHookFloatOne = 0.125f;
    _nHookAttachedNodeIndex = _dwIndexWithSize / sizeof(CPathNode);
    _iHookNodeX = pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wX;
    _iHookNodeY = pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wY;
    _iHookNodeZ = pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wZ;

    _asm popad
    _asm mov eax, _iHookNodeZ
    _asm mov [esp+0A8h], eax
    _asm push eax
    _asm fild dword ptr [esp+0ACh]
    _asm fmul _fHookFloatOne
    _asm fstp dword ptr [esp]
    _asm mov eax, _iHookNodeY
    _asm mov [esp+0ACh], eax
    _asm push eax
    _asm fild dword ptr [esp+0B0h]
    _asm fmul _fHookFloatOne
    _asm fstp dword ptr [esp]
    _asm mov eax, _iHookNodeX
    ASMJMP(507529h)
}

//These hooks are inside CPed::PositionPedOutOfCollision

//5122BBh
void _declspec(naked) HookPedOutCollisionGetXYZ(void) {
    _asm mov _nHookAttachedNodeIndex, eax
    _asm pushad

    _iHookNodeX = pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wX;
    _iHookNodeY = pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wY;
    _iHookNodeZ = pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wZ;

    _asm popad
    _asm mov edi, _iHookNodeZ
    _asm mov ecx, _iHookNodeX
    _asm mov eax, _iHookNodeY
    ASMJMP(5122DAh)
}

//These hooks are inside CPed::ProcessObjective

//51F726h
void _declspec(naked) HookProcessObjectiveGetXYZOne(void) {
    _asm mov _nHookAttachedNodeIndex, eax
    _asm pushad

    _fHookFloatOne = 0.125f;
    _iHookNodeX = pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wX;
    _iHookNodeY = pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wY;
    _iHookNodeZ = pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wZ;
    _dwIndexWithSize = _nHookAttachedNodeIndex * sizeof(CPathNode);

    _asm popad
    _asm mov edi, _dwIndexWithSize
    _asm mov eax, _iHookNodeZ
    _asm mov [esp+118h], eax
    _asm push eax
    _asm fild dword ptr [esp+11Ch]
    _asm fmul _fHookFloatOne
    _asm fstp dword ptr [esp]
    _asm mov eax, _iHookNodeY
    _asm mov [esp+11Ch], eax
    _asm push eax
    _asm fild dword ptr [esp+120h]
    _asm fmul _fHookFloatOne
    _asm fstp dword ptr [esp]
    _asm mov eax, _iHookNodeX
    ASMJMP(51F777h)
}

//These hooks are inside CPopulation::AddToPopulation

//53C31Ah
void _declspec(naked) HookAddToPopulationCompareSpawnRate(void) {
    _asm mov _nHookIndexOne, eax
    _asm mov eax, [esp+0BCh]
    _asm mov _nHookIndexTwo, eax
    _asm pushad

    _byteHookSpawnRateOne = pThePaths->m_AttachedPaths[_nHookIndexOne].byteSpawnRate;
    _byteHookSpawnRateTwo = pThePaths->m_AttachedPaths[_nHookIndexTwo].byteSpawnRate;

    if(_byteHookSpawnRateTwo >= _byteHookSpawnRateOne) {
        _asm popad
        _asm mov dl, _byteHookSpawnRateOne
        _asm mov bl, dl
        ASMJMP(53C341h)
    }

    _asm popad
    _asm mov dl, _byteHookSpawnRateOne
    _asm mov bl, _byteHookSpawnRateTwo
    ASMJMP(53C341h)
}

//53C37Bh
void _declspec(naked) HookAddToPopulationIndexArithmetic(void) {
    _asm mov _nHookIndexOne, edx
    _asm mov _nHookIndexTwo, eax
    _asm pushad

    _dwHookArgOne = (DWORD)&pThePaths->m_AttachedPaths[_nHookIndexOne];
    _dwHookArgTwo = (DWORD)&pThePaths->m_AttachedPaths[_nHookIndexTwo];

    _asm popad
    _asm mov edx, _dwHookArgOne
    _asm mov eax, _dwHookArgTwo
    ASMJMP(53C39Ah)
}

void _stdcall _classTrampoline_CPathFind_Init(void)
{
	CPathFind* pPathFind;
	_asm mov pPathFind, ecx

	return pPathFind->Init();
}

void _stdcall _classTrampoline_CPathFind_PreparePathDataForType(uint8_t bytePathDataFor, CTempNode* pTempNode, CPathInfoForObject* pUnusedPathInfos, float fUnkRange, CPathInfoForObject* pPathInfosForObject, int nGroupNodesForObject)
{
	CPathFind* pPathFind;
	_asm mov pPathFind, ecx

	return pPathFind->PreparePathDataForType(bytePathDataFor, pTempNode, pUnusedPathInfos, fUnkRange, pPathInfosForObject, nGroupNodesForObject);
}

void _stdcall _classTrampoline_CPathFind_AllocatePathFindInfoMem(void)
{
	CPathFind* pPathFind;
	_asm mov pPathFind, ecx

	return pPathFind->AllocatePathFindInfoMem();
}

void _stdcall _classTrampoline_CPathFind_PreparePathData(void)
{
	CPathFind* pPathFind;
	_asm mov pPathFind, ecx

	return pPathFind->PreparePathData();
}

void _stdcall _classTrampoline_CPathFind_DoPathSearch(int iPathDataFor, float fOriginX, float fOriginY, float fOriginZ, int iFirstNode, float fDestX, float fDestY, float fDestZ, CPathNode* pIntermediateNodeList[], short *pSteps, short sMaxSteps, void *pVehicle, float *pfPathCost, float fMaxRadius, int iLastNode)
{
	CPathFind* pPathFind;
	_asm mov pPathFind, ecx

	CVector posOrigin(fOriginX, fOriginY, fOriginZ);
	CVector posDest(fDestX, fDestY, fDestZ);
	return pPathFind->DoPathSearch(iPathDataFor, posOrigin, iFirstNode, posDest, pIntermediateNodeList, pSteps, sMaxSteps, pVehicle, pfPathCost, fMaxRadius, iLastNode);
}

int _stdcall _classTrampoline_CPathFind_FindNodeClosestToCoors(float fX, float fY, float fZ, unsigned char iPathDataFor, float fRangeCoefficient, bool bCheckIgnored, bool bCheckRestrictedAccess, bool bCheckUnkFlagFor2, bool bIsVehicleBoat)
{
	CPathFind* pPathFind;
	_asm mov pPathFind, ecx

	CVector posCoors(fX, fY, fZ);
	return pPathFind->FindNodeClosestToCoors(posCoors, iPathDataFor, fRangeCoefficient, bCheckIgnored, bCheckRestrictedAccess, bCheckUnkFlagFor2, bIsVehicleBoat);
}

void _stdcall _classTrampoline_CPathFind_RemoveNodeFromList(CPathNode *pRemoveNode)
{
	CPathFind* pPathFind;
	_asm mov pPathFind, ecx

	return pPathFind->RemoveNodeFromList(pRemoveNode);
}

void _stdcall _classTrampoline_CPathFind_AddNodeToList(CPathNode* pTargetNode, int nHeuristicCostAndListIndex)
{
	CPathFind* pPathFind; 
	_asm mov pPathFind, ecx

	return pPathFind->AddNodeToList(pTargetNode, nHeuristicCostAndListIndex);
}

void _stdcall _classTrampoline_CPathFind_RemoveBadStartNode(float fX, float fY, float fZ, CPathNode **pIntermediateNodeList, short *pSteps)
{
	CPathFind* pPathFind;
	_asm mov pPathFind, ecx

	return pPathFind->RemoveBadStartNode(CVector(fX, fY, fZ), pIntermediateNodeList, pSteps);
}

void _stdcall _classTrampoline_CPathFind_FindNextNodeWandering(unsigned char iPathDataFor, float fX, float fY, float fZ, CPathNode** pCurrentNode, CPathNode** pNextNode, uint8_t bytePreviousDirection, uint8_t *byteNewDirection)
{
	CPathFind* pPathFind;
	_asm mov pPathFind, ecx

	return pPathFind->FindNextNodeWandering(iPathDataFor, CVector(fX, fY, fZ), pCurrentNode, pNextNode, bytePreviousDirection, byteNewDirection);
}

bool _stdcall _classTrampoline_CPathFind_NewGenerateCarCreationCoors(float fX, float fY, float fDirectionVecX, float fDirectionVecY, float fRange, float fZlookUp, bool bShouldSpawnPositiveDirection, CVector *pVecPosition, int *aMainNodeIndex, int *aSubNodeIndex, float *aNodeRangeDiffCoeff, char bDontCheckIgnored)
{
	CPathFind* pPathFind;
	_asm mov pPathFind, ecx

	return pPathFind->NewGenerateCarCreationCoors(CVector2D(fX, fY), CVector2D(fDirectionVecX, fDirectionVecY), fRange, fZlookUp, bShouldSpawnPositiveDirection, pVecPosition, aMainNodeIndex, aSubNodeIndex, aNodeRangeDiffCoeff, bDontCheckIgnored);
}

bool _stdcall _classTrampoline_CPathFind_GeneratePedCreationCoors(float fX, float fY, float fMinRange, float fMaxRange, float fSecMinRange, float fSecMaxRange, CVector *pvecSpawnPos, int *pStartNodeIndex, int *pNextNodeIndex, float *fRandomByte, RwMatrix *rwTransformationMatrix)
{
	CPathFind* pPathFind;
	_asm mov pPathFind, ecx

	return pPathFind->GeneratePedCreationCoors(CVector2D(fX, fY), fMinRange, fMaxRange, fSecMinRange, fSecMaxRange, pvecSpawnPos, pStartNodeIndex, pNextNodeIndex, fRandomByte, rwTransformationMatrix);
}

bool _stdcall _classTrampoline_CPathFind_TestCoorsCloseness(float fDestinationX, float fDestinationY, float fDestinationZ, uint8_t uiPathDataFor, float fOriginX, float fOriginY, float fOriginZ)
{
	CPathFind* pPathFind;
	_asm mov pPathFind, ecx

	return pPathFind->TestCoorsCloseness(CVector(fDestinationX, fDestinationY, fDestinationZ), uiPathDataFor, CVector(fOriginX, fOriginY, fOriginZ));
}

float _stdcall _classTrampoline_CPathFind_CalcRoadDensity(float fX, float fY)
{
	CPathFind* pPathFind;
	_asm mov pPathFind, ecx

	return pPathFind->CalcRoadDensity(CVector2D(fX, fY));
}

int _stdcall _classTrampoline_CPathFind_FindNodeClosestToCoorsFavourDirection(float fX, float fY, float fZ, uint8_t uiPathDataFor, float fLookAtX, float fLookAtY)
{
	CPathFind* pPathFind;
	_asm mov pPathFind, ecx

	return pPathFind->FindNodeClosestToCoorsFavourDirection(CVector(fX, fY, fZ), uiPathDataFor, CVector2D(fLookAtX, fLookAtY));
}

bool _stdcall _classTrampoline_CPathFind_TestCrossesRoad(CPathNode* pStartNode, CPathNode* pConnectedNode)
{
	CPathFind* pPathFind;
	_asm mov pPathFind, ecx

	return pPathFind->TestCrossesRoad(pStartNode, pConnectedNode);
}

bool _stdcall _classTrampoline_CPathFind_TestForPedTrafficLight(CPathNode* pStartNode, CPathNode* pConnectedNode)
{
	CPathFind* pPathFind;
	_asm mov pPathFind, ecx

	return pPathFind->TestForPedTrafficLight(pStartNode, pConnectedNode);
}

float _stdcall _classTrampoline_CCarPathLink_OneWayLaneOffset(void)
{
	CCarPathLink* pCarPathLink;
	_asm mov pCarPathLink, ecx

	return pCarPathLink->OneWayLaneOffset();
}

void _stdcall _classTrampoline_CAutomobile_PlayHornIfNecessary(void)
{
	CAutomobile* pAutomobile;
	_asm mov pAutomobile, ecx

	return pAutomobile->PlayHornIfNecessary();
}

/*
 * List Of Functions Hooked
 * 1.  CPathFind::Init                 -FINE GRAINED
 * 2.  CPathFind::PreparePathDataForType-THOROUGH REVISION AND DUMP TEST NEEDED
 * 3.  CPathFind::StoreNodeInfoPed     -FINE GRAINED
 * 4.  CPathFind::StoreNodeInfoCar     -FINE GRAINED
 * 5.  CPathFind::ArrangeOneNodeList   -FINE GRAINED
 * 6.  CFileLoader::LoadScene          -FINE GRAINED
 * 7.  CPathFind::PreparePathData      -FINE GRAINED
 * 8.  CPathFind::AllocatePathFindInfoMem- FINE GRAINED
 * 9.  CPathFind::AddNodeToList - FINE GRAINED
 * 10. CPathFind::RemoveNodeFromList - FINE GRAINED
 * 11. CPathFind::FindNodeClosestToCoors - REVISION NEEDED
 *          -can be optimized by setting up a grid system.
 *          -work is needed in improving generation per calls
 * 12. CPathFind::DoPathSearch - REVISION NEEDED
 * 13. CPathFind::RemoveBadStartNode   - REVISION DONE
 * 14. CPathFind::FindNextNodeWandering -REVISION NEEDED
 * 15. CPathFind::NewGenerateCarCreationCoors - Optimization needed, finding new nodes - work is needed in improving generation per calls
 * 16. CPathFind::GeneratePedCreationCoors - FINE GRAINED - work is needed in improving generation per calls
 * 17. CPathFind::TestCoorsCloseness - FINE GRAINED
 * 18. CPathFind::CalcRoadDensity - FINE GRAINED
 *          This functions calculates the sum of displacement between car nodes inside an area.
 *          The number is the divided by the area of the game (2500.0) to get the actual density
 * 19. CPathFind::FindNodeClosestToCoorsFavourDirection - REVISION NEEEDED
 *          This function calculates the nearest node favouring the direction an entity is heading
 *          or if not specified the x/straight direction of the entity
 *          -can be optimized using a grid system
 * 20. CPathFind::TestCrossesRoad
 * 21. CPathFind::TestForPedTrafficLight
 */

void CPathFindHook::ApplyHook() 
{

	// Hooked in CFileLoader::LoadLevel
    InstallFnByCall( 0x48DD5D, &CFileLoader::LoadScene);

    // CCarPathLink::OneWayLaneOffset - REVISION NEEDED

    // Disable Unused CPathFind Treadables in CFileLoader::LoadObjectInstance
    InstallNOPs(0x48AE30, 44);

    // Hooks in CGame::Init
    InstallFnByCall(0x4A4C0C, _classTrampoline_CPathFind_Init);
    InstallNOPs(0x4A4C16, 5); // Remove One Unused Parameter

    InstallFnByCall(0x4A4C1B, _classTrampoline_CPathFind_AllocatePathFindInfoMem);    
    InstallFnByCall(0x4A4CE7, _classTrampoline_CPathFind_PreparePathData);
    // Install PreparePathDataHook
    InstallFnByCall(0x43BF3C, _classTrampoline_CPathFind_PreparePathDataForType);
    InstallFnByCall(0x43BF74, _classTrampoline_CPathFind_PreparePathDataForType);

    InstallFnByJump(0x439070, _classTrampoline_CPathFind_DoPathSearch);
    InstallFnByJump(0x437150, _classTrampoline_CPathFind_FindNodeClosestToCoors);
    InstallFnByJump(0x437330, _classTrampoline_CPathFind_AddNodeToList);
    InstallFnByJump(0x4375C0, _classTrampoline_CPathFind_RemoveNodeFromList);
    InstallFnByJump(0x438F90, _classTrampoline_CPathFind_RemoveBadStartNode );
    InstallFnByJump(0x4386D0, _classTrampoline_CPathFind_FindNextNodeWandering);
    InstallFnByJump(0x4382B0, _classTrampoline_CPathFind_NewGenerateCarCreationCoors);
    InstallFnByJump(0x437B10, _classTrampoline_CPathFind_GeneratePedCreationCoors);
    InstallFnByJump(0x437A40, _classTrampoline_CPathFind_TestCoorsCloseness);
    InstallFnByJump(0x4377F0, _classTrampoline_CPathFind_CalcRoadDensity);
    InstallFnByJump(0x436E40, _classTrampoline_CPathFind_FindNodeClosestToCoorsFavourDirection);
    InstallFnByJump(0x4354E0, _classTrampoline_CPathFind_TestCrossesRoad);
    InstallFnByJump(0x4356B0, _classTrampoline_CPathFind_TestForPedTrafficLight);

    InstallFnByJump(0x434EB0, _classTrampoline_CCarPathLink_OneWayLaneOffset);

    InstallFnByJump(0x435140, CPathFind::TakeWidthIntoAccountForCoors);
    InstallFnByJump(0x4351C0, CPathFind::TakeWidthIntoAccountForWandering);



    // hooks inside CAutopilot::ModifySpeed
    void (CAutoPilot::*pCAutoPilot_ModifySpeed)(float fModSpeed);
    pCAutoPilot_ModifySpeed = &CAutoPilot::ModifySpeed;
    InstallFnByJump(0x418CD0, (void*&)pCAutoPilot_ModifySpeed);
	

    //hooks inside CCarCtrl::GenerateOneEmergencyServicesCar
    InstallFnByJump(0x41C4F1, HookGenEmerCarCheckVehicleType);
    InstallFnByJump(0x41C6A5, HookGenEmerCarGetAttachedZCoorsOne);
    CMemory::InstallPatch<CPathFind*>(0x41C4BD, pThePaths);

    //whole function replacement hook for CCarCtrl::FindLinksToGoWithTheseNodes
    InstallFnByJump(0x41CC20, CCarCtrl::FindLinksToGoWithTheseNodes);

    //hooks inside CCarCtrl::JoinCarWithRoadSystemGotoCoors
    CMemory::InstallPatch<CPathFind*>(0x41CECF, pThePaths);
    CMemory::InstallPatch<CPathFind*>(0x41CF21, pThePaths);
    InstallFnByJump(0x41CF52, HookJoinCarWithRoadFixPathPointerSubtract);

    //whole function replacement hook for CCarCtrl::JoinCarWithRoadSystems
    InstallFnByJump(0x41D000, CCarCtrl::JoinCarWithRoadSystem);

    //hooks inside CCarCtrl::SteerAICarWithPhysicsFollowPath
    InstallFnByJump(0x41EF70, HookSteerAICarFixDetachedNodeMultiplierOne);
    CMemory::InstallPatch<signed char*>(0x41EF7E, &pThePaths->m_CarPathLinks[0].NormalVecX);
    CMemory::InstallPatch<signed char*>(0x41EFAA, &pThePaths->m_CarPathLinks[0].NormalVecY);
    InstallFnByJump(0x41EFEB, HookSteerAICarFixDetachedNodeMultiplierTwo);
    CMemory::InstallPatch<signed char*>(0x41EFF8, &pThePaths->m_CarPathLinks[0].NormalVecX);
    CMemory::InstallPatch<CPathFind*>(0x41F015, pThePaths);
    CMemory::InstallPatch<signed char*>(0x41F02B, &pThePaths->m_CarPathLinks[0].NormalVecY);
    CMemory::InstallPatch<uint32_t>(0x41F045, OFFSETOF(CPathFind, m_CarPathLinks[0]));
    InstallFnByJump(0x41F088, HookSteerAICarFixDetachedPreGetLaneDistanceOne);
    InstallFnByJump(0x41F0C8, HookSteerCarAIGetDetachedNodeXYCoorsOne);
    InstallFnByJump(0x41F130, HookSteerCarAIGetDetachedNodeXYCoorsTwo);
    InstallFnByJump(0x41F346, HookSteerCarAIFixDetachedPreGetLaneDistanceTwo);
    InstallFnByJump(0x41F386, HookSteerCarAIGetDetachedNodeXYCoorsThree);
    InstallFnByJump(0x41F440, HookSteerCarAIFixDetachedNodeMultiplierThree);
    CMemory::InstallPatch<signed char*>(0x41F44E, &pThePaths->m_CarPathLinks[0].NormalVecX);
    CMemory::InstallPatch<signed char*>(0x41F47A, &pThePaths->m_CarPathLinks[0].NormalVecY);
    InstallFnByJump(0x41F4BB, HookSteerCarAIFixDetachedNodeMultiplierFour);
    CMemory::InstallPatch<signed char*>(0x41F4C8, &pThePaths->m_CarPathLinks[0].NormalVecX);
    CMemory::InstallPatch<signed char*>(0x41F4F4, &pThePaths->m_CarPathLinks[0].NormalVecY);
    InstallFnByJump(0x41F525, HookSteerCarAIGetDetachedNodeXYCoorsFour);
    InstallFnByJump(0x41F838, HookSteerCarAIFixDetachedPreGetLaneDistanceThree);
    InstallFnByJump(0x41F87B, HookSteerCarAIGetDetachedNodeXYCoorsFive);

    //hook for CCarCtrl::PickNextNodeToFollowPath
    InstallFnByJump(0x420D50, CCarCtrl::PickNextNodeToFollowPath);
    InstallFnByJump(0x4213A0, CCarCtrl::PickNextNodeToChaseCar);

    //june 28, 2012
    InstallFnByJump(0x421F70, CCarCtrl::PickNextNodeRandomly);
    InstallFnByJump(0x421DC0, CCarCtrl::FindPathDirection);

    //hook CCarCtrl::PickNextNodeAccordingStrategy
    InstallFnByJump(0x422A10, CCarCtrl::PickNextNodeAccordingStrategy);

    //hook CCarCtrl::UpdateCarOnRails
    InstallFnByJump(0x425BF0, CCarCtrl::UpdateCarOnRails);

    //hooks in CCarCtrl::GenerateOneRandomCar
    CMemory::InstallPatch<CPathFind*>(0x4272F0, pThePaths);
    InstallFnByJump(0x42733C, HookGenOneRandomCarCompareSpawnRate);
    InstallFnByJump(0x427380, HookGenOneRandomCarCheckBoat);
    InstallFnByJump(0x42752A, HookGenOneRandomCarCheckVehClass);
    CMemory::InstallPatch<CPathFind*>(0x4275DF, pThePaths);
    InstallFnByJump(0x427623, HookGenOneRandomCarGetProperLaneOne); //Hardest function of all times
    InstallFnByJump(0x427B07, HookGenOneRandomCarGetXYsOne);
    InstallFnByJump(0x427CC6, HookGenRandomCarPathsGeneric);

    InstallFnByJump(0x427DB5, HookGenOneRandomCarGetXYZsTwo);
    CMemory::InstallPatch<CPathFind*>(0x427F5D, pThePaths);
    InstallFnByJump(0x427FA4, HookGenOneRandomCarGetDetachedNodeOffsetOne);
    CMemory::InstallPatch<signed char*>(0x427FB1, &(pThePaths->m_CarPathLinks[0].NormalVecX));
    CMemory::InstallPatch<unsigned int>(0x427FC7, OFFSETOF(CPathFind, m_CarPathLinks[0]));
    CMemory::InstallPatch<signed char*>(0x427FE5, &(pThePaths->m_CarPathLinks[0].NormalVecY));
    InstallFnByJump(0x428026, HookGenOneRandomCarGetDetachedNodeOffsetTwo);
    CMemory::InstallPatch<signed char*>(0x428033, &(pThePaths->m_CarPathLinks[0].NormalVecX));
    CMemory::InstallPatch<signed char*>(0x42805F, &(pThePaths->m_CarPathLinks[0].NormalVecY));
    InstallFnByJump(0x4280B4, HookGenOneRandomCarGetDetachedNodeOne);
    InstallFnByJump(0x42810A, HookGenOneRandomCarGetDetachedNodeXYOne);
    InstallFnByJump(0x428198, HookGenOneRandomCarGetDetachedNodeXYTwo);
    InstallFnByJump(0x428236, HookGenRandomCarGetDetachedNodeTwo);
    CMemory::InstallPatch<signed char*>(0x428243, &(pThePaths->m_CarPathLinks[0].NormalVecY));
    CMemory::InstallPatch<signed char*>(0x428275, &(pThePaths->m_CarPathLinks[0].NormalVecX));
    InstallFnByJump(0x4282B0, HookGenRandomCarGetDetachedNodeThree);
    CMemory::InstallPatch<signed char*>(0x4282BD, &(pThePaths->m_CarPathLinks[0].NormalVecY));
    CMemory::InstallPatch<signed char*>(0x4282EF, &(pThePaths->m_CarPathLinks[0].NormalVecX));
    InstallFnByJump(0x42846B, HookGenRandomCarGetDetachedNodeXYThree);
    InstallFnByJump(0x4284E2, HookGenRandomCarGetDetachedNodeXYFour);
    InstallFnByJump(0x428585, HookGenOneRandomCarGetXYZsThree);
    InstallFnByJump(0x4286C0, HookGenRandomCarGetNodeZsOnly);

    //patches in CRestart::FindClosestPoliceRestartPoint
    CMemory::InstallPatch<CPathFind*>(0x442BB7, pThePaths);
    InstallFnByJump(0x442BD8, HookRestartForPoliceGetXYZ);

    //patches in CRestart::FindClosestHospitalRestartPoint
    CMemory::InstallPatch<CPathFind*>(0x442E79, pThePaths);
    InstallFnByJump(0x442E9C, HookRestartForHospitalGetXYZ);

    //patches in CFileLoader::LoadInstance
    CMemory::InstallPatch<CPathFind*>(0x48AE89, pThePaths);

    //patches in CGame::Initialize
    CMemory::InstallPatch<CPathFind*>(0x4A4C08, pThePaths);
    CMemory::InstallPatch<CPathFind*>(0x4A4C12, pThePaths);
    CMemory::InstallPatch<CPathFind*>(0x4A4CE0, pThePaths);

    //hooks in CarCheatSpawner
    CMemory::InstallPatch<CPathFind*>(0x4AE993, pThePaths);
    InstallFnByJump(0x4AE9DD, HookCarCheatSpawner);
    
    //patches in CPlayerInfo::Process
    CMemory::InstallPatch<CPathFind*> (0x4BD66D, pThePaths);
    CMemory::InstallPatch<CPathFind*> (0x4BD687, pThePaths);
    CMemory::InstallPatch<CPathFind*> (0x4BE6A3, pThePaths);

    //hooks in CWorld::RemoveFallenCars
    CMemory::InstallPatch<CPathFind*>(0x4D4945, pThePaths);
    InstallFnByJump(0x4D4966, HookRemoveFallenCarsGetXYZ);

    //hooks in CWorld::RemoveFallenPeds
    CMemory::InstallPatch<CPathFind*>(0x4D4AD1, pThePaths);
    InstallFnByJump(0x4D4AF2, HookRemoveFallenPedsGetXYZ);

    //hooks in CPed::FollowPath
    InstallFnByJump(0x4F7800, HookPedFollowPathGetXY);

    //hook in sub_4F99F0
    CMemory::InstallPatch<CPathFind*>(0x4F9BB5, pThePaths);
    InstallFnByJump(0x4F9D47, HookSub4F99F0GetXYZ);

    //This hook is inside CPed::SeekFollowingPath
    InstallFnByJump(0x4FA201, HookSeekFollowingPathGetXYZ);

    //These hook are inside CPed:WanderPath
    CMemory::InstallPatch<CPathFind*>(0x4FA8EA , pThePaths);
    InstallFnByJump(0x4FA946, HookWanderPathGetXYZOne);
    CMemory::InstallPatch<CPathFind*>(0x4FAB49, pThePaths);
    InstallFnByJump(0x4FABA6, HookWanderPathGetXYZTwo);
    CMemory::InstallPatch<CPathFind*>(0x4FAC36, pThePaths);
    CMemory::InstallPatch<CPathFind*>(0x4FAC5D, pThePaths);
    
    //These hooks are inside CPed::SetWanderPath
    CMemory::InstallPatch<CPathFind*>(0x4FAEEA, pThePaths);
    CMemory::InstallPatch<CPathFind*>(0x4FB064, pThePaths);
    
    //These hooks are inside CPed::Flee
    CMemory::InstallPatch<CPathFind*>(0x4FB42B, pThePaths);

    //These hooks are inside CPed::ProcessControl
    CMemory::InstallPatch<CPathFind*>(0x506F47, pThePaths);
    InstallFnByJump(0x507184, HookPedProcessControlGetXYZOne);
    InstallFnByJump(0x5072D5, HookPedProcessControlGetPathNodeOne);
    InstallFnByJump(0x507347, HookPedProcessControlGetXYZTwo);
    InstallFnByJump(0x5073D0, HookPedProcessControlGetXYZThree);
    InstallFnByJump(0x507460, HookPedProcessControlGetXYZFour);
    InstallFnByJump(0x5074E4, HookPedProcessControlGetXYZFive);

    
    //This hook is in CPed::WillChat
    CMemory::InstallPatch<CPathFind*>(0x50AC91, pThePaths);
    
    //These hooks are inside CPed::PositionPedOutOfCollision
    CMemory::InstallPatch<CPathFind*>(0x51228C, pThePaths);
    InstallFnByJump(0x5122BB, HookPedOutCollisionGetXYZ);

    // hooks for CPed::FindBestCoordsFromNodes
    bool (CPed::*pFindBestCoordsFromNodes)(float fUnusedX, float fUnusedY, float fUnusedZ, CVector* vecBestCoords);
    pFindBestCoordsFromNodes = &CPed::FindBestCoordsFromNodes;
    InstallFnByJump(0x513DF0, (void*&)pFindBestCoordsFromNodes);

    // These hooks are inside CPed::ProcessObjective
    CMemory::InstallPatch<CPathFind*>(0x51F6F8, pThePaths);
    InstallFnByJump(0x51F726, HookProcessObjectiveGetXYZOne);
    CMemory::InstallPatch<CPathFind*>(0x51F859, pThePaths);

    void (CPathNode::*pGetNodeCoors)(CVector* vecNodePosition);
    pGetNodeCoors = &CPathNode::GetNodeCoors;
    InstallFnByJump(0x520E90, (void*&)pGetNodeCoors);

    //These hooks are inside CPopulation::AddToPopulation
    CMemory::InstallPatch<CPathFind*>(0x53C2C0, pThePaths);
    InstallFnByJump(0x53C31A, HookAddToPopulationCompareSpawnRate);
    InstallFnByJump(0x53C37B, HookAddToPopulationIndexArithmetic);

    //TEMPORARY HOOK DISABLE FOR PED PATH TESTING
    CMemory::InstallPatch<unsigned char>(0x444280, 0xC3); // CRoadBlocks::GenerateRoadBlocks
	//CMemory::InstallPatch<unsigned char>(0x463F90, 0xC3); // CTraffilights::DisplayActualLight
	// the above function was just producing a false alert because of multipiliers

    InstallFnByJump(0x465C10, CTrafficLights::ShouldCarStopForLightN); //CTrafficLights::ShouldCarStopForLights
    InstallFnByJump(0x4661C0, CTrafficLights::ScanForLightsOnMapN); //CTrafficLights::ScanForLightsOnMap
	InstallFnByJump(0x5881F0, _classTrampoline_CAutomobile_PlayHornIfNecessary);
}

void CPathFindHook::RemoveHook(){
}

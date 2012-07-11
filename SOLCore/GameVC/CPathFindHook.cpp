#include "../StdInc.h"

template<> CPathFindHook * CSingleton<CPathFindHook>::m_pSingleton = NULL;
CPathFind* pThePaths = NULL;

CPathFindHook::CPathFindHook() {
    pThePaths = new CPathFind();   
//    pThePaths = (CPathFind*)0x9B6E5C;
}

CPathFindHook::~CPathFindHook() {
    RemoveHook();
    delete pThePaths;
    pThePaths = NULL;
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
CDetachedNode* _pHookDetachedNode;
DWORD _dwHookLocal;
int _iHookNodeX, _iHookNodeY, _iHookNodeZ;
float _fHookFloatOne, _fHookFloatTwo;
int _nHookReturn;
int _nHookIndexOne, _nHookIndexTwo;
byte _byteHookSpawnRateOne, _byteHookSpawnRateTwo;
byte _byteHookLocal;
#define ASMJMP(x) {_asm push x _asm retn} 

// ---------------------------------------------------------------------
// These hooks are inside CCarCtrl::GenerateOneEmergencyServicesCar.
// They make sure coordinates of Pathfind member are attached properly
//----------------------------------------------------------------------

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

//----------------------------------------------------------------
// This is a hook inside CCarCtrl::FindLinksToGoWithTheseNodes.
// It replaces the entire original function by jump to this 
// right after the function starts. This function seems to get 
// loaded when the a chasing cop car stops right near the player.
// To-Do: Change into a grid type setup
//----------------------------------------------------------------

//41CC20
void _cdecl HookFindLinksToGoWithTheseNodes(CVehicle* pVehicle) {
    _dwHookArgOne = pVehicle->field_1A6;
    CDebug::DebugAddText("HookFindLinksToGoWithTheseNodes");

    //unnecessary R* leftover?
    if (_dwHookArgOne) {
        _asm mov eax, _dwHookArgOne
        _asm push eax
        _asm mov eax, 649A30h
        _asm call eax
        _asm pop eax
    }
    
    int nConnectedPointInfo = pThePaths->m_AttachedPaths[pVehicle->Autopilot.m_dwMainNode].wRouteInfoIndex;
    int _nLoop = 0;

    for(int _nLoop = 0; _nLoop < 12 && pVehicle->Autopilot.m_dwNextNodeIndex != (pThePaths->AttachedPointsInfo[_nLoop + nConnectedPointInfo] & CPathFind::eATTACHEDPOINTSINFONODEINDEXONLY); _nLoop++);
    pVehicle->Autopilot.m_dwNextDetachedNodeIndex = pThePaths->DetachedPointsInfo[_nLoop + nConnectedPointInfo];
    if(pVehicle->Autopilot.m_dwMainNode >= pVehicle->Autopilot.m_dwNextNodeIndex) {
        pVehicle->Autopilot.m_byteNextDirectionScale = 1;
    }
    else {
        pVehicle->Autopilot.m_byteNextDirectionScale = -1;
    }

    int nStartNode = pVehicle->Autopilot.m_dwMainNode;
    int nFoundNode, nFoundDetachedNode;

    if(pThePaths->m_AttachedPaths[nStartNode].bitUnkCount4To7 == 1) {
        nFoundNode = 0;
        nFoundDetachedNode = pThePaths->DetachedPointsInfo[pThePaths->m_AttachedPaths[nStartNode].wRouteInfoIndex];
    }
    else {
        nFoundNode = -1;
        float fPrevCoefficient = 999999.88f;
        CPathNode* pPathNodeStart = &pThePaths->m_AttachedPaths[nStartNode];
        CVector vecStartNode((float)(pPathNodeStart->wX) / 8.0f, (float)(pPathNodeStart->wY) / 8.0f, (float)(pPathNodeStart->wZ) / 8.0f);

        for(int j = 0; j < pThePaths->m_AttachedPaths[nStartNode].bitUnkCount4To7; j++) {
            int nConnectedNextNode = pThePaths->AttachedPointsInfo[j+ pThePaths->m_AttachedPaths[nStartNode].wRouteInfoIndex] & CPathFind::eATTACHEDPOINTSINFONODEINDEXONLY;
            if(nConnectedNextNode == pVehicle->Autopilot.m_dwNextNodeIndex) {
                continue;
            }
            
            CVector vecNextConnectedNode;
            vecNextConnectedNode.fX = (float)(pThePaths->m_AttachedPaths[nConnectedNextNode].wX) / 8.0f;
            vecNextConnectedNode.fY = (float)(pThePaths->m_AttachedPaths[nConnectedNextNode].wY) / 8.0f;
            vecNextConnectedNode.fZ = (float)(pThePaths->m_AttachedPaths[nConnectedNextNode].wZ) / 8.0f;
            float fCurrentCoefficient;
            RwV3d* vPosADDR = &pVehicle->__parent.__parent.matrix.rwMatrix.vPos;
            _asm mov eax, vPosADDR
            _asm push eax
            _asm lea eax, [vecNextConnectedNode]
            _asm push eax
            _asm lea eax, [vecStartNode]
            _asm push eax
            _asm mov eax, 414090h
            _asm call eax
            _asm fstp fCurrentCoefficient
            if(fCurrentCoefficient < fPrevCoefficient) {
                nFoundNode = j;
                fPrevCoefficient = fCurrentCoefficient;
            }
        }
        nFoundDetachedNode = pThePaths->DetachedPointsInfo[nFoundNode + pPathNodeStart->wRouteInfoIndex];
    }
    pVehicle->Autopilot.m_dwCurrentDetachedNodeIndex = nFoundDetachedNode;
    if((pThePaths->AttachedPointsInfo[nFoundNode + pThePaths->m_AttachedPaths[nStartNode].wRouteInfoIndex] & CPathFind::eATTACHEDPOINTSINFONODEINDEXONLY) >= nStartNode) {
        pVehicle->Autopilot.m_byteCurrentDirectionScale = 1;
    }
    else {
        pVehicle->Autopilot.m_byteCurrentDirectionScale = -1;
    }
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

    _nHookAttachedNodeIndex = ((uint32_t)_pHookPathNode - (uint32_t)&pThePaths->m_AttachedPaths[0])/ sizeof(CPathNode);

    _asm popad
    _asm mov ecx, _nHookAttachedNodeIndex
    _asm mov [ebx+128h], ecx
    _asm lea ecx, [ebx+128h]
    _asm mov eax, 418CA0h
    _asm call eax
    _asm mov edx, [ebx+178h]
    _asm mov _pHookPathNode, edx
    _asm pushad

    _nHookAttachedNodeIndex = ((uint32_t)_pHookPathNode - (uint32_t)&pThePaths->m_AttachedPaths[0])/ sizeof(CPathNode);

    _asm popad
    _asm mov ecx, _nHookAttachedNodeIndex
    ASMJMP(41CF97h)
}

/* 
 * This is a direct replacement hook for CCarCtrl::JoinCarWithRoadSystem.
 * This function is usually loaded when a wander system is initiated for
 * vehicles. 
 */

//41D000
void _cdecl HookJoinCarWithRoadSystem(CVehicle* pVehicle) {
    CDebug::DebugAddText("JoinCarWithRoadSystem working .....................");
	pVehicle->Autopilot.m_dwNextNodeIndex = 0;
	pVehicle->Autopilot.m_dwMainNode = 0;
	pVehicle->Autopilot.m_dwPrevMainNode = 0;
	pVehicle->Autopilot.m_dwNextDetachedNodeIndex = 0;
	pVehicle->Autopilot.m_dwPrevDetachedNodeIndex = 0;
	pVehicle->Autopilot.m_dwCurrentDetachedNodeIndex = 0;
	
	int nNodeClosestToDirection = pThePaths->FindNodeClosestToCoorsFavourDirection(pVehicle->__parent.__parent.matrix.rwMatrix.vPos.x,
																		pVehicle->__parent.__parent.matrix.rwMatrix.vPos.y,
																		pVehicle->__parent.__parent.matrix.rwMatrix.vPos.z,
																		0,
																		pVehicle->__parent.__parent.matrix.rwMatrix.vLookAt.x,
																		pVehicle->__parent.__parent.matrix.rwMatrix.vLookAt.y);
																		
	float fnodeDirClosestX = (float)(pThePaths->m_AttachedPaths[nNodeClosestToDirection].wX) / 8.0f;
	float fnodeDirClosestY = (float)(pThePaths->m_AttachedPaths[nNodeClosestToDirection].wY) / 8.0f;
	
	int nClosestNode = -1;
	float fPreviousSearchCoefficient = 999999.88f;
	for(int i = 0; i < pThePaths->m_AttachedPaths[nNodeClosestToDirection].bitUnkCount4To7; i++) {
		int nNextConnectedNode = pThePaths->AttachedPointsInfo[i + pThePaths->m_AttachedPaths[nNodeClosestToDirection].wRouteInfoIndex] & CPathFind::eATTACHEDPOINTSINFONODEINDEXONLY;
		float fnextnodeX = (float)(pThePaths->m_AttachedPaths[nNextConnectedNode].wX) / 8.0f;
		float fnextnodeY = (float)(pThePaths->m_AttachedPaths[nNextConnectedNode].wY) / 8.0f;
		
		float fCurrentLength = sqrt((fnextnodeY - fnodeDirClosestY) * (fnextnodeY - fnodeDirClosestY) + (fnextnodeX - fnodeDirClosestX) * (fnextnodeX - fnodeDirClosestX));
		if(fCurrentLength < fPreviousSearchCoefficient) {
			fPreviousSearchCoefficient = fCurrentLength;
			nClosestNode = nNextConnectedNode;
		}
	}
	
	if (nClosestNode < 0) {
		return;
	}
	
	float fLookAtX = pVehicle->__parent.__parent.matrix.rwMatrix.vLookAt.x;
	float fLookAtY = pVehicle->__parent.__parent.matrix.rwMatrix.vLookAt.y;
	
	if(fLookAtX == 0.0f && fLookAtY == 0.0f) {
		fLookAtX = 1.0f;
	}
	
	float fClosestFoundX = (float)(pThePaths->m_AttachedPaths[nClosestNode].wX) / 8.0f;
	float fClosestFoundY = (float)(pThePaths->m_AttachedPaths[nClosestNode].wY) / 8.0f;
	
	if(((fnodeDirClosestY - fClosestFoundY) * fLookAtY + (fnodeDirClosestX - fClosestFoundX) * fLookAtX) < 0.0f) {
		int nTempIndex = nClosestNode;
		nClosestNode = nNodeClosestToDirection;
		nNodeClosestToDirection = nTempIndex;
	}
	
	pVehicle->Autopilot.m_dwPrevMainNode = 0;
	pVehicle->Autopilot.m_dwMainNode = nClosestNode;
	pVehicle->Autopilot.m_dwNextNodeIndex = nNodeClosestToDirection;
	pVehicle->Autopilot.m_nRouteListStep = 0;
	HookFindLinksToGoWithTheseNodes(pVehicle);
	pVehicle->Autopilot.m_byteCurrentLanes = 0;
	pVehicle->Autopilot.m_byteNextLanes = 0;
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

    _dwIndexWithSize = _nHookDetachedNodeIndex * sizeof(CDetachedNode);

    _asm popad
    _asm mov ebp, _dwIndexWithSize
    ASMJMP(41EF7Bh)
}

//41EFEB
void _declspec(naked) HookSteerAICarFixDetachedNodeMultiplierTwo(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _dwIndexWithSize = _nHookDetachedNodeIndex * sizeof(CDetachedNode);

    _asm popad
    _asm mov esi, _dwIndexWithSize
    ASMJMP(41EFF5h)
}


//41F088
void _declspec(naked) HookSteerAICarFixDetachedPreGetLaneDistanceOne(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _pHookDetachedNode = &pThePaths->m_DetachedNodes[_nHookDetachedNodeIndex];

    _asm popad
    _asm mov ecx, _pHookDetachedNode
    ASMJMP(41F09Eh)
}

//41F0C8
void _declspec(naked) HookSteerCarAIGetDetachedNodeXYCoorsOne(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _nHookReturn = pThePaths->m_DetachedNodes[_nHookDetachedNodeIndex].wX;

    _asm popad
    _asm mov eax, _nHookReturn
    _asm mov [esp+0A0h], eax
    _asm fild dword ptr [esp+0A0h]
    _asm pushad

    _nHookReturn = pThePaths->m_DetachedNodes[_nHookDetachedNodeIndex].wY;

    _asm popad
    _asm mov eax, _nHookReturn
    ASMJMP(41F0EEh)
}

//41F130
void _declspec(naked) HookSteerCarAIGetDetachedNodeXYCoorsTwo(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _nHookReturn = pThePaths->m_DetachedNodes[_nHookDetachedNodeIndex].wX;

    _asm popad
    _asm mov eax, _nHookReturn
    _asm mov [esp+0A0h], eax
    _asm fild dword ptr [esp+0A0h]
    _asm pushad

    _nHookReturn = pThePaths->m_DetachedNodes[_nHookDetachedNodeIndex].wY;

    _asm popad
    _asm mov eax, _nHookReturn
    ASMJMP(41F156h)
}

//41F346
void _declspec(naked) HookSteerCarAIFixDetachedPreGetLaneDistanceTwo(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _pHookDetachedNode = &pThePaths->m_DetachedNodes[_nHookDetachedNodeIndex];

    _asm popad
    _asm mov ecx, _pHookDetachedNode
    ASMJMP(41F35Ch)
}

//41F386
void _declspec(naked) HookSteerCarAIGetDetachedNodeXYCoorsThree(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _nHookReturn = pThePaths->m_DetachedNodes[_nHookDetachedNodeIndex].wX;

    _asm popad
    _asm mov eax, _nHookReturn
    _asm mov [esp+0A0h], eax
    _asm fild dword ptr [esp+0A0h]
    _asm pushad

    _nHookReturn = pThePaths->m_DetachedNodes[_nHookDetachedNodeIndex].wY;

    _asm popad
    _asm mov eax, _nHookReturn
    ASMJMP(41F3ACh)
}

//41F440
void _declspec(naked) HookSteerCarAIFixDetachedNodeMultiplierThree(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _dwIndexWithSize = _nHookDetachedNodeIndex * sizeof(CDetachedNode);

    _asm popad
    _asm mov ebp, _dwIndexWithSize
    ASMJMP(41F44Bh)
}

//41F4BB
void _declspec(naked) HookSteerCarAIFixDetachedNodeMultiplierFour(void){
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _dwIndexWithSize = _nHookDetachedNodeIndex * sizeof(CDetachedNode);

    _asm popad
    _asm mov edx, _dwIndexWithSize
    ASMJMP(41F4C5h)
}



//41F525
void _declspec(naked) HookSteerCarAIGetDetachedNodeXYCoorsFour(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _nHookReturn = pThePaths->m_DetachedNodes[_nHookDetachedNodeIndex].wY;

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

    _nHookReturn = pThePaths->m_DetachedNodes[_nHookDetachedNodeIndex].wX;

    _asm popad
    _asm mov eax, _nHookReturn
    ASMJMP(41F558h)
}

//41F838
void _declspec(naked) HookSteerCarAIFixDetachedPreGetLaneDistanceThree(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _pHookDetachedNode = &pThePaths->m_DetachedNodes[_nHookDetachedNodeIndex];

    _asm popad
    _asm mov ecx, _pHookDetachedNode
    ASMJMP(41F84Eh)
}

//41F87B
void _declspec(naked) HookSteerCarAIGetDetachedNodeXYCoorsFive(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _nHookReturn = pThePaths->m_DetachedNodes[_nHookDetachedNodeIndex].wY;
    _dwIndexWithSize = _nHookDetachedNodeIndex * sizeof(CDetachedNode);
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

    _nHookReturn = pThePaths->m_DetachedNodes[_nHookDetachedNodeIndex].wX;

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

    _byteHookLocal = pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].bitUnkCount4To7;
    //_dwIndexWithSize = _nHookAttachedNodeIndex * sizeof(CPathNode);

    for(_nHooki = 0; _nHooki < _byteHookLocal && _nHookCompareIndexOne != (pThePaths->AttachedPointsInfo[pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wRouteInfoIndex + _nHooki] & CPathFind::eATTACHEDPOINTSINFONODEINDEXONLY); _nHooki++) {
    }

    _nHookReturn = pThePaths->DetachedPointsInfo[pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wRouteInfoIndex + _nHooki];

    _asm popad
    _asm mov eax, _nHookReturn
    _asm mov [esp+20h], eax
    _asm pushad

    if(pThePaths->m_DetachedNodes[_nHookReturn].wPathsIndex == _nHookCompareIndexOne) {
        _byteHookLocal = pThePaths->m_DetachedNodes[_nHookReturn].bitLeftLanes;
        _asm popad
        _asm mov dl, _byteHookLocal
        _asm movzx eax, dl
        ASMJMP(4276B7h)
    }

    _byteHookLocal = pThePaths->m_DetachedNodes[_nHookReturn].bitRightLanes;
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

    _byteHookLocal = pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].bitUnkCount4To7;
    if(_byteHookLocal == 1) {
        _asm popad
        ASMJMP(427CD6h)
    }
    _asm popad
    _asm mov _pHookVehicle, ebp
    _asm fldz
    _asm pushad

    for(_nHooki = _pHookVehicle->Autopilot.m_dwNextDetachedNodeIndex; _nHooki == _pHookVehicle->Autopilot.m_dwNextDetachedNodeIndex; _nHooki = pThePaths->DetachedPointsInfo[_dwHookLocal + pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wRouteInfoIndex]) {
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
    _pHookVehicle->Autopilot.m_dwCurrentDetachedNodeIndex = _nHooki;
    if((pThePaths->AttachedPointsInfo[_dwHookLocal + pThePaths->m_AttachedPaths[_nHookAttachedNodeIndex].wRouteInfoIndex] & CPathFind::eATTACHEDPOINTSINFONODEINDEXONLY) >= _nHookAttachedNodeIndex) {
        _pHookVehicle->Autopilot.m_byteCurrentDirectionScale = 1;
    }
    else {
        _pHookVehicle->Autopilot.m_byteCurrentDirectionScale = -1;
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

    _dwIndexWithSize = _nHookDetachedNodeIndex * sizeof(CDetachedNode);
    

    _asm popad
    _asm mov edi, _dwIndexWithSize
    ASMJMP(427FAEh)
}

//428026h
void _declspec(naked) HookGenOneRandomCarGetDetachedNodeOffsetTwo(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _dwIndexWithSize = _nHookDetachedNodeIndex * sizeof(CDetachedNode);

    _asm popad
    _asm mov esi, _dwIndexWithSize
    ASMJMP(428030h)
}

//4280B4h
void _declspec(naked) HookGenOneRandomCarGetDetachedNodeOne(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _pHookDetachedNode = &pThePaths->m_DetachedNodes[_nHookDetachedNodeIndex];

    _asm popad
    _asm mov ecx, _pHookDetachedNode
    ASMJMP(4280CAh)
}


//42810Ah
void _declspec(naked) HookGenOneRandomCarGetDetachedNodeXYOne(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _iHookNodeX = pThePaths->m_DetachedNodes[_nHookDetachedNodeIndex].wX;
    _iHookNodeY = pThePaths->m_DetachedNodes[_nHookDetachedNodeIndex].wY;

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

    _iHookNodeX = pThePaths->m_DetachedNodes[_nHookDetachedNodeIndex].wX;
    _iHookNodeY = pThePaths->m_DetachedNodes[_nHookDetachedNodeIndex].wY;

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

    _dwIndexWithSize = _nHookDetachedNodeIndex * sizeof(CDetachedNode);

    _asm popad
    _asm mov edi, _dwIndexWithSize
    ASMJMP(428240h)
}


//4282B0
void _declspec(naked) HookGenRandomCarGetDetachedNodeThree(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _dwIndexWithSize = _nHookDetachedNodeIndex * sizeof(CDetachedNode);

    _asm popad
    _asm mov edx, _dwIndexWithSize
    ASMJMP(4282BAh)
}


//42846Bh
void _declspec(naked) HookGenRandomCarGetDetachedNodeXYThree(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _iHookNodeX = pThePaths->m_DetachedNodes[_nHookDetachedNodeIndex].wX;
    _iHookNodeY = pThePaths->m_DetachedNodes[_nHookDetachedNodeIndex].wY;

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

    _iHookNodeX = pThePaths->m_DetachedNodes[_nHookDetachedNodeIndex].wX;
    _iHookNodeY = pThePaths->m_DetachedNodes[_nHookDetachedNodeIndex].wY;

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

void CPathFindHook::ApplyHook() {
    void (CPathFind::*p_mPreparePathDataForType)(uint8_t bytePathDataFor, CTempNode* pTempNode, CPathInfoForObject* pUnusedPathInfos, float fUnkRange, CPathInfoForObject* pPathInfosForObject, int nGroupNodesForObject);
    void (CPathFind::*p_mInit)(void);
    void (CPathFind::*p_mAllocatePathFindInfoMem)(void);
    void (CPathFind::*p_mPreparePathData)(void);
    void (CPathFind::*p_mDoPathSearch)(int iPathDataFor, float fOriginX, float fOriginY, float fOriginZ, int iFirstNode, float fDestX, float fDestY, float fDestZ, CPathNode **pIntermediateNodeList, short *pSteps, short sMaxSteps, void *pVehicle, float *pfDistance, float fMaxRadius, int iLastNode); //pVehicle, pfDistance and iLastNode are ununsed
    int (CPathFind::*p_mFindNodeClosestToCoors)(float fX, float fY, float fZ, unsigned char iPathDataFor, float fRangeCoefficient, bool bCheckIgnored, bool bCheckRestrictedAccess, bool bCheckUnkFlagFor2, bool bIsVehicleBoat);
    void (CPathFind::*p_mRemoveNodeFromList)(CPathNode *pRemoveNode);
    void (CPathFind::*p_mAddNodeToList)(CPathNode *pTargetNode, int iParamDisplacement);
    void (CPathFind::*p_mRemoveBadStartNode)(float fX, float fY, float fZ, CPathNode **pIntermediateNodeList, short *pSteps);
    void (CPathFind::*p_mFindNextNodeWandering)(unsigned char iPathDataFor, float fX, float fY, float fZ, CPathNode** pCurrentNode, CPathNode** pNextNode, uint8_t bytePreviousDirection, uint8_t *byteNewDirection);
    bool (CPathFind::*p_mNewGenerateCarCreationCoors)(float fX, float fY, float fDirectionVecX, float fDirectionVecY, float fRange, float fZlookUp, bool bShouldSpawnPositiveDirection, CVector *pVecPosition, int *aMainNodeIndex, int *aSubNodeIndex, float *aNodeRangeDiffCoeff, char bDontCheckIgnored);
    bool (CPathFind::*p_mGeneratePedCreationCoors)(float fX, float fY, float fRangeForRand, float fRange, float fRange1, float fRange2, CVector *pVecOutPosition, int *aStartNodeIndex, int *aFollowNodeIndex, float *frand, RwMatrix *rwMatrix);
    bool (CPathFind::*p_mTestCoorsCloseness)(float fDestinationX, float fDestinationY, float fDestinationZ, uint8_t uiPathDataFor, float fOriginX, float fOriginY, float fOriginZ);
    float (CPathFind::*p_mCalcRoadDensity)(float fX, float fY);
    int (CPathFind::*p_mFindNodeClosestToCoorsFavourDirection)(float fX, float fY, float fZ, uint8_t uiPathDataFor, float fLookAtX, float fLookAtY);
    bool (CPathFind::*p_mTestCrossesRoad)(CPathNode* pStartNode, CPathNode* pConnectedNode);
    bool (CPathFind::*p_mTestForPedTrafficLight)(CPathNode* pStartNode, CPathNode* pConnectedNode);

    float (CDetachedNode::*p_mCalculateLaneDistance)();
    // CDetachedNode::CalculateLaneDistance - REVISION NEEDED

    p_mInit = &CPathFind::Init;
    p_mAllocatePathFindInfoMem = &CPathFind::AllocatePathFindInfoMem;
    p_mPreparePathData = &CPathFind::PreparePathData;
    p_mPreparePathDataForType = &CPathFind::PreparePathDataForType;

    p_mDoPathSearch = &CPathFind::DoPathSearch;
    p_mFindNodeClosestToCoors = &CPathFind::FindNodeClosestToCoors;
    p_mRemoveNodeFromList = &CPathFind::RemoveNodeFromList;
    p_mAddNodeToList = &CPathFind::AddNodeToList;
    p_mRemoveBadStartNode = &CPathFind::RemoveBadStartNode;
    p_mFindNextNodeWandering = &CPathFind::FindNextNodeWandering;
    p_mNewGenerateCarCreationCoors = &CPathFind::NewGenerateCarCreationCoors;
    p_mGeneratePedCreationCoors = &CPathFind::GeneratePedCreationCoors;
    p_mTestCoorsCloseness = &CPathFind::TestCoorsCloseness;
    p_mCalcRoadDensity = &CPathFind::CalcRoadDensity;
    p_mFindNodeClosestToCoorsFavourDirection = &CPathFind::FindNodeClosestToCoorsFavourDirection;
    p_mTestCrossesRoad = &CPathFind::TestCrossesRoad;
    p_mTestForPedTrafficLight = &CPathFind::TestForPedTrafficLight;

    p_mCalculateLaneDistance = &CDetachedNode::CalculateLaneDistance;
    // Disable Unused CPathFind Treadables in CFileLoader::LoadObjectInstance
    CMemory::NoOperation(0x48AE30, 44);

    // Hooks in CGame::Init
    CMemory::InstallCallHook(0x4A4C0C, (void*&)p_mInit, ASM_CALL);
    CMemory::NoOperation(0x4A4C16, 5); // Remove One Unused Parameter

    CMemory::InstallCallHook(0x4A4C1B, (void*&)p_mAllocatePathFindInfoMem, ASM_CALL);    
    CMemory::InstallCallHook(0x4A4CE7, (void*&)p_mPreparePathData, ASM_CALL);
    // Install PreparePathDataHook
    CMemory::InstallCallHook(0x43BF3C, (void*&)p_mPreparePathDataForType, ASM_CALL);
    CMemory::InstallCallHook(0x43BF74, (void*&)p_mPreparePathDataForType, ASM_CALL);

    CMemory::InstallCallHook(0x439070, (void*&)p_mDoPathSearch, ASM_JMP);
    CMemory::InstallCallHook(0x437150, (void*&)p_mFindNodeClosestToCoors, ASM_JMP);
    CMemory::InstallCallHook(0x437330, (void*&)p_mAddNodeToList, ASM_JMP);
    CMemory::InstallCallHook(0x4375C0, (void*&)p_mRemoveNodeFromList, ASM_JMP);
    CMemory::InstallCallHook(0x438F90, (void*&)p_mRemoveBadStartNode , ASM_JMP);
    CMemory::InstallCallHook(0x4386D0, (void*&)p_mFindNextNodeWandering, ASM_JMP);
    CMemory::InstallCallHook(0x4382B0, (void*&)p_mNewGenerateCarCreationCoors, ASM_JMP);
    CMemory::InstallCallHook(0x437B10, (void*&)p_mGeneratePedCreationCoors, ASM_JMP);
    CMemory::InstallCallHook(0x437A40, (void*&)p_mTestCoorsCloseness, ASM_JMP);
    CMemory::InstallCallHook(0x4377F0, (void*&)p_mCalcRoadDensity, ASM_JMP);
    CMemory::InstallCallHook(0x436E40, (void*&)p_mFindNodeClosestToCoorsFavourDirection, ASM_JMP);
    CMemory::InstallCallHook(0x4354E0, (void*&)p_mTestCrossesRoad, ASM_JMP);
    CMemory::InstallCallHook(0x4356B0, (void*&)p_mTestForPedTrafficLight, ASM_JMP);

    CMemory::InstallCallHook(0x434EB0, (void*&)p_mCalculateLaneDistance, ASM_JMP);
    CMemory::InstallCallHook(0x435140, &CPedPath::CalculateBestRandomCoors, ASM_JMP);
    CMemory::InstallCallHook(0x4351C0, &CPedPath::CalculateRandomCoordinates, ASM_JMP);

    // hooks inside CAutopilot::ModifySpeed
    //CMemory::InstallCallHook(0x418D48, HookModSpeedGetDetachedNormalXOne, ASM_JMP);
    //CMemory::InstallCallHook(0x418D68, HookModSpeedGetDetachedYCoorOne, ASM_JMP);
    //CMemory::InstallCallHook(0x418DAA, HookModSpeedGetDetachedNormalXTwo, ASM_JMP);
    //CMemory::InstallCallHook(0x418DCB, HookModSpeedGetDetachedXCoorOne, ASM_JMP);
    //CMemory::InstallCallHook(0x418DEF, HookModSpeedGetDetachedNormalYOne, ASM_JMP);
    //CMemory::InstallCallHook(0x418E21, HookModSpeedGetDetachedYCoorTwo, ASM_JMP);
    //CMemory::InstallCallHook(0x418E48, HookModSpeedGetDetachedXCoorTwo, ASM_JMP);
    //CMemory::InstallCallHook(0x418E7C, HookModSpeedGetDetachedNormalYTwo, ASM_JMP);
    //CMemory::InstallCallHook(0x418EB8, HookModSpeedGetDetachedNormalYThree, ASM_JMP);
    //CMemory::InstallCallHook(0x418EE9, HookModSpeedGetDetachedNormalXThree, ASM_JMP);
    //CMemory::InstallCallHook(0x418F15, HookModSpeedGetDetachedNormalYFour, ASM_JMP);
    //CMemory::InstallCallHook(0x418F45, HookModSpeedGetDetachedNormalXFour, ASM_JMP);
    void (CAutoPilot::*pCAutoPilot_ModifySpeed)(float fModSpeed);
    pCAutoPilot_ModifySpeed = &CAutoPilot::ModifySpeed;
    CMemory::InstallCallHook(0x418CD0, (void*&)pCAutoPilot_ModifySpeed, ASM_JMP);

    //hooks inside CCarCtrl::GenerateOneEmergencyServicesCar
    CMemory::InstallCallHook(0x41C4F1, HookGenEmerCarCheckVehicleType, ASM_JMP);
    CMemory::InstallCallHook(0x41C6A5, HookGenEmerCarGetAttachedZCoorsOne, ASM_JMP);
    CMemory::InstallPatch<CPathFind*>(0x41C4BD, pThePaths);

    //whole function replacement hook for CCarCtrl::FindLinksToGoWithTheseNodes
    CMemory::InstallCallHook(0x41CC20, HookFindLinksToGoWithTheseNodes, ASM_JMP);

    //hooks inside CCarCtrl::JoinCarWithRoadSystemGotoCoors
    CMemory::InstallPatch<CPathFind*>(0x41CECF, pThePaths);
    CMemory::InstallPatch<CPathFind*>(0x41CF21, pThePaths);
    CMemory::InstallCallHook(0x41CF52, HookJoinCarWithRoadFixPathPointerSubtract, ASM_JMP);

    //whole function replacement hook for CCarCtrl::JoinCarWithRoadSystems
    CMemory::InstallCallHook(0x41D000, HookJoinCarWithRoadSystem, ASM_JMP);

    //hooks inside CCarCtrl::SteerAICarWithPhysicsFollowPath
    CMemory::InstallCallHook(0x41EF70, HookSteerAICarFixDetachedNodeMultiplierOne, ASM_JMP);
    CMemory::InstallPatch<signed char*>(0x41EF7E, &pThePaths->m_DetachedNodes[0].NormalVecX);
    CMemory::InstallPatch<signed char*>(0x41EFAA, &pThePaths->m_DetachedNodes[0].NormalVecY);
    CMemory::InstallCallHook(0x41EFEB, HookSteerAICarFixDetachedNodeMultiplierTwo, ASM_JMP);
    CMemory::InstallPatch<signed char*>(0x41EFF8, &pThePaths->m_DetachedNodes[0].NormalVecX);
    CMemory::InstallPatch<CPathFind*>(0x41F015, pThePaths);
    CMemory::InstallPatch<signed char*>(0x41F02B, &pThePaths->m_DetachedNodes[0].NormalVecY);
    CMemory::InstallPatch<uint32_t>(0x41F045, OFFSETOF(CPathFind, m_DetachedNodes[0]));
    CMemory::InstallCallHook(0x41F088, HookSteerAICarFixDetachedPreGetLaneDistanceOne, ASM_JMP);
    CMemory::InstallCallHook(0x41F0C8, HookSteerCarAIGetDetachedNodeXYCoorsOne, ASM_JMP);
    CMemory::InstallCallHook(0x41F130, HookSteerCarAIGetDetachedNodeXYCoorsTwo, ASM_JMP);
    CMemory::InstallCallHook(0x41F346, HookSteerCarAIFixDetachedPreGetLaneDistanceTwo, ASM_JMP);
    CMemory::InstallCallHook(0x41F386, HookSteerCarAIGetDetachedNodeXYCoorsThree, ASM_JMP);
    CMemory::InstallCallHook(0x41F440, HookSteerCarAIFixDetachedNodeMultiplierThree, ASM_JMP);
    CMemory::InstallPatch<signed char*>(0x41F44E, &pThePaths->m_DetachedNodes[0].NormalVecX);
    CMemory::InstallPatch<signed char*>(0x41F47A, &pThePaths->m_DetachedNodes[0].NormalVecY);
    CMemory::InstallCallHook(0x41F4BB, HookSteerCarAIFixDetachedNodeMultiplierFour, ASM_JMP);
    CMemory::InstallPatch<signed char*>(0x41F4C8, &pThePaths->m_DetachedNodes[0].NormalVecX);
    CMemory::InstallPatch<signed char*>(0x41F4F4, &pThePaths->m_DetachedNodes[0].NormalVecY);
    CMemory::InstallCallHook(0x41F525, HookSteerCarAIGetDetachedNodeXYCoorsFour, ASM_JMP);
    CMemory::InstallCallHook(0x41F838, HookSteerCarAIFixDetachedPreGetLaneDistanceThree, ASM_JMP);
    CMemory::InstallCallHook(0x41F87B, HookSteerCarAIGetDetachedNodeXYCoorsFive, ASM_JMP);

    //hook for CCarCtrl::PickNextNodeToFollowPath
    CMemory::InstallCallHook(0x420D50, CCarCtrl::PickNextNodeToFollowPath, ASM_JMP);
    CMemory::InstallCallHook(0x4213A0, CCarCtrl::PickNextNodeToChaseCar, ASM_JMP);

    //june 28, 2012
    CMemory::InstallCallHook(0x421F70, CCarCtrl::PickNextNodeRandomly, ASM_JMP);
    CMemory::InstallCallHook(0x421DC0, CCarCtrl::FindPathDirection, ASM_JMP);

    //hook CCarCtrl::PickNextNodeAccordingStrategy
    CMemory::InstallCallHook(0x422A10, CCarCtrl::PickNextNodeAccordingStrategy, ASM_JMP);

    //hook CCarCtrl::UpdateCarOnRails
    CMemory::InstallCallHook(0x425BF0, CCarCtrl::UpdateCarOnRails, ASM_JMP);

    //hooks in CCarCtrl::GenerateOneRandomCar
    CMemory::InstallPatch<CPathFind*>(0x4272F0, pThePaths);
    CMemory::InstallCallHook(0x42733C, HookGenOneRandomCarCompareSpawnRate, ASM_JMP);
    CMemory::InstallCallHook(0x427380, HookGenOneRandomCarCheckBoat, ASM_JMP);
    CMemory::InstallCallHook(0x42752A, HookGenOneRandomCarCheckVehClass, ASM_JMP);
    CMemory::InstallPatch<CPathFind*>(0x4275DF, pThePaths);
    CMemory::InstallCallHook(0x427623, HookGenOneRandomCarGetProperLaneOne, ASM_JMP); //Hardest function of all times
    CMemory::InstallCallHook(0x427B07, HookGenOneRandomCarGetXYsOne, ASM_JMP);
    CMemory::InstallCallHook(0x427CC6, HookGenRandomCarPathsGeneric, ASM_JMP);

    CMemory::InstallCallHook(0x427DB5, HookGenOneRandomCarGetXYZsTwo, ASM_JMP);
    CMemory::InstallPatch<CPathFind*>(0x427F5D, pThePaths);
    CMemory::InstallCallHook(0x427FA4, HookGenOneRandomCarGetDetachedNodeOffsetOne, ASM_JMP);
    CMemory::InstallPatch<signed char*>(0x427FB1, &(pThePaths->m_DetachedNodes[0].NormalVecX));
    CMemory::InstallPatch<unsigned int>(0x427FC7, OFFSETOF(CPathFind, m_DetachedNodes[0]));
    CMemory::InstallPatch<signed char*>(0x427FE5, &(pThePaths->m_DetachedNodes[0].NormalVecY));
    CMemory::InstallCallHook(0x428026, HookGenOneRandomCarGetDetachedNodeOffsetTwo, ASM_JMP);
    CMemory::InstallPatch<signed char*>(0x428033, &(pThePaths->m_DetachedNodes[0].NormalVecX));
    CMemory::InstallPatch<signed char*>(0x42805F, &(pThePaths->m_DetachedNodes[0].NormalVecY));
    CMemory::InstallCallHook(0x4280B4, HookGenOneRandomCarGetDetachedNodeOne, ASM_JMP);
    CMemory::InstallCallHook(0x42810A, HookGenOneRandomCarGetDetachedNodeXYOne, ASM_JMP);
    CMemory::InstallCallHook(0x428198, HookGenOneRandomCarGetDetachedNodeXYTwo, ASM_JMP);
    CMemory::InstallCallHook(0x428236, HookGenRandomCarGetDetachedNodeTwo, ASM_JMP);
    CMemory::InstallPatch<signed char*>(0x428243, &(pThePaths->m_DetachedNodes[0].NormalVecY));
    CMemory::InstallPatch<signed char*>(0x428275, &(pThePaths->m_DetachedNodes[0].NormalVecX));
    CMemory::InstallCallHook(0x4282B0, HookGenRandomCarGetDetachedNodeThree, ASM_JMP);
    CMemory::InstallPatch<signed char*>(0x4282BD, &(pThePaths->m_DetachedNodes[0].NormalVecY));
    CMemory::InstallPatch<signed char*>(0x4282EF, &(pThePaths->m_DetachedNodes[0].NormalVecX));
    CMemory::InstallCallHook(0x42846B, HookGenRandomCarGetDetachedNodeXYThree, ASM_JMP);
    CMemory::InstallCallHook(0x4284E2, HookGenRandomCarGetDetachedNodeXYFour, ASM_JMP);
    CMemory::InstallCallHook(0x428585, HookGenOneRandomCarGetXYZsThree, ASM_JMP);
    CMemory::InstallCallHook(0x4286C0, HookGenRandomCarGetNodeZsOnly, ASM_JMP);

    //patches in CRestart::FindClosestPoliceRestartPoint
    CMemory::InstallPatch<CPathFind*>(0x442BB7, pThePaths);
    CMemory::InstallCallHook(0x442BD8, HookRestartForPoliceGetXYZ, ASM_JMP);

    //patches in CRestart::FindClosestHospitalRestartPoint
    CMemory::InstallPatch<CPathFind*>(0x442E79, pThePaths);
    CMemory::InstallCallHook(0x442E9C, HookRestartForHospitalGetXYZ, ASM_JMP);

    //patches in CFileLoader::LoadInstance
    CMemory::InstallPatch<CPathFind*>(0x48AE89, pThePaths);

    //patches in CGame::Initialize
    CMemory::InstallPatch<CPathFind*>(0x4A4C08, pThePaths);
    CMemory::InstallPatch<CPathFind*>(0x4A4C12, pThePaths);
    CMemory::InstallPatch<CPathFind*>(0x4A4CE0, pThePaths);

    //hooks in CarCheatSpawner
    CMemory::InstallPatch<CPathFind*>(0x4AE993, pThePaths);
    CMemory::InstallCallHook(0x4AE9DD, HookCarCheatSpawner, ASM_JMP);
    
    //patches in CPlayerInfo::Process
    CMemory::InstallPatch<CPathFind*> (0x4BD66D, pThePaths);
    CMemory::InstallPatch<CPathFind*> (0x4BD687, pThePaths);
    CMemory::InstallPatch<CPathFind*> (0x4BE6A3, pThePaths);

    //hooks in CWorld::RemoveFallenCars
    CMemory::InstallPatch<CPathFind*>(0x4D4945, pThePaths);
    CMemory::InstallCallHook(0x4D4966, HookRemoveFallenCarsGetXYZ, ASM_JMP);

    //hooks in CWorld::RemoveFallenPeds
    CMemory::InstallPatch<CPathFind*>(0x4D4AD1, pThePaths);
    CMemory::InstallCallHook(0x4D4AF2, HookRemoveFallenPedsGetXYZ, ASM_JMP);

    //hooks in CPed::FollowPath
    CMemory::InstallCallHook(0x4F7800, HookPedFollowPathGetXY, ASM_JMP);

    //hook in sub_4F99F0
    CMemory::InstallPatch<CPathFind*>(0x4F9BB5, pThePaths);
    CMemory::InstallCallHook(0x4F9D47, HookSub4F99F0GetXYZ, ASM_JMP);

    //This hook is inside CPed::SeekFollowingPath
    CMemory::InstallCallHook(0x4FA201, HookSeekFollowingPathGetXYZ, ASM_JMP);

    //These hook are inside CPed:WanderPath
    CMemory::InstallPatch<CPathFind*>(0x4FA8EA , pThePaths);
    CMemory::InstallCallHook(0x4FA946, HookWanderPathGetXYZOne, ASM_JMP);
    CMemory::InstallPatch<CPathFind*>(0x4FAB49, pThePaths);
    CMemory::InstallCallHook(0x4FABA6, HookWanderPathGetXYZTwo, ASM_JMP);
    CMemory::InstallPatch<CPathFind*>(0x4FAC36, pThePaths);
    CMemory::InstallPatch<CPathFind*>(0x4FAC5D, pThePaths);
    
    //These hooks are inside CPed::SetWanderPath
    CMemory::InstallPatch<CPathFind*>(0x4FAEEA, pThePaths);
    CMemory::InstallPatch<CPathFind*>(0x4FB064, pThePaths);
    
    //These hooks are inside CPed::Flee
    CMemory::InstallPatch<CPathFind*>(0x4FB42B, pThePaths);

    //These hooks are inside CPed::ProcessControl
    CMemory::InstallPatch<CPathFind*>(0x506F47, pThePaths);
    CMemory::InstallCallHook(0x507184, HookPedProcessControlGetXYZOne, ASM_JMP);
    CMemory::InstallCallHook(0x5072D5, HookPedProcessControlGetPathNodeOne, ASM_JMP);
    CMemory::InstallCallHook(0x507347, HookPedProcessControlGetXYZTwo, ASM_JMP);
    CMemory::InstallCallHook(0x5073D0, HookPedProcessControlGetXYZThree, ASM_JMP);
    CMemory::InstallCallHook(0x507460, HookPedProcessControlGetXYZFour, ASM_JMP);
    CMemory::InstallCallHook(0x5074E4, HookPedProcessControlGetXYZFive, ASM_JMP);

    
    //This hook is in CPed::WillChat
    CMemory::InstallPatch<CPathFind*>(0x50AC91, pThePaths);
    
    //These hooks are inside CPed::PositionPedOutOfCollision
    CMemory::InstallPatch<CPathFind*>(0x51228C, pThePaths);
    CMemory::InstallCallHook(0x5122BB, HookPedOutCollisionGetXYZ, ASM_JMP);

    // hooks for CPed::FindBestCoordsFromNodes
    bool (CPed::*pFindBestCoordsFromNodes)(float fUnusedX, float fUnusedY, float fUnusedZ, CVector* vecBestCoords);
    pFindBestCoordsFromNodes = &CPed::FindBestCoordsFromNodes;
    CMemory::InstallCallHook(0x513DF0, (void*&)pFindBestCoordsFromNodes, ASM_JMP);

    // These hooks are inside CPed::ProcessObjective
    CMemory::InstallPatch<CPathFind*>(0x51F6F8, pThePaths);
    CMemory::InstallCallHook(0x51F726, HookProcessObjectiveGetXYZOne, ASM_JMP);
    CMemory::InstallPatch<CPathFind*>(0x51F859, pThePaths);

    void (CPathNode::*pGetNodeCoors)(CVector* vecNodePosition);
    pGetNodeCoors = &CPathNode::GetNodeCoors;
    CMemory::InstallCallHook(0x520E90, (void*&)pGetNodeCoors, ASM_JMP);

    //These hooks are inside CPopulation::AddToPopulation
    CMemory::InstallPatch<CPathFind*>(0x53C2C0, pThePaths);
    CMemory::InstallCallHook(0x53C31A, HookAddToPopulationCompareSpawnRate, ASM_JMP);
    CMemory::InstallCallHook(0x53C37B, HookAddToPopulationIndexArithmetic, ASM_JMP);

    //TEMPORARY HOOK DISABLE FOR PED PATH TESTING
    CMemory::InstallPatch<unsigned char>(0x444280, 0xC3);
    CMemory::InstallPatch<unsigned char>(0x463F90, 0xC3);
    CMemory::InstallPatch<unsigned char>(0x465C10, 0x30); //CTrafficLights::ShouldCarStopForLights
    CMemory::InstallPatch<byte>(0x465C11, 0xC0);
    CMemory::InstallPatch<byte>(0x465C12, 0xC3);

    CMemory::InstallPatch<unsigned char>(0x4661C0, 0xC3);
    CMemory::InstallPatch<unsigned char>(0x5881F0, 0xC3);
}

void CPathFindHook::RemoveHook(){
}

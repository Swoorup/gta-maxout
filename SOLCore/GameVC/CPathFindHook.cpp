#include "../StdInc.h"

template<> CPathFindHook * CSingleton<CPathFindHook>::m_pSingleton = NULL;

CPathFind* pThePaths = NULL;

CPathFindHook::CPathFindHook() {
    //pThePaths = new CPathFind();   
    pThePaths = (CPathFind*)0x9B6E5C;
}

CPathFindHook::~CPathFindHook() {
    RemoveHook();
    //delete pThePaths;
    //pThePaths = NULL;
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
float _fHookFloatOne, _fHookFloatTwo;
int _nHookReturn;
#define ASMJMP(x) {_asm push x _asm retn} 

//-----------------------------------------------------------
// These are hooks inside CAutopilot::ModifySpeed. They make
// sure the coordinates values are calculated properly with 
// the new path system
//-----------------------------------------------------------

//418D48
void _declspec(naked) HookModSpeedGetDetachedNormalXOne(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad
    
    _nHookReturn = pThePaths->m_DetachedNodes[_nHookDetachedNodeIndex].NormalVecX;
    _dwIndexWithSize = _nHookDetachedNodeIndex * sizeof(CDetachedNode);

    _asm popad
    _asm mov ecx, _dwIndexWithSize
    _asm mov eax, _nHookReturn
    ASMJMP(418D59h)
}

//418D68
void _declspec(naked) HookModSpeedGetDetachedYCoorOne(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _fHookFloatOne = 0.0099999998f;
    _nHookReturn = pThePaths->m_DetachedNodes[_nHookDetachedNodeIndex].wY;
    _dwIndexWithSize = _nHookDetachedNodeIndex * sizeof(CDetachedNode);

    _asm popad
    _asm fmul _fHookFloatOne
    _asm mov eax, _nHookReturn
    _asm mov ebp, _dwIndexWithSize
    ASMJMP(418D80h)
}

//418DAA
void _declspec(naked) HookModSpeedGetDetachedNormalXTwo(void) {
    _asm mov _dwIndexWithSize, ebp
    _asm pushad
    
    _nHookReturn = pThePaths->m_DetachedNodes[_dwIndexWithSize / sizeof(CDetachedNode)].NormalVecX;

    _asm popad
    _asm mov eax, _nHookReturn
    ASMJMP(418DB1h)
}

//418DCB
void _declspec(naked) HookModSpeedGetDetachedXCoorOne(void) {
    _asm mov _dwIndexWithSize, ebp
    _asm pushad

    _nHookReturn = pThePaths->m_DetachedNodes[_dwIndexWithSize/sizeof(CDetachedNode)].wX;

    _asm popad
    _asm mov eax, _nHookReturn
    ASMJMP(418DD2h)
}

//418DEF
void _declspec(naked) HookModSpeedGetDetachedNormalYOne(void) {
    _asm mov _dwIndexWithSize, ebp
    _asm pushad

    _nHookReturn = pThePaths->m_DetachedNodes[_dwIndexWithSize/sizeof(CDetachedNode)].NormalVecY;

    _asm popad
    _asm mov eax, _nHookReturn
    ASMJMP(418DF6h)
}

//418E21
void _declspec(naked) HookModSpeedGetDetachedYCoorTwo(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _nHookReturn = pThePaths->m_DetachedNodes[_nHookDetachedNodeIndex].wY;
    _dwIndexWithSize = _nHookDetachedNodeIndex * sizeof(CDetachedNode);

    _asm popad
    _asm mov eax, _nHookReturn
    _asm mov edx, _dwIndexWithSize
    ASMJMP(418E32h)
}

//418E48
void _declspec(naked) HookModSpeedGetDetachedXCoorTwo(void) {
    _asm mov _dwIndexWithSize, edx
    _asm pushad

    _nHookReturn = pThePaths->m_DetachedNodes[_dwIndexWithSize/sizeof(CDetachedNode)].wX;

    _asm popad
    _asm mov eax, _nHookReturn
    ASMJMP(418E4Fh)
}

//418E7C
void _declspec(naked) HookModSpeedGetDetachedNormalYTwo(void) {
    _asm mov _dwIndexWithSize, ecx
    _asm pushad

    _nHookReturn = pThePaths->m_DetachedNodes[_dwIndexWithSize/sizeof(CDetachedNode)].NormalVecY;

    _asm popad
    _asm mov eax, _nHookReturn
    ASMJMP(418E83h)
}

//418EB8
void _declspec(naked) HookModSpeedGetDetachedNormalYThree(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _nHookReturn = pThePaths->m_DetachedNodes[_nHookDetachedNodeIndex].NormalVecY;
    _dwIndexWithSize = _nHookDetachedNodeIndex * sizeof(CDetachedNode);

    _asm popad
    _asm mov eax, _nHookReturn
    _asm mov ebp, _dwIndexWithSize
    ASMJMP(418ECAh)
}

//418EE9
void _declspec(naked) HookModSpeedGetDetachedNormalXThree(void) {
    _asm mov _dwIndexWithSize, ebp
    _asm pushad

    _nHookReturn = pThePaths->m_DetachedNodes[_dwIndexWithSize/sizeof(CDetachedNode)].NormalVecX;

    _asm popad
    _asm mov eax, _nHookReturn
    ASMJMP(418EF0h)
}

//418F15
void _declspec(naked) HookModSpeedGetDetachedNormalYFour(void) {
    _asm mov _nHookDetachedNodeIndex, eax
    _asm pushad

    _nHookReturn = pThePaths->m_DetachedNodes[_nHookDetachedNodeIndex].NormalVecY;
    _dwIndexWithSize = _nHookDetachedNodeIndex * sizeof(CDetachedNode);

    _asm popad
    _asm mov eax, _nHookReturn
    _asm mov edx, _dwIndexWithSize
    ASMJMP(418F26h)
}

//418F45
void _declspec(naked) HookModSpeedGetDetachedNormalXFour(void) {
    _asm mov _dwIndexWithSize, edx
    _asm pushad

    _nHookReturn = pThePaths->m_DetachedNodes[_dwIndexWithSize/sizeof(CDetachedNode)].NormalVecX;

    _asm popad
    _asm mov eax, _nHookReturn
    ASMJMP(418F4Ch)
}

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
}

void CPathFindHook::RemoveHook(){
}

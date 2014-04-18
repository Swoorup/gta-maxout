#include "SJLIB/stdinc.h"

// 5881F0
void CAutomobile::PlayCarHorn(void)
{
	_asm 
	{
		mov ecx, this
		mov eax, 0x588230
		call eax
	}
	return;
}

//588A60
void CAutomobile::BlowUpCar(CEntity* ent)
{
	_asm 
	{
		mov ecx, this
		push ent
		mov eax, 588A60h
		call eax
	}
	return;

}

//5886A0h
void CAutomobile::BurstTyre(unsigned char uUnk, bool bUnk)
{
	_asm
	{
		mov ecx, this
		movsx eax, bUnk
		push eax
		movsx eax, uUnk
		push eax
		mov eax, 5886A0h
		call eax
	}
}

void CAutomobile::PlayHornIfNecessary()
{
	if ( ((unsigned __int8)veh.stAutopilot.m_flags >> 1) & 1 ||  veh.stAutopilot.m_flags & 1) 
	{
	    if (!HasCarStoppedBecauseOfLight())
		{
			PlayCarHorn();
		}
	}
}

bool CAutomobile::HasCarStoppedBecauseOfLight(void)
{
	if(veh.bfTypeStatus >> 3 != 2 && veh.bfTypeStatus >> 3 != 3)
		return false;

	int vehCurrentNode = veh.stAutopilot.m_dwCurrentNode;
	int vehNextNode = veh.stAutopilot.m_dwNextNode;
	int vehPrevNode = veh.stAutopilot.m_dwPrevNode;
	
	if(!vehCurrentNode)
		return false;
	
	
	if(vehNextNode)
	{
		int nConnectedSets = 0;
		while(nConnectedSets < pThePaths->m_AttachedPaths[vehCurrentNode].bitnumberOfNodesConnected && vehNextNode != (pThePaths->m_infoConnectedNodes[nConnectedSets + pThePaths->m_AttachedPaths[vehCurrentNode].wRouteInfoIndex] & CPathFind::em_infoConnectedNodesNODEINDEXONLY))
			nConnectedSets++;
		if (nConnectedSets < pThePaths->m_AttachedPaths[vehCurrentNode].bitnumberOfNodesConnected && pThePaths->m_CarPathLinks[pThePaths->m_InfoCarPathLinks[nConnectedSets + pThePaths->m_AttachedPaths[vehCurrentNode].wRouteInfoIndex]].bitTrafficLight)
			return true;
		
	}

	if(vehPrevNode)
	{
		int nConnectedSets = 0;
		while(nConnectedSets < pThePaths->m_AttachedPaths[vehCurrentNode].bitnumberOfNodesConnected && vehPrevNode != (pThePaths->m_infoConnectedNodes[nConnectedSets + pThePaths->m_AttachedPaths[vehCurrentNode].wRouteInfoIndex] & CPathFind::em_infoConnectedNodesNODEINDEXONLY))
			nConnectedSets++;
		if (nConnectedSets < pThePaths->m_AttachedPaths[vehCurrentNode].bitnumberOfNodesConnected && pThePaths->m_CarPathLinks[pThePaths->m_InfoCarPathLinks[nConnectedSets + pThePaths->m_AttachedPaths[vehCurrentNode].wRouteInfoIndex]].bitTrafficLight)
			return true;
	}

	return false;
}


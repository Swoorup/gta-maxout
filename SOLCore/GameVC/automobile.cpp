#include "../StdInc.h"

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
		mov eax, 5886A0h
		push bUnk
		push uUnk
		call eax
	}
}

void CAutomobile::PlayHornIfNecessary()
{
	if ( ((unsigned __int8)_.veh.stAutopilot.m_flags >> 1) & 1 ||  _.veh.stAutopilot.m_flags & 1) 
	{
	    if (!HasCarStoppedBecauseOfLight())
		{
			PlayCarHorn();
		}
	}
}

bool CAutomobile::HasCarStoppedBecauseOfLight(void)
{
	if(_.veh.phys.ent.bfTypeStatus >> 3 != 2 && _.veh.phys.ent.bfTypeStatus >> 3 != 3)
		return false;

	int vehCurrentNode = _.veh.stAutopilot.m_dwCurrentNode;
	int vehNextNode = _.veh.stAutopilot.m_dwNextNode;
	int vehPrevNode = _.veh.stAutopilot.m_dwPrevNode;
	
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


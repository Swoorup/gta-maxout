#include "SJLIB/stdinc.h"

bool& CTrafficLights::bGreenLightsCheatPx = *(bool*)0xA10ADC;

uint8_t CTrafficLights::LightsForCars1(void)
{
	if(CWeather::WindPx > 1.1 || bGreenLightsCheatPx == true)
		return TL_GREENLIGHT;

	int nTime = (CTimer::get_m_snTimeInMilliseconds() >> 1) & 0x3FFF;
	if (nTime <= 4999)
		return TL_GREENLIGHT;
	else
		if (nTime > 5999)
			return TL_REDLIGHT;
		else
			return TL_YELLOWLIGHT;
}


uint8_t CTrafficLights::LightsForCars2(void)
{
if(CWeather::WindPx > 1.1f || bGreenLightsCheatPx == true)
	return TL_GREENLIGHT;

	int nTime = (CTimer::get_m_snTimeInMilliseconds() >> 1) & 0x3FFF;
	if (nTime > 5999)
		if (nTime <= 10999)
			return TL_GREENLIGHT;
		else 
			if (nTime > 11999)
				return TL_REDLIGHT;
			else
				return TL_YELLOWLIGHT;
	else
		return TL_REDLIGHT;
}

int16_t& MI_TRAFFICLIGHT1 = *(int16_t*)0x68E810;
int16_t& MI_MTRAFFIC4 = *(int16_t*)0x68E814;
int16_t& MI_MTRAFFIC1 = *(int16_t*)0x68E818;
int16_t& MI_MTRAFFIC2 = *(int16_t*)0x68E81C;

struct CPathNodeIndex
{
	
	int n;

	CPathNodeIndex(int32_t nIndex)
	{
		n = nIndex;
	}

	int NumOfAttachedNodes()
	{
		return pThePaths->m_AttachedPaths[n].bitnumberOfNodesConnected;
	}

	int GetInfoArrayIndex(int nOffset)
	{
		return (pThePaths->m_AttachedPaths[n].wRouteInfoIndex + nOffset);
	}

	bool operator < (CPathNodeIndex nIndex)
	{
		return n < nIndex.n ? true:false;
	}

	bool operator > (CPathNodeIndex nIndex)
	{
		return n > nIndex.n ? true:false;
	}
};

CPathNodeIndex GetAttachedNodeFromArrayIndex(int nIndex)
{
	return (CPathNodeIndex)(pThePaths->m_infoConnectedNodes[nIndex] & CPathFind::em_infoConnectedNodesNODEINDEXONLY);
}

struct CCarPathInfoLinkIndex
{
	
	int n;

	CCarPathInfoLinkIndex(int32_t nIndex)
	{
		n = nIndex;
	}


	uint8_t TrafficLightState(void)
	{
		return pThePaths->m_CarPathLinks[n].bitTrafficLight;
	}

	bool IsLightEnabledInConnectedNode(void)
	{
		return pThePaths->m_CarPathLinks[n].bitTrafficUnknown;
	}

	int IndexToAttachedNode(void)
	{
		return pThePaths->m_CarPathLinks[n].nIndexToAttachedNode;
	}

	bool operator < (CCarPathInfoLinkIndex nIndex)
	{
		return n < nIndex.n ? true:false;
	}

	bool operator > (CCarPathInfoLinkIndex nIndex)
	{
		return n > nIndex.n ? true:false;
	}
};

CCarPathInfoLinkIndex GetLinkNodeFromArrayIndex(int nIndex)
{
	return (CCarPathInfoLinkIndex)(pThePaths->m_InfoCarPathLinks[nIndex]);
}


bool CTrafficLights::ShouldCarStopForLightN(CVehicle* pVeh, bool bCheckSignal)
{
	CCarPathInfoLinkIndex nLinkNext = pVeh->stAutopilot.m_dwNextCarLinkNode;
	CCarPathInfoLinkIndex nLinkCurrent = pVeh->stAutopilot.m_dwCurrentCarLinkNode;
	CCarPathInfoLinkIndex nLinkPrev = pVeh->stAutopilot.m_dwPrevCarLinkNode;

	uint8_t lightStateAtNextLink = nLinkNext.TrafficLightState();
	uint8_t lightStateAtCurrentLink = nLinkCurrent.TrafficLightState();
	uint8_t lightStateAtPrevLink = nLinkPrev.TrafficLightState();

	bool bIsLightEnAtNextConnection = nLinkNext.IsLightEnabledInConnectedNode();
	bool bIsLightEnAtCurrentConnection = nLinkCurrent.IsLightEnabledInConnectedNode();
	bool bIsLightEnAtPrevConnection = nLinkPrev.IsLightEnabledInConnectedNode();

	/*if(!lightStateAtNextLink || !bIsLightEnAtConnection && nLinkNext.IndexToAttachedNode() != pVeh->stAutopilot.m_dwNextNode || bIsLightEnAtConnection && nLinkNext.IndexToAttachedNode() == pVeh->stAutopilot.m_dwNextNode)
	{
		if( !lightStateAtCurrentLink || !bIsLightEnAtCurrentConnection && nLinkCurrent.IndexToAttachedNode() != pVeh->stAutopilot.m_dwCurrentNode || bIsLightEnAtCurrentConnection && nLinkCurrent.IndexToAttachedNode() == pVeh->stAutopilot.m_dwCurrentNode)
		{
			if((pVeh->bfTypeStatus >> 3) != 3 || !lightStateAtPrevLink || !bIsLightEnAtPrevConnection && nLinkPrev.IndexToAttachedNode() != pVeh->stAutopilot.m_dwPrevNode || bIsLightEnAtPrevConnection && nLinkPrev.IndexToAttachedNode() == pVeh->stAutopilot.m_dwPrevNode)
				return false;
			else
			{
				if(!bCheckSignal)
				{
					if(lightStateAtPrevLink != 1 || !LightsForCars1())
					{
						if (lightStateAtPrevLink != 2)
							return false;
						if (!LightsForCars2())
							return false;

						CVector2D v2dToPrevNode = CVector2D(pVeh->mat.vPos) - pThePaths->m_CarPathLinks[nLinkPrev.n].GetPos();
						v2dToPrevNode.fX *= (float)pThePaths->m_CarPathLinks[nLinkPrev.n].NormalVecX / 100.0f;
						v2dToPrevNode.fY *= (float)pThePaths->m_CarPathLinks[nLinkPrev.n].NormalVecY / 100.0f;
						float fPrevCoef = v2dToPrevNode.fX + v2dToPrevNode.fY;

						if(pVeh->stAutopilot.m_bytePrevDirectionScale == -1)
						{
							if (fPrevCoef > 0.0f && fPrevCoef < 6.0f)
								return true;
						}
						else
						{
							if (fPrevCoef < 0.0f && fPrevCoef > -6.0f)
								return true;
						}
						return false;
					}
				}
			}
		}
		else
		{
		}
	}
	else
	{
	}*/

	if(!( !lightStateAtNextLink || !bIsLightEnAtNextConnection && nLinkNext.IndexToAttachedNode() != pVeh->stAutopilot.m_dwNextNode || bIsLightEnAtNextConnection && nLinkNext.IndexToAttachedNode() == pVeh->stAutopilot.m_dwNextNode))
	{
		if(!bCheckSignal)
		{
			if(lightStateAtNextLink != 1 || !LightsForCars1())
			{
				if (lightStateAtNextLink != 2)
					goto currentCondition;
				if (!LightsForCars2())
					goto currentCondition;
			}
		}
		CVector2D v2dToNextNode = CVector2D(pVeh->mat.vPos) - pThePaths->m_CarPathLinks[nLinkNext.n].GetPos();
		v2dToNextNode.fX *= (float)pThePaths->m_CarPathLinks[nLinkNext.n].NormalVecX / 100.0f;
		v2dToNextNode.fY *= (float)pThePaths->m_CarPathLinks[nLinkNext.n].NormalVecY / 100.0f;
		float fNextCoef = v2dToNextNode.fX + v2dToNextNode.fY;

		if(pVeh->stAutopilot.m_byteNextDirectionScale == -1)
		{
			if (fNextCoef > 0.0f && fNextCoef < 8.0f)
				return true;
		}
		else
		{
			if (fNextCoef < 0.0f && fNextCoef > -8.0f)
				return true;
		}
	}

	currentCondition:if(!( !lightStateAtCurrentLink || !bIsLightEnAtCurrentConnection && nLinkCurrent.IndexToAttachedNode() != pVeh->stAutopilot.m_dwCurrentNode || bIsLightEnAtCurrentConnection && nLinkCurrent.IndexToAttachedNode() == pVeh->stAutopilot.m_dwCurrentNode))
	{
		if(!bCheckSignal)
		{
			if(lightStateAtCurrentLink != 1 || !LightsForCars1())
			{
				if (lightStateAtCurrentLink != 2)
					goto prevCondition;
				if (!LightsForCars2())
					goto prevCondition;
			}
		}

		CVector2D v2dToCurrentNode = CVector2D(pVeh->mat.vPos) - pThePaths->m_CarPathLinks[nLinkCurrent.n].GetPos();
		v2dToCurrentNode.fX *= (float)pThePaths->m_CarPathLinks[nLinkCurrent.n].NormalVecX / 100.0f;
		v2dToCurrentNode.fY *= (float)pThePaths->m_CarPathLinks[nLinkCurrent.n].NormalVecY / 100.0f;
		float fCurrentCoef = v2dToCurrentNode.fX + v2dToCurrentNode.fY;

		if(pVeh->stAutopilot.m_byteCurrentDirectionScale == -1)
		{
			if (fCurrentCoef > 0.0f && fCurrentCoef < 8.0f)
				return true;
		}
		else
		{
			if (fCurrentCoef < 0.0f && fCurrentCoef > -8.0f)
				return true;
		}
			
		
	}
prevCondition:
	if(!((pVeh->bfTypeStatus >> 3) != 3 || !lightStateAtPrevLink || !bIsLightEnAtPrevConnection && nLinkPrev.IndexToAttachedNode() != pVeh->stAutopilot.m_dwPrevNode || bIsLightEnAtPrevConnection && nLinkPrev.IndexToAttachedNode() == pVeh->stAutopilot.m_dwPrevNode))
	{
		if(!bCheckSignal)
		{
			if(lightStateAtPrevLink != 1 || !LightsForCars1())
			{
				if (lightStateAtPrevLink != 2)
					return false;
				if (!LightsForCars2())
					return false;
			}
		}

		CVector2D v2dToPrevNode = CVector2D(pVeh->mat.vPos) - pThePaths->m_CarPathLinks[nLinkPrev.n].GetPos();
		v2dToPrevNode.fX *= (float)pThePaths->m_CarPathLinks[nLinkPrev.n].NormalVecX / 100.0f;
		v2dToPrevNode.fY *= (float)pThePaths->m_CarPathLinks[nLinkPrev.n].NormalVecY / 100.0f;
		float fPrevCoef = v2dToPrevNode.fX + v2dToPrevNode.fY;

		if(pVeh->stAutopilot.m_bytePrevDirectionScale == -1)
		{
			if (fPrevCoef > 0.0f && fPrevCoef < 6.0f)
				return true;
		}
		else
		{
			if (fPrevCoef < 0.0f && fPrevCoef > -6.0f)
				return true;
		}
		return false;
	}
	return false;
}


bool CheckIfEntityIsTrafficLight(CEntity* pEnt)
{
	int MI = pEnt->nModelIndex;	
	if (MI == MI_MTRAFFIC1 || MI == MI_MTRAFFIC2 || MI == MI_MTRAFFIC4 || MI == MI_TRAFFICLIGHT1)
		return true;	
	return false;
}

void CTrafficLights::ScanForLightsOnMapN(void)
{
	for each (CSector itr in CWorld::stSectorList.n)
	{
		CPtrList pListTraverse = itr.stNodeLists[SL_DUMMYCENTER];
		while (pListTraverse.pStart)
		{
			CEntity* pEnt = pListTraverse.pStart->pEntity;
			pListTraverse.pStart = pListTraverse.pStart->pNext;
			if(!CheckIfEntityIsTrafficLight(pEnt))
				continue;

			CVector vecLeftSig(17.0f, 0.0f, 0.0f);
			CVector posLSigInWorld, posRSigInWorld;
			CVector vecRightSig(-15.0f, 0.0f, 0.0f);

			posLSigInWorld = pEnt->mat * vecLeftSig;
			posRSigInWorld = pEnt->mat * vecRightSig;

			CVector2D vecRToLSig(posRSigInWorld - posLSigInWorld);

			for (int nNode = 0; nNode < pThePaths->m_nAttachedNodes; nNode++)
			{
				CVector vecNodeToLSig(pThePaths->m_AttachedPaths[nNode].Form3DVector() - posLSigInWorld);
				
				// nodes is to far from signal
				if (vecNodeToLSig.LengthSquared() >= 10000.0f)
					continue;


				for(int nNodesConnectedOffset = 0; nNodesConnectedOffset < ((CPathNodeIndex)nNode).NumOfAttachedNodes(); nNodesConnectedOffset++)
				{
					int nArrayInfoIndex = ((CPathNodeIndex)nNode).GetInfoArrayIndex(nNodesConnectedOffset);
					CPathNodeIndex nAttachedNode = GetAttachedNodeFromArrayIndex(nArrayInfoIndex);
					
					if (((CPathNodeIndex)nNode).n < nAttachedNode.n)
					{
						CVector posAttachedNode(pThePaths->m_AttachedPaths[nAttachedNode.n].Form3DVector());
						CVector posNode(pThePaths->m_AttachedPaths[nNode].Form3DVector());

						float fAvgHeight = utl::abs<float>(posLSigInWorld.fZ - (posAttachedNode.fZ + posNode.fZ) * 0.5f);

						if (fAvgHeight < 10.0f)
						{
							bool bBastard;
							if( ((posAttachedNode.fY - posLSigInWorld.fY) * vecRToLSig.fX - (posAttachedNode.fX - posLSigInWorld.fX) * vecRToLSig.fY) * ((posNode.fY - posLSigInWorld.fY) * vecRToLSig.fX - (posNode.fX - posLSigInWorld.fX) * vecRToLSig.fX) <= 0.0f)
							{
								bBastard  = ((posRSigInWorld.fY - posNode.fY) * (posAttachedNode.fX - posNode.fX)
											- (posRSigInWorld.fX - posNode.fX) * (posAttachedNode.fY - posNode.fY))
											* ((posLSigInWorld.fY - posNode.fY) * (posAttachedNode.fX - posNode.fX)
											- (posLSigInWorld.fX - posNode.fX) * (posAttachedNode.fY - posNode.fY)) <= 0.0f ? true : false;
								//bBastard = ((posRSigInWorld.fY - posAttachedNode.fY) * (posAttachedNode.fX - posNode.fX) - (posLSigInWorld.fX - posNode.fX) * (posAttachedNode.fX - posNode.fY)) <= 0.0f ? true: false;
							}
							else
								bBastard = false;
							if(bBastard)
							{
								CCarPathInfoLinkIndex nCarPathLink = GetLinkNodeFromArrayIndex(nArrayInfoIndex);
								float frad = (float)CGeneral::GetATanOfXY(CVector2D(pEnt->mat.vLookAt));
								float fdeg = 57.295776f * frad;
								int rotStat;
								// adjust the signal state according to orientation?
								if ( (fdeg <= 60.0f || fdeg >= 150.0f) && (fdeg <= 240.0f || fdeg >= 330.0f))
									rotStat = 2;
								else
									rotStat = 1;
								pThePaths->m_CarPathLinks[nCarPathLink.n].bitTrafficLight = rotStat;
								if(((CPathNodeIndex)nNode).NumOfAttachedNodes() > nAttachedNode.NumOfAttachedNodes())	
									nAttachedNode = nNode;

								if(pThePaths->m_CarPathLinks[nCarPathLink.n].nIndexToAttachedNode != nAttachedNode.n)
									pThePaths->m_CarPathLinks[nCarPathLink.n].bitTrafficUnknown = 1;
							}
						}
					}
				}
			}

			// test the ped cross roads and set ped traffic lights
			for (int nPedNode = pThePaths->m_nCarAttachedNodes; nPedNode < pThePaths->m_nAttachedNodes; nPedNode++)
			{
				CVector2D v2dPedNodeToEntPos = pThePaths->m_AttachedPaths[nPedNode].Form2DVector() - pEnt->mat.vPos;

				float fdistCoeff = fabsf(v2dPedNodeToEntPos.fX) + fabsf(v2dPedNodeToEntPos.fY);

				if (fdistCoeff >= 50.0f)
					continue;

				for (int nNodesConnectedOffset = 0; nNodesConnectedOffset < ((CPathNodeIndex)nPedNode).NumOfAttachedNodes(); nNodesConnectedOffset++)
				{
					int nArrayInfoIndex = ((CPathNodeIndex)nPedNode).GetInfoArrayIndex(nNodesConnectedOffset);

					if(pThePaths->m_infoConnectedNodes[nArrayInfoIndex] & CPathFind::em_infoConnectedNodesCROSSROAD)
					{
						CPathNodeIndex nAttachedNode = GetAttachedNodeFromArrayIndex(nArrayInfoIndex);
						// Fuck me damn, was originally just a position nt a vector forgot to subtract
						CVector2D v2dPedAttachedNodeToEntPos = pThePaths->m_AttachedPaths[nAttachedNode.n].Form2DVector() - pEnt->mat.vPos;

						float fAttacheddistCoeff = fabsf(v2dPedAttachedNodeToEntPos.fX) + fabsf(v2dPedAttachedNodeToEntPos.fY);
						if (fAttacheddistCoeff < 15.0f || fdistCoeff < 15.0f)
							pThePaths->m_infoConnectedNodes[nArrayInfoIndex] |= CPathFind::em_infoConnectedNodesTRAFFICLIGHT;
					}
				}
			}
		}
	}
}
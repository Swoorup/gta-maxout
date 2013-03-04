#ifndef __CPATHFIND_H
#define __CPATHFIND_H

#include "../StdInc.h"
#include "CVector.h"
#include "CVector2D.h"

#pragma pack(push, 1)

class CPathInfoForObjectSingleElement
{
public:
	CVector posCoors; // 0-12
	//node position in z axis
	uint8_t byteNodeType; // 12-13
	//determines whether the node is attached or detached
	signed char sbNextNode; // 13-14
	//connects to the next attached node
	unsigned char byteLeftLanes; // 14-15
	//the number of left lanes
	unsigned char byteRightLanes; // 15-16
	//the number of right lanes
	unsigned char byteSpeedLimit; // 16-17
	//can have maximum of 3 because only 2 bits are adjusted in the flags
	signed char sbMedianWidth; // 17-18
	//median gap between left and right lanes
	unsigned char byteFlags; // 18-19
	//stores 6 flags for the node
	unsigned char byteSpawnRate; // 19-20
	//spawn rate of the object in the node
};

class CPathInfoForObject
{
public:
	CPathInfoForObjectSingleElement m_pathinfo[12];

	void SwapConnectionsToBeRightWayRound(void);
};

class CTempNode
{
public:
	CVector posCoors; // 0-12
    signed char byteNormalX; // 12-13
    //unit vector component-X
    signed char byteNormalY; // 13-14
    //unit vector component-Y
    unsigned int nConnectedAttachedNode; // 14-16
    unsigned int nOtherConnectedAttachedNode; // 16-18
    unsigned char byteLeftLanes; // 18-19
	unsigned char byteRightLanes; // 19-20
	signed char sbMedianWidth; // 20-21
	bool bIsCrossRoad; // 21-22
    unsigned char stateStoreType; //22-23
	_pad(__fxpad00, 1); // 23-24

	enum 
	{
		NOT_IN_RANGE = 1,
		AVERAGED_NODE = 2,
	};
};

struct CTempDetachedNode
{
	CVector posCoors; // 0-12
	unsigned int sNextNodeIndex; // 12-14
	unsigned char byteLeftLanes; // 14-15
	unsigned char byteRightLanes; // 15-16
	signed char sbMedianWidth; // 16-17
	bool bIsCrossRoad; // 17-18
	_pad(__fxpad00, 2); // 18-20
};

class CPathNode
{
public:
	signed int wNextListOrNodeIndex; // 0-4
	signed int wPreviousNodeIndex; // 0-8
	int wX; // 8-12
    //node position in x axis multiplied by 8 to save precision
	int wY; // 12-16
    //node position in y axis multiplied by 8 to save precision
	int wZ; // 16-20
    //node position in z axis multiplied by 8 to save precision
	short heuristicCost; // 20-22
    //dynamic store for displacement between two specific node
	int wRouteInfoIndex; // 22-26
    //m_infoConnectedNodes index and m_nConnectionWeight index
	char sbMedianWidth; // 26-27
    //median gap between left and right lanes
	unsigned char ucFloodColor; // 27-28

	//bits are inversed. Lowest bit starts from the right side. That is 76543210
	unsigned char bitnumberOfNodesConnected:4; // 16.0-16.4
    //number of nodes attached with the current one
    unsigned char bitUnknownFlag3:1; // 16.4-16.5
    //is used in CCarCtrl::PickNextNodeRandomly
    unsigned char bitIsIgnoredNode:1; // 16.5-16.6
    //determines whether the node should be ignored
    unsigned char bitRestrictedAccess:1; // 16.6-16.7
	unsigned char bitCopsRoadBlock:1; // 16.7-17.0
    //determines if the node is used for law enforcement barricades

	unsigned char bitIsVehicleBoat:1; // 17.0-17.1
    //determines if the current node is for boats
	unsigned char bitHaveUnrandomizedVehClass:1; // 17.1-17.2
    //only specific vehicles can follow this route
	unsigned char bitUnkFlagFor2:1; // 17.2-17.3 //Unknown flag
	unsigned char bitSpeedLimit:2; // 17.3-17.5
    //the maximum speed limit in this route. Speeds are controlled in CAutopilot
    unsigned char bitPadFlags8To10:3; // 17.5-18.0

	unsigned char byteSpawnRate; // 18-19
	unsigned char byteField0x013; // 19-20

    CPathNode()
	{
		wNextListOrNodeIndex = -1;
		wPreviousNodeIndex = -1;
		ucFloodColor = 0;
		bitUnkFlagFor2 = 0;
		bitPadFlags8To10 = 0;
		bitnumberOfNodesConnected = 0;
		heuristicCost = 32766;
	}

    void GetNodeCoors(CVector* vecNodePosition);

	CVector Form3DVector()
	{
		return CVector((float)wX / 8.0f, (float)wY / 8.0f, (float)wZ / 8.0f);
	}

	CVector2D Form2DVector()
	{
		return CVector2D((float)wX / 8.0f, (float)wY / 8.0f);
	}

	void StoreCoorWithPrecision(CVector& posNodeCoors)
	{
		wX = (signed int)(posNodeCoors.fX * 8.0f);
		wY = (signed int)(posNodeCoors.fY * 8.0f);
		wZ = (signed int)(posNodeCoors.fZ * 8.0f);
	}
};

class CCarPathLink{
public:
	int wX; // 0-2
    int wY; // 2-4
    int nIndexToAttachedNode; // 4-6
    signed char NormalVecX; // 6-7
    signed char NormalVecY; // 7-8
    unsigned char bitLeftLanes:3; // 8.0-8.3
	unsigned char bitRightLanes:3; // 8.3-8.6
	unsigned char padTwoBits:2; // 8.6-9.0
    unsigned char byteTrafficFlags; // 9-10
    signed char sbMedianWidth; // 10-11
    _pad(__fxpad00, 1); // 11-12

    CCarPathLink();
    float OneWayLaneOffset();
};
#define PATHMUL 15

class CPathFind
{
private:
public:
    
	// attached sets of nodes for both cars and peds
    CPathNode		m_AttachedPaths[9650*PATHMUL]; // 0-2F1E8h
    // contains info about lanes, only for cars
    CCarPathLink	m_CarPathLinks[3500*PATHMUL]; // 2F1E8h-395F8h
    //void* pTreadables[1250]; // 395F8h-3A980h
    //is unused and can be removed later on
    int32_t			m_infoConnectedNodes[20400*PATHMUL]; // 3A980h-448E0h
    //this field maybe be unsigned
    uint8_t			m_nConnectionWeight[20400*PATHMUL]; // 448E0h-49890h
    int32_t			m_InfoCarPathLinks[20400*PATHMUL]; // 49890h-537F0h
    int32_t			m_nAttachedNodes; // 537F0h-537F4h
    int32_t			m_nCarAttachedNodes; // 537F4h-537F8h
    int32_t			m_nPedAttachedNodes; // 537F8h-537FCh
    int16_t			w_nTreadables; // 537FCh-537FEh
    uint32_t		m_nConnectedNodes; // 537FEh-53800h
    int32_t			m_nCarPathLinks; // 53800h-53804h
    uint32_t		Unusedfield_53804; // 53804h-53808h
    char			m_nFloodFillAmountUsed[2]; // 53808h-5380Ah;
    CPathNode		m_OpenNodeList[512]; // 5380Ah-5600Ah

    CPathFind();

    enum {
        em_infoConnectedNodesCROSSROAD = 0x80000000,
        em_infoConnectedNodesTRAFFICLIGHT = 0x40000000,
        em_infoConnectedNodesNODEINDEXONLY = 0x3FFFFFFF,
    };

    
	void AddNodeToList(CPathNode *pTargetNode, int nHeuristicCostAndListIndex);
    void AllocatePathFindInfoMem(void);
	float CalcRoadDensity(CVector2D& pos2dCoors);
	void CountFloodFillGroups(unsigned char iPathDataFor);
	void DoPathSearch(int iPathDataFor, CVector& posOrigin, int iFirstNode, CVector& posDest, CPathNode* pIntermediateNodeList[], short *pSteps, short sMaxSteps, void *pVehicle, float *pfPathCost, float fMaxRadius, int iLastNode);
	void FindNextNodeWandering(unsigned char iPathDataFor, CVector& posCoors, CPathNode** pCurrentNode, CPathNode** pNextNode, uint8_t bytePreviousDirection, uint8_t *byteNewDirection);
	int FindNodeClosestToCoors(CVector& posCoors, unsigned char iPathDataFor, float fRangeCoefficient, bool bCheckIgnored, bool bCheckRestrictedAccess, bool bCheckUnkFlagFor2, bool bIsVehicleBoat);
	int FindNodeClosestToCoorsFavourDirection(CVector& posCoors, uint8_t uiPathDataFor, CVector2D& v2dPreferedDirection);
	bool GeneratePedCreationCoors(CVector2D& pos2DCoors, float fRangeForRand, float fRange, float fRange1, float fRange2, CVector *pVecOutPosition, int *aStartNodeIndex, int *aFollowNodeIndex, float *frand, RwMatrix *rwMatrix);
	void Init(void);
	bool NewGenerateCarCreationCoors(CVector2D& pos2DCoors, CVector2D& v2dDirection, float fRange, float fZlookUp, bool bShouldSpawnPositiveDirection, CVector *pVecPosition, int *aMainNodeIndex, int *aSubNodeIndex, float *aNodeRangeDiffCoeff, char bDontCheckIgnored);
    void PreparePathData(void); 
    void PreparePathDataForType(unsigned char bytePathDataFor, CTempNode* pTempNode, CPathInfoForObject* pUnusedPathInfos, float fUnkRange, CPathInfoForObject* pPathInfosForObject, int nGroupNodesForObject);
    void RemoveBadStartNode(CVector& posCoors, CPathNode **pIntermediateNodeList, short *pSteps);
    void RemoveNodeFromList(CPathNode *pRemoveNode);
    bool TestCoorsCloseness(CVector& posDest, uint8_t uiPathDataFor, CVector& posOrigin);
    bool TestCrossesRoad(CPathNode* pStartNode, CPathNode* pConnectedNode);
    bool TestForPedTrafficLight(CPathNode* pStartNode, CPathNode* pConnectedNode);
	
	// temporarily holds all the raw external path nodes
    static CTempDetachedNode* s_pTempExternalNodes;
    static void __stdcall StoreNodeInfoCar(int iNodeInfo_InternalNodesCount, uint8_t eNodeType, int8_t iNextNode, float fNodeX, float fNodeY, float fNodeZ, float fMedianWidth, uint8_t nLeftLanes, uint8_t nRightLanes, bool bIsIgnoredNode, bool bIsRestrictedAccess, uint8_t bSpeedLimit, bool bIsPoliceRoadBlock, uint8_t nVehicleType, uint32_t dwSpawnRate, uint8_t bUnknown);
    static void __stdcall StoreNodeInfoPed(int iNodeInfo_InternalNodesCount, uint8_t eNodeType, int8_t iNextNode, float fNodeX, float fNodeY, float fNodeZ, float fMedianWidth, uint8_t iNode_unknown, bool bIsIgnoredNode, bool bIsRestrictedAccess, uint32_t dwSpawnRate);


	//inlined functions
	// both functions make a two way from list to index and vice versa
	inline CPathNode* GetAppropriateListFromIndex(int index)
	{
		if (index >= 0)
			if (index >= 512)
				return &m_AttachedPaths[index - 512];
			else
				return &m_OpenNodeList[index];
		else
			return NULL;
	}

	inline int GetAppropriateIndexFromPathNode(CPathNode* pNode)
	{
		int index;
		// R* forgot to include check for NULL nodes, this caused crash in SOL, something to do with flood fill //
		if (pNode)
			if (pNode < &m_OpenNodeList[0] || pNode >= &m_OpenNodeList[512])
				index = (pNode - &m_AttachedPaths[0]) + 512;
			else	
				index = pNode - &m_OpenNodeList[0];
		else
			index = -1;
		
		return index;
	}
};

class CPedPath {
public:
    static void _cdecl CalculateBestRandomCoors(CPathNode* pPathNodeA, CPathNode* pPathNodeB, short sRand, float* fX, float* fY);
    static CVector* CPedPath::CalculateRandomCoordinates(CVector* pvecPosition, CPathNode* pPathNode, short sRand);
};

#pragma pack(pop)
#endif
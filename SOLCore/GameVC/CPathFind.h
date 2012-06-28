#ifndef __CPATHFIND_H
#define __CPATHFIND_H

#include "../StdInc.h"
#undef PATHFINDUSEORIGINAL
#pragma pack(push, 1)

struct CPathInfoForObject{
  float fX; // 0-4
  //node position in x axis
  float fY; // 4-8
  //node position in y axis
  float fZ; // 8-12
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

struct CTempNode{
	float fX; // 0-4
    float fY; // 4-8
    float fZ; // 8-12
    signed char byteNormalX; // 12-13
    //unit vector component-X
    signed char byteNormalY; // 13-14
    //unit vector component-Y
    unsigned int PrevDetachedIndex; // 14-16
    unsigned int NextDetachedIndex; // 16-18
    unsigned char byteLeftLanes; // 18-19
	unsigned char byteRightLanes; // 19-20
	signed char sbMedianWidth; // 20-21
	bool bIsCrossRoad; // 21-22
    unsigned char processState; //22-23
	_pad(__fxpad00, 1); // 23-24
};

struct CTempDetachedNode{
	float fX; // 0-4
	float fY; // 4-8
	float fZ; // 8-12
	unsigned int sNextNodeIndex; // 12-14
	unsigned char byteLeftLanes; // 14-15
	unsigned char byteRightLanes; // 15-16
	signed char sbMedianWidth; // 16-17
	bool bIsCrossRoad; // 17-18
	_pad(__fxpad00, 2); // 18-20
};

class CPathNode{
public:
	signed short wField0x00; // 0-2
	signed short wField0x02; // 0-4
	short wX; // 4-6
    //node position in x axis multiplied by 8 to save precision
	short wY; // 6-8
    //node position in y axis multiplied by 8 to save precision
	short wZ; // 8-10
    //node position in z axis multiplied by 8 to save precision
	short wUnkDist0x0A; // 10-12
    //dynamic store for displacement between two specific node
	short wRouteInfoIndex; // 12-14
    //AttachedPointsInfo index and m_InRangedDisplacement index
	char sbMedianWidth; // 14-15
    //median gap between left and right lanes
	unsigned char sbField0x0F; // 15-16

	//bits are inversed. Lowest bit starts from the right side. That is 76543210
	unsigned char bitUnkCount4To7:4; // 16.0-16.4
    //number of next connected sets of nodes to iterate
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
    CPathNode();
};

class CDetachedNode{
public:
	short wX; // 0-2
    short wY; // 2-4
    short wPathsIndex; // 4-6
    signed char NormalVecX; // 6-7
    signed char NormalVecY; // 7-8
    unsigned char bitLeftLanes:3; // 8.0-8.3
	unsigned char bitRightLanes:3; // 8.3-8.6
	unsigned char bitPadData:2; // 8.6-9.0
    unsigned char byteTrafficFlags; // 9-10
    signed char sbMedianWidth; // 10-11
    _pad(__fxpad00, 1); // 11-12

    CDetachedNode();
    float CalculateLaneDistance();
};

class CPathFind{
private:
#ifndef PATHFINDUSEORIGINAL
    static void __stdcall ArrangeOneNodeList(CPathInfoForObject *PathInfo);
#endif

public:
    
    CPathNode m_AttachedPaths[9650]; // 0-2F1E8h
    //PathNode Infos for Car and Peds 
    CDetachedNode m_DetachedNodes[3500]; // 2F1E8h-395F8h
    void* pTreadables[1250]; // 395F8h-3A980h
    //is unused and can be removed later on
    short AttachedPointsInfo[20400]; // 3A980h-448E0h
    //this field maybe be unsigned
    uint8_t m_InRangedDisplacement[20400]; // 448E0h-49890h
    short DetachedPointsInfo[20400]; // 49890h-537F0h
    int m_nAttachedNodes; // 537F0h-537F4h
    int m_nCarAttachedNodes; // 537F4h-537F8h
    int m_nPedAttachedNodes; // 537F8h-537FCh
    short w_nTreadables; // 537FCh-537FEh
    uint16_t m_nAttachedPoints; // 537FEh-53800h
    int m_nDetachedPoints; // 53800h-53804h
    uint32_t Unusedfield_53804; // 53804h-53808h
    char Unusedfield_53808[2]; // 53808h-5380Ah;
    CPathNode m_UnknownNodeList[512]; // 5380Ah-5600Ah

    CPathFind();

    enum {
        eATTACHEDPOINTSINFOCROSSROAD = 0x8000,
        eATTACHEDPOINTSINFOTRAFFICLIGHT = 0x4000,
        eATTACHEDPOINTSINFONODEINDEXONLY = 0x3FFF,
    };

    void Init(void);
    void AllocatePathFindInfoMem(void);
    void PreparePathData(void); 
    void PreparePathDataForType(unsigned char bytePathDataFor, CTempNode* pTempNode, CPathInfoForObject* pUnusedPathInfos, float fUnkRange, CPathInfoForObject* pPathInfosForObject, int nGroupNodesForObject);
    void CountFloodFillGroups(unsigned char iPathDataFor);
    void AddNodeToList(CPathNode *pTargetNode, int iParamDisplacement);
    void RemoveNodeFromList(CPathNode *pRemoveNode);
  
    static CPathNode* staticNodes[9650];
    void DoPathSearch(int iPathDataFor, float fOriginX, float fOriginY, float fOriginZ, int iFirstNode, float fDestX, float fDestY, float fDestZ, CPathNode **pIntermediateNodeList, short *pSteps, short sMaxSteps, void *pVehicle, float *pfDistance, float fMaxRadius, int iLastNode); //pVehicle, pfDistance and iLastNode are ununsed
    void RemoveBadStartNode(float fX, float fY, float fZ, CPathNode **pIntermediateNodeList, short *pSteps);
    int FindNodeClosestToCoors(float fX, float fY, float fZ, unsigned char iPathDataFor, float fRangeCoefficient, bool bCheckIgnored, bool bCheckRestrictedAccess, bool bCheckUnkFlagFor2, bool bIsVehicleBoat);
    void FindNextNodeWandering(unsigned char iPathDataFor, float fX, float fY, float fZ, CPathNode** pCurrentNode, CPathNode** pNextNode, uint8_t bytePreviousDirection, uint8_t *byteNewDirection);
    bool NewGenerateCarCreationCoors(float fX, float fY, float fDirectionVecX, float fDirectionVecY, float fRange, float fZlookUp, bool bShouldSpawnPositiveDirection, CVector *pVecPosition, int *aMainNodeIndex, int *aSubNodeIndex, float *aNodeRangeDiffCoeff, char bDontCheckIgnored);
    bool GeneratePedCreationCoors(float fX, float fY, float fRangeForRand, float fRange, float fRange1, float fRange2, CVector *pVecOutPosition, int *aStartNodeIndex, int *aFollowNodeIndex, float *frand, RwMatrix *rwMatrix);
    bool TestCoorsCloseness(float fDestinationX, float fDestinationY, float fDestinationZ, uint8_t uiPathDataFor, float fOriginX, float fOriginY, float fOriginZ);
    float CalcRoadDensity(float fX, float fY);
    int FindNodeClosestToCoorsFavourDirection(float fX, float fY, float fZ, uint8_t uiPathDataFor, float fLookAtX, float fLookAtY);
    bool TestCrossesRoad(CPathNode* pStartNode, CPathNode* pConnectedNode);
    bool TestForPedTrafficLight(CPathNode* pStartNode, CPathNode* pConnectedNode);

    // Static Objects
    static int g_nCarGroupNodes;
    static int g_nPedGroupNodes;
    static CPathInfoForObject* g_pCarPathInfos;
    static CPathInfoForObject* g_pPedPathInfos;
    static CTempDetachedNode* g_pTempDetachedNodes;
    static void __stdcall StoreNodeInfoCar(int iNodeInfo_InternalNodesCount, uint8_t eNodeType, int8_t iNextNode, float fNodeX, float fNodeY, float fNodeZ, float fMedianWidth, uint8_t nLeftLanes, uint8_t nRightLanes, bool bIsIgnoredNode, bool bIsRestrictedAccess, uint8_t bSpeedLimit, bool bIsPoliceRoadBlock, uint8_t nVehicleType, uint32_t dwSpawnRate, uint8_t bUnknown);
    static void __stdcall StoreNodeInfoPed(int iNodeInfo_InternalNodesCount, uint8_t eNodeType, int8_t iNextNode, float fNodeX, float fNodeY, float fNodeZ, float fMedianWidth, uint8_t iNode_unknown, bool bIsIgnoredNode, bool bIsRestrictedAccess, uint32_t dwSpawnRate);
};

class CPedPath {
public:
    static void _cdecl CalculateBestRandomCoors(CPathNode* pPathNodeA, CPathNode* pPathNodeB, short sRand, float* fX, float* fY);
    static CVector* CPedPath::CalculateRandomCoordinates(CVector* pvecPosition, CPathNode* pPathNode, short sRand);
};

#pragma pack(pop)
#endif
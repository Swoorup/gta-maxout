#ifndef __CPATHFIND_H
#define __CPATHFIND_H

#include "../StdInc.h"

#undef PATHFINDUSEORIGINAL

#pragma pack(push, 1)

struct CPathInfoForObject{
  float fX; // 0-4
  float fY; // 4-8
  float fZ; // 8-12
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
  //median width of the node between left and right nodes
  unsigned char byteFlags; // 18-19
  //stores 6 flags for the node
  unsigned char byteSpawnRate; // 19-20
  //spawn rate of the object in the node
};

class CPathNode{
public:
	short wField0x00;       // 0-2
	short wField0x02;       // 0-4
	short wX;               // 4-6
	short wY;               // 6-8
	short wZ;               // 8-10
	short wUnkDist0x0A;       // 10-12
	short wRouteInfoIndex;  // 12-14
	char sbMedianWidth;     // 14-15
	unsigned char sbField0x0F;       // 15-16

	//bits are inversed. Lowest bit starts from the right side. That is 76543210
	unsigned char bitUnkCount4To7:4;    // 16.0-16.4
    unsigned char bitUnknownFlag3:1;    // 16.4-16.5
    unsigned char bitIgnoredNode:1;     // 16.5-16.6
    unsigned char bitRestrictedAccess:1;// 16.6-16.7
	unsigned char bitCopsRoadBlock:1;   // 16.7-17.0

	unsigned char bitIsVehicleBoat:1;   // 17.0-17.1
	unsigned char bitHaveUnrandomizedVehClass:1;    // 17.1-17.2
	unsigned char bitUnkFlagFor2:1;      // 17.2-17.3 //Unknown flag
	unsigned char bitSpeedLimit:2;      // 17.3-17.5
    unsigned char bitPadFlags8To10:3;   // 17.5-18.0
    
	unsigned char byteSpawnRate;        // 18-19
	unsigned char byteField0x013;       // 19-20

    CPathNode();
};

struct CTempDetachedNode{
	float fX;       // 0-4
	float fY;       // 4-8
	float fZ;       // 8-12
	unsigned short sNextNodeIndex;  // 12-14
	unsigned char byteLeftLanes;    // 14-15
	unsigned char byteRightLanes;   // 15-16
	signed char sbMedianWidth;      // 16-17
	bool bIsCrossRoad;              // 17-18
	short pad;                      // 18-20
};

struct CTempNode{
	float fX;
    float fY;
    float fZ;
    signed char byteNormalX;
    signed char byteNormalY;
    unsigned short PrevDetachedIndex;
    unsigned short NextDetachedIndex;
    unsigned char byteLeftLanes;
	unsigned char byteRightLanes;
	signed char sbMedianWidth;
	bool bIsCrossRoad;
    unsigned char processState;
	char _padding;
};

class CDetachedNode{
public:
	short wX;           // 0-2
    short wY;           // 2-4
    short wPathsIndex;  // 4-6
    signed char NormalVecX; // 6-7
    signed char NormalVecY; // 7-8
    unsigned char bitLeftLanes:3;   // 8.0-8.3
	unsigned char bitRightLanes:3;  // 8.3-8.6
	unsigned char bitPadData:2;     // 8.6-9.0
    unsigned char byteTrafficFlags; // 9-10
    signed char sbMedianWidth;      // 10-11
    char padded;                    // 11-12

    CDetachedNode();
};


class CPathFind{
private:
#ifndef PATHFINDUSEORIGINAL
    static void __stdcall ArrangeOneNodeList(CPathInfoForObject *PathInfo);
#endif

public:
  CPathNode m_AttachedPaths[9650];          // 0-2F1E8h
  CDetachedNode m_DetachedNodes[3500];      // 2F1E8h-395F8h
  void* pTreadables[1250];                  // 395F8h-3A980h
  short AttachedPointsInfo[20400];          // 3A980h-448E0h
  unsigned char m_InRangedDisplacement[20400];// 448E0h-49890h
  short DetachedPointsInfo[20400];          // 49890h-537F0h
  int m_nAttachedNodes;                     // 537F0h-537F4h
  int m_nCarAttachedNodes;                  // 537F4h-537F8h
  int m_nPedAttachedNodes;                  // 537F8h-537FCh
  short w_nTreadables;                      // 537FCh-537FEh
  unsigned short m_nAttachedPoints;         // 537FEh-53800h
  int m_nDetachedPoints;                    // 53800h-53804h
  unsigned int Unusedfield_53804;                 // 53804h-53808h
  char Unusedfield_53808[2];                      // 53808h-5380Ah;
  CPathNode m_UnknownNodeList[512];               // 5380Ah-5600Ah

  CPathFind();

  void Init(void);
  void AllocatePathFindInfoMem(void);
  void PreparePathData(void); 
  void PreparePathDataForType(unsigned char bytePathDataFor,
		                    CTempNode* pTempNode,
						    CPathInfoForObject* pUnusedPathInfos,
						    float fUnkRange,
						    CPathInfoForObject* pPathInfosForObject,
						    int nGroupNodesForObject);
  void CountFloodFillGroups(unsigned char iPathDataFor);
  //void AddNodeToList(CPathNode* pPathNode, 

  // Static Objects
  static int g_nCarGroupNodes;
  static int g_nPedGroupNodes;
  static CPathInfoForObject* g_pCarPathInfos;
  static CPathInfoForObject* g_pPedPathInfos;
  static CTempDetachedNode* g_pTempDetachedNodes;
  static void __stdcall StoreNodeInfoCar( int iNodeInfo_InternalNodesCount,
                                   uint8_t eNodeType,
                                   int8_t iNextNode,
                                   float fNodeX,
                                   float fNodeY,
                                   float fNodeZ,
                                   float fMedianWidth,
                                   uint8_t nLeftLanes,
                                   uint8_t nRightLanes,
                                   bool bIsIgnoredNode,
                                   bool bIsRestrictedAccess,
                                   uint8_t bSpeedLimit,
                                   bool bIsPoliceRoadBlock,
                                   uint8_t nVehicleType,
                                   uint32_t dwSpawnRate,
                                   uint8_t bUnknown);
    static void __stdcall StoreNodeInfoPed( int iNodeInfo_InternalNodesCount, 
                                   uint8_t eNodeType, 
                                   int8_t iNextNode, 
                                   float fNodeX, 
                                   float fNodeY,
                                   float fNodeZ,
                                   float fMedianWidth,
                                   uint8_t iNode_unknown,
                                   bool bIsIgnoredNode,
                                   bool bIsRestrictedAccess,
                                   uint32_t dwSpawnRate);
};

#pragma pack(pop)
#endif
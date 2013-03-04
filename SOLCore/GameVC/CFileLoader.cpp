#include "../StdInc.h"

#define VTYPE_CAR 0
#define VTYPE_BOAT 1

#define NODEOBJECT_PEDS 0
#define NODEOBJECT_CARS 1
#define NODEOBJECT_BOATS 2

#define NODEFLAGS_IGNORENODEAREA    0x00000001
#define NODEFLAGS_POLICEROADBLOCK   0x00000002
#define NODEFLAGS_RESTRICTEDACCESS  0x00000004

// This makes the path coords limited from -2047 to +2047
#ifdef GAMEUSEORIGINALS
#define SIGNEDINT16_LIMIT (double)(signed __int16)(signed int) 
#else
#define SIGNEDINT16_LIMIT (double)(signed int)
#endif

DWORD dwFunc_CFileLoader__LoadLevel = 0x0048D950;
DWORD dwFunc_CFileLoader__LoadScene = 0x0048B050;
DWORD dwFunc_CFileLoader__LoadObjectInstance = 0x0048ABB0;
DWORD dwFunc_CFileLoader__AddOcclusions = 0x00636960;

_declspec(naked) void CFileLoader::LoadLevel(const char* szDatFile){
	_asm jmp dwFunc_CFileLoader__LoadLevel
}

_declspec(naked) void CFileLoader::LoadObjectInstance(const char* szInstLine){
    _asm jmp dwFunc_CFileLoader__LoadObjectInstance
}

#ifdef GAMEUSEORIGINALS
_declspec(naked) void CFileLoader::LoadScene(const char* szSceneFile){
	_asm jmp dwFunc_CFileLoader__LoadScene
}

#else
char* g_szLineBuffer = (char*)0x7D7C38;
void CFileLoader::LoadScene(const char* szSceneFileName){
  unsigned int dwSwitchCase = 0;
  int iNodeInfo_InternalNodesCount = -1;
  int iNodeInfo_ObjectType;
  CDebug::DebugAddText("Creating objects from %s...\n", szSceneFileName);
  FILE* hFile = CFileMgr::OpenFile(szSceneFileName, "rb");
  
  while (true){
    char* szLine = g_szLineBuffer;
    int i = 0;
    if (CFileMgr::LoadLine(hFile, g_szLineBuffer, 256)){
      while (true){
        if (!g_szLineBuffer[i])  break;
        if (g_szLineBuffer[i] < ' ' || g_szLineBuffer[i] == ',') g_szLineBuffer[i] = ' ';
        ++i;
      }
      while ( *szLine <= ' ' && *szLine) ++szLine;
    }
    else
      szLine = NULL;
      
    if (szLine == NULL) break;
      
    if ( *szLine && szLine[0] != '#' ){
      if (dwSwitchCase){
        if (szLine[0] != 'e' || szLine[1] != 'n' || szLine[2] != 'd'){
          if ( dwSwitchCase - 1 <= 5){
            switch (dwSwitchCase){
              case 1:
                CFileLoader::LoadObjectInstance(szLine);
                continue;
              case 2:
              {
                char szZoneName[32];
                int iZoneType; 
                float fZoneX1, fZoneY1, fZoneZ1, fZoneX2, fZoneY2, fZoneZ2;
                int iZoneIsland;
                if (sscanf(szLine, 
                  "%s %d %f %f %f %f %f %f %d", 
                  szZoneName, 
                  &iZoneType, 
                  &fZoneX1, 
                  &fZoneY1, 
                  &fZoneZ1, 
                  &fZoneX2, 
                  &fZoneY2, 
                  &fZoneZ2, 
                  &iZoneIsland) == 9)
                  CTheZones::CreateZone(szZoneName, iZoneType, fZoneX1, 
                  fZoneY1, fZoneZ1, fZoneX2, fZoneY2, fZoneZ2, iZoneIsland);
                continue;
              }
              case 3:
              {
                int iCullUnk = 0; // This value always seem to be 0
                CVector CullCenter, CullLowerLeft, CullUpperRight;
                unsigned int dwCullFlags;
                sscanf(szLine,
                  "%f %f %f %f %f %f %f %f %f %d %d",
                  &CullCenter.fX,
                  &CullCenter.fY,
                  &CullCenter.fZ,
                  &CullLowerLeft.fX,
                  &CullLowerLeft.fY,
                  &CullLowerLeft.fZ,
                  &CullUpperRight.fX,
                  &CullUpperRight.fY,
                  &CullUpperRight.fZ,
                  &dwCullFlags,
                  &iCullUnk);
                CCullZones::AddCullZone(
                  CullCenter,
                  CullLowerLeft.fX,
                  CullUpperRight.fX,
                  CullLowerLeft.fY,
                  CullUpperRight.fY,
                  CullLowerLeft.fZ,
                  CullUpperRight.fZ,
                  dwCullFlags,
                  iCullUnk);
                continue;
              }
              case 4:
              {
                 float fOccluMidX, fOccluMidY, fOccluBottomZ, fOccluWidthX, fOccluWidthY, fOccluBoxHeight, fOccluRotation;
                 sscanf(szLine, "%f %f %f %f %f %f %f", 
                  &fOccluMidX, 
                  &fOccluMidY, 
                  &fOccluBottomZ, 
                  &fOccluWidthX, 
                  &fOccluWidthY, 
                  &fOccluBoxHeight, 
                  &fOccluRotation);
                 fOccluBottomZ += fOccluBoxHeight /2.0f;
                 CFileLoader::AddOcclusions( fOccluMidX, fOccluMidY, fOccluBottomZ, fOccluWidthX, fOccluWidthY, fOccluBoxHeight, fOccluRotation);
                 continue;
              }
              case 5: // unused switch case leftover by R*
              {
                int iPickUpID;
                CVector PickUpPosition;
                sscanf(szLine, "%d %f %f %f", &iPickUpID, &PickUpPosition.fX, &PickUpPosition.fY, &PickUpPosition.fZ);
                continue;
              }
              case 6:
                if (iNodeInfo_InternalNodesCount == -1){
                  uint32_t dwDelimiter;
                  char szUnused[84];
                  sscanf(szLine, "%d %d %s", &iNodeInfo_ObjectType, &dwDelimiter, szUnused);
                  iNodeInfo_InternalNodesCount = 0;
                }
                else{
                  int iNode_NodeType;
                  int iNode_NextNode;
                  int iNode_unknown;
                  float fNode_X;
                  float fNode_Y;
                  float fNode_Z;
                  float fNode_Median;
                  uint32_t dwNode_LeftLanes;
                  uint32_t dwNode_RightLanes;
                  uint32_t dwNode_SpeedLimit;
                  uint32_t dwNode_Flags;
                  float fNode_SpawnRate;
                  
                  bool bIsIgnoredNode = FALSE;
                  bool bIsPoliceRoadBlock = FALSE;
                  bool bIsRestrictedAccess = FALSE;
                  
                  if (sscanf(szLine, "%d %d %d %f %f %f %f %d %d %d %d %f",
                        &iNode_NodeType,
                        &iNode_NextNode,
                        &iNode_unknown,
                        &fNode_X,
                        &fNode_Y,
                        &fNode_Z,
                        &fNode_Median,
                        &dwNode_LeftLanes,
                        &dwNode_RightLanes,
                        &dwNode_SpeedLimit,
                        &dwNode_Flags,
                        &fNode_SpawnRate) != 12)
                    fNode_SpawnRate = 1.0f;
                  
                  if ( dwNode_Flags & NODEFLAGS_RESTRICTEDACCESS)
                    bIsRestrictedAccess = TRUE;
                  if ( dwNode_Flags & NODEFLAGS_IGNORENODEAREA)
                    bIsIgnoredNode = TRUE;
                  if ( dwNode_Flags & NODEFLAGS_POLICEROADBLOCK)
                    bIsPoliceRoadBlock = TRUE; 
                    
                  if (iNodeInfo_ObjectType == NODEOBJECT_PEDS){
                      CPathFind::StoreNodeInfoPed(iNodeInfo_InternalNodesCount, 
                                      (unsigned char)iNode_NodeType, 
                                      (signed char)iNode_NextNode, 
                                      SIGNEDINT16_LIMIT(fNode_X), 
                                      SIGNEDINT16_LIMIT(fNode_Y),
                                      SIGNEDINT16_LIMIT(fNode_Z),
                                      fNode_Median,
                                      (uint8_t)iNode_unknown,
                                      bIsIgnoredNode,
                                      bIsRestrictedAccess,
                                      (signed int)(15.0f * fNode_SpawnRate));
                  }
                  else if (iNodeInfo_ObjectType == NODEOBJECT_CARS){
                    CPathFind::StoreNodeInfoCar( iNodeInfo_InternalNodesCount,
                                    (unsigned char)iNode_NodeType,
                                    (signed char)iNode_NextNode,
                                    SIGNEDINT16_LIMIT(fNode_X),
                                    SIGNEDINT16_LIMIT(fNode_Y),
                                    SIGNEDINT16_LIMIT(fNode_Z),
                                    fNode_Median,
                                    (unsigned char)dwNode_LeftLanes,
                                    (unsigned char)dwNode_RightLanes,
                                    bIsIgnoredNode,
                                    bIsRestrictedAccess,
                                    (unsigned char)dwNode_SpeedLimit,
                                    bIsPoliceRoadBlock,
                                    VTYPE_CAR,
                                    (signed int)(15.0f * fNode_SpawnRate),
                                    0);
                  } 
                  else if (iNodeInfo_ObjectType == NODEOBJECT_BOATS){
                    CPathFind::StoreNodeInfoCar( iNodeInfo_InternalNodesCount,
                                    (unsigned char)iNode_NodeType,
                                    (signed char)iNode_NextNode,
                                    SIGNEDINT16_LIMIT(fNode_X),
                                    SIGNEDINT16_LIMIT(fNode_Y),
                                    SIGNEDINT16_LIMIT(fNode_Z),
                                    fNode_Median,
                                    (unsigned char)dwNode_LeftLanes,
                                    (unsigned char)dwNode_RightLanes,
                                    bIsIgnoredNode,
                                    bIsRestrictedAccess,
                                    (unsigned char)dwNode_SpeedLimit,
                                    bIsPoliceRoadBlock,
                                    VTYPE_BOAT,
                                    (signed int)(15.0f * fNode_SpawnRate),
                                    0);
                  }
                  ++iNodeInfo_InternalNodesCount;
                  if ( iNodeInfo_InternalNodesCount == 12) iNodeInfo_InternalNodesCount = -1;
                }
                break;
              default:
                continue;
            }
          }
        }
        else 
          dwSwitchCase = 0;
      }
      else{
        if      (szLine[0] == 'i' && szLine[1] == 'n' && szLine[2] == 's' && szLine[3] == 't') dwSwitchCase = 1;
        else if (szLine[0] == 'z' && szLine[1] == 'o' && szLine[2] == 'n' && szLine[3] == 'e') dwSwitchCase = 2;
        else if (szLine[0] == 'c' && szLine[1] == 'u' && szLine[2] == 'l' && szLine[3] == 'l') dwSwitchCase = 3;
        else if (szLine[0] == 'o' && szLine[1] == 'c' && szLine[2] == 'c' && szLine[3] == 'l') dwSwitchCase = 4;
        else if (szLine[0] == 'p' && szLine[1] == 'i' && szLine[2] == 'c' && szLine[3] == 'k') dwSwitchCase = 5;
        else if (szLine[0] == 'p' && szLine[1] == 'a' && szLine[2] == 't' && szLine[3] == 'h') dwSwitchCase = 6;
      }
    }
  }
  CFileMgr::CloseFile(hFile);
  CDebug::DebugAddText("Finished loading IPL\n");

  //Dump pCarPathInfos
}

#endif

__declspec(naked) int CFileLoader::AddOcclusions(float fMidX, 
                                            float fMidY, 
                                            float fBottomZ, 
                                            float fWidthX, 
                                            float fWidthY, 
                                            float fBoxHeight, 
                                            float fRotation)
{
    __asm jmp dwFunc_CFileLoader__AddOcclusions
}
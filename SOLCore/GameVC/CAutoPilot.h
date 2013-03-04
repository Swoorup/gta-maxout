#include "../stdinc.h"
#ifndef __CAUTOPILOT_H
#define __CAUTOPILOT_H

#pragma pack(push, 1)
class CAutoPilot {
public: 
  int m_dwCurrentNode;
  int m_dwNextNode;
  int m_dwPrevNode;
  int m_dwCurrentSpeedScaleFactor;
  int m_dwNextSpeedScaleFactor;
  int m_dwCurrentCarLinkNode;
  int m_dwNextCarLinkNode;
  int m_dwPrevCarLinkNode;
  int m_snGettingNewCommandTimeStamp;
  int m_snUnknownTimeStamp;
  char m_bytePrevDirectionScale;
  char m_byteCurrentDirectionScale;
  char m_byteNextDirectionScale;
  char m_byteCurrentLanes;
  char m_byteNextLanes;
  char m_TrafficBehaviour;
  char m_DriverBehaviour;
  char m_eSimpleAction;
  int m_simple_action_time;
  float m_fCurrentSpeed;
  char m_nMaxSpeed;
  char m_byteSpeedLimit;
  char m_gap_3A[2];
  int m_field_3C;
  char m_flags;
  char m_field_41;
  short m_field_42;
  CVector m_vecTargetPoint;
  CPathNode* m_pIntermediateRouteList[8];
  short m_nRouteListStep;
  char m_gap_72[2];
  
  void RemoveOnePathNode(void);
  void ModifySpeed(float fModSpeed);
};
#pragma pack(pop)

#endif
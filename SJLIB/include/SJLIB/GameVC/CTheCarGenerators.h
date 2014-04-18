#ifndef CTHECARGENERATORS_H
#define CTHECARGENERATORS_H

//------------------------------------------------------------------
// Documentation about the CarGenerator opcode are available in
// Deji's site. Info on Car Colors for Vice city is available here:
// Car Colors: http://www.masterw3.com/gta_vice_city_car_colors.htm
//------------------------------------------------------------------

#include "SJLIB/stdinc.h"
/* push current alignment to stack and set alignment to 1 byte boundary*/
#pragma pack(push, 1)

struct CCarGenerator{
  int m_iModelID;
  CVector m_vecCarPosition;
  float m_fAngle;
  short m_sPrimaryColor;
  short m_sSecondaryColor;
  char m_cForceSpawn;
  char m_AlarmProbability;
  char m_cDoorLock;
  _pad(__fxpad00, 1);
  short m_sMinimumDelay;
  short m_sMaximumdelay;
  int m_iTime;
  int m_iProcessedVehicleHandle;
  short m_nVehiclesToGenerate;
  char m_cField_2A;
  _pad(__fxpad01, 1);
};
/* restore original alignment from stack */
#pragma pack(pop)


int CTheCarGenerators__CreateCarGenerator(float fX, float fY, float fZ, float fangle, int iModelID, int primaryCol, int secondaryCol, unsigned char forceSpawn, unsigned char alarmProbability, char doorLockProbability, int minDelay, int maxDelay);
void CCarGenerator__SwitchOn(int index);
void CCarGenerator__SwitchOff(int index);

#endif
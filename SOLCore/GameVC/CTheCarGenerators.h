//To-do
//Create Destructor
#ifndef CTHECARGENERATORS_H
#define CTHECARGENERATORS_H

#include "..\StdInc.h"
//see documentation In Deji's site
//CarColors http://www.masterw3.com/gta_vice_city_car_colors.htm

#pragma pack(push)  /* push current alignment to stack */
#pragma pack(1)     /* set alignment to 1 byte boundary */

struct CCarGenerator{
  int modelID;
  RwV3d pos;
  float angle;
  short primcolor;
  short secondaryColor;
  char forceSpawn;
  char AlarmProbability;
  char doorLock;
  char gap_1B[1];
  short mindelay;
  short maxdelay;
  int time;
  int ProcessedVehicleHandle;
  short numOfVehiclesToGenerate;
  char field_2A;
  char __padding;
};
#pragma pack(pop)   /* restore original alignment from stack */



int CTheCarGenerators__CreateCarGenerator(float fX, float fY, float fZ, float fangle, int iModelID, int primaryCol, int secondaryCol, unsigned char forceSpawn, unsigned char alarmProbability, char doorLockProbability, int minDelay, int maxDelay);
void CCarGenerator__SwitchOn(int index);
void CCarGenerator__SwitchOff(int index);

#endif
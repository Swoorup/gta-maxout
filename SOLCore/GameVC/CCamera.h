#ifndef __CCAMERA_H
#define __CCAMERA_H

#include "../StdInc.h"
#pragma pack(push, 1)

class CCamera {
public:
  _pad(__fxpad00, 0x820);
  CMatrix field_820;
  char cameraInFreeMode;
  _pad(__fxpad02, 7);
  CMatrix viewMatrix;
  RwV3d field_8B8;
  RwV3d field_8C4;
  RwV3d field_8D0;
  RwV3d field_8DC;
  RwV3d field_8E8;
  RwV3d field_8F4;
  RwV3d field_900;
  _pad(__fxpad03, 0x5C);
};
#pragma pack(pop)
#endif
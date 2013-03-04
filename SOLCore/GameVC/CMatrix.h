#ifndef __CMATRIX_H
#define __CMATRIX_H

#include "../StdInc.h"
#pragma pack(push, 1)

class CMatrix {
public:
  CVector vLookRight;
  int __fxpad01;
  CVector vLookAt;
  int __fxpad02;
  CVector vLookUp;
  int __fxpad03;
  CVector vPos;
  int __fxpad04;
  int pAttached;
  int bDeleteOnDetach;
};

#pragma pack(pop)
#endif
#ifndef __CMATRIX_H
#define __CMATRIX_H

#include "../StdInc.h"
#pragma pack(push, 1)

class CMatrix {
public:
  RwMatrix rwMatrix;
  void *matrixPtr;
  int haveRwMatrix;
};

#pragma pack(pop)
#endif
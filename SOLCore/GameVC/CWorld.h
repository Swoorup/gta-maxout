#ifndef __CWORLD_H
#define __CWORLD_H

#include "../StdInc.h"

class CWorld{

public:
    static bool GetIsLineOfSightClear(CVector *a, CVector *b,unsigned char cc , unsigned char dc , unsigned char ec , unsigned char fc, unsigned char gc, unsigned char hcc, unsigned char ic);
};

#endif
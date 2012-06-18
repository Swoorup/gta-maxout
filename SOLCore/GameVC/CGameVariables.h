#ifndef __CGAMEVARIABLES_H
#define __CGAMEVARIABLES_H

#include "../StdInc.h"

class CGameVariables {
private:
    static float* VAR_ms_fFarClipZ;
    static float* VAR_ms_fNearClipZ;
public:
    static inline float GetFarClipZ() {return *VAR_ms_fFarClipZ;};
    static inline float GetNearClipZ() {return *VAR_ms_fNearClipZ;};
};

#endif

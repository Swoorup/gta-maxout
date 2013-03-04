#ifndef __CGAMEVARIABLES_H
#define __CGAMEVARIABLES_H

#include "../stdinc.h"
#include "pathfinding.h"

extern CPathFind* pThePaths;

class CGameVariables {
private:
    static float* VAR_ms_fFarClipZ;
    static float* VAR_ms_fNearClipZ;
    static unsigned int* VAR_CTimer_m_snTimeInMilliseconds;
public:
    static inline float GetFarClipZ() {return *VAR_ms_fFarClipZ;};
    static inline float GetNearClipZ() {return *VAR_ms_fNearClipZ;};
    static inline unsigned int GetTimeInMilliseconds() {return *VAR_CTimer_m_snTimeInMilliseconds;};
    static inline CPathFind* GetPathFind() {return pThePaths;};
};

#endif

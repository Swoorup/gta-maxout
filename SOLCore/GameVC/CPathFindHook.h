#ifndef __CPATHFINDHOOK_H
#define __CPATHFINDhOOK_H

#include "../StdInc.h"

class CAutoPilotHook;

class CPathFindHook : public CSingleton <CPathFindHook> {
private:
    CAutoPilotHook* m_pAutoPilotHook;
    void RemoveHook(void);
public:
    CPathFindHook();
    ~CPathFindHook();

    void ApplyHook(void);
};

#endif
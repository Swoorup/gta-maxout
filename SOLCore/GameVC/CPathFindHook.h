class CPathFindHook;

#ifndef __CPATHFINDHOOK_H
#define __CPATHFINDhOOK_H

#include "../StdInc.h"

class CPathFindHook : public CSingleton < CPathFindHook >
{
private:
    void RemoveHook(void);
public:
    CPathFindHook();
    ~CPathFindHook();

    void ApplyHook(void);
};

#endif
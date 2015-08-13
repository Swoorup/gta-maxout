class CGameHookManager;

#ifndef __CGAMEHOOKMANAGER_H
#define __CGAMEHOOKMANAGER_H

#include "SJLIB/stdinc.h"

class CGameHookManager : public CSingleton <CGameHookManager>
{
private:
    CPathFindHook* m_pPathFindHook;
    void RemoveHook(void);
public:
    CGameHookManager(void);
    ~CGameHookManager(void);

    void ApplyHook(void);
};

#endif
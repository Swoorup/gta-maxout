class CPathFindHook;

#ifndef __CPATHFINDHOOK_H
#define __CPATHFINDhOOK_H

class CPathFindHook : public CSingleton < CPathFindHook >
{
private:
    void RemoveHook(void);
public:
    CPathFindHook(void);
    ~CPathFindHook(void);

    void ApplyHook(void);
};

#endif
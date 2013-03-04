#ifndef __CPATHFINDHOOK_H
#define __CPATHFINDhOOK_H

#include "../StdInc.h"

class CPathFindHook : public CSingleton <CPathFindHook> {
private:
    void RemoveHook(void);
public:


	void InitPathBuffer(void);
	void DeletePathBuffer(void);

    void ApplyHook(void);
};

#endif
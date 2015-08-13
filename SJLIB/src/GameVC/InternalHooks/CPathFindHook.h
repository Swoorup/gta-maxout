#pragma once

#include "SJLIB/stdinc.h"

class CPathFindHook : public CSingleton <CPathFindHook> {
private:
    void RemoveHook(void);
public:


	void InitPathBuffer(void);
	void DeletePathBuffer(void);

    void ApplyHook(void);
};

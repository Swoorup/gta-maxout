class CAutoPilotHook;

#ifndef __CAUTOPILOTHOOK
#define __CAUTOPILOTHOOK

#include "../stdinc.h"

class CAutoPilotHook:public CSingleton <CAutoPilotHook> {
public:
	void ApplyHookForPaths(void);
};

#endif
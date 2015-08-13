#include "SJLIB/stdinc.h"

#ifndef TIMER_H
#define TIMER_H



#pragma pack(push, 1)
class CTimer
{
public:
	static inline UINT32 get_m_snTimeInMilliseconds()
	{
		return (*(UINT32*)0x974B2C);
	}

	static inline float get_ms_fTimeStep()
	{
		return (*(float*)0x975424);
	}
};

#pragma pack(pop)
#endif
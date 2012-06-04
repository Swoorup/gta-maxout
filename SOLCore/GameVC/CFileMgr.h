#ifndef __CFILEMGR_H
#define __CFILEMGR_H

#include "../StdInc.h"

class CFileMgr{

public:
    static FILE* OpenFile(char const *szFileName, char const *szMode);
    static bool LoadLine(FILE* hFile, char* Buf, size_t MaxCount);
    static int CloseFile(FILE* hFile);
    static int SetDir(const char* szDirectory);
};

#endif
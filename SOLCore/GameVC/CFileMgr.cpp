#include "../StdInc.h"

DWORD dwFunc_CFileMgr__SetDir = 0x48E030;

FILE* CFileMgr::OpenFile(char const *szFileName, char const *szMode){
    return fopen(szFileName, szMode);
}

bool CFileMgr::LoadLine(FILE* hFile, char* Buf, size_t MaxCount){
  if (fgets(Buf, MaxCount, hFile)) return true;
  else return false;
}

int CFileMgr::CloseFile(FILE* hFile){
    return fclose(hFile);
}

int __declspec (naked) CFileMgr::SetDir(const char *szDirectory){
    __asm jmp dwFunc_CFileMgr__SetDir
}
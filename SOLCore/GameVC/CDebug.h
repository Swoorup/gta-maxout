#ifndef __CDEBUG_H
#define __CDEBUG_H

#include "../StdInc.h"
#define CDEBUG_DISPLAY_LINES 15
#define CDEBUG_MAX_CHARACTERS 256

class CDebug{
private:
    static char* m_szTextBuffer[CDEBUG_DISPLAY_LINES];
    static FILE* m_File;
    static class CCustomFont *m_Font;

    CDebug(void);
    ~CDebug(void);
public:
    static void Initialize(void);
    static void DebugAddText(char const *szFormatText, ...);
    static void DebugDisplayText(void);
    static void Shutdown(void);

    static void WriteMessageEvent(char const *szFormatMessage, ...);
    static void WriteErrorEvent(char* pszFunction, char* pszFormat, ...);
    static void WriteWarningEvent(char* pszFunction, char* pszFormat, ...);
};

#endif
        
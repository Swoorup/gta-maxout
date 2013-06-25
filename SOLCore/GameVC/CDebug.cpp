#include "../StdInc.h"

CDebug::CDebug(){
}

CDebug::~CDebug(){
}

FILE* CDebug::m_File = NULL;
CCustomFont* CDebug::m_Font = NULL;
char *CDebug::m_szTextBuffer[CDEBUG_DISPLAY_LINES] = {NULL};

void CDebug::Initialize(void){
    for (int i = 0; i < CDEBUG_DISPLAY_LINES; i++){
        m_szTextBuffer[i] = (char*)malloc(CDEBUG_MAX_CHARACTERS);
        memset(m_szTextBuffer[i], 0, CDEBUG_MAX_CHARACTERS);
    }
    FILE* m_File = fopen("sol_log.txt", "w");
    if(m_File) fclose(m_File);
   // m_Font = new CCustomFont("Calibri", 8, NULL);
    //m_Font->InitObjects();
}

void CDebug::DebugAddText(char const*szFormatText, ...)
{
	/*
    char szDebugText[CDEBUG_MAX_CHARACTERS];

    va_list args;
	va_start(args, szFormatText);
	_vsnprintf(szDebugText,CDEBUG_MAX_CHARACTERS, szFormatText, args);
    szDebugText[CDEBUG_MAX_CHARACTERS - 1] = '\0';
	va_end(args);
	
    for (int i =0; szDebugText[i] != '\0'; i++){
        if (szDebugText[i] == '\n'){
            szDebugText[i] = '\0';
            break;
        }
    }

    m_File = fopen("log.txt", "a+");
	fprintf(m_File, "DBG: %s\n", szDebugText);
    fclose(m_File);

    OutputDebugStringA(szDebugText);

    if (m_Font == NULL) return;
    //swap pointers and store message at the last buffer
    char *szTemp = m_szTextBuffer[0];
    for (int i = 0; i < CDEBUG_DISPLAY_LINES; i++){
        if (i == CDEBUG_DISPLAY_LINES - 1) 
            m_szTextBuffer[i] = szTemp;
        else 
        m_szTextBuffer[i] = m_szTextBuffer[i+1];
    }
    strcpy(m_szTextBuffer[CDEBUG_DISPLAY_LINES - 1], szDebugText);
	*/
}

void CDebug::DebugDisplayText(void){
	//    if (m_Font == NULL ) return;
	//    for (int i = 0; i<CDEBUG_DISPLAY_LINES; i++)  
	//        m_Font->DrawText(10.0f, 50.0f + i*10.0f, 0xFFFFFFFF,m_szTextBuffer[i],NULL);
	    
	//    RwV3d* playerPos;
	//    playerPos = FindPlayerCentreOfWorld_NoSniperShift();
	//    
	//    char PositionStrBuf[256];
	//sprintf(PositionStrBuf,"Current Position: %f %f %f",playerPos->x,playerPos->y,playerPos->z);
	//m_Font->DrawText(10.0f, 30.0f,0xFFFFFFFF,PositionStrBuf,NULL);
}

void CDebug::Shutdown(void){
    for (int i = 0; i < CDEBUG_DISPLAY_LINES; i++)
        free(m_szTextBuffer[i]);
    fclose(m_File);
    delete m_Font;

}

void CDebug::WriteMessageEvent(char const *szFormatMessage, ...){
    char szErrorMsg[2048];

	va_list args;
	va_start(args, szFormatMessage);
	vsprintf(szErrorMsg, szFormatMessage, args);
	va_end(args);

    m_File = fopen("sol_log.txt", "a+");
    fprintf(m_File, "MSG: %s\n", szErrorMsg);
    fclose(m_File);
}

void CDebug::WriteErrorEvent(char* pszFunction, char* pszFormat, ...) {
	char szErrorMsg[2048];

	va_list args;
	va_start(args, pszFormat);
	vsprintf(szErrorMsg, pszFormat, args);
	va_end(args);

    m_File = fopen("sol_log.txt", "a+");
    fprintf(m_File, "Error in %s: %s\n", pszFunction, szErrorMsg);
    fclose(m_File);
}

void CDebug::WriteWarningEvent(char* pszFunction, char* pszFormat, ...) {
	char szErrorMsg[2048];

	//if(!bLogWarnings) false;

	va_list args;
	va_start(args, pszFormat);
	vsprintf(szErrorMsg, pszFormat, args);
	va_end(args);

    m_File = fopen("sol_log.txt", "a+");
    fprintf(m_File, "Warning in %s: %s\n", pszFunction, szErrorMsg);
    fclose(m_File);
}
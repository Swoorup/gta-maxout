#include "SJLIB/stdinc.h"

#pragma comment (lib, "d3dx8.lib")
char szSOLIcon[] = "Icons//SOL.ico";
using namespace HookSystem;

CGameHookManager* g_pGameHooks;

void SetGameWindowName(const char* szWindowName)
{
	CMemory::InstallPatch<const char*>(0x602D36, szWindowName);
}

#include <dbghelp.h>
#include <shellapi.h>
#include <shlobj.h>
#include <Strsafe.h>
#pragma comment(lib, "DbgHelp.lib")

bool _cdecl except_handler(	_EXCEPTION_RECORD* excRecord, 
							_EXCEPTION_REGISTRATION_RECORD* excRec, 
							_CONTEXT* excContext)
{
	if ( excRecord->ExceptionFlags & 0x66 )
	{
	    return true;
	}
	else
	{

		static _EXCEPTION_POINTERS ep;
		ep.ContextRecord = excContext;
		ep.ExceptionRecord = excRecord;
		//GenerateDump(&ep);
		char Text[1024];
	    if ( excRecord->ExceptionCode == 0xE06D7363 )
		{
			_asm mov eax, 6782E0h
			_asm call eax
		}
		sprintf(
		Text,
		"Unhandled exception: %08x\nAt address:          %08x\n",
		excRecord->ExceptionCode,
		excContext->Eip);
		MessageBoxA(0, Text, "Unhandled Exception", 8192u);
		return true;
	}
	return true;
}

LONG WINAPI lpTopLevelExceptionFilter(_EXCEPTION_POINTERS* ep)
{
	FILE* fp = fopen("errorlog.txt", "w");
	_CONTEXT* context = ep->ContextRecord;
	fprintf(fp, "Address: %08X error\n", context->Eip);
	fprintf(fp, "Stack: \n");
	void* esp = (void*)context->Esp;
	for (int i = 100; i; i--) 
	{
		if (IsBadReadPtr(esp, 4))
			fprintf(fp, "Bad stack address %08X\n", &esp);
		else
			fprintf(fp, "%08X\n", *(DWORD**)esp);
		esp = (char*)esp + 4;
	}
	fclose(fp);
	return 0;
}


BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	CPathFindHook pPathFindHook;
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
            //g_pGameHooks = new CGameHookManager();
           // g_pGameHooks->ApplyHook();

	
	if(*(uint8_t*)0x5ABA07 != 0x57) 
	{
		D3D8HookInit(false);
		HookSectorList();
		pPathFindHook.InitPathBuffer();
		pPathFindHook.ApplyHook();
	
		HookSystem::InstallFnByJump(0x677E40, except_handler);
        //if ( IconHandle != NULL) SetClassLong(pPresentationParameters->hDeviceWindow, GCL_HICON, (LONG)IconHandle);

          //D3D8HookInit(true);
            
            //Apply Patches
           //PatchVehicleLimits();
            //PatchMiscData();//PASSED
            //PatchRadar(FALSE);//PASSED
        PatchWater();//PASSED MINOR REVISION NEEDED
            //PatchMapMenu(); 
            
            //ApplyCustomPathPatch();
            //InstallFileLoaderHooks();

			CMemory::InstallPatch<unsigned char>(0x5ABA07, 0x57);
		}
		else
		{
			// avoid unloading DLL by loading it again
			// avoid deadlocks to the executable by loading it as an flt
		
				
			
		}
		SetUnhandledExceptionFilter(lpTopLevelExceptionFilter);
		LoadLibraryA("SJLib.asi");
        break;
    case DLL_PROCESS_DETACH:
       //if (g_pGameHooks){
       //     delete g_pGameHooks;
       //    g_pGameHooks = NULL;
       // }
		break;
    }
    return TRUE;
}
#include "StdInc.h"

#pragma comment (lib, "d3dx8.lib")
char szWindowName[] = "GTA: State Of Liberty";
char szSOLIcon[] = "Icons//SOL.ico";

CGameHookManager* g_pGameHooks;

BOOL WINAPI DllMain(HINSTANCE hinstDLL,
                    DWORD fdwReason,
                    LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            g_pGameHooks = new CGameHookManager();
            g_pGameHooks->ApplyHook();
            CMemory::InstallPatch<char*>(0x602D36, szWindowName);
            //if ( IconHandle != NULL) SetClassLong(pPresentationParameters->hDeviceWindow, GCL_HICON, (LONG)IconHandle);
            //D3D8HookInit(false);
            
            //Apply Patches
            //PatchVehicleLimits();
            PatchMiscData();//PASSED
            PatchRadar(FALSE);//PASSED
            PatchWater();//PASSED MINOR REVISION NEEDED
            //PatchMapMenu(); 
            
            //ApplyCustomPathPatch();
            //InstallFileLoaderHooks();
            break;

        case DLL_PROCESS_DETACH:
            if (g_pGameHooks){
                delete g_pGameHooks;
                g_pGameHooks = NULL;
            }
            break;
    }
    return TRUE;
}
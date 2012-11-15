#include "Main.h"
#include "Utils.h"
#include "resource.h"
#include <shlwapi.h>
#include <stdio.h>


#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN     // Exclude all uncommon functions from windows.h to reduce executable size
#define _WIN32_WINNT 0x0400     // So we can use IsDebuggerPresent()
#include <windows.h>
#endif

#include <shlobj.h>
#include <Psapi.h>

bool TerminateGTAIfRunning ( void )
{
    DWORD dwProcessIDs[250];
    DWORD pBytesReturned = 0;
    unsigned int uiListSize = 50;
    if ( EnumProcesses ( dwProcessIDs, 250 * sizeof(DWORD), &pBytesReturned ) )
    {
        for ( unsigned int i = 0; i < pBytesReturned / sizeof ( DWORD ); i++ )
        {
            // Open the process
            HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, dwProcessIDs[i]);
            if ( hProcess )
            {
                HMODULE pModule;
                DWORD cbNeeded;
                if ( EnumProcessModules ( hProcess, &pModule, sizeof ( HMODULE ), &cbNeeded ) )
                {
                    char szModuleName[500];
                    if ( GetModuleFileNameEx( hProcess, pModule, szModuleName, 500 ) )
                    {
                        if ( strcmpi ( szModuleName + strlen ( szModuleName ) - strlen ( "gta_vc.exe" ), "gta_vc.exe" ) == 0 )
                        {
                            if ( MessageBox ( 0, "An instance of gta-vc.exe is already running. It needs to be terminated before GTA: SOL can be started. Do you want to do that now?", "Information", MB_YESNO | MB_ICONQUESTION ) == IDYES )
                            {
                                TerminateProcess ( hProcess, 0 );
                                CloseHandle ( hProcess );
                                return true;
                            }

                            return false;
                        } 
                    }
                }

                // Close the process
                CloseHandle ( hProcess );
            }
        }
    }

    return true;
}



void GetAppPath ( char * szBuffer, size_t sizeBufferSize )
{
    // Get current module full path
    GetModuleFileName ( NULL, szBuffer, sizeBufferSize - 1 );

    // Strip the module name out of the path.
    PathRemoveFileSpec ( szBuffer );

    // Save to a temp registry key
}



int GetGamePath ( char * szBuffer, size_t sizeBufferSize )
{
    WIN32_FIND_DATA fdFileInfo;

    GetAppPath(szBuffer, 1024);
	
    char szExePath[MAX_PATH];
    sprintf ( szExePath, "%s\\gta-vc.exe", szBuffer );

    if ( INVALID_HANDLE_VALUE != FindFirstFile( szExePath, &fdFileInfo ) )
    {
        //WriteRegistryStringValue ( HKEY_CURRENT_USER, "Software\\Multi Theft Auto: San Andreas", "GTA:SA Path", szBuffer );
    }
    else
    {
        return 0;
    }
    return 1;
}

int WINAPI WinMain ( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{

    bool validate = false;

    if ( !TerminateGTAIfRunning () )
    {
        MessageBox ( 0, "GTA: State Of Liberty couldn't start because an another instance of GTA is running.", "Error", MB_ICONERROR );
        return 0;
    }


    WIN32_FIND_DATA fdFileInfo;
    PROCESS_INFORMATION piLoadee;
    STARTUPINFO siLoadee;

    char szGTAPath[MAX_PATH];

	int iResult;

	iResult = GetGamePath (szGTAPath, MAX_PATH );
	if ( iResult == 0 ) {
		MessageBox ( 0, "Launcher is located on invalid SOL installation Directory. Please move the Launcher to the SOL installation directory.", "Error!", MB_ICONEXCLAMATION | MB_OK );
        return 5;
	}
	else if ( iResult == -1 ) {
		MessageBox ( 0, "The path to your installation of GTA: San Andreas contains unsupported (unicode) characters. Please move your Grand Theft Auto: State Of Liberty installation to a compatible path that contains only standard ASCII characters and reinstall Multi Theft Auto: San Andreas.", "Error!", MB_ICONEXCLAMATION | MB_OK );
		return 5;
	}

    

    // If we aren't compiling in debug-mode...
    HWND hwndSplash = NULL;
    #ifndef MTA_DEBUG
	#ifndef MTA_ALLOW_DEBUG
        // Are we debugged? Quit... if not compiled debug
        if ( IsDebuggerPresent () )
        {
            // Exit without a message so it'll be a little harder for the hacksors
            ExitProcess(-1);
        }

        // Show the splash and wait 2 seconds
        hwndSplash = CreateDialog ( hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, 0 );
        Sleep ( 1000 );
	#endif
    #endif


    // Basic check for the data files
    {
        char szFileName[MAX_PATH] = {'\0'};
        _snprintf ( szFileName, MAX_PATH, "%s\\SOL\\Scene.dat", szGTAPath );

        // Check if vorbis.ax exists
        if ( INVALID_HANDLE_VALUE == FindFirstFile ( szFileName, &fdFileInfo ) )
        {
            if ( hwndSplash )
                DestroyWindow ( hwndSplash );
            MessageBox( NULL, "Load failed.  Please ensure that "
                              "the data files have been installed "
                              "correctly.", "Error!", MB_ICONEXCLAMATION|MB_OK );
            return 1;
        }
    }

    /*// Check for client file
    {
        char szSceneFileName[MAX_PATH] = {'\0'};
        _snprintf ( szSceneFileName, MAX_PATH, "%s\\%s", szGTAPath, CHECK_DM_CLIENT_NAME );

        if ( INVALID_HANDLE_VALUE == FindFirstFile ( szSceneFileName, &fdFileInfo ) )
        {
            if ( hwndSplash )
                DestroyWindow ( hwndSplash );
            MessageBox( NULL, "Load failed.  Please ensure that '"
                              CHECK_DM_CLIENT_NAME "' is installed "
                              "correctly.", "Error!", MB_ICONEXCLAMATION|MB_OK );
            return 1;
        }
    }*/


    // Grab the Exe Path
    char szGTAEXEPath[MAX_PATH];
    strcpy ( szGTAEXEPath, szGTAPath );
    strcat ( szGTAEXEPath, "\\" );
    strcat ( szGTAEXEPath, SOL_GTAEXE_NAME ) ;

   
    // Make sure the gta executable exists
    SetCurrentDirectory ( szGTAPath );
    if ( INVALID_HANDLE_VALUE == FindFirstFile( szGTAEXEPath, &fdFileInfo ) )
    {
        if ( hwndSplash )
            DestroyWindow ( hwndSplash );
        char szMsg [ 2*MAX_PATH ];
        _snprintf ( szMsg, sizeof(szMsg), "Load failed. Could not find gta-vc.exe in %s.", szGTAPath );
        MessageBox( 0, szMsg, "Error!", MB_ICONEXCLAMATION|MB_OK );
        return 1;
    }

    // Launch GTA using CreateProcess
    memset( &piLoadee, 0, sizeof ( PROCESS_INFORMATION ) );
    memset( &siLoadee, 0, sizeof ( STARTUPINFO ) );
    siLoadee.cb = sizeof ( STARTUPINFO );

    // Start GTA
    if ( 0 == CreateProcess ( szGTAEXEPath,
                              lpCmdLine,
                              NULL,
                              NULL,
                              FALSE,
                              CREATE_SUSPENDED,
                              NULL,
                              szGTAPath,
                              &siLoadee,
                              &piLoadee ) )
    {
        if ( hwndSplash )
            DestroyWindow ( hwndSplash );
        MessageBox( NULL, "Could not start Grand Theft Auto: State Of Liberty.  "
                          "Please try restarting, or if the problem persists,"
                          "contact SOL developers at www.stateofliberty.com.", "Error!", MB_ICONEXCLAMATION|MB_OK );
        return 2;
    }

    char szCoreDLL[MAX_PATH] = {'\0'};
    _snprintf ( szCoreDLL, MAX_PATH, "%s\\%s", szGTAPath, SOL_DLL_NAME );

    // Check if the core (solcore.dll exists)
    if ( INVALID_HANDLE_VALUE == FindFirstFile ( szCoreDLL, &fdFileInfo ) )
    {
        if ( hwndSplash )
            DestroyWindow ( hwndSplash );
        MessageBox( NULL, "Load failed.  Please ensure that "
                          "the file SOLcore.dll is in the modules "
                           "directory within the SOL root directory.", "Error!", MB_ICONEXCLAMATION|MB_OK );
        // Kill GTA and return errorcode
        TerminateProcess ( piLoadee.hProcess, 1 );
        return 1;
    }


    // Change the search path and current directory
    char szOrigPath [ 1024 ];
    DWORD dwGetPathResult = GetEnvironmentVariable ( "Path", szOrigPath, sizeof(szOrigPath) );
    if ( dwGetPathResult == 0 || dwGetPathResult >= sizeof(szOrigPath) )
    {
        if ( hwndSplash )
            DestroyWindow ( hwndSplash );
        MessageBox( NULL, "Load failed.  Unable to get the current Path environment variable.",
                          "Error!", MB_ICONEXCLAMATION|MB_OK );
        // Kill GTA and return errorcode
        TerminateProcess ( piLoadee.hProcess, 1 );
        return 1;
    }

    // NO Point Loading this here, just to check for these stuffs 
    // Check if the core can be loaded - failure may mean msvcr90.dll or d3dx9_40.dll etc is not installed
    /*HMODULE hCoreModule = LoadLibrary( szCoreDLL );
    if ( hCoreModule == NULL )
    {
        if ( hwndSplash )
            DestroyWindow ( hwndSplash );
        MessageBox( NULL, "Load failed.  Please ensure that \n"
                            "Microsoft Visual C++ 2008 SP1 Redistributable Package (x86) \n"
                            "and the latest DirectX is correctly installed.", "Error!", MB_ICONEXCLAMATION|MB_OK );
        // Kill GTA and return errorcode
        TerminateProcess ( piLoadee.hProcess, 1 );
        return 1;
    }*/
    
    // Inject the core into GTA
    RemoteLoadLibrary ( piLoadee.hProcess, szCoreDLL );
    
    // Resume execution for the game.
    ResumeThread ( piLoadee.hThread );

    if ( hwndSplash )
        DestroyWindow ( hwndSplash );

	#ifdef MTA_DEBUG
	WaitForSingleObject ( piLoadee.hProcess, INFINITE );
	#endif

    // Cleanup and exit.
    CloseHandle ( piLoadee.hProcess );
    CloseHandle ( piLoadee.hThread );

    // Success
    return 0;
}

/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto v1.0
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        loader/Main.h
*  PURPOSE:     MTA loader
*  DEVELOPERS:  Ed Lyons <eai@opencoding.net>
*               Christian Myhre Lundheim <>
*               Cecill Etheredge <ijsf@gmx.net>
*
*  Multi Theft Auto is available from http://www.multitheftauto.com/
*
*****************************************************************************/

#ifndef __MAIN_H
#define __MAIN_H

#define SOL_GTAEXE_NAME "gta-vc.exe"

#ifdef MTA_DEBUG
    #define MTA_DLL_NAME            "core_d.dll"
    #define CHECK_DM_LUA_NAME       "mods\\deathmatch\\lua5.1d.dll"
    #define CHECK_DM_CLIENT_NAME    "mods\\deathmatch\\Client_d.dll"
#else
    #define SOL_DLL_NAME            "SOLcore.dll"
    #define CHECK_DM_LUA_NAME       "mods\\deathmatch\\lua5.1.dll"
    #define CHECK_DM_CLIENT_NAME    "mods\\deathmatch\\Client.dll"
#endif

#endif
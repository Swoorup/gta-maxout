#pragma once

#define _CRT_SECURE_NO_WARNINGS
//enable/disable defines
#define INSTALL_PATCH_FOR_VCPATH_INSTANCE

// standard include directives
#include <Windows.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <functional>
#include <typeinfo>
#include <vector>

// directx
#include <d3d8.h>
#include <d3dx8.h>

// include ASMJIT
//#include <asmjit/asmjit.h>
#include <asmjit/x86.h>

// utilies directives for general usuage
#include "CSingleton.h"
#include "hooksystem.h"
#include "utils.h"
#include "main.h"

// hooks for the game
#include "GameVC/InternalHooks/dxd8_system.h"
#include "GameVC/InternalHooks/CPathFindHook.h"
#include "GameVC/InternalHooks/CGameHookManager.h"
#include "GameVC/InternalHooks/sectorlist_hooks.h"


#include "GamePatches.h"

// game sdk includes
#include "GameVC/CVector.h"
#include "GameVC/CVector2D.h"
#include "GameVC/CCurves.h"
#include "GameVC/CGeneral.h"

// game definations and new patches includes
#include "GameVC/waterlevel.h"
#include "GameVC/physical.h"
#include "GameVC/entity.h"
#include "GameVC/automobile.h"
#include "GameVC/vehicle.h"
#include "GameVC/timer.h"
#include "GameVC/weather.h"
#include "GameVC/trafficlights.h"

#include "GameVC/CGameVariables.h"
#include "GameVC/RenderWare.h"
#include "GameVC/CMatrix.h"
#include "GameVC/world.h"
#include "GameVC/CCamera.h"
#include "GameVC/GameVC.h"
#include "GameVC/CFileMgr.h"
#include "GameVC/CDebug.h"
#include "GameVC/CFileLoader.h"
#include "GameVC/CTheZones.h"
#include "GameVC/CCullZones.h"
#include "GameVC/pathfinding.h"
#include "GameVC/CTheCarGenerators.h"
#include "GameVC/CFont.h"
#include "GameVC/CTxdStore.h"
#include "GameVC/CSprite2D.h"
#include "GameVC/CommonDefinations.h"
#include "GameVC/CAutoPilot.h"
#include "GameVC/CCarCtrl.h"
#include "GameVC/CPed.h"

//#pragma comment(lib,"d3d8.lib")
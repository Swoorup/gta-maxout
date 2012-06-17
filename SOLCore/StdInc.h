#pragma once

#include "main.h"

// standard include directives for C++
#include <Windows.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

// utilies directives for general usuage
#include "CSingleton.h"
#include "CMemory.h"
#include "Utilities.h"
#include "D3D8Hook.h"
#include "CCustomFont.h"

// to be disengaged
#include "PathBoundariesHack.hpp"
#include "GamePatches.h"

// game definations and new patches includes
#include "GameVC\CPathFindHook.h"
#include "GameVC\CGameHookManager.h"
#include "GameVC\RenderWare.h"
#include "GameVC\CMatrix.h"
#include "GameVC\CWorld.h"
#include "GameVC\CCamera.h"
#include "GameVC\GameVC.h"
#include "GameVC\CFileMgr.h"
#include "GameVC\CDebug.h"
#include "GameVC\CFileLoader.h"
#include "GameVC\CTheZones.h"
#include "GameVC\CCullZones.h"
#include "GameVC\CPathFind.h"
#include "GameVC\CTheCarGenerators.h"
#include "GameVC\CFont.h"
#include "GameVC\CTxdStore.h"
#include "GameVC\CSprite2D.h"
#include "main.h"
#include "PathBoundariesHack.hpp"
#include "CCustomPathHooks.h"

#define ARRLEN(a) (sizeof(a)/sizeof(a[0])) 
#define PATHLIMITMUL 10

float f8xDivider = 0.125f;
float fPathShiftX = 0.0f;
float fPathShiftY = 0.0f;
float fPathShiftZ = 0.0f;
/*void PatchPathBounds()
{
    CMemory::InstallPatch<float>(0x687C7C,1.0f); //Stop reading with x0.125
    CMemory::InstallPatch<float>(0x691f28,1.0f); //Stop reading

    //Ped and Car Paths read Hack
    CMemory::InstallPatch<float>(0x687CD4, 1.0f); //Stop writing with x8
    
    CMemory::InstallPatch<float>(0x687C88, 1.0f); //Paths.ipl 1/16 multiplier remove

    //CarPathReading Patch
    CMemory::InstallPatch<float>(0x687050, 1.0f);

    //Car Lanes align
    CMemory::InstallPatch<float>(0x687C74, 0.1f);

    //Car Median Write patch
    //CMemory::InstallPatch<float>(0x687CD0, 1.44f);

    //Car Cheat Spawn Patch
    CMemory::InstallPatch<float>(0x68F2A8, 1.0f);

    //Car Spawning but speeding too fast patch
    CMemory::InstallPatch<float>(0x686DEC, 0.9999f);

    //Yet Another Patch
    CMemory::InstallPatch<float>(0x6912E4, 1.0f);

    //1/16 Player vehicle function patch
    CMemory::InstallPatch<float>(0x687180, 0.1f);

    //Peds Median Patch
    //CMemory::InstallPatch<float>(0x687CD8, 3.0f);

    //Ped Path Search Radius Hack Dirty One
    //CMemory::InstallPatch<float>(0x687CF8, 999999.0f);

};*/

/*****************************************************************************/
/** Paths Structure and Function Stubs and Mappings   	                    **/
/*****************************************************************************/
struct CPathNode0        //size = 20
{
  __int16 field_0;      //0x0
  __int16 field_2;      //0x2
  __int16 x;            //0x4
  __int16 y;            //0x6
  __int16 z;            //0x8
  WORD field_0A;        //0xA
  __int16 nextPointIndex;   //0xC
  char median;          //0xE
  char gap_F;           //0xF
  unsigned __int8 flags;//0x10
  char flag1;           //0x11
  char flag2;           //0x12
  char field_13;        //0x13
};

struct CSearchNode //size = 12
{
  __int16 X;
  __int16 Y;
  __int16 RouteIndex;
  char field06;
  char field07;
  char LRlanes;
  char field09;
  __int16 field0A;
};
/*
#pragma pack(push, 1)
struct GlobalMap
{
 CPathNode AttachedPaths[9650];   
  CSearchNode SearchPaths[3500];
  void *pTreadables[1250];
  __int16 pointsInfo[20400];
  __int8 tanAngle[20400];
  __int16 SearchPointsInfo[20400];
  int m_nAttachedNodes;
  int m_nAttachedCarNodes;
  int totalVehicleRoutePointIndexm;
  __int16 short_nTreadables;
  WORD totalPointInfoIndex;
  DWORD totalSearchPoints;
  DWORD field_53804;
  char field_53808[2];
  CPathNode unkPathNode[512];

};
#pragma pack(pop)
*/
struct GlobalMapData
{
    CPathNode0 Paths[9650 * PATHLIMITMUL];           // 0x00000
    CSearchNode SearchPaths[3500 * PATHLIMITMUL];   // 0x2F1E8
    int InstBuildings[1250 * PATHLIMITMUL];         // 0x395F8
    __int16 pointsInfo[20400 * PATHLIMITMUL];       // 0x3A980
    __int8 field_448E0[20400 * PATHLIMITMUL];       // 0x448E0
    __int16 SearchPointsInfo[20400 * PATHLIMITMUL]; // 0x49890
    int lastPedRoutePointIndex;                     // 0x537F0
    int lastVehicleRoutePointIndex;                 // 0x537F4
    int totalVehicleRoutePointIndexm;               // 0x537F8
    __int16 numberOfBuildings;                      // 0x537FC
    WORD totalPointInfoIndexm;                      // 0x537FE
    DWORD totalSearchPointsm;                       // 0x53800
    DWORD field_53804;                              // 0x53804
    char field_53808[2];                            // 0x53808
    CPathNode unkPathNode[512 * PATHLIMITMUL];      // 0x5380A
};


DWORD Func_PathsVariableInit = 0x43C170;  //thiscall convention
void PathsVariableInit(GlobalMapData* __globalMapData)
{
    __asm mov ecx, __globalMapData
    __asm call Func_PathsVariableInit
}

DWORD Func_PathsAllocateMemory = 0x4366E0; //stdcall convention
void PathsAllocateMemory(GlobalMapData* __globalMapData) 
{
    __asm mov ecx, __globalMapData
    __asm push 4500 //unused Var
    __asm call Func_PathsAllocateMemory
}

//LOAD PATHS CONTENT BETWEEN THESE TOO

DWORD Func_PreparePathData = 0x43BB40;  //thiscall convention
void PreparePathData(GlobalMapData* __globalMapData)
{
    __asm mov ecx, __globalMapData
    __asm call Func_PreparePathData
}

//Call only IPL data
DWORD Func_CFileLoader_LoadScene = 0x48B050; //cdecl convention
void CFileLoader_LoadScene(char* fileName)
{
    __asm push fileName
    __asm call Func_CFileLoader_LoadScene
    __asm pop ecx
}

/*****************************************************************************/

//Our Path Grids
#define PATHGRIDLIMIT    4

GlobalMapData gPathGridsArray[PATHGRIDLIMIT*PATHGRIDLIMIT]; //4 rows and 3 columns


static uint32_t dwPathDataRefs[] = {
	   0x41C4BD, 0x41C6BD, 0x41C6DD, 0x41CE23, 0x41CECF, 0x41CF21, 0x41CF59, 0x41CF87,
	   0x41D03E, 0x41F015, 0x41F094, 0x41F352, 0x41F844, 0x420DB5, 0x420E10, 0x42112E,
	   0x421168, 0x421427, 0x4214E9, 0x421502, 0x42154E, 0x421565, 0x421AE4, 0x421B1E,
	   0x421FFE, 0x422021, 0x4220CD, 0x422167, 0x422187, 0x4221F3, 0x422333, 0x422428,
	   0x422620, 0x42264E, 0x422782, 0x4227BC, 0x425D7C, 0x425DD6, 0x4272F0, 0x4275DF,
	   0x427B1C, 0x427B5C, 0x427DC1, 0x427E0E, 0x427F5D, 0x4280C0, 0x42859B, 0x4285A8,
	   0x4286CC, 0x4286EE, 0x437375, 0x437396, 0x4373D7, 0x43741A, 0x437431, 0x437477,
	   0x437495, 0x4374C6, 0x4374E7, 0x437529, 0x43758A, 0x4375F5, 0x437616, 0x43763C,
	   0x43765E, 0x43769D, 0x4376D9, 0x4376F7, 0x437725, 0x437746, 0x437769, 0x43778A,
	   0x4377C7, 0x438E96, 0x438EB7, 0x438F3D, 0x439255, 0x439273, 0x439364, 0x439383,
	   0x43C26F, 0x442BB7, 0x442BE3, 0x442E79, 0x442EA7, 0x444475, 0x4444AD, 0x444AB3,
	   0x45335E, 0x453423, 0x45510E, 0x45525E, 0x455297, 0x45842B, 0x458505, 0x45ACCA,
	   0x45ACE4, 0x45AD20, 0x465C2C, 0x465DFE, 0x465FE0, 0x46631A, 0x4666B0, 0x46674D,
	   0x46687A, 0x4668C3, 0x4668FE, 0x466931, 0x48AE89, 0x48B550, 0x48B9E1, 0x48CD10,
	   0x48CD96, 0x48CF49, 0x48D27C, 0x48D474, 0x4A4C08, 0x4A4C12, 0x4A4CE0, 0x4AE993,
	   0x4BD66D, 0x4BD687, 0x4BE6A3, 0x4D4945, 0x4D4AD1, 0x4F9BB5, 0x4FA8EA, 0x4FAB49,
	   0x4FAC36, 0x4FAC5D, 0x4FAEEA, 0x4FB064, 0x4FB42B, 0x506F47, 0x5072E0, 0x50AC91,
	   0x51228C, 0x513E2D, 0x513ED4, 0x513F64, 0x514068, 0x514172, 0x51F6F8, 0x51F859,
	   0x53C2C0, 0x53C391, 0x53C396, 0x61B14E, 0x61CA59, 0x630943, 0x6309DF, 0x630A35,
	   0x63129B, 0x6312D2, 0x41CD94, 0x41D0E0, 0x41D120, 0x41D1E2, 0x41D205, 0x42142E,
	   0x421653, 0x421685, 0x421DD8, 0x421E12, 0x421E4C, 0x44431C, 0x4445A2, 0x4446FD,
	   0x444814, 0x45514B, 0x466357, 0x46646B, 0x4664B1, 0x466779, 0x4AE9EA, 0x4D4975,
	   0x4D4B01, 0x5071D1, 0x50741D, 0x5074A1, 0x507525, 0x5122CF, 0x51F773, 0x41CDA3,
	   0x41D0F1, 0x41D12F, 0x41D1F1, 0x41D219, 0x421445, 0x421664, 0x421696, 0x421DF1,
	   0x421E25, 0x421E61, 0x44437F, 0x4445B3, 0x444721, 0x44482A, 0x455152, 0x466370,
	   0x466480, 0x4664D4, 0x46678E, 0x4AE9F7, 0x4D498A, 0x4D4B16, 0x5071B2, 0x5073FE,
	   0x507482, 0x507506, 0x5122D6, 0x51F754, 0x41CDB4, 0x421460, 0x4445EA, 0x444732,
	   0x444863, 0x455159, 0x466388, 0x466494, 0x4664FB, 0x4AEA07, 0x4D4991, 0x4D4B1D,
	   0x507193, 0x5073DF, 0x507463, 0x5074E7, 0x5122C8, 0x51F735, 0x41CC59, 0x41CC88,
	   0x41CCDE, 0x41CD13, 0x41CE47, 0x41CE6C, 0x41D0C4, 0x420E8E, 0x421521, 0x42157B,
	   0x42161B, 0x42182D, 0x4220F4, 0x422139, 0x422296, 0x4222BE, 0x4223A3, 0x4223CB,
	   0x42251A, 0x42764B, 0x42766E, 0x427D31, 0x427D6F, 0x4355DB, 0x4355FF, 0x43565D,
	   0x43567F, 0x444457, 0x466427, 0x466847, 0x44457A, 0x41CCD1, 0x41D08F, 0x4215DB,
	   0x421FCE, 0x427631, 0x427CCC, 0x427D23, 0x4355BE, 0x435644, 0x4666D5, 0x41C4F7,
	   0x422A24, 0x422AC3, 0x427386, 0x427530, 0x427547, 0x427342, 0x427356, 0x53C320,
	   0x53C334, 0x418DCE, 0x418E4B, 0x41F0D5, 0x41F13D, 0x41F393, 0x41F554, 0x41F8C4,
	   0x421018, 0x42102F, 0x4211C3, 0x42121F, 0x4219A3, 0x4219BA, 0x421B7E, 0x421BE1,
	   0x42281C, 0x422878, 0x425F17, 0x425F6F, 0x42812C, 0x4281BA, 0x42848D, 0x428504,
	   0x444521, 0x444536, 0x465D63, 0x465F33, 0x466123, 0x418D7C, 0x418E2E, 0x41F0EA,
	   0x41F152, 0x41F3A8, 0x41F533, 0x41F889, 0x420FF8, 0x421007, 0x4211B4, 0x421210,
	   0x421983, 0x421992, 0x421B6F, 0x421BD2, 0x42280D, 0x422869, 0x425F06, 0x425F60,
	   0x428117, 0x4281A5, 0x428478, 0x4284EF, 0x4444F7, 0x444508, 0x465D3D, 0x465F0D,
	   0x4660FD, 0x421FF3, 0x42215C, 0x4222D9, 0x4223E6, 0x42768D, 0x465C57, 0x465C6E,
	   0x465E27, 0x465E3E, 0x466009, 0x466020, 0x4666ED, 0x418D55, 0x418DAD, 0x418EEC,
	   0x418F48, 0x41EF7E, 0x41EFF8, 0x41F44E, 0x41F4C8, 0x420F3D, 0x420FA0, 0x4212A0,
	   0x421302, 0x4218C1, 0x421924, 0x421C67, 0x421CCA, 0x422597, 0x4225CB, 0x4228F2,
	   0x422954, 0x425CF4, 0x425D57, 0x427FB1, 0x428033, 0x428275, 0x4282EF, 0x465D73,
	   0x465F43, 0x466133, 0x418DF2, 0x418E7F, 0x418EC6, 0x418F22, 0x41EFAA, 0x41F02B,
	   0x41F47A, 0x41F4F4, 0x420F5D, 0x420FC0, 0x42127A, 0x4212DC, 0x4218E1, 0x421944,
	   0x421C41, 0x421CA4, 0x4228CC, 0x42292E, 0x425D0A, 0x425D6D, 0x427FE5, 0x42805F,
	   0x428243, 0x4282BD, 0x465D4D, 0x465F1D, 0x46610D, 0x420EE9, 0x420F08, 0x42186B,
	   0x42188A, 0x4222E5, 0x4222F2, 0x4223F2, 0x422402, 0x422550, 0x422573, 0x42769C,
	   0x4276AA, 0x435613, 0x435693, 0x41CC66, 0x41CD1D, 0x41CE78, 0x41D0D1, 0x420EAA,
	   0x42152D, 0x421596, 0x42162E, 0x422103, 0x4222A3, 0x4223B0, 0x427655, 0x427D7C,
	   0x4355E5, 0x435667, 0x466437, 0x466853, 0x4669DC, 0x513F4C, 0x51404F, 0x51415A,
	   0x41CC95, 0x41CCEE, 0x41CE53, 0x420EC4, 0x42183E, 0x42214B, 0x4222C8, 0x4223D5,
	   0x422527, 0x427678, 0x427D4C, 0x435609, 0x435689, 0x4444A8, 0x466630, 0x444469,
	   0x4060A5, 0x4060C7, 0x40612A, 0x40614C, 0x4067CC, 0x4067D6, 0x4067F8, 0x4060D7,
	   0x40615C, 0x406808, 0x4060DD, 0x406162, 0x40680E, 0x4060E5, 0x40616A, 0x406816,
	   0x4060EF, 0x406174, 0x406820, 0x4060FC, 0x406181, 0x40682A, 0x406106, 0x40618B,
	   0x406837, 0x466735, 0x466A08, 0x444AA5, 0x466748, 0x4373A6, 0x437406, 0x4374F6,
	   0x437552, 0x437671, 0x437799, 0x438CC0, 0x43C28A, 0x4373B0, 0x43740D, 0x437500,
	   0x43755C, 0x43767B, 0x4377A3, 0x438CB7
	};

RwV2d GlobalCordOffset[PATHGRIDLIMIT * PATHGRIDLIMIT];

void RelocateGlobalMapDataRefs(GlobalMapData* newReference)
{
    uint32_t dwMod;
    uint32_t oldReference = *(uint32_t*)dwPathDataRefs[0];
    for(int i = 0; i < ARRLEN(dwPathDataRefs); i++) {
		if(*((uint32_t*)dwPathDataRefs[i]) < oldReference || *((uint32_t*)dwPathDataRefs[i]) >= (oldReference + 0x5600C * PATHLIMITMUL)) { //We might have NOPed some addresses
			continue;
		}

		dwMod = *((uint32_t*)dwPathDataRefs[i]);

		dwMod -= oldReference;
        
		dwMod += (uint32_t)newReference;

		*((uint32_t*)dwPathDataRefs[i]) = dwMod;
	}
}

void IncreasePathLimit(GlobalMapData* _initialReference) {
	

	static uint32_t dwPathStructRefs[] = {
	   0x434F3B, 0x434F8E, 0x434FE0, 0x435020, 0x435056, 0x4350C3, 0x435129, 0x43532E,
	   0x43550A, 0x4356DA, 0x435748, 0x4357EC, 0x435895, 0x43598B, 0x435A8A, 0x435BD9,
	   0x4368A9, 0x4369D2, 0x4369DA, 0x4369E4, 0x436B94, 0x436EDA, 0x436EE2, 0x436EE8,
	   0x43708E, 0x437096, 0x43709C, 0x437196, 0x43719E, 0x4371A4, 0x437353, 0x4373F7,
	   0x437455, 0x43754A, 0x43757B, 0x4375A4, 0x4378FB, 0x4379A9, 0x437A10, 0x437B3C,
	   0x437B7E, 0x437B98, 0x437C91, 0x4382BB, 0x438335, 0x438410, 0x438848, 0x43889E,
	   0x438958, 0x438A0B, 0x438C5A, 0x438C62, 0x438C6C, 0x438D4D, 0x438ED2, 0x4391D5,
	   0x43922F, 0x4392B2, 0x4392C3, 0x43940F, 0x439417, 0x43956F, 0x43957D, 0x4395B3,
	   0x4395C1, 0x43968D, 0x43970F, 0x4397F2, 0x439808, 0x439820, 0x43984A, 0x43986F,
	   0x439897, 0x4398BC, 0x4398E4, 0x43990A, 0x43992B, 0x43999F, 0x439B1E, 0x439B68,
	   0x439BC5, 0x439CC4, 0x439CDC, 0x439CF4, 0x439D1E, 0x439D43, 0x439D6B, 0x439D90,
	   0x439DB8, 0x439DDE, 0x439DFF, 0x43A523, 0x43A5B7, 0x43A5CF, 0x43A5D8, 0x43A5E0,
	   0x43A5E7, 0x43A5EF, 0x43A723, 0x43A72B, 0x43A873, 0x43A881, 0x43A89A, 0x43A8A2,
	   0x43A8DB, 0x43A8F1, 0x43A94E, 0x43A9A2, 0x43A9AB, 0x43A9B3, 0x43A9B9, 0x43A9C0,
	   0x43A9E9, 0x43A9EF, 0x43AA04, 0x43AA45, 0x43AA5E, 0x43AAA4, 0x43AABD, 0x43AAC3,
	   0x43AAD6, 0x43AADC, 0x43AAF1, 0x43AB03, 0x43AB09, 0x43AB1E, 0x43AB2F, 0x43AB35,
	   0x43AB3F, 0x43AB48, 0x43AB4E, 0x43AB58, 0x43AB61, 0x43AB67, 0x43AB80, 0x43AB87,
	   0x43AB8E, 0x43AB96, 0x43AB9C, 0x43ABBA, 0x43AC07, 0x43AC2F, 0x43AE1B, 0x43AE28,
	   0x43B051, 0x43B05F, 0x43B1F9, 0x43B247, 0x43B296, 0x43B2E1, 0x43B2EA, 0x43B2F2,
	   0x43B2F8, 0x43B2FF, 0x43B35A, 0x43B393, 0x43B3AB, 0x43B3E4, 0x43B3FD, 0x43B436,
	   0x43B44F, 0x43B455, 0x43B468, 0x43B46E, 0x43B478, 0x43B483, 0x43B489, 0x43B493,
	   0x43B49E, 0x43B4A4, 0x43B4AE, 0x43B4B7, 0x43B4BD, 0x43B4C7, 0x43B4D0, 0x43B4D6,
	   0x43B4E4, 0x43B4EB, 0x43B4F2, 0x43B4FA, 0x43B500, 0x43B555, 0x43B55D, 0x43B57D,
	   0x43B593, 0x43B5D2, 0x43B64B, 0x43B653, 0x43B664, 0x43B68E, 0x43B6B1, 0x43B6EA,
	   0x43B7F9, 0x43B86B, 0x43B89A, 0x43B8F6, 0x43B96B, 0x43B9C4, 0x43BA99, 0x43BAB4,
	   0x43BACE, 0x43BAD6, 0x43BAE7, 0x43BAFB, 0x43BBD1, 0x43BF11, 0x43BF47, 0x43BF4D,
	   0x43BF7F, 0x43BF85, 0x43BF8B, 0x43C153, 0x43C15E, 0x43C165, 0x43C177, 0x43C182,
	   0x43C18B, 0x43C193, 0x43C19D, 0x465C38, 0x465C49, 0x465E0A, 0x465E19, 0x465FEC,
	   0x465FFB, 0x4666BE, 0x4666C9, 0x4666F9, 0x466703, 0x41F045, 0x41F09A, 0x41F358,
	   0x41F84A, 0x421134, 0x42116E, 0x421AEA, 0x421B24, 0x422006, 0x422029, 0x42216F,
	   0x42218F, 0x422788, 0x4227C2, 0x425D92, 0x425DDC, 0x427FC7, 0x4280C6, 0x43737B,
	   0x43747C, 0x4374CC, 0x4375FB, 0x437642, 0x4376DE, 0x43772B, 0x43776F, 0x4379BB,
	   0x438E9C, 0x43925A, 0x439369, 0x43B87D, 0x43B8AC, 0x444480, 0x4444BF
	};

	static uint32_t dwPathBlockMargins[] = {
	   0x000000, 0x02F1E8, 0x0395F8, 0x03A980, 0x0448E0, 0x049890, 0x0537F0, 0xFFFFFF
       //0x000000, 0x02F1E8,  0x0395F8, 0x03A980, 0x0448E0, 0x049890,0x049892,0x51518, 0x0537F0, 0x0537F4,0x0537F8, 0x0537FC, 0x0537FE, 0x53800, 0x5380A, 0x5380C, 0xFFFFFF
        //0x000000, 0x02F1E8, 0x0395F8, 0x03A980, 0x0448E0,0x049890, 0x51518,0x0537F0, 0x5600A, 0xFFFFFF
	};
    //4393f8
    //43948a
	DWORD dwOldVal, dwTempVal;
	uint32_t dwMod;

	VirtualProtect((void*)0x401000, 0x27CE00, PAGE_EXECUTE_READWRITE, &dwOldVal);

	for(int i = 0; i < ARRLEN(dwPathDataRefs); i++) {
		if(*((uint32_t*)dwPathDataRefs[i]) < 0x9B6E5C || *((uint32_t*)dwPathDataRefs[i]) >= 0xA0CE68) {
			continue;
		}

		dwMod = *((uint32_t*)dwPathDataRefs[i]);

		dwMod -= 0x9B6E5C;

        
		for(int j = 0; j < ARRLEN(dwPathBlockMargins)-1; j++) {
			if(dwMod < dwPathBlockMargins[j+1]) {
				dwMod = (dwMod-dwPathBlockMargins[j]) + PATHLIMITMUL*dwPathBlockMargins[j];
				break;
			}
		}
		dwMod += (uint32_t)_initialReference;

		*((uint32_t*)dwPathDataRefs[i]) = dwMod;
	}

    
    
    
	for(int i = 0; i < ARRLEN(dwPathStructRefs); i++) {
    	if(*((uint32_t*)dwPathStructRefs[i]) < 0x02F1E8 || *((uint32_t*)dwPathStructRefs[i]) > 0x5380C) {
			continue;
		}

		dwMod = *((uint32_t*)dwPathStructRefs[i]);
 
		for(int j = 0; j < ARRLEN(dwPathBlockMargins)-1; j++) {
			if(dwMod < dwPathBlockMargins[j+1]) {
				dwMod = (dwMod-dwPathBlockMargins[j]) + PATHLIMITMUL*dwPathBlockMargins[j];
				break;
			}
		}

		*((uint32_t*)dwPathStructRefs[i]) = dwMod;
	}

	*((uint32_t*)0x436731) *= PATHLIMITMUL;
	*((uint32_t*)0x43674C) *= PATHLIMITMUL;
	*((uint32_t*)0x4367A5) *= PATHLIMITMUL;
	*((uint32_t*)0x4367C0) *= PATHLIMITMUL;
	*((uint32_t*)0x43680F) *= PATHLIMITMUL;
	*((uint32_t*)0x436801) *= PATHLIMITMUL;
	*((uint32_t*)0x435C3D) *= PATHLIMITMUL;
	*((uint32_t*)0x435FAD) *= PATHLIMITMUL;
	*((uint32_t*)0x43955D) *= PATHLIMITMUL;

    //Addons by Me
    *((uint32_t*)0x43BBA3) *= PATHLIMITMUL;
    *((uint32_t*)0x43BBB1) *= PATHLIMITMUL;

    //2 byte hardcoded
    *((uint16_t*)0x43BC35) *= PATHLIMITMUL;
    *((uint16_t*)0x43BC7E) *= PATHLIMITMUL;

    *((uint16_t*)0x43BDC1) *= PATHLIMITMUL;
    *((uint16_t*)0x43BF03) *= PATHLIMITMUL;

    //At CPathNode::DoPathSearch
    *((uint32_t*)0x43945F) *= PATHLIMITMUL;

    //At Paths Variables Init - Could be initiliazing unused data in PathNode structure
    *((uint32_t*)0x43C215) *= PATHLIMITMUL;

    //Another patch at Allocate paths memory - No effect could be removed
    *((uint32_t*)0x436820) *= PATHLIMITMUL;

    //This is done as the dll is attached late
	_asm mov eax, 43C260h
    _asm call eax

	VirtualProtect((void*)0x401000, 0x27CE00, dwOldVal, &dwTempVal);
}

BYTE CurGrid;
#define SETGRID(i) RelocateGlobalMapDataRefs(&gPathGridsArray[i])
#define CURRENTGRID ((*(DWORD*)dwPathDataRefs - &gPathGridsArray[0])/(sizeof(GlobalMapData)))


void PreInitPaths()
{
    PathsVariableInit(&(gPathGridsArray[0]));
    PathsAllocateMemory(&gPathGridsArray[0]);
}

//Every levels has now been loaded so created all instances of levels
void InitPaths()
{
    wchar_t buff[256];
    //Copy the first global map data grid to every other grids.
    for (int i = 1; i < PATHGRIDLIMIT * PATHGRIDLIMIT; i++)
        memcpy(&gPathGridsArray[i], &gPathGridsArray[0], sizeof(GlobalMapData));

    //Now load paths grid into each separate grids

    CFileLoader_LoadScene("Paths\\paths.ipl");
    PreparePathData(&gPathGridsArray[0]);

    wsprintfW(buff, L"Total Points: %d\n Last ped nodes: %d\n Last Vehicle Nodes: %d\n", gPathGridsArray[0].totalPointInfoIndexm, gPathGridsArray[0].lastPedRoutePointIndex, gPathGridsArray[0].lastVehicleRoutePointIndex);
    MessageBoxW(NULL,buff,NULL,NULL);
    //LoadforAnotherGrid
    //ChangeGridDependancyFirst
    
    RelocateGlobalMapDataRefs(&gPathGridsArray[1]);
    PathsAllocateMemory(&gPathGridsArray[1]); //This allocates the memory for ipl data for paths
    CFileLoader_LoadScene("Paths\\pathsLC.ipl");   //This fills the allocated memory for Paths
    PreparePathData(&gPathGridsArray[1]);               //This then stores the path data into the global map structure

    
    wsprintfW(buff, L"Total Points: %d\n Last ped nodes: %d\n Last Vehicle Nodes: %d\n", gPathGridsArray[1].totalPointInfoIndexm, gPathGridsArray[1].lastPedRoutePointIndex, gPathGridsArray[1].lastVehicleRoutePointIndex);
    MessageBoxW(NULL,buff,NULL,NULL);
    RelocateGlobalMapDataRefs(&gPathGridsArray[2]);
    PathsAllocateMemory(&gPathGridsArray[2]); //This allocates the memory for ipl data for paths
    CFileLoader_LoadScene("Paths\\pathsSA.ipl");   //This fills the allocated memory for Paths
    //CFileLoader_LoadScene("Data\\Maps\\pathsSA2.ipl");
    //CFileLoader_LoadScene("Data\\Maps\\pathsSA3.ipl");
    //CFileLoader_LoadScene("Data\\Maps\\pathsSA4.ipl");
    //CFileLoader_LoadScene("Data\\Maps\\pathsSA5.ipl");
    PreparePathData(&gPathGridsArray[2]);               //This then stores the path data into the global map structure

    wsprintfW(buff, L"Total Points: %d\n Last ped nodes: %d\n Last Vehicle Nodes: %d\n", gPathGridsArray[2].totalPointInfoIndexm, gPathGridsArray[2].lastPedRoutePointIndex, gPathGridsArray[2].lastVehicleRoutePointIndex);
    MessageBoxW(NULL,buff,NULL,NULL);

    //Now Install Hooks in multiplier Address
    InstallPathDivHooks();

}

void InstallPatch_Custom_Load_Paths()
{
    //Disable default loading system for Paths
    CMemory::NoOperation(0x4A4C07, 25);
    CMemory::InstallCallHook(0x4A4CE7,InitPaths, ASM_CALL);

    CMemory::InstallCallHook(0x4a4c07, PreInitPaths, ASM_CALL);
}



void RemovePathRefProtection(){
     for(int i = 0; i < ARRLEN(dwPathDataRefs); i++) {
		CMemory::UnProtect(dwPathDataRefs[i],sizeof(uint32_t));
     }
}

BYTE CurrentGrid = 0;

RwV3d* CCustomPathProcessor(){
    RwV3d* CurrentPosition =  FindPlayerCentreOfWorld_NoSniperShift();
    if (CurrentPosition->y > 2000.0f && CurrentPosition->x > -1000.0f){
        SETGRID(1);
        fPathShiftX = 1312.5f;
        fPathShiftY = 5000.0f;
        fPathShiftZ = 0.0f;
    }
    else if(CurrentPosition->y < 3000.0f && CurrentPosition->x > -2500.0f){
        SETGRID(0);
        fPathShiftX = 0.0f;
        fPathShiftY = 0.0f;
        fPathShiftZ = 0.0f;
    }
    else{
        SETGRID(2);
        fPathShiftX = -6000.0f;
        fPathShiftY = 0.0f;
        fPathShiftZ = 6.0f;
    }
    return CurrentPosition;
}


void ApplyCustomPathPatch(){
            ZeroMemory(gPathGridsArray,sizeof(GlobalMapData) * 12);
			IncreasePathLimit(&gPathGridsArray[0]);
            RemovePathRefProtection();
            InstallPatch_Custom_Load_Paths();

            CMemory::InstallCallHook(0x0426DF4, &CCustomPathProcessor, ASM_CALL);
}
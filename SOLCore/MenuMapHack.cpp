#include "main.h"
#include "StdInc.h"

#define TILES_IN_SECTION 9
#define TOTAL_TILES 81

CSprite2d MapMenuTexStore[TOTAL_TILES];

//============================================================================
DWORD TXDSLOT_FRONTEND3 = NULL;
char MenuMapName[12];
void _declspec(naked) HookCMenuManager__LoadTextures() {
    __asm push ebx
    CTxdStore::PushCurrentTxd();
    TXDSLOT_FRONTEND3 = CTxdStore::FindTxdSlot("frontend3");
    if (TXDSLOT_FRONTEND3 == -1)
        TXDSLOT_FRONTEND3 = CTxdStore::AddTxdSlot("frontend3");
    CTxdStore::LoadTxd(TXDSLOT_FRONTEND3, "MODELS/FRONTEN3.TXD");
    CTxdStore::AddRef(TXDSLOT_FRONTEND3);
    CTxdStore::SetCurrentTxd(TXDSLOT_FRONTEND3);
    for (int i = 0; i < TOTAL_TILES; i++){
        sprintf(MenuMapName, "menuMap%02d", i);
        MapMenuTexStore[i].SetTexture(MenuMapName);
        MapMenuTexStore[i].SetAddressing(RwTextureAddressMode::rwTEXTUREADDRESSBORDER);
    }
    CTxdStore::PopCurrentTxd();
    __asm pop ebx
    __asm ret

}

//============================================================================
//At this instant the ebp register which should be pointing to the ret address at stack is destroyed. Hence no local Vars can be used
DWORD j;
DWORD Func__ReleaseTxd = 0x580B10;
DWORD RetAddress = 0x4A39F7;
void _declspec(naked) HookCMenuManager__UnloadTextures(){    
    __asm call Func__ReleaseTxd
    __asm pushad
    TXDSLOT_FRONTEND3 = CTxdStore::FindTxdSlot("frontend3");
    for (j=0; j< TOTAL_TILES; j++){
        if (MapMenuTexStore[j].RwTexture){
            RwTextureDestroy(MapMenuTexStore[j].RwTexture);
            MapMenuTexStore[j].RwTexture = NULL;
        }
    }
    __asm{
        push TXDSLOT_FRONTEND3
        call Func__ReleaseTxd
        pop ecx
        popad 
        jmp RetAddress
    }
}

//============================================================================
BYTE(__cdecl *sub_4C5B30)(void) = (BYTE(*)(void))0x4C5B30;
void (__cdecl *CRadar__DrawBlips)(void) = (void(*)(void))0x4C4200;

bool loaded = false;
CMenuManager* PMENUMANAGER;
void HookNew_CMenuManager__DrawMapTextures()
{
   __asm mov PMENUMANAGER, ecx //Since we are detouring a thiscall implementation, the struct ptr is contained in this register
    
  CRect CurrentTilePos;
  CRGBA mColor(255, 255, 255, BYTE(PMENUMANAGER->menuPageAlpha));
 
  PMENUMANAGER->IsOnMapMenu = 1;
  sub_4C5B30();//Update player Pos??

  RwV2d mTileStartOffset;
  mTileStartOffset.x = PMENUMANAGER->mapPos.x - PMENUMANAGER->mapScale;  
  mTileStartOffset.y = PMENUMANAGER->mapPos.y - PMENUMANAGER->mapScale;
  
  double mTileSize = PMENUMANAGER->mapScale * 2.0f / TILES_IN_SECTION;
  
  for (int y = 0; y <TILES_IN_SECTION; y++){
      for (int x = 0; x <TILES_IN_SECTION; x++){
          CurrentTilePos.left = mTileStartOffset.x + (float)x * mTileSize;
          CurrentTilePos.right = CurrentTilePos.left + mTileSize;
          CurrentTilePos.top = mTileStartOffset.y + (float)y * mTileSize;
          CurrentTilePos.bottom = CurrentTilePos.top + mTileSize;
          
          CurrentTilePos.left = CurrentTilePos.left/640.0f * (float)ResolutionX;
          CurrentTilePos.right = CurrentTilePos.right/640.0f * (float)ResolutionX;
          CurrentTilePos.top = CurrentTilePos.top/448.0f * (float)ResolutionY;
          CurrentTilePos.bottom = CurrentTilePos.bottom/448.0f * (float)ResolutionY;

          if (!(CurrentTilePos.right < 0.0f) && !(CurrentTilePos.left > (float)ResolutionX)){
              if (!(CurrentTilePos.bottom < 0.0f) && !(CurrentTilePos.top > (float)ResolutionY)){
                  MapMenuTexStore[x + y * TILES_IN_SECTION].DrawTextureRect(CurrentTilePos, mColor);
              }
          }
      }
  }

  //Scaling = 0.2 Somewhere at 48d
  PMENUMANAGER->mapScale=PMENUMANAGER->mapScale / 5.0f; 
  CRadar__DrawBlips();
  PMENUMANAGER->mapScale=PMENUMANAGER->mapScale * 5.0f; 
  PMENUMANAGER->IsOnMapMenu = 0;
  //v147 = (ResolutionX - 10);
  //CFont__SetWrapx(v147);
  //CFont__SetRightJustifyWrap(fTen);
  //sub_48F429(v1, "FEH_MPH");

 
}

// This hack is done by redirecting the calls to CMenuManager__DrawMapTexture

void PatchMapMenu(){
    ZeroMemory(MapMenuTexStore, sizeof(MapMenuTexStore));
    CMemory::UnProtect(0x4A2CC2,5);
    CMemory::InstallCallHook(0x4A2CC2,(DWORD)&HookNew_CMenuManager__DrawMapTextures, ASM_CALL);

    CMemory::UnProtect(0x4A273A,5);
    CMemory::InstallCallHook(0x4A273A,(DWORD)&HookNew_CMenuManager__DrawMapTextures, ASM_CALL);
    
    CMemory::UnProtect(0x4A3BB1, 5);
    CMemory::InstallCallHook(0x4A3BB1, (DWORD)&HookCMenuManager__LoadTextures, ASM_CALL);
    
    CMemory::UnProtect(0x4A39F2,5);
    CMemory::InstallCallHook(0x4A39F2,(DWORD)&HookCMenuManager__UnloadTextures, ASM_JMP);

    CMemory::InstallPatch<float>(0x68FD10,0.0028070009f); //Adjust X Center of Menu Map
    CMemory::InstallPatch<float>(0x68FD1C,-0.0009999993f); //Adjust Y Center of Menu Map

    //Map Move Accleration Addy 68D4AC
    //Patch for Max zoom in and zoom out
    
    CMemory::InstallPatch<float>(0x68D4A8,3200.0f); //Adjust MaxScale
    UnProtect(0x497918, 4);
    *(PFLOAT)0x497918 = 3200.0f;

    CMemory::InstallPatch<float>(0x68D4B0,1000.0f); //Adjust MinScale
    UnProtect(0x497B54,4);
    *(PFLOAT)0x497B54 = 1000.0f;

    UnProtect(0x497AB4,4);
    *(PFLOAT)0x497AB4 = 1000.0f;

    //Adjust default Scale
    UnProtect(0x4A3CEC, 4);
    *(PFLOAT)0x4A3CEC = 1000.0f;
}
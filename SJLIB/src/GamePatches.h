// Need to be removed

#pragma once

#include <Windows.h>
#include "GameVC/RenderWare.h"

void PatchMapMenu(void);
void PatchMiscData();
void PatchRadar(bool bdebugMsg);
void PatchWater(void);
void PatchVehicleLimits(void);

void InstallFileLoaderHooks(void);

enum eMenuOptions
{
E_MENU_STATS = 0,
E_MENU_DEFAULT = 1,
E_MENU_BREIF = 2,
E_MENU_AUDIOOPTIONS = 3,
E_MENU_DISPLAYOPTIONS = 4,
E_MENU_LANGUAGE = 5,
E_MENU_MAP = 6,
E_MENU_STARTCONFIRM = 7,
E_MENU_LOAD = 8,
E_MENU_DELETE = 9,
E_MENU_LOADCONFIRM = 10,
E_MENU_DELETECONFIRM = 11,
E_MENU_STARTGAME = 12,
E_MENU_DELETING = 13,
E_MENU_DELETESUCCESS = 14,
E_MENU_SAVE = 15,
E_MENU_OVERWRITE = 16,
E_MENU_SAVING = 17,
E_MENU_SAVESUCCESS = 18,
E_MENU_UNKNOWN = 19,
E_MENU_CHEATSWARNING = 20,
E_MENU_CRASHY = 21,
E_MENU_UNKNOWNSAVE = 22,
E_MENU_SAVEUNSUCCESSFUL = 23,
E_MENU_SAVEUNSUCCESSFUL2 = 24,
E_MENU_LOADFAIL_CORRUPT = 25,
E_MENU_CONTROLOPTIONS = 26,
E_MENU_OPTIONS = 27,
E_MENU_SUREQUIT = 28,
E_MENU_MAIN = 29,
E_MENU_CONTROLSETTINGS = 30,
E_MENU_MOUSESETTINGS = 31,
E_MENU_PAUSE = 32,
E_MENU_QUITSPLASH = 34,
};

class CMenuManager
{
public:
  char radioStation;
  char gap_1[3];
  float field_4;
  char field_8;
  char field_9;
  char HudMode;
  char gap_B[1];
  int radarMode;
  char field_10;
  char field_11;
  char showMenuOnNextUpdate;
  char gap_13[1];
  int field_14;
  int brightness;
  float drawDistance;
  char subtitles;
  char mapLegend;
  char wideScreen;
  char field_23;
  char field_24;
  char frameLimiter;
  char audioHardware;
  char speakersConfiguration;
  char dynamicAcousticMode;
  char sfxVolume;
  char musicVolume;
  char currentRadio;
  char field_2C;
  char gap_2D[3];
  int activeMenuEntry;
  char quitApp;
  char IsOnMapMenu;
  char field_36;
  char field_37;
  char IsMenuActive;
  char field_39;
  char field_3A;
  char MakeSave;
  char field_3C;
  char gap_3d[3];
  float mapScale;
  RwV2d mapPos;
  char field_4C;
  char field_4D;
  char field_4E;
  char field_4F;
  int currentLanguage;
  int field_54;
  char textsReloaded;
  char field_59;
  char mp3VolumeBoost;
  char standartControls;
  int previousVideoMode;
  int videoMode;
  int mouseMoveX;
  int mouseMoveY;
  char MenuMode;
  char field_6D;
  char texts_reloaded;
  char gap_6F[1];
  int field_70;
  char gap_74[4];
  int *pKbdInputEventQueue;
  char field_7C;
  char gap_7D[3];
  int field_80;
  RwTexture* frontendTextures[26];
  char frontendTexturesLoaded;
  char gap_ED[3];
  int field_F0;
  int field_F4;
  int CurrentMenuPage;//eMenuOptions
  int previousMenuPage;
  int saveNo;
  int field_104;
  int menuPageAlpha;
  int field_10C;
  char field_110;
  char gap_111[3];
  int currMouseInputEvent;
  int currJoypadInputEvent;
  char field_11C;
  char field_11D;
  char field_11E;
  char gap_11F[1];
  int field_120;
  char field_124[5];
  char gap_129[3];
  int field_12C;
  float field_130;
  int field_134;
  int field_138;
  int field_13C;
  char field_140;
  char gap_141[3];
  int field_144;
  char field_148;
  char field_149;
  char field_14A;
  char gap_14B[1];
  int processingInputEvent;
  char gap_150[4];
  int field_154;
  char field_158;
  char field_159;
  char field_15A;
  char savedSkinPath[256];
  char currPlayerSkinPath[169];
  int field_304;
  char gap_308[84];
  int field_35C;
  int field_360;
  char gap_364[768];
  int field_664;
  int field_668;
  int field_66C;
  int field_670;
  int field_674;
  int field_678;
  char gap_67C[4];
  int field_680;
  char field_684;
  char __padding[3];
};
/*
struct CObjectVC {
   CPhysical phys; // 0-288
   //physical structure of this object
   CMatrix matDummyInitial; // 288-360
   //initial matrix, when converted from a dummy object
   float fAttachForce; // 360-34
   //how strongly the object is attached to the ground
   uint8_t byteObjectType; // 364-365
   //0 - default, not used, 1 - map object, 2 - projectiles, pickups, script objects, 3 - dead car parts and roadblocks, 4 - cutscene object, 5 - spiketraps + ?
   uint8_t bIsPickupObject:1; // 365.0-365.1
   //is a pickup object
   uint8_t bDoCircleEffect:1; // 365.1-365.2
   //do the circle blinking effect for pickups
   uint8_t bRenderPickupQuantity:1; // 365.2-365.3
   //render pickup quantity as dollars
   uint8_t bRenderPickupAvailability:1; // 365.3-365.4
   //render pickup ammunation quantity
   uint8_t bWindowMinorCollisionDamage:1; // 365.4-365.5
   //window has received minor collision damage
   uint8_t bHasWindowBeenBrokenByMelee:1; // 365.5-365.6
   //window has been broken by melee
   uint8_t bHasObjectExplosionTriggered:1; // 365.6-365.7
   //has object explosion been triggered (barrels, water hydrants)
   uint8_t bIsVehicleComponent:1; // 365.7-366.0
   //is this a separated vehicle component
   uint8_t bSpecialLighting:1; // 366.0-366.1
   //used for weapon models
   uint8_t bNoVehicleCollisionWhenDetached:1; // 366.1-366.2
   //used for traffic light objects
   uint8_t bPadFlags:6; // 366.2-367.0
   uint8_t bytePickupObjectBonusType; // 367-368
   //used for bonus and clothes pickups
   uint16_t wPickupObjectQuantity; // 368-370
   //used for money pickups
   _pad(__fxpad00, 2); // 370-372
   float fDamageMultiplier; // 372-376
   //object damage multiplier - how easily it breaks
   uint8_t byteCollisionDamageType; // 376-377
   //what happens when the object receives damage
   uint8_t byteSpecialCollisionType; // 377-378
   //special collision type for some objects
   uint8_t byteCameraAvoids; // 378-379
   //whether the camera avoids this object
   uint8_t byteBounceScore; // 379-380
   //how many times the player has hit this with his head (beachball)
   _pad(__fxpad01, 4); // 380-384
   uint32_t dwObjectTimer; // 384-388
   //for some objects this shows when it will disappear (car parts)
   uint16_t wRefModelId; // 388-390
   //the ID of the model this object is a part of (car parts)
   _pad(__fxpad02, 2); // 390-392
   CEntity* pInitialSurface; // 392-396
   //the surface the object is on when created
   CPhysical* pContactPhysical; // 396-400
   //a physical that is currently in contact with this object
   uint8_t byteVehicleMainColor; // 400-401
   //main color for vehicle parts
   uint8_t byteVehicleExtraColor; // 401-402
   //extra color for vehicle parts
   _pad(__fxpad03, 2); // 402-404
};

struct CPickupVC {
   CVector vecPos; // 0-12
   //position of the pickup
   float fStandProximity; // 12-16
   //how close the player is standing to the pickup?
   CObjectVC* pObject; // 16-20
   //entity associated with the pickup
   CObjectVC* pExtraObject; // 20-24
   //extra entity (for minigun for example)
   uint32_t dwPickupQuantity; // 24-28
   //used for weapons and money
   uint32_t dwTimer; // 28-32
   //either the time it was created or when it should disappear
   uint16_t wMoneyGenerationRate; // 32-34
   //how quickly this pickup generates money
   uint16_t wModelId; // 34-36
   //model ID of the pickup
   uint16_t wUniqueId; // 36-38
   //unique identifier of this pickup
   char szPickupTextKey[8]; // 38-46
   //key of the text that is shown when on this pickup
   uint8_t bytePickupType; // 46-47
   //shows if pickup slot is in use and its type
   uint8_t byteRemoved; // 47-48
   //pickup has been removed
   uint8_t byteEffects; // 48-49
   //which kind of visual effects this pickup has (values 0/1)
   _pad(__fxpad02, 3); // 49-52

   #define WEPSTATE_NORMAL 0
#define WEPSTATE_SHOOTING 1
#define WEPSTATE_RELOADING 2
#define WEPSTATE_OUTOFAMMO 3

struct CWeapon {
   uint32_t dwWeaponID; // 0-4
   //ID of the weapon in this slot
   uint32_t dwWeaponState; // 4-8
   //state of weapon
   uint32_t dwAmmoLoaded; // 8-12
   //currently loaded amount of ammo
   uint32_t dwAmmoTotal; // 12-16
   //total amount of ammo
   uint32_t dwLastShotTime; // 16-20
   //time of the last shot made, also updated on reloading
   uint8_t byteWepCamMode; // 20-21
   //related to weapon camera mode, never used?
   _pad(__fxpad00, 3); // 21-24
};
};
*/

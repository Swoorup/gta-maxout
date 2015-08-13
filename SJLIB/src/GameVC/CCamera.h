#ifndef __CCAMERA_H
#define __CCAMERA_H

#include "SJLIB/stdinc.h"
#include "CommonDefinations.h"

#pragma pack(push, 1)

class CCameraJPT {
public:
  _pad(__fxpad00, 0x820);
  CMatrix field_820;
  char cameraInFreeMode;
  _pad(__fxpad02, 7);
  CMatrix viewMatrix;
  RwV3d field_8B8;
  RwV3d field_8C4;
  RwV3d field_8D0;
  RwV3d field_8DC;
  RwV3d field_8E8;
  RwV3d field_8F4;
  RwV3d field_900;
  _pad(__fxpad03, 0x5C);
};

struct CCam {
 bool bBelowMinDist; // 0-1
 //used for follow ped mode
 bool bBehindPlayerDesired; // 1-2
 //used for follow ped mode
 bool bCamLookingAtVector; // 2-3
 //is camera looking at vector
 bool bCollisionChecksOn; // 3-4
 //are collision checks on
 bool bFixingBeta; // 4-5
 //used for camera on a string
 bool bTheHeightFixerVehicleIsATrain; // 5-6
 //height fixer
 bool bLookBehindCamWasInFront; // 6-7
 //looking behind & cam was in front
 bool bLookingBehind; // 7-8
 //is looking behind
 bool bLookingLeft; // 8-9
 //is looking left
 bool bLookingRight; // 9-10
 //is looking right
 bool bRotating; // 10-11
 _pad(__fxpad00,1); // 11-12
 short nMode; // 12-14
 //camera mode
 _pad(__fxpad01,2); // 14-16
 DWORD dwFinishTime; // 16-20
 //finish time
 int nDoCollisionChecksOnFrameNum;  // 20-24
 //do collision check on frame num
 int nDoCollisionCheckEveryNumOfFrames; // 24-28
 //do collision check every num of frames
 int nFrameNumWereAt; // 28-32
 //frame num we're at
 int nRunningVectorArrayPos; // 32-36
 //running vector array pos
 int nRunningVectorCounter; // 36-40
 //running vector counter
 int nDirectionWasLooking; // 40-44
 //previous looking direction
 float fMaxRollAngle; // 44-48
 //maximum roll angle
 float fRoll; // 48-52
 //roll amount
 float fRollSpeed; // 52-56
 //roll speed
 float fSyphonModeTargetZOffSet; // 56-60
 //syphon mode target X offset
 float fAmountFractionObscured; // 60-64
 //amount of fraction obscured
 float fAlphaSpeedOverOneFrame; // 64-68
 //alpha speed over one frame
 float fBetaSpeedOverOneFrame; // 68-72
 //beta speed over one frame
 float fBufferedTargetBeta; // 72-76
 //buffered target beta
 float fBufferedTargetOrientation; // 76-80
 //buffered target orientation
 float fBufferedTargetOrientationSpeed; // 80-84
 //buffered target orientation speed
 float fCamBufferedHeight; // 84-88
 //buffered height
 float fCamBufferedHeightSpeed; // 88-92
 //buffered height speed
 float fCloseInPedHeightOffset; // 92-96
 //close in ped height offset
 float fCloseInPedHeightOffsetSpeed; // 96-100
 //close in ped height offset speed
 float fCloseInCarHeightOffset; // 100-104
 //close in car height offset
 float fCloseInCarHeightOffsetSpeed; // 104-108
 //close in car height offset speed
 float fDimensionOfHighestNearCar; // 108-112
 //dimensions of highest near car
 float fDistanceBeforeChanges; // 112-116
 //distance before changes
 float fFovSpeedOverOneFrame; // 116-120
 //FOV speed over one frame
 float fMinDistAwayFromCamWhenInterPolating; // 120-124
 //minimum distance away from camera when interpolating
 float fPedBetweenCameraHeightOffset; // 124-128
 //ped between camera height offset
 float fPlayerInFrontSyphonAngleOffset; // 128-132
 //player in front syphon angle offset
 float fRadiusForDead; // 132-136
 //radius for dead
 float fRealGroundDist; // 136-140
 //real ground distance
 float fTargetBeta; // 140-144
 //target beta
 float fTimeElapsedFloat; // 144-148
 //time elapsed
 float fTilt; // 148-152
 //tilt amount
 float fTiltSpeed; // 152-156
 //tilt speed
 float fTransitionBeta; // 156-160
 //transition beta
 float fTrueBeta; // 160-164
 //true beta
 float fTrueAlpha; // 164-168
 //true alpha
 float fInitialPlayerOrientation; // 168-172
 //initial player orientation
 float fAlpha; // 172-176
 //alpha
 float fAlphaSpeed; // 176-180
 //alpha speed
 float fFOV; // 180-184
 //FOV
 float fFOVSpeed; // 184-188
 //FOV speed
 float fBeta; // 188-192
 //beta
 float fBetaSpeed; // 192-196
 //beta speed
 float fDistance; // 196-200
 //distance
 float fDistanceSpeed; // 200-204
 //distance speed
 float fCaMinDistance; // 204-208
 //CA min distance
 float fCaMaxDistance; // 208-212
 //CA max distance
 float fSpeedVar; // 212-216
 //speed var
 float fTargetZoomGroundOne; // 216-220
 //target zoom ground one
 float fTargetZoomGroundTwo; // 220-224
 //target zoom ground two
 float fTargetZoomGroundThree; // 224-228
 //target zoom ground three
 float fTargetZoomOneZExtra; // 228-232
 //target zoom one Z extra
 float fTargetZoomTwoZExtra; // 232-236
 //target zoom two Z extra
 float fTargetZoomThreeZExtra; // 236-240
 //target zoom three Z etra
 float fTargetZoomZCloseIn; // 240-244
 //target zoom Z close in
 float fMinRealGroundDist; // 244-248
 //minimum real ground distance
 float fTargetCloseInDist; // 248-252
 //target close in distance
 CVector vecSourceSpeedOverOneFrame; // 252-264
 //source speed over one frame
 CVector vecTargetSpeedOverOneFrame; // 264-276
 //target speed over one frame
 CVector vecUpOverOneFrame; // 276-288
 //angle (up) change during last frame
 CVector vecTargetCoorsForFudgeInter; // 288-300
 //camera target position
 CVector vecCamFixedModeVector; // 300-312
 //fixed mode target
 CVector vecCamFixedModeSource; // 312-324
 //fixed mode source
 CVector vecCamFixedModeUpOffSet; // 324-336
 //fixed mode angle (up)
 CVector vecLastAboveWaterCamPosition; // 336-348
 //last position above water
 CVector vecBufferedPlayerBodyOffset; // 348-360
 //buffered player body offset
 CVector vecLookFront; // 360-372
 //angle of the camera (front)
 CVector vecSource; // 372-384
 //source position of camera
 CVector vecSourceBeforeLookBehind; // 384-396
 //source position of camera before looking behind
 CVector vecLookUp; // 396-408
 //angle of the camera
 CVector vecArrPrevVectors[2]; // 408-432
 //previous vectors for average
 CEntity* pTargetEntity; // 432-436
 //target entity of the cam
 float fCameraDistance; // 436-440
 //camera distance (zero!?)
 float fIdealAlpha; // 440-444
 //ideal alpha
 float fPlayerVelocity; // 444-448
 //player velocity
 CVehicle* pLastCarEntered; // 448-452
 //not used
 CPed* pLastPedLookedAt; // 452-456
 //not used
 bool bFirstPersonRunAboutActive; // 456-457
 //not used
 _pad(__fxpad02,3); // 457-460
};

struct CQueuedCamMode{
	int       Mode;                   // CameraMode
    float       Duration;               // How long for (<0.0f -> indefinately)
    int       MinZoom, MaxZoom;       // How far is player allowed to zoom in & out
};

struct CCameraVC {
 CMatrix matCamera; // 0-72
 //matrix of the camera
 _pad(__pad01a,2); // 72-74
 uint8_t bFollowPlayer; // 74-75
 //is camera following player
 _pad(__pad01b,34); // 75-109
 uint8_t bWideScreen; // 109-110
 //is widescreen mode on
 _pad(__pad02b,8); // 110-118
 uint8_t byteActiveCam; // 118-119
 //active cam ID
 _pad(__pad02c,273); // 119-392
 CCam stCams[3]; // 392-1772
 //camera instances
 _pad(__pad05a,8); // 1772-1780
 CQueuedCamMode stPlayerMode; // 1780-1792
 //player special mode
 CQueuedCamMode stPlayerWeaponMode; // 1792-1804
 //player weapon mode, higher priority
 CVector vecPrevCamPos; // 1804-1816
 //previous camera pos
 CVector vecRealPrevCamPos; // 1816-1828
 //real previous camera pos (actual position?)
 CVector vecAimingTargetCoors; // 1828-1840
 //aiming target coords
 CVector vecFixedModeVector; // 1840-1852
 //fixed mode target
 CVector vecFixedModeSource; // 1852-1864
 //fixed mode source
 CVector vecFixedModeUpOffset; // 1864-1876
 //fixed mode up offset
 CVector vecCutSceneOffset; // 1876-1888
 //offset used in cutscenes
 CVector vecStartingSourceForInterPol; // 1888-1900
 //starting source for interpolation
 CVector vecStartingTargetForInterPol; // 1900-1912
 //starting target for interpolation
 CVector vecStartingUpForInterPol; // 1912-1924
 //starting up angle for interpolation
 CVector vecSourceSpeedAtStartInter; // 1924-1936
 //source speed at interpolation start
 CVector vecTargetSpeedAtStartInter; // 1936-1948
 //target speed at interpolation start
 CVector vecUpSpeedAtStartInter; // 1948-1960
 //up speed at interpolation start
 CVector vecSourceWhenInterPol; // 1960-1972
 //source when interpolating
 CVector vecTargetWhenInterPol; // 1972-1984
 //target when interpolating
 CVector vecUpWhenInterPol; // 1984-1996
 //up when interpolating
 CVector vecClearGeometry; // 1996-2008
 //clear geometry vector
 CVector vecGameCamPos; // 2008-2020
 //game camera position
 CVector vecSourceDuringInter; // 2020-2032
 //source during interpolation
 CVector vecTargetDuringInter; // 2032-2044
 //target during interpolation
 CVector vecUpDuringInter; // 2044-2056
 //up during interpolation
 _pad(__pad06a, 24); // 2056-2080
 CMatrix matView; // 2080-2152
 //matrix view of the camera
 _pad(__pad06b, 8); // 2152-2160
 CMatrix matWorld; // 2160-2232
 //matrix used to calculate 2D coords
};

#pragma pack(pop)
#endif
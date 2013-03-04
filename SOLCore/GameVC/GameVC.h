#ifndef GAMEVC_H
#define GAMEVC_H

#include "..\StdInc.h"


// Defines
#define MODEL_BGA			"BGA"
#define MODEL_BOUNCA		"BOUNCA"
#define MODEL_BURGER		"BURGER"
#define MODEL_CDRIVRA		"CDRIVRA"
#define MODEL_CDRIVRB		"CDRIVRB"
#define MODEL_CGONA			"CGONA"
#define MODEL_CGONB			"CGONB"
#define MODEL_CHEF			"CHEF"
#define MODEL_CMRAMAN		"CMRAMAN"
#define MODEL_COURIER		"COURIER"
#define MODEL_CREWA			"CREWA"
#define MODEL_CREWB			"CREWB"
#define MODEL_DGOONA		"DGOONA"
#define MODEL_DGOONB		"DGOONB"
#define MODEL_DGOONC		"DGOONC"
#define MODEL_FLOOZYA		"FLOOZYA"
#define MODEL_FLOOZYB		"FLOOZYB"
#define MODEL_FLOOZYC		"FLOOZYC"
#define MODEL_FSFA			"FSFA"
#define MODEL_IGALSCB		"IGALSCB"
#define MODEL_IGBUDDY		"IGBUDDY"
#define MODEL_IGBUDY2		"IGBUDY2"
#define MODEL_IGCANDY		"IGCANDY"
#define MODEL_IGCOLON		"IGCOLON"
#define MODEL_IGDIAZ		"IGDIAZ"
#define MODEL_IGGONZ		"IGGONZ"
#define MODEL_IGHLARY		"IGHLARY"
#define MODEL_IGHLRY2		"IGHLRY2"
#define MODEL_IGKEN			"IGKEN"
#define MODEL_IGMERC		"IGMERC"
#define MODEL_IGMERC2		"IGMERC2"
#define MODEL_IGMIKE		"IGMIKE"
#define MODEL_IGMIKE2		"IGMIKE2"
#define MODEL_IGPHIL		"IGPHIL"
#define MODEL_IGPHIL2		"IGPHIL2"
#define MODEL_IGPHIL3		"IGPHIL3"
#define MODEL_IGSONNY		"IGSONNY"
#define MODEL_MBA			"MBA"
#define MODEL_MBB			"MBB"
#define MODEL_MGOONA		"MGOONA"
#define MODEL_MPORNA		"MPORNA"
#define MODEL_MSERVER		"MSERVER"
#define MODEL_PLAYER		"PLAYER"
#define MODEL_PLAYER1		"PLAYER1"
#define MODEL_PLAYER2		"PLAYER2"
#define MODEL_PLAYER3		"PLAYER3"
#define MODEL_PLAYER4		"PLAYER4"
#define MODEL_PLAYER5		"PLAYER5"
#define MODEL_PLAYER6		"PLAYER6"
#define MODEL_PRINTRA		"PRINTRA"
#define MODEL_PRINTRB		"PRINTRB"
#define MODEL_PRINTRC		"PRINTRC"
#define MODEL_PSYCHO		"PSYCHO"
#define MODEL_S_KEEP		"S_KEEP"
#define MODEL_SAM			"SAM"
#define MODEL_SGC			"SGC"
#define MODEL_SGOONA		"SGOONA"
#define MODEL_SGOONB		"SGOONB"
#define MODEL_SHOOTRA		"SHOOTRA"
#define MODEL_SHOOTRB		"SHOOTRB"
#define MODEL_SPANDXA		"SPANDXA"
#define MODEL_SPANDXB		"SPANDXB"
#define MODEL_STRIPA		"STRIPA"
#define MODEL_STRIPB		"STRIPB"
#define MODEL_SSTRIPC		"STRIPC"

//CAR models are referenced by their model IDs
#define CAR_LANDSTAL		130
#define CAR_IDAHO			131
#define CAR_STINGER			132
#define CAR_LINERUN			133
#define CAR_PEREN			134
#define CAR_SENTINEL		135
#define BOAT_RIO			136
#define CAR_FIRETRUK		137
#define CAR_TRASH			138
#define CAR_STRETCH			139
#define CAR_MANANA			140
#define CAR_INFERNUS		141
#define CAR_VOODOO			142
#define CAR_PONY			143
#define CAR_MULE			144
#define CAR_CHEETAH			145
#define CAR_AMBULAN			146
#define CAR_FBICAR			147
#define CAR_MOONBEAM		148
#define CAR_ESPERANT		149
#define CAR_TAXI			150
#define CAR_WASHING			151
#define CAR_BOBCAT			152
#define CAR_MRWHOOP			153
#define CAR_BFINJECT		154
#define CAR_HUNTER			155
#define CAR_POLICE			156
#define CAR_ENFORCER		157
#define CAR_SECURICA		158
#define CAR_BANSHEE			159
#define BOAT_PREDATOR		160
#define CAR_BUS				161
#define CAR_RHINO			162
#define CAR_BARRACKS		163
#define CAR_CUBAN			164
#define HELI_CHOPPER		165
#define BIKE_ANGEL			166
#define CAR_COACH			167
#define CAR_CABBIE			168
#define CAR_STALLION		169
#define CAR_RUMPO			170
#define CAR_RCBANDIT		171
#define CAR_ROMERO			172
#define CAR_PACKER			173
#define CAR_SENTXS			174
#define CAR_ADMIRAL			175
#define BOAT_SQUALO			176
#define CAR_SEASPAR			177
#define BIKE_PIZZABOY		178
#define CAR_GANGBUR			179
#define BOAT_SPEEDER		182
#define BOAT_REEFER			183
#define BOAT_TROPIC			184
#define CAR_FLATBED			185
#define CAR_YANKEE			186
#define CAR_CADDY			187
#define CAR_ZEBRA			188
#define CAR_TOPFUN			189
#define BOAT_SKIMMER		190
#define BIKE_PCJ600			191
#define BIKE_FAGGIO			192
#define BIKE_FREEWAY		193
#define CAR_RCBARON			194
#define CAR_RCRAIDER		195
#define CAR_GLENDALE		196
#define CAR_OCEANIC			197
#define BIKE_SANCHEZ		198
#define CAR_SPARROW			199
#define CAR_PATRIOT			200
#define CAR_LOVEFIST		201
#define BOAT_COASTG			202
#define BOAT_DINGHY			203
#define CAR_HERMES			204
#define CAR_SABRE			205
#define CAR_SABRETUR		206
#define CAR_PHEONIX			207
#define CAR_WALTON			208
#define CAR_REGINA			209
#define CAR_COMET			210
#define CAR_DELUXO			211
#define CAR_BURRITO			212
#define CAR_SPAND			213
#define BOAT_MARQUIS		214
#define CAR_BAGGAGE			215
#define CAR_KAUFMAN			216
#define CAR_MAVERICK		217
#define CAR_VCNMAV			218
#define CAR_RANCHER			219
#define CAR_FBIRANCH		220
#define CAR_VIRGO			221
#define CAR_GREENWOO		222
#define BOAT_JETMAX			223
#define CAR_HOTRING			224
#define CAR_SANDKING		225
#define CAR_BLISTAC			226
#define CAR_POLMAV			227
#define CAR_BOXVILLE		228
#define CAR_BENSON			229
#define CAR_MESA			230
#define CAR_RCGOBLIN		231
#define CAR_HOTRINA			232
#define CAR_HOTRINB			233
#define CAR_BLOODRA			234
#define CAR_BLOODRB			235
#define CAR_VICECHEE		236

//Weapon are referenced by their Index but model are requested/loaded by their model IDs
#define WEAPON_NONE			0
#define WEAPON_BRASSKNUCKLE	1
#define WEAPON_SCREWDRIVER	2
#define WEAPON_GOLFCLUB		3
#define WEAPON_NITESTICK	4
#define WEAPON_KNIFECUR		5
#define WEAPON_BAT			6
#define WEAPON_HAMMER		7
#define WEAPON_CLEAVER		8
#define WEAPON_MACHETE		9
#define WEAPON_KATANA		10
#define WEAPON_CHNSAW		11
#define WEAPON_GRENADE		12
#define WEAPON_BOMB			13
#define WEAPON_TEARGAS		14
#define WEAPON_MOLOTOV		15
#define WEAPON_MISSILE		16
#define WEAPON_COLT45		17
#define WEAPON_PYTHON		18
#define WEAPON_CHROMEGUN	19
#define WEAPON_SHOTGSPA		20
#define WEAPON_BUDDYSHOT	21
#define WEAPON_TEC9			22
#define WEAPON_UZI			23
#define WEAPON_INGRAMS1		24
#define WEAPON_MP5LGN		25
#define WEAPON_M4			26
#define WEAPON_RUGER		27
#define WEAPON_SNIPER		28
#define WEAPON_LASER		29
#define WEAPON_ROCKETLA		30
#define WEAPON_FLAME		31
#define WEAPON_M60			32
#define WEAPON_MINIGUN		33
#define WEAPON_DETONATOR	34
#define WEAPON_HELICANNON	35
#define WEAPON_CAMERA		36

//Models
#define ID_BRASSKNUCKLE	259
#define ID_SCREWDRIVER	260
#define ID_GOLFCLUB		261
#define ID_NITESTICK	262
#define ID_KNIFECUR		263
#define ID_BAT			264
#define ID_HAMMER		265
#define ID_CLEAVER		266
#define ID_MACHETE		267
#define ID_KATANA		268
#define ID_CHNSAW		269
#define ID_GRENADE		270
#define ID_TEARGAS		271
#define ID_MOLOTOV		272
#define ID_MISSILE		273
#define ID_COLT45		274
#define ID_PYTHON		275
#define ID_RUGER		276
#define ID_CHROMEGUN	277
#define ID_SHOTGSPA		278
#define ID_BUDDYSHOT	279
#define ID_M4			280
#define ID_TEC9			281
#define ID_UZI			282
#define ID_INGRAMS1		283
#define ID_MP5LGN		284
#define ID_SNIPER		285
#define ID_LASER		286
#define ID_ROCKETLA		287
#define ID_FLAME		288
#define ID_M60			289
#define ID_MINIGUN		290
#define ID_BOMB			291
#define ID_CAMERA		292
#define ID_DETONATOR	NULL	//does not have modelID
#define ID_HELICANNON	NULL	//does not have modelID


#define ID_INFO			365
#define ID_BRIBE		375
#define	ID_BONUS		376
#define ID_HEALTH		366
#define ID_BODYARMOUR	368
#define ID_ADRENALINE	367
#define ID_MONEY		337
#define ID_BRIEFCASE		335
#define ID_CAMERAPICKUP	382
#define ID_PETROLPUMP	370

namespace PEDTYPE
{
    enum
    { 
        PLAYER1,
        PLAYER2,
        PLAYER3, 
        PLAYER4, 
        CIVMALE,
        CIVFEMALE,
        COP,
        GANG1,
        GAMG2,
        GANG3,
        GANG4,
        GANG5,
        GANG6,
        GANG7,
        GANG8,
        GANG9,
        EMERGENCY,
        FIREMAN,
        CRIMINAL,
        SPECIAL,
    };
};

#define WEATHER_SUNNY		0
#define WEATHER_CLOUDY		1
#define WEATHER_RAINING		2
#define WEATHER_FOGGY		3
#define WEATHER_EXTRASUNNY	4
#define WEATHER_STORM		5
#define WEATHER_INTERIOR	6

#define INTERIOR_OUTSIDE	0
#define INTERIOR_HOTEL		1
#define INTERIOR_MANSION	2
#define INTERIOR_BANK		3
#define INTERIOR_MALL		4
#define INTERIOR_STRIPCLUB	5
#define INTERIOR_LAWYERS	6
#define INTERIOR_CAFEROBINA	7
#define INTERIOR_CONCERT	8
#define INTERIOR_STUDIO		9
#define INTERIOR_AMMUNATION	10
#define INTERIOR_APPARTMENT	11
#define INTERIOR_POLICEHQ	12
#define INTERIOR_UNKNOWN	12
#define INTERIOR_STADIUM1	14
#define INTERIOR_STADIUM2	15
#define INTERIOR_STADIUM3	16
#define INTERIOR_CLUB		17
#define INTERIOR_PRINTWORKS	18

#define FADE_OUT			0
#define FADE_IN				1

#define IDE_COP				1
#define IDE_SWAT			2
#define IDE_FBI				3

#define DOOR_STATUS_LOCKED	2

namespace CarDriverBehaviour
{
    enum
    {
        GoNowhere = 0,
        FollowRoad_drivebackIfWayIsBlocked = 1,
        KillThePlayer = 2,
        DriveToPlayerAndStop = 4,
        IgnoreRoadPath = 8,
    };
};

namespace RadarIcons
{
    enum
    {
        Small_purple_dot,
        Large_player_type_icon,  
        Small_arrow,
        North_on_the_Map,
        Avery,
        radar_biker,
        Colonel_Cortez,
        Diaz,
        Kent,
        Ken_Rosenberg,
        Phil,
        Bikers_Bar,
        Docks,
        Malibu_Club,
        Cuban_missions,
        P0rn_Studios,
        AmmuNation,
        Haitian_missions,
        Toolshop,
        Save_Game_Icon,
        Pole_Position_Club_Icon,
        Cherry_Poppers_Icon,
        Kauffman_Cabs_Icon,
        lovefist,
        Printworks_Icon,
        No_Icon,
        Sunshine_Autos_Icon,
        Spray_N_Pay,
        Clothing_pickup,
        Tommys_Home_Icon,
        The_Phone_Icon,
        Wildstyle_station_logo,
        Flash_station_logo,
        KChat_station_logo,
        Fever_station_logo,
        VRock_station_logo,
        VCPR_station_logo,
        Espantoso_station_logo,
        Emotion_station_logo,
        Wave_station_logo,
    };
};

namespace CoronaType
{
    enum
    {
        round_light,
        round_light_less_bright, 
        moon,
        small_cloud, 
        smudge_bigger_dot, 
        octagon,
        circle_with_no_hole,
        circle_with_hole, 
        long_bar_of_light, 
    };	//(lens flare is enabled by 1/2, disabled with 0)
};

#include "CommonDefinations.h"
typedef RwV3d* (__cdecl *FindPlayerCentreOfWorld_NoSniperShift_t)(void);  
typedef void (__cdecl *LoadingScreen_t)(char const *szGameStateText, char const *szLoadingStageText, char const *szUnusedStr);
typedef int (__cdecl *FindPlayerPed_t)(void);
typedef CVehicle* (__cdecl *FindPlayerVehicle_t)(void);
typedef void (_cdecl *FindPlayerCoors_t)(CVector*);

extern FindPlayerCentreOfWorld_NoSniperShift_t FindPlayerCentreOfWorld_NoSniperShift;
extern FindPlayerPed_t FindPlayerPed;
extern LoadingScreen_t LoadingScreen;
extern FindPlayerVehicle_t FindPlayerVehicle;
extern FindPlayerCoors_t FindPlayerCoors;
extern CCameraVC& TheCamera;

#endif
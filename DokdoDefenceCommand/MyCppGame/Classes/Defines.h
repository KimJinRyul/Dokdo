//
//  Defines.h
//  MyCppGame
//
//  Created by Jinryul Kim on 2014. 7. 24..
//
//

#ifndef DokdoDefenceCommand_Defines_h
#define DokdoDefenceCommand_Defines_h

#define APP_NAME    "DokdoDefenceCommand"
#define SAVE_FILE   "ddc.dat"
#define CLEAR_FILE  "clear.dat"
#define DESIGN_RESOLUTION_WIDTH     480
#define DESIGN_RESOLUTION_HEIGHT    800

enum MENU_TAGS
{
    MENU_TAG_NONE = 0,
    MENU_TAG_FACEBOOK,
    MENU_TAG_TWITTER,
    MENU_TAG_CREDIT,
    MENU_TAG_START,
    MENU_TAG_UPGRADE,
    MENU_TAG_SCORE,
    MENU_TAG_OPTION,
    MENU_TAG_INNERBTN,
    MENU_TAG_STARTHAN,
    MENU_TAG_UPGRADEHAN,
    MENU_TAG_SCOREHAN,
    MENU_TAG_OPTIONHAN,
    MENU_TAG_SELECTBAR,
    MENU_TAG_CREDITWND,
    MENU_TAG_BK,
    MENU_TAG_OPTIONDLG,
    MENU_TAG_VERYEASY,
    MENU_TAG_VERYEASYHAN,
    MENU_TAG_VERYEASYCLEAR,
    MENU_TAG_EASY,
    MENU_TAG_EASYHAN,
    MENU_TAG_EASYCLEAR,
    MENU_TAG_NORMAL,
    MENU_TAG_NORMALHAN,
    MENU_TAG_NORMALCLEAR,
    MENU_TAG_HARD,
    MENU_TAG_HARDHAN,
    MENU_TAG_HARDCLEAR,
    MENU_TAG_VERYHARD,
    MENU_TAG_VERYHARDHAN,
    MENU_TAG_VERYHARDCLEAR,
    MENU_TAG_IMPOSSIBLE,
    MENU_TAG_IMPOSSIBLEHAN,
    MENU_TAG_IMPOSSIBLECLEAR,
    MENU_TAG_ENDLESS,
    MENU_TAG_ENDLESSHAN,
    MENU_TAG_BACK,
    MENU_TAG_UPGRADEWND,
    MENU_TAG_SCOREDLG,
    MENU_TAG_SOUNDOPTION,
    MENU_TAG_EFFECTOPTION,
    MENU_TAG_RESETOPTION,
    MENU_TAG_CLEARDLG,
    MENU_TAG_CLEARTITLE,
    MENU_TAG_LABEL_TIME,
    MENU_TAG_LABEL_ENERMY,
    MENU_TAG_LABEL_FORCE,
    MENU_TAG_LABEL_SCORE,
    MENU_TAG_LABEL_TIMETITLE,
    MENU_TAG_LABEL_ENERMYTITLE,
    MENU_TAG_LABEL_FORCETITLE,
    MENU_TAG_LABEL_SCORETITLE,
    MENU_TAG_LABEL_INCOMETITLE,
    MENU_TAG_LABEL_INCOME,
    MENU_TAG_HIGHSCORE,
    MENU_TAG_UP1,
    MENU_TAG_UP2,
    MENU_TAG_PREV,
    MENU_TAG_NEXT,
    MENU_TAG_DOKDO_UP_BTN,
    MENU_TAG_CANNON_UP_BTN,
    MENU_TAG_MISSILE_UP_BTN,
    MENU_TAG_NAVY_UP_1,
    MENU_TAG_NAVY_UP_2,
    MENU_TAG_NAVY_UP_3,
    MENU_TAG_NAVY_UP_4,
    MENU_TAG_BACK_UP,
    MENU_TAG_RESETDLG,
    MENU_TAG_RESETTXT,
    MENU_TAG_BOTTOM,
    MENU_TAG_BACKTXT,
    MENU_TAG_DIALOGLEVEL,
    MENU_TAG_DIALOGOPTION,
    MENU_TAG_DIALOGSCORE,
    MENU_TAG_DIALOGRESULT,
    MENU_TAG_MAINMENU,
    MENU_TAG_SNSMENU,
    MENU_TAG_CREDITMENU,
    MENU_TAG_LEVELMENU,
    MENU_LABEL_MONEY,
    MENU_LABEL_VULCAN_RANGE,
    MENU_LABEL_VULCAN_RANGETITLE,
    MENU_LABEL_VULCAN_SPM,
    MENU_LABEL_VULCAN_SPMTITLE,
    MENU_LABEL_VULCAN_DAMAGE,
    MENU_LABEL_VULCAN_DAMAGETITLE,
    MENU_LABEL_CANNON_RANGE,
    MENU_LABEL_CANNON_RANGETITLE,
    MENU_LABEL_CANNON_SPM,
    MENU_LABEL_CANNON_SPMTITLE,
    MENU_LABEL_CANNON_DAMAGE,
    MENU_LABEL_CANNON_DAMAGETITLE,
    MENU_LABEL_MISSILE_RANGE,
    MENU_LABEL_MISSILE_RANGETITLE,
    MENU_LABEL_MISSILE_SPM,
    MENU_LABEL_MISSILE_SPMTITLE,
    MENU_LABEL_MISSILE_DAMAGE,
    MENU_LABEL_MISSILE_DAMAGETITLE,
    MENU_LABEL_UNIT_HP_1,
    MENU_LABEL_UNIT_HP_1TITLE,
    MENU_LABEL_UNIT_RANGE_1,
    MENU_LABEL_UNIT_RANGE_1TITLE,
    MENU_LABEL_UNIT_SPM_1,
    MENU_LABEL_UNIT_SPM_1TITLE,
    MENU_LABEL_UNIT_DAMAGE_1,
    MENU_LABEL_UNIT_DAMAGE_1TITLE,
    MENU_LABEL_UNIT_HP_2,
    MENU_LABEL_UNIT_HP_2TITLE,
    MENU_LABEL_UNIT_RANGE_2,
    MENU_LABEL_UNIT_RANGE_2TITLE,
    MENU_LABEL_UNIT_SPM_2,
    MENU_LABEL_UNIT_SPM_2TITLE,
    MENU_LABEL_UNIT_DAMAGE_2,
    MENU_LABEL_UNIT_DAMAGE_2TITLE,
    MENU_LABEL_UNIT_HP_3,
    MENU_LABEL_UNIT_HP_3TITLE,
    MENU_LABEL_UNIT_RANGE_3,
    MENU_LABEL_UNIT_RANGE_3TITLE,
    MENU_LABEL_UNIT_SPM_3,
    MENU_LABEL_UNIT_SPM_3TITLE,
    MENU_LABEL_UNIT_DAMAGE_3,
    MENU_LABEL_UNIT_DAMAGE_3TITLE,
    MENU_LABEL_UNIT_HP_4,
    MENU_LABEL_UNIT_HP_4TITLE,
    MENU_LABEL_UNIT_RANGE_4,
    MENU_LABEL_UNIT_RANGE_4TITLE,
    MENU_LABEL_UNIT_SPM_4,
    MENU_LABEL_UNIT_SPM_4TITLE,
    MENU_LABEL_UNIT_DAMAGE_4,
    MENU_LABEL_UNIT_DAMAGE_4TITLE,
    MENU_LABEL_DOKDOLV,
    MENU_LABEL_CANNONLV,
    MENU_LABEL_MISSILELV,
    MENU_LABEL_NAVYLV_1,
    MENU_LABEL_NAVYLV_2,
    MENU_LABEL_NAVYLV_3,
    MENU_LABEL_NAVYLV_4,
    MENU_LABEL_VULCAN_PRICE,
    MENU_LABEL_CANNON_PRICE,
    MENU_LABEL_MISSILE_PRICE,
    MENU_LABEL_UNIT_PRICE1,
    MENU_LABEL_UNIT_PRICE2,
    MENU_LABEL_UNIT_PRICE3,
    MENU_LABEL_UNIT_PRICE4
};

enum MENU_ZORDER
{
    MENU_ZORDER_BK = 0,
    MENU_ZORDER_CREDIT,
    MENU_ZORDER_BATCHNODE,
    MENU_ZORDER_MENU,
    MENU_ZORDER_DIALOG
};

enum MENU_STATE
{
    MENU_STATE_MAIN = 0,
    MENU_STATE_START,
    MENU_STATE_UPGRADE,
    MENU_STATE_SCORE,
    MENU_STATE_OPTION,
    MENU_STATE_RESET,
    MENU_STATE_CREDIT,
    MENU_STATE_RESULT,
    MENU_STATE_FINISH,
    MENU_STATE_BACK
};


/////////////////////////////////////////// for SceneGame
enum GAME_ZORDER
{
    GAME_ZORDER_SEA = 1,
    GAME_ZORDER_SURFACE,
    GAME_ZORDER_CLOUD,
    GAME_ZORDER_SURFACEFIRE,
    GAME_ZORDER_AIR,
    GAME_ZORDER_AIRFIRE,
    GAME_ZORDER_INTERFACE
};

enum GAME_SURFACE_ZORDER
{
    GAME_SURFACE_ZORDER_RADAR = 1,
    GAME_SURFACE_ZORDER_SUBMARINE,
    GAME_SURFACE_ZORDER_SHIPTAIL,
    GAME_SURFACE_ZORDER_SHIP,
    GAME_SURFACE_ZORDER_DOKDO,
    GAME_SURFACE_ZORDER_SHADOW,
    GAME_SURFACE_ZORDER_WATERCOLUMN,
    GAME_SURFACE_ZORDER_LYNX,
    GAME_SURFACE_ZORDER_HELICOPTER,
    GAME_SURFACE_ZORDER_BULLET,
    GAME_SURFACE_ZORDER_CLOUD
};

enum GAME_AIR_ZORDER
{
    GAME_AIR_ZORDER_BOMB = 1,
    GAME_AIR_ZORDER_BOMBER,
    GAME_AIR_ZORDER_FIGHTER,
    GAME_AIR_ZORDER_STRATEGYBOMBER,
    GAME_AIR_ZORDER_MISSILE,
    GAME_AIR_ZORDER_PEACEEYE,
    GAME_AIR_ZORDER_NUCLEAR
};

enum GAME_TAGS
{
    GAME_TAG_BTN_CANNON = 1,
    GAME_TAG_BTN_MISSILE,
    GAME_TAG_BTN_NUCLEAR,
    GAME_TAG_BTN_PKG,
    GAME_TAG_BTN_KDX2,
    GAME_TAG_BTN_E747,
    GAME_TAG_BTN_KSS3,
    GAME_TAG_BTN_KDX3,
    GAME_TAG_BTN_DOKDO,
    GAME_TAG_BTN_F15K,
    GAME_TAG_BTN_ACTIVATE,
    GAME_TAG_BTN_INNERIMG,
    GAME_TAG_LABEL_DOKDOENERGY,
    GAME_TAG_FORCE_PKG,
    GAME_TAG_FORCE_KDX2,
    GAME_TAG_FORCE_KSS3,
    GAME_TAG_FORCE_E747,
    GAME_TAG_FORCE_KDX3,
    GAME_TAG_FORCE_DOKDO,
    GAME_TAG_FORCE_F15K,
    GAME_TAG_FORCE_BULLET,
    GAME_TAG_FORCE_MISSILE,
    GAME_TAG_ENERMY_PATROL,
    GAME_TAG_ENERMY_DESTROYER,
    GAME_TAG_ENERMY_CRUISER,
    GAME_TAG_ENERMY_AIRCRAFT,
    GAME_TAG_ENERMY_LYNX,
    GAME_TAG_ENERMY_HELICOPTER,
    GAME_TAG_ENERMY_FIGHTER,
    GAME_TAG_ENERMY_BOMBER,
    GAME_TAG_ENERMY_STRATEGYBOMBER,
    GAME_TAG_ENERMY_SUBMARINE,
    GAME_TAG_ENERMY_BULLET,
    GAME_TAG_ENERMY_MISSILE,
    GAME_TAG_RADAR_MAX,
    GAME_TAG_RADAR_CANNON,
    GAME_TAG_RADAR_MISSILE,
    GAME_TAG_RADAR_LINE,
    GAME_TAG_SEA,
    GAME_TAG_PAUSEDLG,
    GAME_TAG_PAUSETXT1,
    GAME_TAG_PAUSETXT2,
    GAME_TAG_DOKDO,
    GAME_TAG_DOKDO_ENERGYBAR,
    GAME_TAG_DOKDO_ENERGYBAR_INNER,
    GAME_TAG_NOWLOADING,
    GAME_TAG_SCOREBOARD,
    GAME_TAG_SHOOT_BATCHNODE,
    GAME_TAG_SMOKE
};

enum UNIT_TYPE
{
    UNIT_TYPE_SUBMARINE = 0,
    UNIT_TYPE_SHIP,
    UNIT_TYPE_HELICOPTER,
    UNIT_TYPE_AIR
};

enum GAME_STATE
{
    GAME_STATE_LOADING = 0,
    GAME_STATE_PLAY,
    GAME_STATE_PAUSE,
    GAME_STATE_CLEAR,
    GAME_STATE_OVER
};

// Lv : 0 ~ 40
/*
 Dokdo
 Power : Lv - 3%
 SPM : Lv ~ 0.5%
 Range : Lv ~ 0.005
 
 Force
 HP : Lv ~ 2%
 Power : Lv ~ 2%
 SPM : Lv ~ 0.5
 Range : Lv ~ 0.003
 
 Price
 PKG : Lv  5
 KDX2 : Lv 5
 KSS3 : Lv 6
 E747 : Lv 7
 KDX3 : Lv 8
 Dokdo : Lv 10
 */

#define WEAPONHEIGHT            0.14
#define MINERAL_TIME            0.05
#define MINERAL_GET             4
#define MINERAL_MAX             1000000

#define FEBA_YPOS               460

#define NAVY_MAX                22
#define PKG_MAX                 12
#define KDX2_MAX                10
#define KSS3_MAX                7
#define E747_MAX                1
#define KDX3_MAX                6
#define DOKDO_MAX               1

#define CRUISER_MAX             6
#define CARRIER_MAX             3
#define BOMBER_MAX              3

#define FORCE_PKG_PRICE         500
#define FORCE_KDX2_PRICE        1000
#define FORCE_KSS3_PRICE        1800
#define FORCE_E747_PRICE        900
#define FORCE_KDX3_PRICE        1600
#define FORCE_DOKDO_PRICE       2400
#define FORCE_NUCLEAR_PRICE     24000
#define FORCE_F15K_PRICE        12000

#define SPEED_VULCAN            2.8
#define SPEED_CANNON            3.6
#define SPEED_MISSILE           3.4
#define SPEED_TORPEDO           6.0
#define SPEED_BOMB              8.5
#define SPEED_NUCLEAR           4.5

#define VERYEASY_CLEAR_TIME                  3 * 60
#define VERYEASY_REINFORCE_MIN               1.0
#define VERYEASY_REINFORCE_VARIATION         0.0
#define VERYEASY_ADDENERMY_MIN               3.6
#define VERYEASY_ADDENERMY_VARIATION         0.0

#define EASY_CLEAR_TIME                     4 * 60
#define EASY_REINFORCE_MIN                  1.0
#define EASY_REINFORCE_VARIATION            0.5
#define EASY_ADDENERMY_MIN                  3.4
#define EASY_ADDENERMY_VARIATION            0.5

#define NORMAL_CLEAR_TIME                     5 * 60
#define NORMAL_REINFORCE_MIN                  1.2
#define NORMAL_REINFORCE_VARIATION            0.6
#define NORMAL_ADDENERMY_MIN                  3.2
#define NORMAL_ADDENERMY_VARIATION            0.6

#define HARD_CLEAR_TIME                     7 * 60
#define HARD_REINFORCE_MIN                  1.5
#define HARD_REINFORCE_VARIATION            1.5
#define HARD_ADDENERMY_MIN                  3.0
#define HARD_ADDENERMY_VARIATION            0.8

#define VERYHARD_CLEAR_TIME                     10 * 60
#define VERYHARD_REINFORCE_MIN                  2.0
#define VERYHARD_REINFORCE_VARIATION            2.0
#define VERYHARD_ADDENERMY_MIN                  2.8
#define VERYHARD_ADDENERMY_VARIATION            0.8

#define IMPOSSIBLE_CLEAR_TIME                     12 * 60
#define IMPOSSIBLE_REINFORCE_MIN                  3.0
#define IMPOSSIBLE_REINFORCE_VARIATION            3.0
#define IMPOSSIBLE_ADDENERMY_MIN                  2.6
#define IMPOSSIBLE_ADDENERMY_VARIATION            0.8

#define ENDLESS_CLEAR_TIME                     100 * 60
#define ENDLESS_REINFORCE_MIN                  2.0
#define ENDLESS_REINFORCE_VARIATION            40.0
#define ENDLESS_ADDENERMY_MIN                  3.2
#define ENDLESS_ADDENERMY_VARIATION            2.2

#define MENU_UPGRADE_LEVEL_SIZE     45
#define MENU_UPGRADE_PRICE_SIZE     30
#define MENU_UPGRADE_STATUS_SIZE    19
#define MENU_UPGRADE_MONEY_SIZE     34

#define SCENE_TAG_MENU                          5000
#define SCENE_TAG_GAME                          5001
#define SCENE_TAG_CREDIT                        5002
#define SCENE_TAG_UPGRADE                       5003
#define LAYER_TAG_MENU                          6000
#define LAYER_TAG_GAME                          6001
#define LAYER_TAG_CREDIT                        6002
#define LAYER_TAG_UPGRADE                       6003

struct DokdoLv
{
    DokdoLv()
    {
        nVulcanLv = nCannonLv = nMissileLv = 0;
    }
    int nVulcanLv;
    int nCannonLv;
    int nMissileLv;
};

struct UnitLvOld
{
    UnitLvOld()
    {
        nPKGLv = nKDX2Lv = nKSS3Lv = nE747Lv = nKDX3Lv = nDOKDOLv = 0;
    }
    int nPKGLv;
    int nKDX2Lv;
    int nKSS3Lv;
    int nE747Lv;
    int nKDX3Lv;
    int nDOKDOLv;
};

struct UnitLv
{
    UnitLv()
    {
        nPKGLv = nKDX2Lv = nKSS3Lv = nE747Lv = nKDX3Lv = nDOKDOLv = nF15KLv = nReserved = 0;
    }
    int nPKGLv;
    int nKDX2Lv;
    int nKSS3Lv;
    int nE747Lv;
    int nKDX3Lv;
    int nDOKDOLv;
    int nF15KLv;
    int nReserved;
};

struct HIGHSCORE
{
    HIGHSCORE()
    {
        memset(&time, 0, sizeof(tm));
        score = 0;
    }
    struct tm time;
    unsigned long score;
};

struct OPTIONS
{
    OPTIONS()
    {
        bBGMSil = false;
        bEffectSil = false;
    }
    bool bBGMSil;
    bool bEffectSil;
};

struct DDC_SAVE_DATA_OLD
{
    DDC_SAVE_DATA_OLD()
    {
        nMoney = 0;
    }
    int nMoney;
    DokdoLv dokdoLv;
    UnitLvOld unitLv;
    HIGHSCORE highscore[12];
    OPTIONS option;
};

struct DDC_SAVE_DATA
{
    DDC_SAVE_DATA()
    {
        nMoney = 0;
    }
    int nMoney;
    DokdoLv dokdoLv;
    UnitLv unitLv;
    HIGHSCORE highscore[12];
    OPTIONS option;
};

struct DDC_CLEAR_DATA
{
    DDC_CLEAR_DATA()
    {
        veryeasy = easy = normal = hard = veryhard = impossible = false;
    }
    bool veryeasy;
    bool easy;
    bool normal;
    bool hard;
    bool veryhard;
    bool impossible;
};


#endif

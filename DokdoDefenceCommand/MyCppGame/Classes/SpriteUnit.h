//
//  SpriteUnit.h
//  MyCppGame
//
//  Created by Jinryul Kim on 2014. 8. 6..
//
//

#ifndef __DokdoDefenceCommand__SpriteUnit__
#define __DokdoDefenceCommand__SpriteUnit__

#include "cocos2d.h"
#include "UnitManager.h"
#include "DokdoCalculator.h"

#define UNIT_SUBMARINE     0
#define UNIT_KSS3          1

#define UNIT_PATROL        2
#define UNIT_PKG           3
#define UNIT_DESTROYER     4
#define UNIT_KDX2          5
#define UNIT_CRUISER       6
#define UNIT_KDX3          7
#define UNIT_CARRIER       8
#define UNIT_DOKDO         9

#define UNIT_LYNX          10
#define UNIT_HELICOPTER    11

#define UNIT_BOMBER        12
#define UNIT_FIGHTER       13
#define UNIT_F15K          14
#define UNIT_E747          15
#define UNIT_STRATEGIC     16

#define ENERGYBAR_SHOWTIME  1.2

#define TAG_DETECTED        1000
#define TAG_ENERGYBAR       1001
#define TAG_ENERGYBAR_INNER 1002


#define SPEED_PKG               43
#define SPEED_KDX2              55
#define SPEED_KSS3              47
#define SPEED_E747              35
#define SPEED_KDX3              62
#define SPEED_DOKDO             73
#define SPEED_F15K              40

#define SPEED_PATROL            56
#define SPEED_DESTROYER         71
#define SPEED_CRUISER           83
#define SPEED_CARRIIER          95
#define SPEED_SUBMARINE         75
#define SPEED_HELICOPTER        53
#define SPEED_LYNX              59
#define SPEED_FIGHTER           48
#define SPEED_BOMBER            58
#define SPEED_STRATEGYBOMBER    65

#define FORCE_PKG_HP            49
#define FORCE_PKG_VULCAN_POWER  6
#define FORCE_PKG_VULCAN_SPM    120
#define FORCE_PKG_VULCAN_RANGE  270

#define FORCE_KDX2_HP           120
#define FORCE_KDX2_CANNON_POWER 21
#define FORCE_KDX2_CANNON_SPM   28
#define FORCE_KDX2_CANNON_RANGE 280
#define FORCE_KDX2_VULCAN_POWER 3
#define FORCE_KDX2_VULCAN_SPM   96
#define FORCE_KDX2_VULCAN_RANGE 270

#define FORCE_KSS_HP                30
#define FORCE_KSS_TORPEDO_POWER     91
#define FORCE_KSS_TORPEDO_SPM       12
#define FORCE_KSS_TORPEDO_RANGE     270

#define FORCE_F15K_HP               120
#define FORCE_F15K_MISSILE_POWER    60
#define FORCE_F15K_MISSILE_SPM      96
#define FORCE_F15K_MISSILE_RANGE    310
#define FORCE_F15K_VULCAN_POWER     8
#define FORCE_F15K_VULCAN_SPM       160
#define FORCE_F15K_VULCAN_RANGE     270

#define FORCE_E747_HP               150
#define FORCE_E747_BMEWS_RANGE      210

#define FORCE_KDX3_HP               240
#define FORCE_KDX3_CANNON_POWER     16
#define FORCE_KDX3_CANNON_SPM       26
#define FORCE_KDX3_CANNON_RANGE     270
#define FORCE_KDX3_MISSILE_POWER    40
#define FORCE_KDX3_MISSILE_SPM      20
#define FORCE_KDX3_MISSILE_RANGE    310

#define FORCE_DOKDO_HP                  500
#define FORCE_DOKDO_RESTORATION_POWER   14
#define FORCE_DOKDO_RESTORATION_SPM     20
#define FORCE_DOKDO_RESTORATION_RANGE   100
#define FORCE_DOKDO_VULCAN_POWER        8
#define FORCE_DOKDO_VULCAN_SPM          144
#define FORCE_DOKDO_VULCAN_RANGE        270

#define ENERMY_PATROL_HP            35
#define ENERMY_PATROL_VULCAN_POWER  4
#define ENERMY_PATROL_VULCAN_SPM    96
#define ENERMY_PATROL_VULCAN_RANGE  260
#define ENERMY_PATROL_SCORE         10

#define ENERMY_SUBMARINE_HP             30
#define ENERMY_SUBMARINE_TORPEDO_POWER  52
#define ENERMY_SUBMARINE_TORPEDO_SPM    16
#define ENERMY_SUBMARINE_TORPEDO_RANGE  250
#define ENERMY_SUBMARINE_SCORE          100

#define ENERMY_DESTROYER_HP             120
#define ENERMY_DESTROYER_VULCAN_POWER   3
#define ENERMY_DESTROYER_VULCAN_SPM     96
#define ENERMY_DESTROYER_VULCAN_RANGE   250
#define ENERMY_DESTROYER_CANNON_POWER   11
#define ENERMY_DESTROYER_CANNON_SPM     26
#define ENERMY_DESTROYER_CANNON_RANGE   270
#define ENERMY_DESTROYER_SCORE          30

#define ENERMY_CRUISER_HP               250
#define ENERMY_CRUISER_CANNON_POWER     8
#define ENERMY_CRUISER_CANNON_SPM       24
#define ENERMY_CRUISER_CANNON_RANGE     260
#define ENERMY_CRUISER_MISSILE_POWER    24
#define ENERMY_CRUISER_MISSILE_SPM      20
#define ENERMY_CRUISER_MISSILE_RANGE    280
#define ENERMY_CRUISER_SCORE            200

#define ENERMY_AIRCRAFT_HP              500
#define ENERMY_AIRCRAFT_VULCAN_POWER    5
#define ENERMY_AIRCRAFT_VULCAN_SPM      176
#define ENERMY_AIRCRAFT_VULCAN_RANGE    270
#define ENERMY_AIRCRAFT_FIGHTER_SPM     3
#define ENERMY_AIRCRAFT_SCORE           350

#define ENERMY_HELICOPTER_HP            30
#define ENERMY_HELICOPTER_VULCAN_POWER  4
#define ENERMY_HELICOPTER_VULCAN_SPM    104
#define ENERMY_HELICOPTER_VULCAN_RANGE  230
#define ENERMY_HELICOPTER_SCORE         20

#define ENERMY_LYNX_HP                  25
#define ENERMY_LYNX_RADAR_RANGE         110
#define ENERMY_LYNX_SCORE               50

#define ENERMY_FIGHTER_HP               60
#define ENERMY_FIGHTER_MISSILE_POWER    38
#define ENERMY_FIGHTER_MISSILE_SPM      28
#define ENERMY_FIGHTER_MISSILE_RANGE    290
#define ENERMY_FIGHTER_VULCAN_POWER     20
#define ENERMY_FIGHTER_VULCAN_SPM       80
#define ENERMY_FIGHTER_VULCAN_RANGE     230
#define ENERMY_FIGHTER_SCORE            70

#define ENERMY_BOMBER_HP                120
#define ENERMY_BOMBER_CANNON_POWER      19
#define ENERMY_BOMBER_CANNON_SPM        40
#define ENERMY_BOMBER_CANNON_RANGE      250
#define ENERMY_BOMBER_SCORE             90

#define ENERMY_STRATEGYBOMBER_HP        250
#define ENERMY_STRATEGYBOMBER_BOMB_POWER 20
#define ENERMY_STRATEGYBOMBER_BOMB_CTN   6
#define ENERMY_STRATEGYBOMBER_BOMB_SPM   8
#define ENERMY_STRATEGYBOMBER_BOMB_RANGE 190
#define ENERMY_STRATEGYBOMBER_SCORE         500

#define ENERMY_RANGE_RATE       12
#define ENERMY_SPM_RATE         10

class SpriteUnit : public cocos2d::Sprite
{
public:
    static SpriteUnit* create(int type, float reinforce, bool enermy);
    bool initWithType(int type, float reinforce, bool enermy);
    int getType();
    
    void setEnergy(float energy);
    float subEnergy(float damage);
    void update(float dt);
    void setDetected(bool detected);
    bool isShip();
    bool isSubmarine();
    bool isSurface();
    bool isAir();
    bool isHelicopter();
    bool isEnermy();
    bool isWaterLevel();
    
    int mType;
    float mEnergyBarTime,
        mWeaponCoolTime, mSubWeaponCoolTime,
        mWeaponCoolTimeMax, mSubWeaponCoolTimeMax;
    float mEnergy, mMaxEnergy;
    bool mDetected, mControlled, mEnermy;
    float mSpeed;
    float mRange, mSubRange;
    float mPower, mSubPower;
    int mScore;
    
private:
    void showEnergyBar();
};

#endif /* defined(__DokdoDefenceCommand__SpriteUnit__) */

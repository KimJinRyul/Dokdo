//
//  DokdoCalculator.hpp
//  DokdoDefenceCommand
//
//  Created by 김진율 on 2021/04/02.
//

#ifndef DokdoCalculator_hpp
#define DokdoCalculator_hpp

#include "cocos2d.h"

#define MAX_LEVEL               60
#define MAX_PRICE               999999999

#define DOKDO_POWER_RATE        0.07    // 0.07 * 60 = 0.7 * 6 = 4.2 -> 420%
#define UNIT_POWER_RATE         0.06    // 0.06 * 60 = 0.6 * 6 = 3.6 -> 360%
#define UNIT_SPM_RATE            0.005   // 0.005 * 60 = 0.05 * 6 = 0.3 -> 30%
#define UNIT_HP_RATE            0.06    // 0.06 * 60 = 0.6 * 6 = 3.6 -> 360%
#define UNIT_RANGE_RAGE            0.008    // 0.008 * 60 = 0.08 * 6 = 0.48 -> 48%

#define DOKDO_VULCAN_POWER      4
#define DOKDO_VULCAN_SPM        190
#define DOKDO_VULCAN_RANGE      280

#define DOKDO_CANNON_POWER      30
#define DOKDO_CANNON_SPM        40
#define DOKDO_CANNON_RANGE      290

#define DOKDO_MISSILE_POWER     80
#define DOKDO_MISSILE_SPM       18
#define DOKDO_MISSILE_RANGE     330

#define NUCLEAR_RANGE            250

#define UPGRADE_VULCAN_PRICE                    500
#define UPGRADE_CANNON_PRICE                    800
#define UPGRADE_MISSILE_PRICE                   1200

#define UPGRADE_PKG_PRICE                       500
#define UPGRADE_KDX2_PRICE                      800
#define UPGRADE_KDX3_PRICE                      1200
#define UPGRADE_DOKDO_PRICE                     1600
#define UPGRADE_E747_PRICE                      300
#define UPGRADE_KSS3_PRICE                      1400
#define UPGRADE_F15K_PRICE                      900

USING_NS_CC;

class DokdoCalculator
{
public:
    static int getDokdoRange(int base, int lv);
    static int getDokdoSPM(int base, int lv);
    static int getDokdoDamage(int base, int lv);
    
    static int getUnitHP(int base, int lv);
    static int getUnitRange(int base, int lv);
    static int getUnitSPM(int base, int lv);
    static int getUnitDamage(int base, int lv);
    
    static int getUnitPrice(int base, int lv, int dc);
    static int getUpgradePrice(int base, int lv);
    
    static time_t getCurrentDate();
    static long getCurrentTime();
    
    static float getDokdoCoolTime(int spm, int lv);

    static float getDistance(Vec2 pt1, Vec2 pt2);
};

#endif /* DokdoCalculator_hpp */

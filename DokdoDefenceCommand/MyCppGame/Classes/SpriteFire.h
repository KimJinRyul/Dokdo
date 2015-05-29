//
//  SpriteFire.h
//  MyCppGame
//
//  Created by Jinryul Kim on 2014. 8. 8..
//
//

#ifndef __DokdoDefenceCommand__SpriteFire__
#define __DokdoDefenceCommand__SpriteFire__

#include "cocos2d.h"

enum FIRE_TARGET
{
    TARGET_SEALEVEL = 0,
    TARGET_SURFACE,
    TARGET_ALL
};

enum FIRE_TYPE
{
    TYPE_TORPEDO = 0,
    TYPE_VULCAN,
    TYPE_CANNON,
    TYPE_MISSILE,
    TYPE_BOMB,
    TYPE_NUCLEAR
};

class SpriteFire : public cocos2d::Sprite
{
public:
    static SpriteFire* create(FIRE_TYPE type, FIRE_TARGET target, float damage, bool enermy);
    bool initWithType(FIRE_TYPE type, FIRE_TARGET target, float damage, bool enermy);

    FIRE_TYPE mType;
    FIRE_TARGET mTarget;
    float mDamage;
    bool mEnermy;
    
private:
    void FireOn(cocos2d::Ref* ref);
};

#endif /* defined(__DokdoDefenceCommand__SpriteFire__) */

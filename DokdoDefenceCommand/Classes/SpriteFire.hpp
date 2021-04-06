//
//  SpriteFire.hpp
//  DokdoDefenceCommand
//
//  Created by 김진율 on 2021/04/02.
//

#ifndef SpriteFire_hpp
#define SpriteFire_hpp


#include "cocos2d.h"

USING_NS_CC;
using namespace std;

enum FIRE_TARGET {
    TARGET_SEALEVEL = 0,
    TARGET_SURFACE,
    TARGET_ALL
};

enum FIRE_TYPE {
    TYPE_TORPEDO = 0,
    TYPE_VULCAN,
    TYPE_CANNON,
    TYPE_MISSILE,
    TYPE_BOMB,
    TYPE_NUCLEAR
};

class SpriteFire : public Sprite
{
public:
    static SpriteFire* create(FIRE_TYPE type, FIRE_TARGET target, float damage, bool enermy, Vec2 targetPos);
    bool initWithType(FIRE_TYPE type, FIRE_TARGET target, float damage, bool enermy, Vec2 targetPos);

    FIRE_TYPE mType;
    FIRE_TARGET mTarget;
    float mDamage;
    bool mEnermy;
    Vec2 mTargetPos;
    
private:
    void FireOn(Ref* ref);
};

#endif /* SpriteFire_hpp */

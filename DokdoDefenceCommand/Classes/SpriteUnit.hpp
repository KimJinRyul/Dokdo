//
//  SpriteUnit.hpp
//  DokdoDefenceCommand
//
//  Created by 김진율 on 2021/04/02.
//

#ifndef SpriteUnit_hpp
#define SpriteUnit_hpp

#include "cocos2d.h"
#include "UnitManager.hpp"
#include "DokdoCalculator.hpp"

USING_NS_CC;
using namespace std;

class SpriteUnit : public Sprite
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

#endif /* SpriteUnit_hpp */

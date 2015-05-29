//
//  SpriteFire.cpp
//  MyCppGame
//
//  Created by Jinryul Kim on 2014. 8. 8..
//
//

#include "SpriteFire.h"

USING_NS_CC;
using namespace std;

SpriteFire* SpriteFire::create(FIRE_TYPE type, FIRE_TARGET target, float damage, bool enermy)
{
    SpriteFire* spFire = new SpriteFire();
    if(spFire && spFire->initWithType(type, target, damage, enermy))
    {
        spFire->autorelease();
        return spFire;
    }
    CC_SAFE_DELETE(spFire);
    return nullptr;
}

bool SpriteFire::initWithType(FIRE_TYPE type, FIRE_TARGET target, float damage, bool enermy)
{
    mType = type;
    mTarget = target;
    mDamage = damage;
    mEnermy = enermy;
    
    bool bRet = false;
    if(mType == TYPE_VULCAN)
    {
        bRet = initWithSpriteFrameName("bullet.png");
        if(bRet)
        {
            setScale(0.3);
        }
    }
    else if(mType == TYPE_CANNON)
    {
        bRet = initWithSpriteFrameName("bullet.png");
        if(bRet)
        {
            setScale(0.5);
        }
    }
    else if(mType == TYPE_TORPEDO)
    {
        bRet = initWithSpriteFrameName("torpedo.png");
        if(bRet)
        {
            Sprite* tail = Sprite::createWithSpriteFrameName("shiptail02_01.png");
            tail->setAnchorPoint(Vec2(0.5, 0.1));
            tail->setRotation(180);
            tail->setPosition(Vec2(getContentSize().width / 2, 0));
            tail->setOpacity(0);
            tail->setScaleX(0.4);
            
            FadeIn* fadeIn = FadeIn::create(2.0);
            tail->runAction(fadeIn);
            
            addChild(tail);
        }
    }
    else if(mType == TYPE_MISSILE)
    {
        bRet = initWithSpriteFrameName("MISSILE.png");
        
        if(bRet)
        {
            Sprite* backFire = Sprite::createWithSpriteFrameName("bullet.png");
            backFire->setOpacity(180);
            backFire->setAnchorPoint(Vec2(0.5, 0.1));
            backFire->setRotation(180);
            backFire->setPosition(Vec2(getContentSize().width / 2, 0));
            backFire->setVisible(false);
            addChild(backFire);
        
            DelayTime* delay = DelayTime::create(0.4);
            CallFuncN* cf = CallFuncN::create(CC_CALLBACK_1(SpriteFire::FireOn, this));
            Sequence* sequence = Sequence::create(delay, cf, nullptr);
            backFire->runAction(sequence);
        }
    }
    else if(mType == TYPE_BOMB || mType == TYPE_NUCLEAR)
    {
        bRet = initWithSpriteFrameName("MISSILE.png");
    }
    
    return bRet;
}

void SpriteFire::FireOn(Ref* ref)
{
    Sprite* backfire = (Sprite*)ref;
    backfire->setVisible(true);

    ScaleTo* scaleTo = ScaleTo::create(0.15, 0.4);
    ScaleTo* scaleTo2 = ScaleTo::create(0.15, 0.7);
    Sequence* scaleSeq = Sequence::create(scaleTo, scaleTo2, nullptr);
    RepeatForever* repeat = RepeatForever::create(scaleSeq);
    backfire->runAction(repeat);
}
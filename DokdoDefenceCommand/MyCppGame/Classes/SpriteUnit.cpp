//
//  SpriteUnit.cpp
//  MyCppGame
//
//  Created by Jinryul Kim on 2014. 8. 6..
//
//

#include "SpriteUnit.h"

USING_NS_CC;
using namespace std;

SpriteUnit* SpriteUnit::create(int type, float reinforce, bool enermy)
{
    SpriteUnit* spUnit = new SpriteUnit();
    if(spUnit && spUnit->initWithType(type, reinforce, enermy))
    {
        spUnit->autorelease();
        return spUnit;
    }
    CC_SAFE_DELETE(spUnit);
    return nullptr;
}

bool SpriteUnit::initWithType(int type, float reinforce, bool enermy)
{
    mType = type;
    mEnermy = enermy;
    mControlled = false;
    mDetected = true;
    mEnergyBarTime = 0.f;
    mWeaponCoolTime = mSubWeaponCoolTime = 0;
    
    
    if(initWithSpriteFrameName(UnitManager::getFilePath(mType)))
    {
        Sprite* energy = Sprite::createWithSpriteFrameName("energybar2.png");
        
        energy->setScaleX(getContentSize().width / energy->getContentSize().width);
        energy->setAnchorPoint(Vec2(1, 0));
        energy->setPosition(Vec2(getContentSize().width, getContentSize().height + 5));
        energy->setTag(TAG_ENERGYBAR);
        
        Sprite* inner = Sprite::createWithSpriteFrameName("energybar.png");
        inner->setAnchorPoint(Vec2(1, 0));
        inner->setPosition(Vec2(energy->getContentSize().width, 0));
        inner->setTag(TAG_ENERGYBAR_INNER);
        
        energy->addChild(inner);
        energy->setVisible(false);
        addChild(energy, 10);
        
        Sprite* front = nullptr;        // 뱃머리
        Sprite* tail = nullptr;         // 배후미
        Sprite* propeller = nullptr;    // 프로펠러
        Sprite* shadow = nullptr;       // 그림자
        Sprite* backFire = nullptr, *backFire2 = nullptr;     // 전투기 화염
        Sprite* wingtailR = nullptr, *wingtailL = nullptr; // 좌우 날개 궤적
        Sprite* detected = nullptr;     // 잠수함 발견
        Sprite* radar = nullptr;        // Lynx, Dokdo, PeaceEye
        
        switch(type)
        {
            case UNIT_PKG:
                mSpeed = SPEED_PKG;
                mScore = 0;
                mEnergy = mMaxEnergy = DokdoCalculator::getUnitHP(FORCE_PKG_HP, reinforce);
                mRange = DokdoCalculator::getUnitRange(FORCE_PKG_VULCAN_RANGE, reinforce);
                mSubRange = 0;
                mPower = DokdoCalculator::getUnitDamage(FORCE_PKG_VULCAN_POWER, reinforce);
                mSubPower = 0;
                mWeaponCoolTimeMax =  60.0 / DokdoCalculator::getUnitSPM(FORCE_PKG_VULCAN_SPM, reinforce);
                mSubWeaponCoolTimeMax = 0;
                front = Sprite::createWithSpriteFrameName("shiptail03.png");
                front->setRotation(180);
                front->setPosition(Vec2(4, 5));
                tail = Sprite::createWithSpriteFrameName("shiptail02_03.png");
                tail->setRotation(180);
                tail->setPosition(Vec2(6, -35));
                break;
            case UNIT_KDX2:
                mSpeed = SPEED_KDX2;
                mScore = 0;
                mEnergy = mMaxEnergy = DokdoCalculator::getUnitHP(FORCE_KDX2_HP, reinforce);
                mRange = DokdoCalculator::getUnitRange(FORCE_KDX2_CANNON_RANGE, reinforce);
                mSubRange = DokdoCalculator::getUnitRange(FORCE_KDX2_VULCAN_RANGE, reinforce);
                mPower = DokdoCalculator::getUnitDamage(FORCE_KDX2_CANNON_POWER, reinforce);
                mSubPower = DokdoCalculator::getUnitDamage(FORCE_KDX2_VULCAN_POWER, reinforce);
                mWeaponCoolTimeMax =  60.0 / DokdoCalculator::getUnitSPM(FORCE_KDX2_CANNON_SPM, reinforce);
                mSubWeaponCoolTimeMax = 60.0 / DokdoCalculator::getUnitSPM(FORCE_KDX2_VULCAN_SPM, reinforce);
                front = Sprite::createWithSpriteFrameName("shiptail03.png");
                front->setRotation(180);
                front->setPosition(Vec2(4, 25));
                tail = Sprite::createWithSpriteFrameName("shiptail02_03.png");
                tail->setRotation(180);
                tail->setPosition(Vec2(7, -35));
                break;
            case UNIT_KDX3:
                mSpeed = SPEED_KDX3;
                mScore = 0;
                mEnergy = mMaxEnergy = DokdoCalculator::getUnitHP(FORCE_KDX3_HP, reinforce);
                mRange = DokdoCalculator::getUnitRange(FORCE_KDX3_MISSILE_RANGE, reinforce);
                mSubRange = DokdoCalculator::getUnitRange(FORCE_KDX3_CANNON_RANGE, reinforce);
                mPower = DokdoCalculator::getUnitDamage(FORCE_KDX3_MISSILE_POWER, reinforce);
                mSubPower = DokdoCalculator::getUnitDamage(FORCE_KDX3_CANNON_POWER, reinforce);
                mWeaponCoolTimeMax =  60.0 / DokdoCalculator::getUnitSPM(FORCE_KDX3_MISSILE_SPM, reinforce);
                mSubWeaponCoolTimeMax = 60.0 / DokdoCalculator::getUnitSPM(FORCE_KDX3_CANNON_SPM, reinforce);
                front = Sprite::createWithSpriteFrameName("shiptail03.png");
                front->setRotation(180);
                front->setPosition(Vec2(8, 45));
                tail = Sprite::createWithSpriteFrameName("shiptail02_03.png");
                tail->setRotation(180);
                tail->setPosition(Vec2(10, -35));
                break;
            case UNIT_DOKDO:
                mSpeed = SPEED_DOKDO;
                mScore = 0;
                mEnergy = mMaxEnergy = DokdoCalculator::getUnitHP(FORCE_DOKDO_HP, reinforce);
                mRange = DokdoCalculator::getUnitRange(FORCE_DOKDO_RESTORATION_RANGE, reinforce);
                mSubRange = DokdoCalculator::getUnitRange(FORCE_DOKDO_VULCAN_RANGE, reinforce);
                mPower = DokdoCalculator::getUnitDamage(FORCE_DOKDO_RESTORATION_POWER, reinforce);
                mSubPower = DokdoCalculator::getUnitDamage(FORCE_DOKDO_VULCAN_POWER, reinforce);
                mWeaponCoolTimeMax =  60.0 / DokdoCalculator::getUnitSPM(FORCE_DOKDO_RESTORATION_SPM, reinforce);
                mSubWeaponCoolTimeMax = 60.0 / DokdoCalculator::getUnitSPM(FORCE_DOKDO_VULCAN_SPM, reinforce);
                front = Sprite::createWithSpriteFrameName("shiptail03.png");
                front->setRotation(180);
                front->setPosition(Vec2(11, 29));
                tail = Sprite::createWithSpriteFrameName("shiptail02_03.png");
                tail->setRotation(180);
                tail->setPosition(Vec2(13, -35));
                radar = Sprite::createWithSpriteFrameName("controller_active.png");
                radar->setOpacity(80);
                radar->setScale((mRange * 2) / radar->getContentSize().height);
                radar->setPosition(Vec2(getContentSize().width/2, getContentSize().height/2));
                break;
            case UNIT_KSS3:
                mSpeed = SPEED_KSS3;
                mScore = 0;
                mEnergy = mMaxEnergy = DokdoCalculator::getUnitHP(FORCE_KSS_HP, reinforce);
                mRange = DokdoCalculator::getUnitRange(FORCE_KSS_TORPEDO_RANGE, reinforce);
                mSubRange = 0;
                mPower = DokdoCalculator::getUnitDamage(FORCE_KSS_TORPEDO_POWER, reinforce);
                mSubPower = 0;
                mWeaponCoolTimeMax =  60.0 / DokdoCalculator::getUnitSPM(FORCE_KSS_TORPEDO_SPM, reinforce);
                mSubWeaponCoolTimeMax = 0;
                detected = Sprite::createWithSpriteFrameName("jang00.png");
                detected->setAnchorPoint(Vec2(0, 0));
                detected->setTag(TAG_DETECTED);
                detected->setVisible(false);
                mDetected = false;
                break;
            case UNIT_E747:
                mSpeed = SPEED_E747;
                mScore = 0;
                mEnergy = mMaxEnergy = DokdoCalculator::getUnitHP(FORCE_E747_HP, reinforce);
                mRange = DokdoCalculator::getUnitRange(FORCE_E747_BMEWS_RANGE, reinforce);
                mSubRange = 0;
                mPower = 0;
                mSubPower = 0;
                mWeaponCoolTimeMax =  0;
                mSubWeaponCoolTimeMax = 0;
                radar = Sprite::createWithSpriteFrameName("radar_00.png");
                radar->setOpacity(80);
                radar->setScale((mRange * 2) / radar->getContentSize().height);
                radar->setPosition(Vec2(getContentSize().width/2, getContentSize().height/2));
                break;
            case UNIT_F15K:
                mSpeed = SPEED_F15K;
                mScore = 0;
                mEnergy = mMaxEnergy = DokdoCalculator::getUnitHP(FORCE_F15K_HP, reinforce);
                mRange = DokdoCalculator::getUnitRange(FORCE_F15K_MISSILE_RANGE, reinforce);
                mSubRange = DokdoCalculator::getUnitRange(FORCE_F15K_VULCAN_RANGE, reinforce);
                mPower = DokdoCalculator::getUnitDamage(FORCE_F15K_MISSILE_POWER, reinforce);
                mSubPower = DokdoCalculator::getUnitDamage(FORCE_F15K_VULCAN_POWER, reinforce);
                mWeaponCoolTimeMax =  60.0 / DokdoCalculator::getUnitSPM(FORCE_F15K_MISSILE_SPM, reinforce);
                mSubWeaponCoolTimeMax = 60.0 / DokdoCalculator::getUnitSPM(FORCE_F15K_VULCAN_SPM, reinforce);
                backFire = Sprite::createWithSpriteFrameName("bullet.png");
                backFire->setRotation(180);
                backFire->setPosition(Vec2(26, 0));
                backFire->setOpacity(160);
                backFire->setAnchorPoint(Vec2(0.5, 0.1));
                
                backFire2 = Sprite::createWithSpriteFrameName("bullet.png");
                backFire2->setRotation(180);
                backFire2->setPosition(Vec2(32, 0));
                backFire2->setOpacity(160);
                backFire2->setAnchorPoint(Vec2(0.5, 0.1));
                
                shadow = Sprite::createWithSpriteFrameName("fighter_s.png");
                shadow->setRotation(180);
                shadow->setPosition(Vec2(28, -40));
                
                wingtailL = Sprite::createWithSpriteFrameName("tail.png");
                wingtailL->setRotation(180);
                wingtailL->setPosition(Vec2(1, -25));
                
                wingtailR = Sprite::createWithSpriteFrameName("tail.png");
                wingtailR->setRotation(180);
                wingtailR->setPosition(Vec2(getContentSize().width-1, -25));
                
                break;
            case UNIT_PATROL:
                mSpeed = SPEED_PATROL;
                mScore = ENERMY_PATROL_SCORE * reinforce;
                mEnergy = mMaxEnergy = ENERMY_PATROL_HP * reinforce;
                mRange = ENERMY_PATROL_VULCAN_RANGE * (1.0 + (reinforce / ENERMY_RANGE_RATE));
                mSubRange = 0;
                mPower = ENERMY_PATROL_VULCAN_POWER * reinforce;
                mSubPower = 0;
                mWeaponCoolTimeMax = 60.0 / (ENERMY_PATROL_VULCAN_SPM * (1.0 + (reinforce / ENERMY_SPM_RATE)));
                mSubWeaponCoolTimeMax = 0;
                front = Sprite::createWithSpriteFrameName("shiptail03.png");
                front->setPosition(Vec2(9, 42));
                tail = Sprite::createWithSpriteFrameName("shiptail02_03.png");
                tail->setPosition(Vec2(8, 80));
                break;
            case UNIT_DESTROYER:
                mSpeed = SPEED_DESTROYER;
                mScore = ENERMY_DESTROYER_SCORE * reinforce;
                mEnergy = mMaxEnergy = ENERMY_DESTROYER_HP * reinforce;
                mRange = ENERMY_DESTROYER_CANNON_RANGE * (1.0 + (reinforce / ENERMY_RANGE_RATE));
                mSubRange = ENERMY_DESTROYER_VULCAN_RANGE * (1.0 + (reinforce / ENERMY_RANGE_RATE));
                mPower = ENERMY_DESTROYER_CANNON_POWER * reinforce;
                mSubPower = ENERMY_DESTROYER_VULCAN_POWER * reinforce;
                mWeaponCoolTimeMax = 60.0 / (ENERMY_DESTROYER_CANNON_SPM * (1.0 + (reinforce / ENERMY_SPM_RATE)));
                mSubWeaponCoolTimeMax = 60.0 / (ENERMY_DESTROYER_VULCAN_SPM * (1.0 + (reinforce / ENERMY_SPM_RATE)));
                front = Sprite::createWithSpriteFrameName("shiptail03.png");
                front->setPosition(Vec2(10, 42));
                tail = Sprite::createWithSpriteFrameName("shiptail02_03.png");
                tail->setPosition(Vec2(8, 105));
                break;
            case UNIT_CRUISER:
                mSpeed = SPEED_CRUISER;
                mScore = ENERMY_CRUISER_SCORE * reinforce;
                mEnergy = mMaxEnergy = ENERMY_CRUISER_HP * reinforce;
                mRange =  ENERMY_CRUISER_MISSILE_RANGE * (1.0 + (reinforce / ENERMY_RANGE_RATE));
                mSubRange = ENERMY_CRUISER_CANNON_RANGE * (1.0 + (reinforce / ENERMY_RANGE_RATE));
                mPower =  ENERMY_CRUISER_MISSILE_POWER * reinforce;
                mSubPower = ENERMY_CRUISER_CANNON_POWER * reinforce;
                mWeaponCoolTimeMax = 60.0 / (ENERMY_CRUISER_MISSILE_SPM * (1.0 + (reinforce / ENERMY_SPM_RATE)));
                mSubWeaponCoolTimeMax = 60.0 / (ENERMY_CRUISER_CANNON_SPM * (1.0 + (reinforce / ENERMY_SPM_RATE)));
                front = Sprite::createWithSpriteFrameName("shiptail03.png");
                front->setPosition(Vec2(15, 43));
                tail = Sprite::createWithSpriteFrameName("shiptail02_03.png");
                tail->setPosition(Vec2(12, 160));
                break;
            case UNIT_CARRIER:
                mSpeed = SPEED_CARRIIER;
                mScore = ENERMY_AIRCRAFT_SCORE * reinforce;
                mEnergy = mMaxEnergy = ENERMY_AIRCRAFT_HP * reinforce;
                mRange =  ENERMY_AIRCRAFT_VULCAN_RANGE * (1.0 + (reinforce / ENERMY_RANGE_RATE));
                mSubRange = 0;
                mPower =  ENERMY_AIRCRAFT_VULCAN_POWER * reinforce;
                mSubPower = 0;
                mWeaponCoolTimeMax = 60.0 / (ENERMY_AIRCRAFT_VULCAN_SPM * (1.0 + (reinforce / ENERMY_SPM_RATE)));
                mSubWeaponCoolTimeMax = 60.0 / (ENERMY_AIRCRAFT_FIGHTER_SPM * (1.0 + (reinforce / ENERMY_SPM_RATE)));
                front = Sprite::createWithSpriteFrameName("shiptail03.png");
                front->setPosition(Vec2(20, 38));
                tail = Sprite::createWithSpriteFrameName("shiptail02_03.png");
                tail->setPosition(Vec2(17, 150));
                break;
            case UNIT_HELICOPTER:
                mSpeed = SPEED_HELICOPTER;
                mScore = ENERMY_HELICOPTER_SCORE * reinforce;
                mEnergy = mMaxEnergy = ENERMY_HELICOPTER_HP * reinforce;
                mRange = ENERMY_HELICOPTER_VULCAN_RANGE * (1.0 + (reinforce / ENERMY_RANGE_RATE));
                mSubRange = 0;
                mPower = ENERMY_HELICOPTER_VULCAN_POWER * reinforce;
                mSubPower = 0;
                mWeaponCoolTimeMax = 60.0 / (ENERMY_HELICOPTER_VULCAN_SPM * (1.0 + (reinforce / ENERMY_SPM_RATE)));
                mSubWeaponCoolTimeMax = 0;
                propeller = Sprite::createWithSpriteFrameName("helicopter_01.png");
                propeller->setPosition(Vec2(16, 26));
                shadow = Sprite::createWithSpriteFrameName("helicopter_s.png");
                shadow->setPosition(Vec2(16, -30));
                
                break;
            case UNIT_LYNX:
                mSpeed = SPEED_LYNX;
                mScore = ENERMY_LYNX_SCORE * reinforce;
                mEnergy = mMaxEnergy = ENERMY_LYNX_HP * reinforce;
                mRange = ENERMY_LYNX_RADAR_RANGE * (1.0 + (reinforce / ENERMY_RANGE_RATE));
                mSubRange = 0;
                mPower = 0;
                mSubPower = 0;
                mWeaponCoolTimeMax = 0;
                mSubWeaponCoolTimeMax = 0;
                propeller = Sprite::createWithSpriteFrameName("lynx00.png");
                propeller->setPosition(Vec2(14, 28));
                shadow = Sprite::createWithSpriteFrameName("lynx01_s.png");
                shadow->setPosition(Vec2(14, -30));
                radar = Sprite::createWithSpriteFrameName("radar_00.png");
                radar->setOpacity(80);
                radar->setScale((mRange * 2) / radar->getContentSize().height);
                radar->setPosition(Vec2(getContentSize().width/2, getContentSize().height/2));
                
                break;
            case UNIT_FIGHTER:
                mSpeed = SPEED_FIGHTER;
                mScore = ENERMY_FIGHTER_SCORE * reinforce;
                mEnergy = mMaxEnergy = ENERMY_FIGHTER_HP * reinforce;
                mRange =  ENERMY_FIGHTER_MISSILE_RANGE * (1.0 + (reinforce / ENERMY_RANGE_RATE));
                mSubRange = ENERMY_FIGHTER_VULCAN_RANGE * (1.0 + (reinforce / ENERMY_RANGE_RATE));
                mPower =  ENERMY_FIGHTER_MISSILE_POWER * reinforce;
                mSubPower = ENERMY_FIGHTER_VULCAN_POWER * reinforce;
                mWeaponCoolTime = mWeaponCoolTimeMax = 60.0 / (ENERMY_FIGHTER_MISSILE_SPM * (1.0 + (reinforce / ENERMY_SPM_RATE)));
                mSubWeaponCoolTime = mSubWeaponCoolTimeMax = 60.0 / (ENERMY_FIGHTER_VULCAN_SPM * (1.0 + (reinforce / ENERMY_SPM_RATE)));
                backFire = Sprite::createWithSpriteFrameName("bullet.png");
                backFire->setPosition(Vec2(26, 59));
                backFire->setOpacity(160);
                backFire->setAnchorPoint(Vec2(0.5, 0.1));
                shadow = Sprite::createWithSpriteFrameName("fighter_s.png");
                shadow->setPosition(Vec2(25, -35));
                wingtailL = Sprite::createWithSpriteFrameName("tail.png");
                wingtailL->setPosition(Vec2(0, 90));
                wingtailR = Sprite::createWithSpriteFrameName("tail.png");
                wingtailR->setPosition(Vec2(getContentSize().width, 90));
                break;
            case UNIT_BOMBER:
                mSpeed = SPEED_BOMBER;
                mScore = ENERMY_BOMBER_SCORE * reinforce;
                mEnergy = mMaxEnergy = ENERMY_BOMBER_HP * reinforce;
                mRange = ENERMY_BOMBER_CANNON_RANGE * (1.0 + (reinforce / ENERMY_RANGE_RATE));
                mSubRange = 0;
                mPower = ENERMY_BOMBER_CANNON_POWER * reinforce;
                mSubPower = 0;
                mWeaponCoolTimeMax = 60.0 / (ENERMY_BOMBER_CANNON_SPM * (1.0 + (reinforce / ENERMY_SPM_RATE)));
                mSubWeaponCoolTimeMax = 0;
                shadow = Sprite::createWithSpriteFrameName("bomber_s.png");
                shadow->setPosition(Vec2(35, -30));
                wingtailL = Sprite::createWithSpriteFrameName("tail.png");
                wingtailL->setPosition(Vec2(0, 70));
                wingtailR = Sprite::createWithSpriteFrameName("tail.png");
                wingtailR->setPosition(Vec2(getContentSize().width-2, 70));
                break;
            case UNIT_STRATEGIC:
                mSpeed = SPEED_STRATEGYBOMBER;
                mScore = ENERMY_STRATEGYBOMBER_SCORE * reinforce;
                mEnergy = mMaxEnergy = ENERMY_STRATEGYBOMBER_HP * reinforce;
                mRange = ENERMY_STRATEGYBOMBER_BOMB_RANGE * (1.0 + (reinforce / ENERMY_RANGE_RATE));
                mSubRange = 0;
                mPower = ENERMY_STRATEGYBOMBER_BOMB_POWER * reinforce;
                mSubPower = 0;
                mWeaponCoolTimeMax = 60.0 / (ENERMY_STRATEGYBOMBER_BOMB_SPM * (1.0 + (reinforce / ENERMY_SPM_RATE)));
                mSubWeaponCoolTime = mSubWeaponCoolTimeMax = 0;
                shadow = Sprite::createWithSpriteFrameName("b52h_s.png");
                shadow->setPosition(Vec2(100, -45));
                wingtailL = Sprite::createWithSpriteFrameName("tail.png");
                wingtailL->setPosition(Vec2(1, 160));
                wingtailR = Sprite::createWithSpriteFrameName("tail.png");
                wingtailR->setPosition(Vec2(getContentSize().width-2, 160));
                break;
            case UNIT_SUBMARINE:
                mSpeed = SPEED_SUBMARINE;
                mScore = ENERMY_SUBMARINE_SCORE * reinforce;
                mEnergy = mMaxEnergy = ENERMY_SUBMARINE_HP * reinforce;
                mRange = ENERMY_SUBMARINE_TORPEDO_RANGE * (1.0 + (reinforce / ENERMY_RANGE_RATE));
                mSubRange = 0;
                mPower = ENERMY_SUBMARINE_TORPEDO_POWER * reinforce;
                mSubPower = 0;
                mWeaponCoolTimeMax = 60.0 / (ENERMY_SUBMARINE_TORPEDO_SPM * (1.0 + (reinforce / ENERMY_SPM_RATE)));
                mSubWeaponCoolTimeMax = 0;
                detected = Sprite::createWithSpriteFrameName("sub_j00.png");
                detected->setAnchorPoint(Vec2(0, 0));
                detected->setTag(TAG_DETECTED);
                detected->setVisible(false);
                mDetected = false;
                break;
        }
        
        SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
        if(front)
        {
            addChild(front, -1);
            Animation* animation = Animation::create();
            animation->addSpriteFrame(frameCache->getSpriteFrameByName("shiptail03.png"));
            animation->addSpriteFrame(frameCache->getSpriteFrameByName("shiptail04.png"));
            animation->setDelayPerUnit(0.25);
            front->runAction(RepeatForever::create(Animate::create(animation)));
        }
        
        if(tail)
        {
            addChild(tail, -1);
            Animation* animation = Animation::create();
            animation->addSpriteFrame(frameCache->getSpriteFrameByName("shiptail02_03.png"));
            animation->addSpriteFrame(frameCache->getSpriteFrameByName("shiptail02_04.png"));
            animation->setDelayPerUnit(0.25);
            tail->runAction(RepeatForever::create(Animate::create(animation)));
        }
        
        if(propeller)
        {
            addChild(propeller);
            propeller->runAction(RepeatForever::create(RotateBy::create(1.2, 360)));
        }
        
        if(shadow)
        {
            addChild(shadow, -1);
        }
        
        if(backFire)
        {
            addChild(backFire);
            backFire->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.18, 0.6),
                                                                       ScaleTo::create(0.18, 0.9),
                                                                       nullptr)));
        }
        
        if(backFire2)
        {
            addChild(backFire2);
            backFire2->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.18, 0.6),
                                                                       ScaleTo::create(0.18, 0.9),
                                                                       nullptr)));
        }
        
        if(wingtailL && wingtailR)
        {
            addChild(wingtailR, -1);
            addChild(wingtailL, -1);
        }
        
        if(detected)
        {
            addChild(detected);
        }
        
        if(radar)
        {
            addChild(radar, -1);
        }
        
        
        return true;
    }
    else
    {
        return false;
    }
}

int SpriteUnit::getType()
{
    return mType;
}

bool SpriteUnit::isSubmarine()
{
    return mType <= UNIT_KSS3;
}

bool SpriteUnit::isShip()
{
    return UNIT_PATROL <= mType && mType <= UNIT_DOKDO;
}

bool SpriteUnit::isAir()
{
    return mType >= UNIT_BOMBER;
}

bool SpriteUnit::isHelicopter()
{
    return mType == UNIT_LYNX || mType == UNIT_HELICOPTER;
}

bool SpriteUnit::isSurface()
{
    return mType < UNIT_BOMBER;
}

bool SpriteUnit::isWaterLevel()
{
    return mType < UNIT_LYNX;
}

bool SpriteUnit::isEnermy()
{
    return mEnermy;
}

void SpriteUnit::setDetected(bool detected)
{
    if(isSubmarine())
    {
        mDetected = detected;
        Sprite* detected = ((Sprite*)getChildByTag(TAG_DETECTED));
        if(detected)
        {
            detected->setVisible(mDetected);
        }
    }
}

void SpriteUnit::setEnergy(float energy)
{
    mEnergy = mMaxEnergy = energy;
    mWeaponCoolTime = mSubWeaponCoolTime = mEnergyBarTime = 0;
}

float SpriteUnit::subEnergy(float damage)
{
    mEnergyBarTime = ENERGYBAR_SHOWTIME;
    mEnergy -= damage;
    if(mEnergy < 0)
        mEnergy = 0;
    else if(mEnergy > mMaxEnergy)
        mEnergy = mMaxEnergy;
    
    showEnergyBar();
    
    return mEnergy;
}

void SpriteUnit::update(float dt)
{
    if(mEnergyBarTime > 0)
    {
        mEnergyBarTime -= dt;
        if(mEnergyBarTime <= 0)
        {
            mEnergyBarTime = 0;
            ((Sprite*)getChildByTag(TAG_ENERGYBAR))->setVisible(false);
        }
    }
    
    if(mWeaponCoolTime > 0)
    {
        mWeaponCoolTime -= dt;
        if(mWeaponCoolTime < 0)
        {
            mWeaponCoolTime = 0;
        }
    }
    
    if(mSubWeaponCoolTime > 0)
    {
        mSubWeaponCoolTime -= dt;
        if(mSubWeaponCoolTime < 0)
        {
            mSubWeaponCoolTime = 0;
        }
    }
}

void SpriteUnit::showEnergyBar()
{
    Sprite* energy = (Sprite*)getChildByTag(TAG_ENERGYBAR);
    
    if(energy)
    {
        energy->setVisible(true);
        Sprite* inner = (Sprite*)energy->getChildByTag(TAG_ENERGYBAR_INNER);
        inner->setScaleX(mEnergy / mMaxEnergy);
        
        mEnergyBarTime = ENERGYBAR_SHOWTIME;
    }
}

//
//  SceneGame.h
//  MyCppGame
//
//  Created by Jinryul Kim on 2014. 7. 25..
//
//

#ifndef __DokdoDefenceCommand__SceneGame__
#define __DokdoDefenceCommand__SceneGame__

#include "cocos2d.h"
#include "Defines.h"
#include "SceneMenu.h"
#include "SpriteScoreBoard.h"
#include "SpriteUnit.h"
#include "SaveManager.h"
#include "DokdoCalculator.h"
#include "SpriteFire.h"

#define DOKDO_XPOS      240
#define DOKDO_YPOS      200

#define DOKDO_ENERGY            1000

#define PARTICLE_MAX    10

#define MINIMUM_DISTANCE   180     // 적 / 아군 과의 기본거리

#define IMCOME_RATE		0.5f	// 점수 대비 획득 자금 비율  ex) 0.5 -> 의 50%

class SceneGame : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene(int difficulty);
    virtual bool init();
    CREATE_FUNC(SceneGame);
    
    bool isPaused();
    void setDifficulty(int difficulty);
    
private:
    virtual void onTouchesBegan(std::vector<cocos2d::Touch*> touches, cocos2d::Event* event);
    virtual void onTouchesMoved(std::vector<cocos2d::Touch*> touches, cocos2d::Event* event);
    virtual void onTouchesEnded(std::vector<cocos2d::Touch*> touches, cocos2d::Event* event);
    cocos2d::EventListenerTouchAllAtOnce* mTouchListener;
    
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
    
    void initParticles();
    void initValiablies();
    void addShoot(float dt);
    void update(float dt);
    void updateTime(float dt);
    void addCloud(float dt);
    void startGame(float dt);
    void selfRemover(cocos2d::Node* sender);
    void Loading();
    void AddWeaponBtn(std::string txtpath, std::string imgpath, cocos2d::Vec2 pt, int tag);
    void AddSummonBtn(bool rev, float y, int tag, std::string innerpath);
    void addEnermy();
    void moveBtn(cocos2d::Sprite* spBtn, bool rev, int price, bool disable = false);
    void updateSummonBtn();
    void updateWeaponBtn();
    bool selectWeapon(cocos2d::Vec2 pt);
    bool selectSummon(cocos2d::Vec2 pt);
    void fireBullet(cocos2d::Vec2 origin,
                    cocos2d::Vec2 target,
                    float damage,
                    bool enermy,
                    float speed,
                    FIRE_TYPE fireType,
                    FIRE_TARGET targetType);
    void fireMissile(cocos2d::Vec2 origin,
                     cocos2d::Vec2 target,
                     float damage,
                     bool enermy);
    void fireTorpedo(cocos2d::Vec2 origin,
                     cocos2d::Vec2 target,
                     float damage,
                     bool enermy);
    void fireBomb(cocos2d::Vec2 origin,
                  cocos2d::Vec2 target,
                  float damage,
                  bool enermy);
    void fireNuclear();
    void fireF15K();
    
    cocos2d::Vec2 getTargetPos(cocos2d::Vec2 target, float distance, int error);
    void moveUnits(float dt);
    bool checkPause(cocos2d::Vec2 pt);
    void checkWeapons();
    bool fireMatch(FIRE_TARGET target, int unitType);
    void showDokdoEnergyBar();
    
    bool addUnit(int type, float reinforce, bool enermy, bool beginEnermy = false);
    bool addLynx(float reinforce, int probability);
    void addEnermyVERYEASY(float fReinforce);
    void addEnermyEASY(float fReinforce);
    void addEnermyNORMAL(float fReinforce);
    void addEnermyHARD(float fReinforce);
    void addEnermyVERYHARD(float fReinforce);
    void addEnermyIMPOSSIBLE(float fReinforce);
    void addEnermyENDLESS(float fReinforce);
    
    bool getNewEnermyPosition(SpriteUnit* sprite, bool begin);
    bool getNewForcePosition(SpriteUnit* unit);
    
    void addWaterColumn(cocos2d::Vec2 pt, float scale, float delayPerUnit);
    void addExplosion(cocos2d::Vec2 pt, float scale, float delayPerUnit, bool surface);
    void addShootFire(cocos2d::Vec2 pt, float scale, float delayPerUnit, float angle);
    void weaponFinished(cocos2d::Node* node);
    void f15kFinished(cocos2d::Node* node);
    void bombFinished(cocos2d::Node* node);
    void addParticleFlash(cocos2d::Vec2 pt);
    void addParticleExplosion(cocos2d::Vec2 pt, float scale);
    
    void destroyGame(int income, bool highscore);
    void resumeGame();
    void pauseGame();
    
    cocos2d::Size mWinSize;
    DDC_SAVE_DATA* mSaveData;
    int mDifficulty;
    cocos2d::SpriteBatchNode* sbnShoot;
    cocos2d::SpriteBatchNode* batchSurface, *batchSurfaceFire, *batchAir, *batchAirFire, *batchInterface;
    float mfClearTime, mfReinforce, mfReinforceVariation, mfAddEnermyTime ,mfAddEnermyVariation, mfCurEnermyTime, mGameFinishTerm;
    cocos2d::Vec2 ptDokdo;
    
    int mUnitCnt, mPKGCnt, mKDX2Cnt, mKDX3Cnt, mDOKDOCnt, mE747Cnt, mKSS3Cnt;
    int mCruiserCnt, mCarrierCnt, mStrategyBomberCtn;
    
    float   mVulcanCoolTime, mCannonCoolTime, mMissileCoolTime,
            mVulcanCoolTimeMax, mCannonCoolTimeMax, mMissileCoolTimeMax,
            mVulcanRange, mCannonRange, mMissileRange,
            mVulcanPower, mCannonPower, mMissilePower;
    
    int mPKGPrice, mKDX2Price, mKSS3Price, mE747Price, mKDX3Price, mDOKDOPrice, mNUCLEARPrice, mF15KPrice;
    float mDokdoHP, mDokdoMaxHP;
    float mHPShowTime;
    SpriteScoreBoard* mScoreBoard;
    
    float mMineralTime;
    int mMineral, mNuclearMineral, mF15KMineral;
    int mEnermyCtn, mForceCtn;
    
    int mSelectedWeapon;
    int mGameState;
    
    std::vector<SpriteFire*> mArrFires;
    std::vector<SpriteFire*> mArrEnermyFires;
    std::vector<SpriteUnit*> mArrUnits;
    std::vector<SpriteUnit*> mArrEnermies;
    std::vector<cocos2d::ParticleSystemQuad*> mArrParticleFlash;
    std::vector<cocos2d::ParticleSystemQuad*> mArrParticleExplosions;
    
    float m180PI;                                // 자주 계산되는 값, 180.0 / Math.PI
    float mPI180;                                 // 자주 계산되는 값, Math.PI / 180.0
};

#endif /* defined(__DokdoDefenceCommand__SceneGame__) */

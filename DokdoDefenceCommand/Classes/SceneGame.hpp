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
#include "SceneMenu.hpp"
#include "SpriteScoreBoard.hpp"
#include "SpriteUnit.hpp"
#include "SaveManager.hpp"
#include "DokdoCalculator.hpp"
#include "SpriteFire.hpp"

#define DOKDO_XPOS      240
#define DOKDO_YPOS      200

#define DOKDO_ENERGY            1000

#define PARTICLE_MAX    10

#define MINIMUM_DISTANCE   180     // 적 / 아군 과의 기본거리

#define IMCOME_RATE		0.5f	// 점수 대비 획득 자금 비율  ex) 0.5 -> 의 50%

USING_NS_CC;
using namespace std;

class SceneGame : public Layer
{
public:
    static Scene* createScene(int difficulty);
    virtual bool init();
    CREATE_FUNC(SceneGame);
    
    bool isPaused();
    void setDifficulty(int difficulty);
    
private:
    virtual void onTouchesBegan(vector<Touch*> touches, Event* event);
    virtual void onTouchesMoved(vector<Touch*> touches, Event* event);
    virtual void onTouchesEnded(vector<Touch*> touches, Event* event);
    EventListenerTouchAllAtOnce* mTouchListener;
    
    void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
    
    void initParticles();
    void initValiablies();
    void addShoot(float dt);
    void update(float dt);
    void updateTime(float dt);
    void addCloud(float dt);
    void startGame(float dt);
    void selfRemover(Node* sender);
    void Loading();
    void AddWeaponBtn(string txtpath, string imgpath, Vec2 pt, int tag);
    void AddSummonBtn(bool rev, float y, int tag, string innerpath);
    void addEnermy();
    void moveBtn(Sprite* spBtn, bool rev, int price, bool disable = false);
    void updateSummonBtn();
    void updateWeaponBtn();
    bool selectWeapon(Vec2 pt);
    bool selectSummon(Vec2 pt);
    void fireBullet(Vec2 origin,
                    Vec2 target,
                    float damage,
                    bool enermy,
                    float speed,
                    FIRE_TYPE fireType,
                    FIRE_TARGET targetType);
    void fireMissile(Vec2 origin,
                     Vec2 target,
                     float damage,
                     bool enermy);
    void fireTorpedo(Vec2 origin,
                     Vec2 target,
                     float damage,
                     bool enermy);
    void fireBomb(Vec2 origin,
                  Vec2 target,
                  float damage,
                  bool enermy);
    void fireNuclear();
    void fireF15K();
    
    Vec2 getTargetPos(Vec2 target, float distance, int error);
    void moveUnits(float dt);
    bool checkPause(Vec2 pt);
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
    
    void addWaterColumn(Vec2 pt, float scale, float delayPerUnit);
    void addExplosion(Vec2 pt, float scale, float delayPerUnit, bool surface);
    void addShootFire(Vec2 pt, float scale, float delayPerUnit, float angle);
    void weaponFinished(Node* node);
    void f15kFinished(Node* node);
    void bombFinished(Node* node);
    void addParticleFlash(Vec2 pt);
    void addParticleExplosion(Vec2 pt, float scale);
    
    void destroyGame(int income, bool highscore);
    void resumeGame();
    void pauseGame();
    
    Size mWinSize;
    DDC_SAVE_DATA* mSaveData;
    int mDifficulty;
    SpriteBatchNode* sbnShoot;
    SpriteBatchNode* batchSurface, *batchSurfaceFire, *batchAir, *batchAirFire, *batchInterface;
    float mfClearTime, mfReinforce, mfReinforceVariation, mfAddEnermyTime ,mfAddEnermyVariation, mfCurEnermyTime, mGameFinishTerm;
    Vec2 ptDokdo;
    
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
    
    vector<SpriteFire*> mArrFires;
    vector<SpriteFire*> mArrEnermyFires;
    vector<SpriteUnit*> mArrUnits;
    vector<SpriteUnit*> mArrEnermies;
    vector<ParticleSystemQuad*> mArrParticleFlash;
    vector<ParticleSystemQuad*> mArrParticleExplosions;
    
    float m180PI;                                // 자주 계산되는 값, 180.0 / Math.PI
    float mPI180;                                 // 자주 계산되는 값, Math.PI / 180.0
};

#endif /* defined(__DokdoDefenceCommand__SceneGame__) */

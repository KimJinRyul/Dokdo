//
//  SceneGame.cpp
//  MyCppGame
//
//  Created by Jinryul Kim on 2014. 7. 25..
//
//

#include "SceneGame.h"
#include "SoundManager.h"

USING_NS_CC;
using namespace std;

Scene* SceneGame::createScene(int difficulty)
{
    Scene* scene = Scene::create();
    scene->setTag(SCENE_TAG_GAME);
    SceneGame* game = SceneGame::create();
    game->setTag(LAYER_TAG_GAME);
    game->setDifficulty(difficulty);
    
    scene->addChild(game);
    
    return scene;
}

void SceneGame::setDifficulty(int difficulty)
{
    mDifficulty = difficulty;
    switch(mDifficulty)
    {
        case MENU_TAG_VERYEASY:
            mfClearTime = VERYEASY_CLEAR_TIME;
            mfReinforce = VERYEASY_REINFORCE_MIN;
            mfReinforceVariation = VERYEASY_REINFORCE_VARIATION;
            mfAddEnermyTime = VERYEASY_ADDENERMY_MIN;
            mfAddEnermyVariation = VERYEASY_ADDENERMY_VARIATION;
            break;
        case MENU_TAG_EASY:
            mfClearTime = EASY_CLEAR_TIME;
            mfReinforce = EASY_REINFORCE_MIN;
            mfReinforceVariation = EASY_REINFORCE_VARIATION;
            mfAddEnermyTime = EASY_ADDENERMY_MIN;
            mfAddEnermyVariation = EASY_ADDENERMY_VARIATION;
            break;
        case MENU_TAG_NORMAL:
            mfClearTime = NORMAL_CLEAR_TIME;
            mfReinforce = NORMAL_REINFORCE_MIN;
            mfReinforceVariation = NORMAL_REINFORCE_VARIATION;
            mfAddEnermyTime = NORMAL_ADDENERMY_MIN;
            mfAddEnermyVariation = NORMAL_ADDENERMY_VARIATION;
            break;
        case MENU_TAG_HARD:
            mfClearTime = HARD_CLEAR_TIME;
            mfReinforce = HARD_REINFORCE_MIN;
            mfReinforceVariation = HARD_REINFORCE_VARIATION;
            mfAddEnermyTime = HARD_ADDENERMY_MIN;
            mfAddEnermyVariation = HARD_ADDENERMY_VARIATION;
            break;
        case MENU_TAG_VERYHARD:
            mfClearTime = VERYHARD_CLEAR_TIME;
            mfReinforce = VERYHARD_REINFORCE_MIN;
            mfReinforceVariation = VERYHARD_REINFORCE_VARIATION;
            mfAddEnermyTime = VERYHARD_ADDENERMY_MIN;
            mfAddEnermyVariation = VERYHARD_ADDENERMY_VARIATION;
            break;
        case MENU_TAG_IMPOSSIBLE:
            mfClearTime = IMPOSSIBLE_CLEAR_TIME;
            mfReinforce = IMPOSSIBLE_REINFORCE_MIN;
            mfReinforceVariation = IMPOSSIBLE_REINFORCE_VARIATION;
            mfAddEnermyTime = IMPOSSIBLE_ADDENERMY_MIN;
            mfAddEnermyVariation = IMPOSSIBLE_ADDENERMY_VARIATION;
            break;
        case MENU_TAG_ENDLESS:
            mfClearTime = ENDLESS_CLEAR_TIME;
            mfReinforce = ENDLESS_REINFORCE_MIN;
            mfReinforceVariation = ENDLESS_REINFORCE_VARIATION;
            mfAddEnermyTime = ENDLESS_ADDENERMY_MIN;
            mfAddEnermyVariation = ENDLESS_ADDENERMY_VARIATION;
            break;
    }
}

void SceneGame::initValiablies()
{
    mGameState = GAME_STATE_LOADING;
    mfCurEnermyTime = 0.f;
    mGameFinishTerm = 0.f;
    mEnermyCtn = mForceCtn = 0;
    mSaveData = SaveManager::load();
    mWinSize = Director::getInstance()->getWinSize();
    ptDokdo = Vec2(DOKDO_XPOS, DOKDO_YPOS);
    
    mDokdoHP = mDokdoMaxHP = DOKDO_ENERGY + (30 * (mSaveData->dokdoLv.nVulcanLv +
                                                   mSaveData->dokdoLv.nCannonLv +
                                                   mSaveData->dokdoLv.nMissileLv));
    
    srand(DokdoCalculator::getCurrentTime());
    
    mHPShowTime = 0;
    mVulcanCoolTime = mCannonCoolTime = mMissileCoolTime = 0;
    mMineralTime = 0;
    mMineral = 0;
    mNuclearMineral = FORCE_NUCLEAR_PRICE * 0.5;    mF15KMineral = FORCE_F15K_PRICE * 0.5;
    // for TEST
    //mMineral = MINERAL_MAX;
    //mNuclearMineral = FORCE_NUCLEAR_PRICE;    mF15KMineral = FORCE_F15K_PRICE;
    
    mSelectedWeapon = 0;
    
    m180PI = (float)(180.0 / M_PI);
    mPI180 = (float)(M_PI / 180.0);
    
    mUnitCnt = mPKGCnt = mKDX2Cnt = mKDX3Cnt = mDOKDOCnt = mE747Cnt = mKSS3Cnt = 0;
    mCruiserCnt = mCarrierCnt = mStrategyBomberCtn = 0;
    
    mVulcanCoolTimeMax = DokdoCalculator::getDokdoCoolTime(DOKDO_VULCAN_SPM, mSaveData->dokdoLv.nVulcanLv);
    mCannonCoolTimeMax = DokdoCalculator::getDokdoCoolTime(DOKDO_CANNON_SPM, mSaveData->dokdoLv.nCannonLv);
    mMissileCoolTimeMax = DokdoCalculator::getDokdoCoolTime(DOKDO_MISSILE_SPM, mSaveData->dokdoLv.nMissileLv);
    
    mVulcanPower = DokdoCalculator::getDokdoDamage(DOKDO_VULCAN_POWER, mSaveData->dokdoLv.nVulcanLv);
    mCannonPower = DokdoCalculator::getDokdoDamage(DOKDO_CANNON_POWER, mSaveData->dokdoLv.nCannonLv);
    mMissilePower = DokdoCalculator::getDokdoDamage(DOKDO_MISSILE_POWER, mSaveData->dokdoLv.nMissileLv);
    
    mVulcanRange = DokdoCalculator::getDokdoRange(DOKDO_VULCAN_RANGE, mSaveData->dokdoLv.nVulcanLv);
    mCannonRange = DokdoCalculator::getDokdoRange(DOKDO_CANNON_RANGE, mSaveData->dokdoLv.nCannonLv);
    mMissileRange = DokdoCalculator::getDokdoRange(DOKDO_MISSILE_RANGE, mSaveData->dokdoLv.nMissileLv);
    
    mPKGPrice = DokdoCalculator::getUnitPrice(FORCE_PKG_PRICE, mSaveData->unitLv.nPKGLv, 5);
    mKDX2Price = DokdoCalculator::getUnitPrice(FORCE_KDX2_PRICE, mSaveData->unitLv.nKDX2Lv, 5);
    mKDX3Price = DokdoCalculator::getUnitPrice(FORCE_KDX3_PRICE, mSaveData->unitLv.nKDX3Lv, 6);
    mKSS3Price = DokdoCalculator::getUnitPrice(FORCE_KSS3_PRICE, mSaveData->unitLv.nKSS3Lv, 8);
    mE747Price = DokdoCalculator::getUnitPrice(FORCE_E747_PRICE, mSaveData->unitLv.nE747Lv, 7);
    mDOKDOPrice = DokdoCalculator::getUnitPrice(FORCE_DOKDO_PRICE, mSaveData->unitLv.nDOKDOLv, 10);
    mF15KPrice = DokdoCalculator::getUnitPrice(FORCE_F15K_PRICE, mSaveData->unitLv.nF15KLv, 10);
    mNUCLEARPrice = DokdoCalculator::getUnitPrice(FORCE_NUCLEAR_PRICE,
                                                  (mSaveData->dokdoLv.nVulcanLv + mSaveData->dokdoLv.nCannonLv + mSaveData->dokdoLv.nMissileLv) / 3,
                                                  1);
}

bool SceneGame::init()
{
    if(!Layer::init())
    {
        return false;
    }

    initValiablies();
    
    Label* labelLoading = LabelCreater::createLabel("Combat readiness", "Capsmall.ttf", 40);
    labelLoading->setPosition(Vec2(mWinSize.width/2, mWinSize.height/2));
    addChild(labelLoading, 2, GAME_TAG_NOWLOADING);

    labelLoading->runAction(RepeatForever::create(Sequence::create(RotateTo::create(1, 6),
                                                                   RotateTo::create(1, -6),
                                                                   nullptr)));
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Shoot.plist");
    sbnShoot = SpriteBatchNode::create("Shoot.png");
    addChild(sbnShoot, 1, GAME_TAG_SHOOT_BATCHNODE);
    
    mTouchListener = EventListenerTouchAllAtOnce::create();
    mTouchListener->onTouchesBegan = CC_CALLBACK_2(SceneGame::onTouchesBegan, this);
    mTouchListener->onTouchesMoved = CC_CALLBACK_2(SceneGame::onTouchesMoved, this);
    mTouchListener->onTouchesEnded = CC_CALLBACK_2(SceneGame::onTouchesEnded, this);
    getEventDispatcher()->addEventListenerWithFixedPriority(mTouchListener, 1);
    
    schedule(schedule_selector(SceneGame::addShoot), 0.2);
    Loading();
    
    setKeypadEnabled(true);
    
    return true;
}

void SceneGame::Loading()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Explosion.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Game.plist");
    
    batchSurface = SpriteBatchNode::create("Game.png");
    batchSurfaceFire = SpriteBatchNode::create("Explosion.png");
    batchAir = SpriteBatchNode::create("Game.png");
    batchAirFire = SpriteBatchNode::create("Explosion.png");
    batchInterface = SpriteBatchNode::create("Game.png");
    
    addChild(batchSurface, GAME_ZORDER_SURFACE);
    addChild(batchSurfaceFire, GAME_ZORDER_SURFACEFIRE);
    addChild(batchAir, GAME_ZORDER_AIR);
    addChild(batchAirFire, GAME_ZORDER_AIRFIRE);
    addChild(batchInterface, GAME_ZORDER_INTERFACE);
        
    BlendFunc bf = {GL_ONE, GL_ONE};
    batchSurfaceFire->setBlendFunc(bf);
    batchAirFire->setBlendFunc(bf);
    
    BlendFunc bf2 = {GL_DST_ALPHA, GL_ONE_MINUS_SRC_ALPHA};
    batchSurface->setBlendFunc(bf2);
    batchAir->setBlendFunc(bf2);
    batchInterface->setBlendFunc(bf2);
    
    scheduleOnce(schedule_selector(SceneGame::startGame), 2.5f);
}

void SceneGame::AddWeaponBtn(string txtpath, string imgpath, Vec2 pt, int tag)
{
    Sprite *spBK = Sprite::createWithSpriteFrameName("controller_back.png");
    spBK->setOpacity(120);
    spBK->setAnchorPoint(Vec2(0.5, 0));
    spBK->setPosition(pt);
    
    Sprite *spTEXT = Sprite::createWithSpriteFrameName(txtpath);
    spTEXT->setAnchorPoint(Vec2(0.5, 0));
    spTEXT->setPosition(Vec2(spBK->getContentSize().width / 2, 0));
    spBK->addChild(spTEXT);
    
    Sprite *spACTIVATE = Sprite::createWithSpriteFrameName("controller_active.png");
    spACTIVATE->setPosition(Vec2(spBK->getContentSize().width / 2, spBK->getContentSize().height * 0.59));
    spACTIVATE->setOpacity(120);
    spACTIVATE->setScale(0.7f);
    spBK->addChild(spACTIVATE, 1, GAME_TAG_BTN_ACTIVATE);
    
    Sprite *spIMAGE = Sprite::createWithSpriteFrameName(imgpath);
    spIMAGE->setPosition(Vec2(spBK->getContentSize().width / 2, spBK->getContentSize().height * 0.6));
    spIMAGE->setOpacity(120);
    spBK->addChild(spIMAGE, 2, GAME_TAG_BTN_INNERIMG);
    
    batchInterface->addChild(spBK, 0, tag);
}

void SceneGame::AddSummonBtn(bool rev, float y, int tag, string innerpath)
{
    Sprite *spBTN = Sprite::createWithSpriteFrameName(innerpath);
    spBTN->setAnchorPoint(Vec2(rev ? 0 : 1, 0.5));
    spBTN->setPosition(Vec2(rev ? mWinSize.width : 0, y));
    spBTN->setTag(tag);
    batchInterface->addChild(spBTN);
}

void SceneGame::startGame(float dt)
{
    unschedule(schedule_selector(SceneGame::addShoot));
    sbnShoot->removeFromParentAndCleanup(true);
    sbnShoot = nullptr;
    
    Sprite *spSEA = Sprite::create("SEA.png");
    spSEA->setPosition(Vec2(mWinSize.width / 2, mWinSize.height / 2));
    addChild(spSEA, GAME_ZORDER_SEA, GAME_TAG_SEA);
    
    Sprite* spMAXRADAR = Sprite::createWithSpriteFrameName("radar_00.png");
    spMAXRADAR->setPosition(ptDokdo);
    spMAXRADAR->setOpacity(80);
    spMAXRADAR->setVisible(false);
    batchSurface->addChild(spMAXRADAR, GAME_SURFACE_ZORDER_RADAR, GAME_TAG_RADAR_MAX);
    spMAXRADAR->runAction(RepeatForever::create(Sequence::create(FadeOut::create(2.5), FadeIn::create(0), nullptr)));
    
    Sprite *spRADARLINE = Sprite::createWithSpriteFrameName("radar_01.png");
    spRADARLINE->setAnchorPoint(Vec2(1, 0));
    spRADARLINE->setPosition(ptDokdo);
    spRADARLINE->setOpacity(160);
    spRADARLINE->setVisible(false);
    spRADARLINE->setScale(mWinSize.height / spRADARLINE->getContentSize().height);
    batchSurface->addChild(spRADARLINE, GAME_SURFACE_ZORDER_RADAR, GAME_TAG_RADAR_LINE);
    spRADARLINE->runAction(RepeatForever::create(RotateBy::create(8, 360)));
    
    Sprite *spCANNONRADAR = Sprite::createWithSpriteFrameName("radar_00.png");
    spCANNONRADAR->setPosition(ptDokdo);
    spCANNONRADAR->setOpacity(80);
    spCANNONRADAR->setVisible(false);
    batchSurface->addChild(spCANNONRADAR, GAME_SURFACE_ZORDER_RADAR, GAME_TAG_RADAR_CANNON);
    
    ScaleTo *scale1 = ScaleTo::create(2.5, mCannonRange / (spCANNONRADAR->getContentSize().width / 2));
    ScaleTo *scale2 = ScaleTo::create(0, 0);
    spCANNONRADAR->runAction(RepeatForever::create(Sequence::create(scale1, scale2, nullptr)));
    
    Sprite *spMISSILERADAR = Sprite::createWithSpriteFrameName("radar_00.png");
    spMISSILERADAR->setPosition(ptDokdo);
    spMISSILERADAR->setOpacity(80);
    spMISSILERADAR->setVisible(false);
    batchSurface->addChild(spMISSILERADAR, GAME_SURFACE_ZORDER_RADAR, GAME_TAG_RADAR_MISSILE);
    
    scale1 = ScaleTo::create(2.5, mMissileRange / (spMISSILERADAR->getContentSize().width / 2));
    scale2 = ScaleTo::create(0, 0);
    spMISSILERADAR->runAction(RepeatForever::create(Sequence::create(scale1, scale2, nullptr)));
    
    Sprite* spDokdo = Sprite::createWithSpriteFrameName("DOKDO.png");
    spDokdo->setPosition(ptDokdo);
    batchSurface->addChild(spDokdo, GAME_SURFACE_ZORDER_DOKDO, GAME_TAG_DOKDO);
    
    Sprite* energyBK = Sprite::createWithSpriteFrameName("energybar2.png");
    energyBK->setScaleX(spDokdo->getContentSize().width / energyBK->getContentSize().width);
    energyBK->setAnchorPoint(Vec2(1, 0));
    energyBK->setPosition(Vec2(320, 165));
    batchInterface->addChild(energyBK, 10, GAME_TAG_DOKDO_ENERGYBAR);
    Sprite* energyInner = Sprite::createWithSpriteFrameName("energybar.png");
    energyInner->setAnchorPoint(Vec2(1, 0));
    energyInner->setPosition(Vec2(energyBK->getContentSize().width, 0));
    energyInner->setTag(GAME_TAG_DOKDO_ENERGYBAR_INNER);
    energyBK->addChild(energyInner);
    energyBK->setVisible(false);
    
    Label* energyLabel = LabelCreater::createLabel("5500 / 5500", "OneSlot.ttf", 20);
    energyLabel->setPosition(Vec2(mWinSize.width/2, 150));
    addChild(energyLabel, GAME_ZORDER_INTERFACE, GAME_TAG_LABEL_DOKDOENERGY);
    energyLabel->setVisible(false);
    
    AddWeaponBtn("controller_taxt_cannon.png",
                 "controller_cannon_00.png",
                 Vec2(mWinSize.width * 0.28, 0),
                 GAME_TAG_BTN_CANNON);
    AddWeaponBtn("controller_taxt_missile.png",
                 "controller_missile_00.png",
                 Vec2(mWinSize.width * 0.72, 0),
                 GAME_TAG_BTN_MISSILE);
    
    AddSummonBtn(false, mWinSize.height * 0.50, GAME_TAG_BTN_PKG, "button_pkg711.png");
    AddSummonBtn(true, mWinSize.height * 0.50, GAME_TAG_BTN_KDX2, "button_kdx2.png");
    AddSummonBtn(false, mWinSize.height * 0.405, GAME_TAG_BTN_KSS3, "button_kss.png");
    AddSummonBtn(true, mWinSize.height * 0.405, GAME_TAG_BTN_E747, "button_e737.png");
    AddSummonBtn(false, mWinSize.height * 0.31, GAME_TAG_BTN_KDX3, "button_kdx3.png");
    AddSummonBtn(true, mWinSize.height * 0.31, GAME_TAG_BTN_DOKDO, "button_dokdoship.png");
    AddSummonBtn(true, mWinSize.height * 0.215, GAME_TAG_BTN_F15K, "button_f15k.png");
    // 핵무기 소환
    Sprite *spBTN = Sprite::createWithSpriteFrameName("button_empty.png");
    spBTN->setAnchorPoint(Vec2(1, 0.5));
    spBTN->setPosition(Vec2(0, mWinSize.height * 0.215));
    spBTN->setTag(GAME_TAG_BTN_NUCLEAR);
    batchInterface->addChild(spBTN);
    
    Sprite *spINNER = Sprite::createWithSpriteFrameName("button_bomber.png");
    Size size = spINNER->getContentSize();
    spINNER->setPosition(Vec2((size.width / 2) + 5, size.height / 2));
    spBTN->addChild(spINNER, -1, GAME_TAG_BTN_INNERIMG);
    
    mScoreBoard = SpriteScoreBoard::create();
    mScoreBoard->setAnchorPoint(Vec2(0.5, 1));
    mScoreBoard->setPosition(Vec2(mWinSize.width/2, mWinSize.height));
    mScoreBoard->setTime(0);
    mScoreBoard->setScore(0);
    mScoreBoard->setHighScore(mSaveData->highscore[0].score);
    mScoreBoard->setMoney(mSaveData->nMoney);
    addChild(mScoreBoard, GAME_ZORDER_INTERFACE);
    
    CallFuncN* cf = CallFuncN::create(CC_CALLBACK_1(SceneGame::selfRemover, this));
    ((Label*)getChildByTag(GAME_TAG_NOWLOADING))->runAction(Sequence::create(FadeOut::create(0.8), cf, nullptr));
    
    initParticles();
    
    switch(mDifficulty)
    {
        case MENU_TAG_IMPOSSIBLE:
            addUnit(UNIT_STRATEGIC, mfReinforce, true, true);
        case MENU_TAG_VERYHARD:
            addUnit(UNIT_CARRIER, mfReinforce, true, true);
        case MENU_TAG_HARD:
            addUnit(UNIT_CRUISER, mfReinforce, true, true);
        case MENU_TAG_NORMAL:
        case MENU_TAG_ENDLESS:
            addUnit(UNIT_FIGHTER, mfReinforce, true, true);
        case MENU_TAG_EASY:
            addUnit(UNIT_BOMBER, mfReinforce, true, true);
            addUnit(UNIT_DESTROYER, mfReinforce, true, true);
        case MENU_TAG_VERYEASY:
            addUnit(UNIT_HELICOPTER, mfReinforce, true, true);
            addUnit(UNIT_PATROL, mfReinforce, true, true);
            break;
    }
    
    mGameState = GAME_STATE_PLAY;
    scheduleUpdate();
}

void SceneGame::showDokdoEnergyBar()
{
    mHPShowTime = 1.5;
    
    Sprite* energyBK = (Sprite*)batchInterface->getChildByTag(GAME_TAG_DOKDO_ENERGYBAR);
    Label* label = (Label*)getChildByTag(GAME_TAG_LABEL_DOKDOENERGY);
    
    if(energyBK && label)
    {
        char szTemp[32] = {0, };
        sprintf(szTemp, "%d / %d", (int)mDokdoHP, (int)mDokdoMaxHP);
        label->setString(szTemp);
        
        Sprite* inner = (Sprite*)energyBK->getChildByTag(GAME_TAG_DOKDO_ENERGYBAR_INNER);
        inner->setScaleX(mDokdoHP / mDokdoMaxHP);
        
        energyBK->setVisible(true);
        label->setVisible(true);
    }
}

void SceneGame::addShoot(float dt)
{
    if(sbnShoot != nullptr)
    {
        Vec2 pt = Vec2(50 + rand() % (int)(mWinSize.width - 100),
                       50 + rand() % (int)(mWinSize.height - 100));
        Sprite* spShoot = Sprite::createWithSpriteFrameName("main_shoot_00.png");
        spShoot->setPosition(pt);
        sbnShoot->addChild(spShoot);
        
        SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
        Animation* animation = Animation::create();
        animation->setDelayPerUnit(0.05);
        char szTEMP[64] = {0, };
        for(int i = 0; i < 9; i++)
        {
            sprintf(szTEMP, "main_shoot_%02d.png", i);
            animation->addSpriteFrame(frameCache->getSpriteFrameByName(szTEMP));
        }
        
        Animate* animate = Animate::create(animation);
        CallFuncN* callfunc = CallFuncN::create(CC_CALLBACK_1(SceneGame::selfRemover, this));
        Sequence* sequence = Sequence::create(animate, FadeOut::create(0.5), callfunc, nullptr);
        spShoot->runAction(sequence);
    }
}

void SceneGame::initParticles()
{
    for(int i = 0; i < PARTICLE_MAX; i++)
    {
        ParticleSystemQuad* explodingRing = ParticleSystemQuad::create("ExplodingRing.plist");
        explodingRing->setSpeed(70);
        explodingRing->setSpeedVar(130);
        explodingRing->setLife(0.2f);
        explodingRing->setLifeVar(0.5f);
        explodingRing->setAngle(rand() % 360);
        explodingRing->setAngleVar(270);
        explodingRing->setEmissionRate(10000);
        explodingRing->setScale(0.3f);
        explodingRing->stopSystem();
        addChild(explodingRing, GAME_ZORDER_SURFACEFIRE);
        mArrParticleFlash.push_back(explodingRing);
        
        explodingRing = ParticleSystemQuad::create("ExplodingRing.plist");
        explodingRing->setScale(1.f);
        explodingRing->stopSystem();
        addChild(explodingRing, GAME_ZORDER_SURFACEFIRE);
        mArrParticleExplosions.push_back(explodingRing);
    }
}

void SceneGame::addParticleFlash(Vec2 pt)
{
    static int curParticle = 0;
    mArrParticleFlash[curParticle]->setPosition(pt);
    mArrParticleFlash[curParticle]->resetSystem();
    if(++curParticle >= PARTICLE_MAX)
    {
        curParticle = 0;
    }
}

void SceneGame::addParticleExplosion(Vec2 pt, float scale)
{
    static int curParticle = 0;
    mArrParticleExplosions[curParticle]->setPosition(pt);
    mArrParticleExplosions[curParticle]->setScale(scale);
    mArrParticleExplosions[curParticle]->resetSystem();
    if(++curParticle >= PARTICLE_MAX)
    {
        curParticle = 0;
    }
}

void SceneGame::addCloud(float dt)
{
    static float cloudTime = 0.f;
    cloudTime += dt;
    if(cloudTime >= 1.2f)
    {
        cloudTime = 0;
        
        BlendFunc multiply = {GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA};
        
        int cloudNum = rand() % 3;
        char szFile[16] = {0, };
        sprintf(szFile, "cloud_%02d.png", cloudNum);
        Sprite* cloud = Sprite::create(szFile);
        cloud->setBlendFunc(multiply);
        
        float scale = 2.5 + (rand() % 25) / 10.f; // 1.0 ~ 2.0
        cloud->setScale(scale);
        
        float xPos = cloud->getBoundingBox().size.width / -2;
        float yPos = rand() % (int)mWinSize.height;
        cloud->setPosition(Vec2(xPos, yPos));
        
        MoveBy* moveBy = MoveBy::create(6.5f + (rand() % 40) / 10.f, Vec2(mWinSize.width + cloud->getBoundingBox().size.width, 0));
        CallFuncN* cf = CallFuncN::create(CC_CALLBACK_1(SceneGame::selfRemover, this));
        Sequence* sequence = Sequence::create(moveBy, cf, nullptr);
        
        cloud->runAction(sequence);
        
        addChild(cloud, GAME_ZORDER_CLOUD);
    }
}

void SceneGame::selfRemover(Node* sender)
{
    sender->removeFromParentAndCleanup(true);
}

void SceneGame::f15kFinished(Node* node)
{
    SpriteUnit* f15k = (SpriteUnit*)node;
    for(vector<SpriteUnit*>::iterator iter = mArrUnits.begin();
        iter != mArrUnits.end();
        iter++)
    {
        SpriteUnit* unit = (SpriteUnit*)*iter;
        if(f15k == unit)
        {
            mArrUnits.erase(iter);
            break;
        }
    }
    f15k->removeFromParentAndCleanup(true);
}

void SceneGame::updateTime(float dt)
{
    float oldTime = mScoreBoard->getTime();
    mScoreBoard->addTime(dt);
    mMineralTime += dt;
    mfCurEnermyTime += dt;
    while(mMineralTime >= MINERAL_TIME)
    {
        mMineral += MINERAL_GET;
        if(mMineral > MINERAL_MAX)          mMineral = MINERAL_MAX;
        
        mNuclearMineral += MINERAL_GET;
        if(mNuclearMineral > mNUCLEARPrice) mNuclearMineral = mNUCLEARPrice;
        
        mF15KMineral += MINERAL_GET;
        if(mF15KMineral > mF15KPrice)       mF15KMineral = mF15KPrice;
        
        mMineralTime -= MINERAL_TIME;
    }
    
    if(mVulcanCoolTime > 0)
    {
        mVulcanCoolTime -= dt;
        if(mVulcanCoolTime < 0)     mVulcanCoolTime = 0;
    }
    if(mCannonCoolTime > 0)
    {
        mCannonCoolTime -= dt;
        if(mCannonCoolTime < 0)     mCannonCoolTime = 0;
    }
    if(mMissileCoolTime > 0)
    {
        mMissileCoolTime -= dt;
        if(mMissileCoolTime < 0)     mMissileCoolTime = 0;
    }
    
    if(mHPShowTime > 0)
    {
        mHPShowTime -= dt;
        if(mHPShowTime < 0)
        {
            mHPShowTime = 0;
            batchInterface->getChildByTag(GAME_TAG_DOKDO_ENERGYBAR)->setVisible(false);
            getChildByTag(GAME_TAG_LABEL_DOKDOENERGY)->setVisible(false);
        }
    }
    
    // 도움말
    if(mDifficulty <= MENU_TAG_NORMAL)
    {
        bool bKorean = false;
        if(Application::getInstance()->getCurrentLanguage() == LanguageType::KOREAN)
        {
            bKorean = true;
        }
        
        if(oldTime < 2.0 && mScoreBoard->getTime() >= 2.0)  // 무기 선택
        {
            Label* tutorial = LabelCreater::createLabel(bKorean ? "무기를 선택" : "Choose your weapon", "JejuHallasan.ttf", 30);
            tutorial->setPosition(Vec2(mWinSize.width / 2, mWinSize.height * 0.1));
            addChild(tutorial, GAME_ZORDER_INTERFACE);
            tutorial->runAction(Sequence::create(FadeOut::create(3.0),
                                                 CallFuncN::create(CC_CALLBACK_1(SceneGame::selfRemover, this)),
                                                 nullptr));
        }
        else if(oldTime < 5.0 && mScoreBoard->getTime() >= 5.0) // 레이더 범위 내를 터치하여 독도로 부터 공격
        {
            Label* tutorial = LabelCreater::createLabel(bKorean ? "레이더 범위내를 터치하여 독도로 부터 공격" : "Touch within range", "JejuHallasan.ttf", 20);
            tutorial->setPosition(Vec2(mWinSize.width / 2, mWinSize.height * 0.45));
            addChild(tutorial, GAME_ZORDER_INTERFACE);
            tutorial->runAction(Sequence::create(FadeOut::create(4.0),
                                                 CallFuncN::create(CC_CALLBACK_1(SceneGame::selfRemover, this)),
                                                 nullptr));
        }
        else if(oldTime < 10.0 && mScoreBoard->getTime() >= 10.0) // 해군 함선을 소환
        {
            Label* tutorial = LabelCreater::createLabel(bKorean ? "해군 전함 및 조기경보기 소환\n조기 경보기는 적 잠수함을 탐지합니다." : "Sailing orders", "JejuHallasan.ttf", 20);
            tutorial->setPosition(Vec2(mWinSize.width / 2, mWinSize.height * 0.35));
            addChild(tutorial, GAME_ZORDER_INTERFACE);
            tutorial->runAction(Sequence::create(FadeOut::create(4.0),
                                                 CallFuncN::create(CC_CALLBACK_1(SceneGame::selfRemover, this)),
                                                 nullptr));
            
        }
        else if(oldTime < 14.0 && mScoreBoard->getTime() >= 14.0) // 적의 종류에 따라 적절한 아군을 소환
        {
            Label* tutorial = LabelCreater::createLabel(bKorean ? "적의 종류에 따라 적절한 아군을 소환하여야 합니다.\n동시에 소환 가능한 아군의 숫자는 제한이 있습니다." : "AWACS can detect enermy submarines.", "JejuHallasan.ttf", 20);
            tutorial->setPosition(Vec2(mWinSize.width / 2, mWinSize.height * 0.35));
            addChild(tutorial, GAME_ZORDER_INTERFACE);
            tutorial->runAction(Sequence::create(FadeOut::create(4.0),
                                                 CallFuncN::create(CC_CALLBACK_1(SceneGame::selfRemover, this)),
                                                 nullptr));
        }
        else if(oldTime < 19.0 && mScoreBoard->getTime() >= 19.0) // 유닛 소개
        {
            Label* unit = LabelCreater::createLabel(bKorean ? "윤영하함" : "Patrol ship", "JejuHallasan.ttf", 25);
            unit->setPosition(Vec2(mWinSize.width * 0.28, mWinSize.height * 0.5));
            addChild(unit, GAME_ZORDER_INTERFACE);
            unit->runAction(Sequence::create(FadeOut::create(4.0),
                                            CallFuncN::create(CC_CALLBACK_1(SceneGame::selfRemover, this)),
                                            nullptr));
            
            unit = LabelCreater::createLabel(bKorean ? "이순신함" : "Frigate", "JejuHallasan.ttf", 25);
            unit->setPosition(Vec2(mWinSize.width * 0.72, mWinSize.height * 0.5));
            addChild(unit, GAME_ZORDER_INTERFACE);
            unit->runAction(Sequence::create(FadeOut::create(4.0),
                                            CallFuncN::create(CC_CALLBACK_1(SceneGame::selfRemover, this)),
                                            nullptr));
            
            unit = LabelCreater::createLabel(bKorean ? "장보고함" : "Submarine", "JejuHallasan.ttf", 25);
            unit->setPosition(Vec2(mWinSize.width * 0.28, mWinSize.height * 0.405));
            addChild(unit, GAME_ZORDER_INTERFACE);
            unit->runAction(Sequence::create(FadeOut::create(4.0),
                                             CallFuncN::create(CC_CALLBACK_1(SceneGame::selfRemover, this)),
                                             nullptr));
            
            unit = LabelCreater::createLabel(bKorean ? "피스아이" : "AWACS", "JejuHallasan.ttf", 25);
            unit->setPosition(Vec2(mWinSize.width * 0.72, mWinSize.height * 0.405));
            addChild(unit, GAME_ZORDER_INTERFACE);
            unit->runAction(Sequence::create(FadeOut::create(4.0),
                                             CallFuncN::create(CC_CALLBACK_1(SceneGame::selfRemover, this)),
                                             nullptr));
            
            unit = LabelCreater::createLabel(bKorean ? "세종대왕함" : "Destroyer", "JejuHallasan.ttf", 25);
            unit->setPosition(Vec2(mWinSize.width * 0.28, mWinSize.height * 0.31));
            addChild(unit, GAME_ZORDER_INTERFACE);
            unit->runAction(Sequence::create(FadeOut::create(4.0),
                                             CallFuncN::create(CC_CALLBACK_1(SceneGame::selfRemover, this)),
                                             nullptr));
            
            unit = LabelCreater::createLabel(bKorean ? "독도함" : "Logistic ship", "JejuHallasan.ttf", 25);
            unit->setPosition(Vec2(mWinSize.width * 0.72, mWinSize.height * 0.31));
            addChild(unit, GAME_ZORDER_INTERFACE);
            unit->runAction(Sequence::create(FadeOut::create(4.0),
                                             CallFuncN::create(CC_CALLBACK_1(SceneGame::selfRemover, this)),
                                             nullptr));
            
            unit = LabelCreater::createLabel(bKorean ? "전술핵폭격" : "Nuclear Weapon", "JejuHallasan.ttf", 25);
            unit->setPosition(Vec2(mWinSize.width * 0.28, mWinSize.height * 0.215));
            addChild(unit, GAME_ZORDER_INTERFACE);
            unit->runAction(Sequence::create(FadeOut::create(4.0),
                                             CallFuncN::create(CC_CALLBACK_1(SceneGame::selfRemover, this)),
                                             nullptr));
            
            unit = LabelCreater::createLabel(bKorean ? "F15K" : "Fighter", "JejuHallasan.ttf", 25);
            unit->setPosition(Vec2(mWinSize.width * 0.72, mWinSize.height * 0.215));
            addChild(unit, GAME_ZORDER_INTERFACE);
            unit->runAction(Sequence::create(FadeOut::create(4.0),
                                             CallFuncN::create(CC_CALLBACK_1(SceneGame::selfRemover, this)),
                                             nullptr));
        }
    }
    
    // Catch Last Moment
    if(mScoreBoard->getTime() >= mfClearTime && oldTime < mfClearTime)
    {
        float reinforce = mfReinforce + (mfReinforceVariation * 1.2);
        switch(mDifficulty)
        {
            case MENU_TAG_NORMAL:
                addUnit(UNIT_PATROL, reinforce, true);
                addUnit(UNIT_PATROL, reinforce, true);
                addUnit(UNIT_PATROL, reinforce, true);
                addUnit(UNIT_DESTROYER, reinforce, true);
                addUnit(UNIT_DESTROYER, reinforce, true);
                addUnit(UNIT_CRUISER, reinforce, true);
                break;
            case MENU_TAG_HARD:
                addUnit(UNIT_FIGHTER, reinforce, true);
                addUnit(UNIT_FIGHTER, reinforce, true);
                addUnit(UNIT_CRUISER, reinforce, true);
                addUnit(UNIT_DESTROYER, reinforce, true);
                addUnit(UNIT_DESTROYER, reinforce, true);
                addUnit(UNIT_DESTROYER, reinforce, true);
                break;
            case MENU_TAG_VERYHARD:
                addUnit(UNIT_STRATEGIC, reinforce, true);
                addUnit(UNIT_FIGHTER, reinforce, true);
                addUnit(UNIT_FIGHTER, reinforce, true);
                addUnit(UNIT_FIGHTER, reinforce, true);
                addUnit(UNIT_CRUISER, reinforce, true);
                addUnit(UNIT_CRUISER, reinforce, true);
                break;
            case MENU_TAG_IMPOSSIBLE:
                addUnit(UNIT_STRATEGIC, reinforce, true);
                addUnit(UNIT_STRATEGIC, reinforce, true);
                addUnit(UNIT_FIGHTER, reinforce, true);
                addUnit(UNIT_FIGHTER, reinforce, true);
                addUnit(UNIT_FIGHTER, reinforce, true);
                addUnit(UNIT_FIGHTER, reinforce, true);
                addUnit(UNIT_BOMBER, reinforce, true);
                addUnit(UNIT_BOMBER, reinforce, true);
                addUnit(UNIT_BOMBER, reinforce, true);
                addUnit(UNIT_CRUISER, reinforce, true);
                addUnit(UNIT_CRUISER, reinforce, true);
                addUnit(UNIT_CARRIER, reinforce, true);
                break;
        }
    }
}

void SceneGame::addEnermy()
{
    float gameTime = mScoreBoard->getTime();
    
    if(mfClearTime >= gameTime)
    {
        float fEnermyVariation = (gameTime / mfClearTime) * mfAddEnermyVariation;
        float fReinforce = mfReinforce + ((gameTime / mfClearTime) * mfReinforceVariation);
        
        while(mfCurEnermyTime >= (mfAddEnermyTime - fEnermyVariation))
        {
            mfCurEnermyTime -= (mfAddEnermyTime - fEnermyVariation);
            
            switch(mDifficulty)
            {
                case MENU_TAG_VERYEASY:
                    addEnermyVERYEASY(fReinforce);
                    break;
                case MENU_TAG_EASY:
                    addEnermyEASY(fReinforce);
                    break;
                case MENU_TAG_NORMAL:
                    addEnermyNORMAL(fReinforce);
                    break;
                case MENU_TAG_HARD:
                    addEnermyHARD(fReinforce);
                    break;
                case MENU_TAG_VERYHARD:
                    addEnermyVERYHARD(fReinforce);
                    break;
                case MENU_TAG_IMPOSSIBLE:
                    addEnermyIMPOSSIBLE(fReinforce);
                    break;
                case MENU_TAG_ENDLESS:
                    addEnermyENDLESS(fReinforce);
                    break;
            }
        }
    }
}

bool SceneGame::getNewForcePosition(SpriteUnit* unit)
{
    float beginAngle = 0;
    float curAngle = 0;
    Vec2 newPos1, newPos2;
    bool b1Fail, b2Fail;
    while(curAngle <= 180)
    {
        newPos1 = Vec2(100.f * sinf((beginAngle + curAngle) * mPI180) + ptDokdo.x,
                       100.f * cosf((beginAngle + curAngle) * mPI180) + ptDokdo.y);
        newPos2 = Vec2(100.f * sinf((beginAngle - curAngle) * mPI180) + ptDokdo.x,
                       100.f * cosf((beginAngle - curAngle) * mPI180) + ptDokdo.y);
        
        b1Fail = b2Fail = false;
        
        if(unit->isShip() || unit->isSubmarine())
        {
            for(int i = 0; i < mArrUnits.size(); i++)
            {
                SpriteUnit* curUnit = mArrUnits[i];
                if((unit->isShip() && curUnit->isShip()) ||
                   (unit->isSubmarine() && curUnit->isSubmarine()))
                {
                    unit->setPosition(newPos1);
                    if(unit->getBoundingBox().intersectsRect(curUnit->getBoundingBox()))
                    {
                        b1Fail = true;
                    }
                
                    unit->setPosition(newPos2);
                    if(unit->getBoundingBox().intersectsRect(curUnit->getBoundingBox()))
                    {
                        b2Fail = true;
                    }
                
                    if(b1Fail && b2Fail)
                        break;
                }
            }
        }
        
        if(b1Fail && b2Fail)
            curAngle += 10;
        else
        {
            if(!b1Fail)
            {
                unit->setPosition(newPos1);
            }
            else
            {
                unit->setPosition(newPos2);
            }
            return true;
        }
    }
    
    return false;
}

bool SceneGame::getNewEnermyPosition(SpriteUnit* unit, bool begin)
{
    for(int i = 0; i < 20; i++)
    {
        float xPos = 25 + (rand() % 430);
        float yPos = 800 + unit->getContentSize().height / 2;
        if(begin == true)
            yPos -= rand() % 120;
        
        unit->setPosition(Vec2(xPos , yPos));
        if(!unit->isShip())
            return true;
        
        bool bFlag = true;
        for(int j = 0; j < mArrEnermies.size(); j++)
        {
            SpriteUnit* curUnit = (SpriteUnit*)mArrEnermies[j];
            if(unit->boundingBox().intersectsRect(curUnit->boundingBox()))
            {
                bFlag = false;
                break;
            }
        }
        
        if(bFlag)
        {
            return true;
        }
    }
    return false;
}

bool SceneGame::addUnit(int unit, float reinforce, bool enermy, bool beginEnermy /*= false*/)
{
    switch(unit)
    {
        case UNIT_CARRIER:
            if(mCarrierCnt < CARRIER_MAX)
            {
                mCarrierCnt++;
            }
            else
                unit = UNIT_DESTROYER;
            break;
        case UNIT_CRUISER:
            if(mCruiserCnt < CRUISER_MAX)
            {
                mCruiserCnt++;
            }
            else
                unit = UNIT_DESTROYER;
            break;
        case UNIT_STRATEGIC:
            if(mStrategyBomberCtn < BOMBER_MAX)
            {
                mStrategyBomberCtn++;
            }
            else
                unit = UNIT_BOMBER;
            break;
        default:        // 3가지 타입 외엔 제한 없음.
            break;
    }
    SpriteUnit* spUnit = SpriteUnit::create(unit, reinforce, enermy);
    
    if(spUnit->isEnermy())
    {
        if(getNewEnermyPosition(spUnit, beginEnermy))
        {
            if(spUnit->isSurface())
            {
                if(spUnit->isSubmarine())
                    batchSurface->addChild(spUnit, GAME_SURFACE_ZORDER_SUBMARINE);
                else if(spUnit->isShip())
                    batchSurface->addChild(spUnit, GAME_SURFACE_ZORDER_SHIP);
                else if(spUnit->getType() == UNIT_LYNX)
                    batchSurface->addChild(spUnit, GAME_SURFACE_ZORDER_LYNX);
                else if(spUnit->isHelicopter())
                    batchSurface->addChild(spUnit, GAME_SURFACE_ZORDER_HELICOPTER);
            }
            else
            {
                switch(spUnit->getType())
                {
                    case UNIT_BOMBER:
                        batchAir->addChild(spUnit, GAME_AIR_ZORDER_BOMBER);
                        break;
                    case UNIT_FIGHTER:
                        batchAir->addChild(spUnit, GAME_AIR_ZORDER_FIGHTER);
                        break;
                    case UNIT_STRATEGIC:
                        batchAir->addChild(spUnit, GAME_AIR_ZORDER_STRATEGYBOMBER);
                        break;
                }
            }
            mArrEnermies.push_back(spUnit);
        }
        else
        {
            spUnit->removeFromParentAndCleanup(true);
        }
        return true;
    }
    else
    {
        if(getNewForcePosition(spUnit))
        {
            if(spUnit->isSurface())
            {
                if(spUnit->isSubmarine())
                    batchSurface->addChild(spUnit, GAME_SURFACE_ZORDER_SUBMARINE);
                else if(spUnit->isShip())
                    batchSurface->addChild(spUnit, GAME_SURFACE_ZORDER_SHIP);
            }
            else
            {
                if(spUnit->getType() == UNIT_E747)
                    batchAir->addChild(spUnit, GAME_AIR_ZORDER_PEACEEYE);
                else if(spUnit->getType() == UNIT_F15K)
                    batchAir->addChild(spUnit, GAME_AIR_ZORDER_FIGHTER);
            }
            mArrUnits.push_back(spUnit);
            return true;
        }
        else
        {
            spUnit->removeFromParentAndCleanup(true);
            return false;
        }
    }
    return false;
}

bool SceneGame::addLynx(float reinforce, int probability)
{
    bool bKSS3 = false;
    if(probability > 0)
    {
        for(int i = 0; i < mArrUnits.size(); i++)
        {
            if(mArrUnits[i]->getType() == UNIT_KSS3)
            {
                bKSS3 = true;
                break;
            }
        }
    }
    
    if(probability == 0 || (bKSS3 && rand() % probability == 0))
    {
        addUnit(UNIT_LYNX, reinforce, true);
        return true;
    }
    return false;
}

void SceneGame::addEnermyVERYEASY(float fReinforce)
{
    if(addLynx(fReinforce, 12))
    {
        mfCurEnermyTime += (mfAddEnermyTime * 0.4);
        return;
    }
    
    int nRand = rand() % 100;
    
    if(nRand < 40)                  addUnit(UNIT_PATROL, fReinforce, true);
    else if(nRand < 70)             addUnit(UNIT_HELICOPTER, fReinforce, true);
    else if(nRand < 90)             addUnit(UNIT_DESTROYER, fReinforce, true);
    else                            addUnit(UNIT_CRUISER, fReinforce, true);
    
    // for TEST

    // 전함만
    /*if(nRand < 25) addUnit(UNIT_PATROL, fReinforce, true);
    else if(nRand < 50) addUnit(UNIT_DESTROYER, fReinforce, true);
    else if(nRand < 75) addUnit(UNIT_CRUISER, fReinforce, true);
    else    addUnit(UNIT_CARRIER, fReinforce, true);*/
    
    // 헬기만
    /*if(nRand < 50) addUnit(UNIT_LYNX, fReinforce, true);
    else addUnit(UNIT_HELICOPTER, fReinforce, true);*/
    
    // 항공기만
    /*if(nRand < 33) addUnit(UNIT_FIGHTER, fReinforce, true);
    else if(nRand < 66) addUnit(UNIT_BOMBER, fReinforce, true);
    else addUnit(UNIT_STRATEGIC, fReinforce, true);*/
    
    // 잠수함만
    //addUnit(UNIT_SUBMARINE, fReinforce, true);
}

void SceneGame::addEnermyEASY(float fReinforce)
{
    if(addLynx(fReinforce, 10))
    {
        mfCurEnermyTime += (mfAddEnermyTime * 0.5);
        return;
    }
    
    int nRand = rand() % 100;
    if(nRand < 30)                  addUnit(UNIT_PATROL, fReinforce, true);
    else if(nRand < 50)             addUnit(UNIT_HELICOPTER, fReinforce, true);
    else if(nRand < 70)             addUnit(UNIT_DESTROYER, fReinforce, true);
    else if(nRand < 90)             addUnit(UNIT_CRUISER, fReinforce, true);
    else                            addUnit(UNIT_FIGHTER, fReinforce, true);
}

void SceneGame::addEnermyNORMAL(float fReinforce)
{
    if(addLynx(fReinforce, 8))
    {
        mfCurEnermyTime += (mfAddEnermyTime * 0.7);
        return;
    }
    
    int nRand = rand() % 100;
    if(nRand < 2)                   addUnit(UNIT_LYNX, fReinforce, true);
    if(nRand < 30)                  addUnit(UNIT_PATROL, fReinforce, true);
    else if(nRand < 50)             addUnit(UNIT_HELICOPTER, fReinforce, true);
    else if(nRand < 70)             addUnit(UNIT_DESTROYER, fReinforce, true);
    else if(nRand < 90)             addUnit(UNIT_CRUISER, fReinforce, true);
    else                            addUnit(UNIT_FIGHTER, fReinforce, true);
}

void SceneGame::addEnermyHARD(float fReinforce)
{
    if(addLynx(fReinforce, 6))
    {
        mfCurEnermyTime += (mfAddEnermyTime * 0.8);
        return;
    }
    
    int nRand = rand() % 100;
    if(nRand < 4)                   addUnit(UNIT_LYNX, fReinforce, true);
    if(nRand < 10)                  addUnit(UNIT_PATROL, fReinforce, true);
    else if(nRand < 20)             addUnit(UNIT_HELICOPTER, fReinforce, true);
    else if(nRand < 40)             addUnit(UNIT_DESTROYER, fReinforce, true);
    else if(nRand < 65)             addUnit(UNIT_CRUISER, fReinforce, true);
    else if(nRand < 85)             addUnit(UNIT_FIGHTER, fReinforce, true);
    else if(nRand < 94)             addUnit(UNIT_BOMBER, fReinforce, true);
    else                            addUnit(UNIT_SUBMARINE, fReinforce, true);
}

void SceneGame::addEnermyVERYHARD(float fReinforce)
{
    if(addLynx(fReinforce, 5))
    {
        mfCurEnermyTime += (mfAddEnermyTime * 0.9);
        return;
    }
    
    int nRand = rand() % 100;
    if(nRand < 6)                   addUnit(UNIT_LYNX, fReinforce, true);
    if(nRand < 10)                  addUnit(UNIT_PATROL, fReinforce, true);
    else if(nRand < 20)             addUnit(UNIT_HELICOPTER, fReinforce, true);
    else if(nRand < 30)             addUnit(UNIT_DESTROYER, fReinforce, true);
    else if(nRand < 50)             addUnit(UNIT_CRUISER, fReinforce, true);
    else if(nRand < 70)             addUnit(UNIT_FIGHTER, fReinforce, true);
    else if(nRand < 85)             addUnit(UNIT_BOMBER, fReinforce, true);
    else if(nRand < 95)             addUnit(UNIT_SUBMARINE, fReinforce, true);
    else                            addUnit(UNIT_CARRIER, fReinforce, true);
}

void SceneGame::addEnermyIMPOSSIBLE(float fReinforce)
{
    if(addLynx(fReinforce, 4))
    {
        mfCurEnermyTime += (mfAddEnermyTime * 0.95);
        return;
    }
    
    int nRand = rand() % 100;
    if(nRand < 7)                   addUnit(UNIT_LYNX, fReinforce, true);
    if(nRand < 5)                   addUnit(UNIT_PATROL, fReinforce, true);
    else if(nRand < 15)             addUnit(UNIT_HELICOPTER, fReinforce, true);
    else if(nRand < 25)             addUnit(UNIT_DESTROYER, fReinforce, true);
    else if(nRand < 44)             addUnit(UNIT_CRUISER, fReinforce, true);
    else if(nRand < 63)             addUnit(UNIT_FIGHTER, fReinforce, true);
    else if(nRand < 77)             addUnit(UNIT_BOMBER, fReinforce, true);
    else if(nRand < 92)             addUnit(UNIT_SUBMARINE, fReinforce, true);
    else if(nRand < 96)             addUnit(UNIT_CARRIER, fReinforce, true);
    else                            addUnit(UNIT_STRATEGIC, fReinforce, true);
}

void SceneGame::addEnermyENDLESS(float fReinforce)
{
    if(addLynx(fReinforce, 4))
    {
        mfCurEnermyTime += (mfAddEnermyTime * 0.95);
        return;
    }
    
    int nRand = rand() % 100;
    if(nRand < 7)                   addUnit(UNIT_LYNX, fReinforce, true);
    if(nRand < 5)                   addUnit(UNIT_PATROL, fReinforce, true);
    else if(nRand < 15)             addUnit(UNIT_HELICOPTER, fReinforce, true);
    else if(nRand < 25)             addUnit(UNIT_DESTROYER, fReinforce, true);
    else if(nRand < 40)             addUnit(UNIT_CRUISER, fReinforce, true);
    else if(nRand < 60)             addUnit(UNIT_FIGHTER, fReinforce, true);
    else if(nRand < 75)             addUnit(UNIT_BOMBER, fReinforce, true);
    else if(nRand < 90)             addUnit(UNIT_SUBMARINE, fReinforce, true);
    else if(nRand < 95)             addUnit(UNIT_CARRIER, fReinforce, true);
    else                            addUnit(UNIT_STRATEGIC, fReinforce, true);
}

void SceneGame::update(float dt)
{
    if(mGameState == GAME_STATE_PLAY)
    {
        addCloud(dt);
        updateTime(dt);
        updateSummonBtn();
        updateWeaponBtn();
        addEnermy();
    
        moveUnits(dt);
        checkWeapons();
        
        if(mfClearTime <= mScoreBoard->getTime() &&
           mArrEnermies.size() == 0)
        {
            mGameState = GAME_STATE_CLEAR;
            DDC_CLEAR_DATA* clearData = SaveManager::loadClear();
            switch (mDifficulty) {
                case MENU_TAG_VERYEASY:
                    clearData->veryeasy = true;
                    break;
                    
                case MENU_TAG_EASY:
                    clearData->easy = true;
                    break;
                    
                case MENU_TAG_NORMAL:
                    clearData->normal = true;
                    break;
                    
                case MENU_TAG_HARD:
                    clearData->hard = true;
                    break;
                    
                case MENU_TAG_VERYHARD:
                    clearData->veryhard = true;
                    break;
                    
                case MENU_TAG_IMPOSSIBLE:
                    clearData->impossible = true;
                    break;
            }
            SaveManager::saveClear(clearData);
            delete clearData;
            mGameFinishTerm = 2.f;
        }
    }
    else if(mGameState == GAME_STATE_OVER || mGameState == GAME_STATE_CLEAR)
    {
        if(mGameFinishTerm > 0)
        {
            mGameFinishTerm -= dt;
            if(mGameFinishTerm <= 0)
            {
                bool highScore = false;
                int income = mScoreBoard->getMoney() - mSaveData->nMoney;
                mSaveData->nMoney = mScoreBoard->getMoney();
                
                if(mSaveData->highscore[0].score <= mScoreBoard->getScore())
                {
                    highScore = true;
                }
                
                bool bFind = false;
                tm preTime;
                unsigned long preScore;
                for(int i = 0; i < 12; i++)
                {
                    if(bFind)
                    {
                        tm timeTemp = mSaveData->highscore[i].time;
                        unsigned long scoreTemp = mSaveData->highscore[i].score;
                        
                        mSaveData->highscore[i].time = preTime;
                        mSaveData->highscore[i].score = preScore;
                        
                        preTime = timeTemp;
                        preScore = scoreTemp;
                    }
                    else if(mSaveData->highscore[i].score <= mScoreBoard->getScore())
                    {
                        bFind = true;
                        preTime = mSaveData->highscore[i].time;
                        preScore = mSaveData->highscore[i].score;
                        
                        time_t rawTime;
                        struct tm *timeinfo;
                        time(&rawTime);
                        timeinfo = localtime(&rawTime);
                        
                        memcpy(&mSaveData->highscore[i].time, timeinfo, sizeof(tm));
                        mSaveData->highscore[i].score = mScoreBoard->getScore();
                    }
                }
                
                SaveManager::save(mSaveData);
                destroyGame(income, highScore);
            }
        }
    }
}

Vec2 SceneGame::getTargetPos(Vec2 target, float distance, int error)
{
    int xError = ((rand() % error) * distance) / 100.0;
    if(rand() % 2 == 0) target.x += xError;
    else                target.x -= xError;
    
    int yError = ((rand() % error) * distance) / 100.0;
    if(rand() % 2 == 0) target.y += yError;
    else                target.y -= yError;
    
    return target;
                
}

void SceneGame::moveUnits(float dt)
{
    // STEP 1 : 잠수함 탐지상태 갱신
    float fForceAvgYPos = 0;
    float fEnermySubMarineAvgXPos = 0;
    int nEnermySubmarineCtn = 0;
    float fForceTop, fForceBottom, fForceRight, fForceLeft;
    fForceTop = 0; fForceBottom = mWinSize.height;
    fForceRight = 0; fForceLeft = mWinSize.width;
    
    Vec2 pos;
    SpriteUnit* spE747 = nullptr;
    SpriteUnit* enermyTmp = nullptr;
    SpriteUnit* unitTmp = nullptr;
    for(vector<SpriteUnit*>::iterator iter = mArrUnits.begin();
        iter != mArrUnits.end();
        iter++)
    {
        unitTmp = (SpriteUnit*)*iter;
        if(unitTmp->isSubmarine())
            unitTmp->setDetected(false);
        unitTmp->mControlled = false;
        
        pos = unitTmp->getPosition();
        fForceAvgYPos += pos.y;
        
        if(unitTmp->getType() != UNIT_DOKDO && unitTmp->getType() != UNIT_F15K)
        {
            if(pos.y > fForceTop)       fForceTop = pos.y;
            if(pos.y < fForceBottom)    fForceBottom = pos.y;
            if(pos.x > fForceRight)     fForceRight = pos.x;
            if(pos.x < fForceLeft)      fForceLeft = pos.x;
        }
        
        // Peace Eye를 미리 찾아둠
        if(unitTmp->getType() == UNIT_E747)
        {
            spE747 = unitTmp;
        }
    }
    
    if(fForceAvgYPos > 0 && mArrUnits.size() > 0)
        fForceAvgYPos /= mArrUnits.size();
    
    for(vector<SpriteUnit*>::iterator iter = mArrEnermies.begin();
        iter != mArrEnermies.end();
        iter++)
    {
        enermyTmp = (SpriteUnit*)*iter;
        if(enermyTmp->isSubmarine())
        {
            enermyTmp->setDetected(false);
            fEnermySubMarineAvgXPos += enermyTmp->getPosition().x;
            nEnermySubmarineCtn++;
        }
    }
    
    if(fEnermySubMarineAvgXPos > 0 && nEnermySubmarineCtn > 0)
        fEnermySubMarineAvgXPos /= nEnermySubmarineCtn;
    
    // 적잠수함들의 detect 여부와 아군 Controlled 여부를 확인함
    float fDetectRange = MINIMUM_DISTANCE + 40;
    Vec2 BasePos = ptDokdo;
    if(spE747 != nullptr)
    {
    	fDetectRange = spE747->mRange;
    	BasePos = spE747->getPosition();

    	for(int i = 0; i < mArrUnits.size(); i++)
    	{
    		if(fDetectRange >= DokdoCalculator::getDistance(BasePos,
    														mArrUnits[i]->getPosition()))
    		{
    			mArrUnits[i]->mControlled = true;
    		}
    	}
    }

    for(int i = 0; i < mArrEnermies.size(); i++)
    {
    	enermyTmp = mArrEnermies[i];
    	if(enermyTmp->isSubmarine())
    	{
    		if(fDetectRange >= DokdoCalculator::getDistance(BasePos, enermyTmp->getPosition()))
    		{
    			enermyTmp->setDetected(true);
    		}
    	}
    }

    
    // 적 링스에 의한 아군 KSS3 탐지 여부 확인
    for(int i = 0; i < mArrEnermies.size(); i++)
    {
        enermyTmp = mArrEnermies[i];
        if(enermyTmp->getType() == UNIT_LYNX)
        {
            for(int j = 0; j < mArrUnits.size(); j++)
            {
                if(mArrUnits[j]->isSubmarine())
                {
                    unitTmp = mArrUnits[j];
                    if(enermyTmp->mRange >= DokdoCalculator::getDistance(enermyTmp->getPosition(),
                                                                      unitTmp->getPosition()))
                    {
                        unitTmp->setDetected(true);
                    }
                }
            }
        }
    }

    // STEP 2 아군 이동 및 사격
    for(int i = 0; i < mArrUnits.size(); i++)
    {
        unitTmp = mArrUnits[i];
        unitTmp->update(dt);
        
        Vec2 oldPos = unitTmp->getPosition();
        
        SpriteUnit* targetEnermy = nullptr;
        float fTargetDistance = mWinSize.height;
        SpriteUnit* targetEnermy2 = nullptr;
        float fTargetDistance2 = mWinSize.height;
        
        for(int j = 0; j < mArrEnermies.size(); j++)
        {
            enermyTmp = mArrEnermies[j];
            
            // 사격 불가능 대상인 경우 continue
            if((unitTmp->getType() == UNIT_PKG || unitTmp->getType() == UNIT_DOKDO) &&
               enermyTmp->isAir())
                continue;
            else if(unitTmp->getType() == UNIT_KSS3 &&
                    (enermyTmp->isHelicopter() || enermyTmp->isAir()))
                continue;
            
            if((unitTmp->getType() != UNIT_E747 && enermyTmp->mDetected) ||
               (unitTmp->getType() == UNIT_E747 && enermyTmp->isSubmarine()))
            {
                float distance = DokdoCalculator::getDistance(oldPos, enermyTmp->getPosition());
                if(distance < fTargetDistance)
                {
                    fTargetDistance2 = fTargetDistance;
                    targetEnermy2 = targetEnermy;
                    
                    fTargetDistance = distance;
                    targetEnermy = enermyTmp;
                }
            }
        }
        
        // main weapon
        if(0 == unitTmp->mWeaponCoolTime)
        {
            float range = unitTmp->mRange * (unitTmp->mControlled ? 1.1 : 1.0);
            if(unitTmp->getType() == UNIT_DOKDO)
            {
                unitTmp->mWeaponCoolTime = unitTmp->mWeaponCoolTimeMax;
                for(int iRes = 0; iRes < mArrUnits.size(); iRes++)
                {
                    if(unitTmp->mRange >= DokdoCalculator::getDistance(mArrUnits[iRes]->getPosition(),
                                                                       unitTmp->getPosition()))
                    {
                        mArrUnits[iRes]->subEnergy(unitTmp->mPower * -1);
                    }
                }
            }
            else if(fTargetDistance <= range && targetEnermy)
            {
                unitTmp->mWeaponCoolTime = unitTmp->mWeaponCoolTimeMax;
                Vec2 ptTarget = getTargetPos(targetEnermy->getPosition(), fTargetDistance, 3);
                switch(unitTmp->getType())
                {
                    case UNIT_PKG:
                        fireBullet(unitTmp->getPosition(), ptTarget, unitTmp->mPower, false, SPEED_VULCAN, TYPE_VULCAN, TARGET_SURFACE);
                        break;
                    case UNIT_KDX2:
                        fireBullet(unitTmp->getPosition(), ptTarget, unitTmp->mPower, false, SPEED_CANNON, TYPE_CANNON, TARGET_ALL);
                        break;
                    case UNIT_KDX3:
                    case UNIT_F15K:
                        fireMissile(unitTmp->getPosition(), ptTarget, unitTmp->mPower, false);
                        break;
                    case UNIT_KSS3:
                        fireTorpedo(unitTmp->getPosition(), ptTarget, unitTmp->mPower, false);
                        break;
                    default:
                        break;
                }
            }
        }
        
        // sub weapon
        if(0 == unitTmp->mSubWeaponCoolTime)
        {
            float range = unitTmp->mSubRange * (unitTmp->mControlled ? 1.1 : 1.0);
            if(fTargetDistance2 > range || targetEnermy2 == nullptr)
            {
                fTargetDistance2 = fTargetDistance;
                targetEnermy2 = targetEnermy;
            }
            
            if(fTargetDistance2 <= range && targetEnermy2)
            {
                unitTmp->mSubWeaponCoolTime = unitTmp->mSubWeaponCoolTimeMax;
                Vec2 ptTarget = getTargetPos(targetEnermy->getPosition(), fTargetDistance, 4);
                switch(unitTmp->getType())
                {
                    case UNIT_KDX2:
                        fireBullet(unitTmp->getPosition(), ptTarget, unitTmp->mSubPower, false, SPEED_VULCAN, TYPE_VULCAN, TARGET_SURFACE);
                        break;
                    case UNIT_KDX3:
                        fireBullet(unitTmp->getPosition(), ptTarget, unitTmp->mSubPower, false, SPEED_CANNON, TYPE_CANNON, TARGET_ALL);
                        break;
                    case UNIT_DOKDO:
                        fireBullet(unitTmp->getPosition(), ptTarget, unitTmp->mSubPower, false, SPEED_VULCAN, TYPE_VULCAN, TARGET_SURFACE);
                        break;
                    case UNIT_F15K:
                        fireBullet(unitTmp->getPosition(), ptTarget, unitTmp->mSubPower, false, SPEED_VULCAN, TYPE_VULCAN, TARGET_ALL);
                        break;
                    default:
                        break;
                }
            }
        }
        
        // target에게 이동
        if(unitTmp->getType() == UNIT_F15K) // F15K는 혼자 움직임.
        {
            continue;
        }
        
        float beginAngle = 180;
        float curAngle = 0;
        
        Vec2 ptTarget;
        if(targetEnermy)
            ptTarget = targetEnermy->getPosition();
        else
            ptTarget = ptDokdo;
        
        if(unitTmp->getType() == UNIT_E747)
        {
        	if(fForceAvgYPos >= ptDokdo.y)
        		ptTarget.y = fForceAvgYPos - 40;
        	else
        		ptTarget.y = ptDokdo.y;

            if(fEnermySubMarineAvgXPos > 0)
                ptTarget.x = fEnermySubMarineAvgXPos;
            else
                ptTarget.x = ptDokdo.x;
        }
        else if(unitTmp->getType() == UNIT_DOKDO)
        {
            if(mArrUnits.size() > 1)
            {
                ptTarget = Vec2((fForceRight + fForceLeft) / 2, (fForceTop + fForceBottom) / 2);
            }
        }
        
        beginAngle -= atan2f(ptTarget.x - oldPos.x, oldPos.y - ptTarget.y) * m180PI;
        Vec2 newPos1, newPos2;
        float curDistance = (mWinSize.height * dt) / unitTmp->mSpeed;
        bool b1Fail = false, b2Fail = false;
        
        while(curAngle <= 90)
        {
            newPos1 = Vec2(curDistance * sinf((beginAngle + curAngle) * mPI180) + oldPos.x,
                           curDistance * cosf((beginAngle + curAngle) * mPI180) + oldPos.y);
            newPos2 = Vec2(curDistance * sinf((beginAngle - curAngle) * mPI180) + oldPos.x,
                           curDistance * cosf((beginAngle - curAngle) * mPI180) + oldPos.y);
            
            // 범위를 넘거나 흔들리는 현상 방지
            if(newPos1.x < 20) newPos1.x = 20;
            if(newPos2.x < 20) newPos2.x = 20;
            if(newPos1.x > mWinSize.width - 20) newPos1.x = mWinSize.width - 20;
            if(newPos2.x > mWinSize.width - 20) newPos2.x = mWinSize.width - 20;
            if(newPos1.y > FEBA_YPOS) newPos1.y = FEBA_YPOS;
            if(newPos2.y > FEBA_YPOS) newPos2.y = FEBA_YPOS;
            
            if(oldPos.x <= ptTarget.x && newPos1.x > ptTarget.x)
                newPos1.x = ptTarget.x;
            else if(oldPos.x >= ptTarget.x && newPos1.x < ptTarget.x)
                newPos1.x = ptTarget.x;
            if(oldPos.x <= ptTarget.x && newPos2.x > ptTarget.x)
                newPos2.x = ptTarget.x;
            else if(oldPos.x >= ptTarget.x && newPos2.x < ptTarget.x)
                newPos2.x = ptTarget.x;
            
            if(oldPos.y <= ptTarget.y && newPos1.y > ptTarget.y)
                newPos1.y = ptTarget.y;
            else if(oldPos.y >= ptTarget.y && newPos1.y < ptTarget.y)
                newPos1.y = ptTarget.y;
            if(oldPos.y <= ptTarget.y && newPos2.y > ptTarget.y)
                newPos2.y = ptTarget.y;
            else if(oldPos.y >= ptTarget.y && newPos2.y < ptTarget.y)
                newPos2.y = ptTarget.y;
            
            b1Fail = b2Fail = false;
            
            if(unitTmp->isShip() || unitTmp->isSubmarine())
            {
                for(int j = 0; j < mArrUnits.size(); j++)
                {
                    if(mArrUnits[j] != unitTmp)
                    {
                        if((mArrUnits[j]->isShip() && unitTmp->isShip()) ||
                           (mArrUnits[j]->isSubmarine() && unitTmp->isSubmarine()))
                        {
                            unitTmp->setPosition(newPos1);
                            if(unitTmp->getBoundingBox().intersectsRect(mArrUnits[j]->getBoundingBox()))
                            {
                                b1Fail = true;
                            }
                            
                            unitTmp->setPosition(newPos2);
                            if(unitTmp->getBoundingBox().intersectsRect(mArrUnits[j]->getBoundingBox()))
                            {
                                b2Fail = true;
                            }
                            unitTmp->setPosition(oldPos);
                        }
                    }
                    
                    if(b1Fail && b2Fail)
                    {
                        break;
                    }
                }
            }
            
            // 아군과의 거리테스트 통과 하였으나 비행유닛이 아닌 경우에는 최근접 적과의 거리도 체크한다.
            if((!b1Fail || !b2Fail) && !unitTmp->isAir())
            {
                if(targetEnermy != nullptr)
                {
                    if(MINIMUM_DISTANCE >= DokdoCalculator::getDistance(newPos1, targetEnermy->getPosition()))
                    {
                        b1Fail = true;
                    }
                    if(MINIMUM_DISTANCE >= DokdoCalculator::getDistance(newPos2, targetEnermy->getPosition()))
                    {
                        b2Fail = true;
                    }
                }
            }
            
            if(!b1Fail)
            {
                unitTmp->setPosition(newPos1);
                break;
            }
            else if(!b2Fail)
            {
                unitTmp->setPosition(newPos2);
                break;
            }
            else
            {
                curAngle += 45;
            }
        }
    }
    
    // STEP 3 적군 이동 및 사격
    vector<SpriteUnit*> arrNewFighter;
    float fGoalKeeperDistance = mWinSize.height;
    SpriteUnit* goalKeeperTarget = nullptr;
    for(int i = 0; i < mArrEnermies.size(); i++)
    {
        enermyTmp = mArrEnermies[i];
        enermyTmp->update(dt);
        Vec2 oldPos = enermyTmp->getPosition();
        
        // 탐지된 지상 레벨 적 중에 가장 가까운 적을 찾아냄.
        float fTemp = 0;
        if(enermyTmp->mDetected == true && enermyTmp->isSurface())
        {
            fTemp = DokdoCalculator::getDistance(ptDokdo, oldPos);
            if(fTemp < fGoalKeeperDistance)
            {
                fGoalKeeperDistance = fTemp;
                goalKeeperTarget = enermyTmp;
            }
        }
        
        SpriteUnit* pTarget = nullptr;
        float fDistance = mWinSize.height;
        SpriteUnit* pTarget2 = nullptr;
        float fDistance2 = mWinSize.height;
        bool bDokdoAttackable = false;
        
        if(DokdoCalculator::getDistance(enermyTmp->getPosition(), ptDokdo) <= enermyTmp->mRange)
        {
            fDistance = DokdoCalculator::getDistance(enermyTmp->getPosition(), ptDokdo);
            bDokdoAttackable = true;
        }
        else
        {
            int nType = enermyTmp->getType();
            for(int j = 0; j < mArrUnits.size(); j++)
            {
                if(nType == UNIT_PATROL ||
                   nType == UNIT_DESTROYER ||
                   nType == UNIT_CARRIER ||
                   nType == UNIT_HELICOPTER ||
                   nType == UNIT_BOMBER ||
                   nType == UNIT_SUBMARINE)
                {
                    // 항공기나 발견되지 않은 잠수함은 공격 못함.
                    if(mArrUnits[j]->isAir() ||
                       !mArrUnits[j]->mDetected)
                        continue;
                }
                else if(nType == UNIT_LYNX)
                {
                    // 링스는 잠수함만...
                    if(!mArrUnits[j]->isSubmarine())
                        continue;
                }
                else if(!mArrUnits[j]->mDetected)
                {
                    continue;
                }
                
                // 잡아도 되는 경우
                float fTemp = DokdoCalculator::getDistance(enermyTmp->getPosition(), mArrUnits[j]->getPosition());
                if(fDistance > fTemp)
                {
                    fDistance2 = fDistance;
                    pTarget2 = pTarget;
                    
                    fDistance = fTemp;
                    pTarget = mArrUnits[j];
                }
            }
        }
        
        // 적 사격
        if((pTarget && fDistance <= enermyTmp->mRange) || bDokdoAttackable)
        {
            Vec2 ptTarget = Vec2(0, 0);
            
            if(pTarget != nullptr)
            {
                ptTarget = getTargetPos(pTarget->getPosition(), fDistance, 15);
            }
            else if(bDokdoAttackable)
            {
                ptTarget = getTargetPos(ptDokdo, fDistance, 30);
            }
            
            if(ptTarget.x > 0 || ptTarget.y > 0)
            {
                if(enermyTmp->mWeaponCoolTime == 0)
                {
                    enermyTmp->mWeaponCoolTime = enermyTmp->mWeaponCoolTimeMax;
                    switch(enermyTmp->getType())
                    {
                        case UNIT_PATROL:
                        case UNIT_CARRIER:
                        case UNIT_HELICOPTER:
                            fireBullet(oldPos, ptTarget, enermyTmp->mPower, true, SPEED_VULCAN, TYPE_VULCAN, TARGET_SURFACE);
                            break;
                            
                        case UNIT_DESTROYER:
                        case UNIT_BOMBER:
                            fireBullet(oldPos, ptTarget, enermyTmp->mPower, true, SPEED_CANNON, TYPE_CANNON, TARGET_SURFACE);
                            break;
                            
                        case UNIT_CRUISER:
                        case UNIT_FIGHTER:
                            fireMissile(oldPos, ptTarget, enermyTmp->mPower, true);
                            break;
                            
                        case UNIT_SUBMARINE:
                            fireTorpedo(oldPos, ptTarget, enermyTmp->mPower, true);
                            break;
                            
                        case UNIT_STRATEGIC:
                            for(int iBomb = 0; iBomb < ENERMY_STRATEGYBOMBER_BOMB_CTN; iBomb++)
                            {
                                ptTarget = getTargetPos(bDokdoAttackable ? ptDokdo : pTarget->getPosition(),
                                                        fDistance,
                                                        60);
                                fireBomb(oldPos, ptTarget, enermyTmp->mPower, true);
                            }
                            break;
                    }
                }
                

            }
        }
        
        if(fDistance2 > enermyTmp->mSubRange || pTarget2 == nullptr)
        {
            fDistance2 = fDistance;
            pTarget2 = pTarget;
        }
        
        if((fDistance2 <= enermyTmp->mSubRange && pTarget2) || bDokdoAttackable || enermyTmp->getType() == UNIT_CARRIER)
        {
        	if(enermyTmp->mSubWeaponCoolTime == 0)
        	{
        		Vec2 ptTarget = Vec2(0, 0);
            	if(nullptr != pTarget2)
            		ptTarget = getTargetPos(pTarget2->getPosition(), fDistance2, 15);
            	else if(bDokdoAttackable || enermyTmp->getType() == UNIT_CARRIER)
            		ptTarget = getTargetPos(ptDokdo, fDistance, 40);

            	if(ptTarget.x > 0 || ptTarget.y > 0)
            	{
                    enermyTmp->mSubWeaponCoolTime = enermyTmp->mSubWeaponCoolTimeMax;

                    switch(enermyTmp->getType())
                	{
                    	case UNIT_DESTROYER:
                        	fireBullet(oldPos, ptTarget, enermyTmp->mSubPower, true, SPEED_VULCAN, TYPE_VULCAN, TARGET_SURFACE);
                        	break;
                    	case UNIT_CRUISER:
                        	fireBullet(oldPos, ptTarget, enermyTmp->mSubPower, true, SPEED_CANNON, TYPE_CANNON, TARGET_ALL);
                        	break;
                    	case UNIT_CARRIER:
                    	{
                        	SpriteUnit* newFighter = SpriteUnit::create(UNIT_FIGHTER,
                                                                    mfReinforce + ((mScoreBoard->getTime() / mfClearTime) * mfReinforceVariation),
                                                                    true);
                        	newFighter->setPosition(enermyTmp->getPosition());
                        	newFighter->setScale(0.05);
                        	newFighter->runAction(ScaleTo::create(2.0, 1.0));
                        	batchAir->addChild(newFighter, GAME_AIR_ZORDER_FIGHTER);
                        	arrNewFighter.push_back(newFighter);
                    	}
                        break;
                	}
            	}
            }
        }
        
        // 이동 ... Lynx인 경우는 독도로 돌진이 아니고 pTarget이 존재하면 pTarget으로 돌진 한다.
        float curMoveDistance = (mWinSize.height * dt) / enermyTmp->mSpeed;
        float beginAngle = 0;
        float curAngle = 0;
        
        if(oldPos.y >= mWinSize.height * 0.7) // 직진
        {
            beginAngle = 180;
        }
        else if(oldPos.y >= mWinSize.height * 0.5) // 커브
        {
            beginAngle = (float)atan2f((ptDokdo.x - oldPos.x) / 2, ptDokdo.y) * m180PI;
            beginAngle = 180 - beginAngle;
        }
        else    // 독도로 러쉬
        {
            beginAngle = (float)atan2f(ptDokdo.x - oldPos.x, ptDokdo.y) *  m180PI;
            beginAngle = 180 - beginAngle;
        }
        
        if(beginAngle >= 90 && beginAngle <= 270)
        {
            Vec2 newPos1, newPos2;
            int nState = 0;
            while(true)
            {
                newPos1 = Vec2(curMoveDistance * sinf((beginAngle + curAngle) * mPI180) + oldPos.x,
                               curMoveDistance * cosf((beginAngle + curAngle) * mPI180) + oldPos.y);
                newPos2 = Vec2(curMoveDistance * sinf((beginAngle - curAngle) * mPI180) + oldPos.x,
                               curMoveDistance * cosf((beginAngle - curAngle) * mPI180) + oldPos.y);
                
                if(newPos1.x < 10)                      newPos1.x = 10;
                if(newPos1.x > mWinSize.width - 10)      newPos1.x = mWinSize.width - 10;
                if(newPos2.x < 10)                      newPos2.x = 10;
                if(newPos2.x > mWinSize.width - 10)      newPos2.x = mWinSize.width - 10;
                if(newPos1.y < ptDokdo.y) newPos1.y = ptDokdo.y;
                if(newPos2.y < ptDokdo.y) newPos2.y = ptDokdo.y;
                
                bool b1Fail = false;
                bool b2Fail = false;
                
                if(DokdoCalculator::getDistance(newPos1, ptDokdo) <= MINIMUM_DISTANCE)
                    b1Fail = true;
                if(DokdoCalculator::getDistance(newPos2, ptDokdo) <= MINIMUM_DISTANCE)
                    b2Fail = true;

                if(enermyTmp->isShip() && (!b1Fail || !b2Fail))
                {
                    for(int j = 0; j < mArrEnermies.size(); j++)
                    {
                        SpriteUnit* other = mArrEnermies[j];
                        
                        if(enermyTmp == other || !other->isShip())
                        {
                            continue;
                        }
                        
                        enermyTmp->setPosition(newPos1);
                        if(enermyTmp->getBoundingBox().intersectsRect(other->getBoundingBox()))
                        {
                            b1Fail = true;
                        }
                        enermyTmp->setPosition(newPos2);
                        if(enermyTmp->getBoundingBox().intersectsRect(other->getBoundingBox()))
                        {
                            b2Fail = true;
                        }
                        
                        enermyTmp->setPosition(oldPos);
                        
                        if(b1Fail && b2Fail)
                        {
                            break;
                        }
                    }
                    
                    if(!b1Fail || !b2Fail)
                    {
                        for(int j = 0; j < mArrUnits.size(); j++)
                        {
                            SpriteUnit* other = mArrUnits[j];
                            if(other->isShip())
                            {
                                if(!b1Fail &&
                                   DokdoCalculator::getDistance(newPos1, other->getPosition()) <= MINIMUM_DISTANCE)
                                {
                                    b1Fail = true;
                                }
                                if(!b2Fail &&
                                   DokdoCalculator::getDistance(newPos2, other->getPosition()) <= MINIMUM_DISTANCE)
                                {
                                    b2Fail = true;
                                }
                                
                                if(b1Fail && b2Fail)
                                {
                                    break;
                                }
                            }
                        }
                    }
                    
                    if(b1Fail && b2Fail)
                    {
                        curAngle += 45;
                        if(curAngle > 90)
                        {
                            nState = 0;
                            break;
                        }
                    }
                    else
                    {
                        if(!b1Fail)
                        {
                            // 적 유닛이 수평으로 이동해야 하는 경우 가능하면 독도 방향으로 이동하도록 한다.
                            if(curAngle == 90 && newPos1.x < ptDokdo.x && !b2Fail)
                            {
                                nState = 2;
                            }
                            else
                            {
                                nState = 1;
                            }
                        }
                        else
                        {
                            nState = 2;
                        }
                        break;
                    }
                }
                else
                {
                    if(b1Fail && b2Fail)
                    {
                        nState = 0;
                    }
                    else
                    {
                        nState = 1;
                    }
                    break;
                }
            }
            
            if(nState == 1)
                enermyTmp->setPosition(newPos1);
            else if(nState == 2)
                enermyTmp->setPosition(newPos2);
        }
    }
    
    // goalKeeper System
    if(goalKeeperTarget != nullptr &&
       mVulcanRange >= fGoalKeeperDistance &&
       mVulcanCoolTime == 0)
    {
        mVulcanCoolTime = mVulcanCoolTimeMax;
        fireBullet(ptDokdo,
                   goalKeeperTarget->getPosition(),
                   mVulcanPower,
                   false,
                   SPEED_VULCAN,
                   TYPE_VULCAN,
                   TARGET_SURFACE);
    }
    
    for(int i = 0; i < arrNewFighter.size(); i++)
    {
        mArrEnermies.push_back(arrNewFighter[i]);
    }
}

void SceneGame::fireMissile(Vec2 origin,
                            Vec2 target,
                            float damage,
                            bool enermy)
{
    SpriteFire* missile = SpriteFire::create(TYPE_MISSILE, TARGET_ALL, damage, enermy);
    missile->setPosition(origin);
    
    float angle = (float)atanf((target.x - origin.x) / (target.y - origin.y)) * m180PI;
    if(origin.y < target.y)
        missile->setRotation(angle);
    else
        missile->setRotation(angle - 180);
    
    batchAir->addChild(missile, GAME_AIR_ZORDER_MISSILE);
    
    float distance = DokdoCalculator::getDistance(origin, target);
    float life = (distance * SPEED_MISSILE) / mWinSize.height;
    MoveTo* moveTo = MoveTo::create(life, target);
    EaseIn* easeIn = EaseIn::create(moveTo, 2.5);
    CallFuncN* cf = CallFuncN::create(CC_CALLBACK_1(SceneGame::weaponFinished, this));
    Sequence* sequence = Sequence::create(easeIn, cf, nullptr);
    missile->runAction(sequence);
    
    if(enermy)
        mArrEnermyFires.push_back(missile);
    else
        mArrFires.push_back(missile);

    SoundManager::playMissile();
}

void SceneGame::fireTorpedo(Vec2 origin,
                            Vec2 target,
                            float damage,
                            bool enermy)
{
    SpriteFire* torpedo = SpriteFire::create(TYPE_TORPEDO, TARGET_SEALEVEL, damage, enermy);
    torpedo->setPosition(origin);
    
    float angle = (float)atanf((target.x - origin.x) / (target.y - origin.y)) * m180PI;
    if(origin.y < target.y)
        torpedo->setRotation(angle);
    else
        torpedo->setRotation(angle - 180);
    
    batchSurface->addChild(torpedo, GAME_SURFACE_ZORDER_SUBMARINE);
    
    float distance = DokdoCalculator::getDistance(origin, target);
    float life = (distance * SPEED_TORPEDO) / mWinSize.height;
    MoveTo* moveTo = MoveTo::create(life, target);
    EaseIn* easeIn = EaseIn::create(moveTo, 1.8);
    CallFuncN* cf = CallFuncN::create(CC_CALLBACK_1(SceneGame::weaponFinished, this));
    Sequence* sequence = Sequence::create(easeIn, cf, nullptr);
    torpedo->runAction(sequence);
    
    if(enermy)
        mArrEnermyFires.push_back(torpedo);
    else
        mArrFires.push_back(torpedo);
}

void SceneGame::fireBomb(Vec2 origin,
                         Vec2 target,
                         float damage,
                         bool enermy)
{
    SpriteFire* bomb = SpriteFire::create(TYPE_BOMB, TARGET_SEALEVEL, damage, enermy);
    bomb->setPosition(origin);
    bomb->setScale(1.5);
    if(enermy)
        bomb->setRotation(180);
    batchAir->addChild(bomb, GAME_AIR_ZORDER_BOMB);
    
    float distance = DokdoCalculator::getDistance(origin, target);
    float life = (distance * SPEED_BOMB) / mWinSize.height;
    
    EaseOut* easeOut = EaseOut::create(MoveTo::create(life, target), 1.5);
    ScaleTo* scaleTo = ScaleTo::create(life, 0.2);
    CallFuncN* cf = CallFuncN::create(CC_CALLBACK_1(SceneGame::bombFinished, this));
    Sequence* sequence = Sequence::create(Spawn::create(easeOut, scaleTo, nullptr), cf, nullptr);
    bomb->runAction(sequence);
}

void SceneGame::fireNuclear()
{
    Sprite* spBomber = Sprite::createWithSpriteFrameName("b52h.png");
    spBomber->setRotation(180);
    spBomber->setScale(3.0);
    spBomber->setPosition(Vec2(mWinSize.width/2, 0 - spBomber->getBoundingBox().size.height / 2));
    batchAir->addChild(spBomber, GAME_AIR_ZORDER_NUCLEAR);
    
    spBomber->runAction(Sequence::create(
                                        MoveTo::create(0.5,
                                                       Vec2(mWinSize.width / 2,
                                                            mWinSize.height + spBomber->getBoundingBox().size.height / 2)),
                                         CallFuncN::create(CC_CALLBACK_1(SceneGame::selfRemover, this)),
                                         nullptr));
    
    Vec2 origin = Vec2(mWinSize.width / 2, 0);
    Vec2 target = Vec2(mWinSize.width / 2, 450);
    
    SpriteFire* bomb = SpriteFire::create(TYPE_NUCLEAR, TARGET_ALL, mDokdoMaxHP, false);
    bomb->setPosition(origin);
    bomb->setScale(2.0);
    batchAir->addChild(bomb, GAME_AIR_ZORDER_BOMB);
    
    
    float distance = DokdoCalculator::getDistance(origin, target);
    float life = (distance * SPEED_NUCLEAR) / mWinSize.height;
    
    EaseOut* easeOut = EaseOut::create(MoveTo::create(life, target), 1.5);
    ScaleTo* scaleTo = ScaleTo::create(life, 0.2);
    CallFuncN* cf = CallFuncN::create(CC_CALLBACK_1(SceneGame::bombFinished, this));
    Sequence* sequence = Sequence::create(Spawn::create(easeOut, scaleTo, nullptr), cf, nullptr);
    bomb->runAction(sequence);
}

void SceneGame::fireF15K()
{
    int nF15K = 2 + (mSaveData->unitLv.nF15KLv / 10);
    for(int i = 0; i < nF15K; i++)
    {
        SpriteUnit* spF15K = SpriteUnit::create(UNIT_F15K, mSaveData->unitLv.nF15KLv, false);
        
        int randDistance = rand() % 400;
        float distance = mWinSize.height +spF15K->getContentSize().height + randDistance;
        
        float moveTime = (7.5f * distance) / mWinSize.height;
        
        spF15K->setPosition(Vec2(100 + rand() % (int)(mWinSize.width - 200),
                            -1 * randDistance));
        
        MoveBy* moveBy = MoveBy::create(moveTime, Vec2(0, distance));
        CallFuncN* cf = CallFuncN::create(CC_CALLBACK_1(SceneGame::f15kFinished, this));
        Sequence* sequence = Sequence::create(moveBy, cf, nullptr);
        spF15K->runAction(sequence);
        
        batchAir->addChild(spF15K, GAME_AIR_ZORDER_FIGHTER);
        mArrUnits.push_back(spF15K);
    }
}

void SceneGame::fireBullet(Vec2 origin,
                           Vec2 target,
                           float damage,
                           bool enermy,
                           float speed,
                           FIRE_TYPE fireType,
                           FIRE_TARGET targetType)
{
    origin.x += (rand() % 4) * (rand() % 2 == 0 ? -1 : 1);
    origin.y += (rand() % 4) * (rand() % 2 == 0 ? -1 : 1);
    
    SpriteFire* fire = SpriteFire::create(fireType, targetType, damage, enermy);
    fire->setPosition(origin);

    float angle = (float)atanf((target.x - origin.x) / (target.y - origin.y)) * m180PI;
    
    if(origin.y < target.y)
    {
        angle -= 180;
    }
    
    fire->setRotation(angle);
    
    if(fireType == TYPE_CANNON)
    {
        addShootFire(origin, 0.6, 0.05, angle - 180);
    }
    else if(fireType == TYPE_VULCAN)
    {
        addShootFire(origin, 0.3, 0.04, angle - 180);
    }
    
    batchSurface->addChild(fire, GAME_SURFACE_ZORDER_BULLET);
    float distance = DokdoCalculator::getDistance(origin, target);
    float life = (distance * speed) / mWinSize.height;
    MoveTo* moveTo = MoveTo::create(life, target);
    EaseOut* easeOut = EaseOut::create(moveTo, 1.5);
    CallFuncN* cf = CallFuncN::create(CC_CALLBACK_1(SceneGame::weaponFinished, this));
    Sequence* sequence = Sequence::create(easeOut, cf, nullptr);
    fire->runAction(sequence);
    
    if(enermy)
    {
        mArrEnermyFires.push_back(fire);
    }
    else
    {
        mArrFires.push_back(fire);
    }

    if(fireType == TYPE_VULCAN)
    {
    	if(enermy)
    	{
    		SoundManager::playEnermyGun();
    	}
    	else
    	{
    		SoundManager::playGun2();
    	}
    }
    else
    {
    	SoundManager::playCannon();
    }
}

bool SceneGame::fireMatch(FIRE_TARGET target, int unitType)
{
    switch(target)
    {
        case TARGET_SEALEVEL:
            return unitType <= UNIT_DOKDO;
        case TARGET_SURFACE:
            return unitType <= UNIT_HELICOPTER;
            break;
        case TARGET_ALL:
            return true;
    }
    return false;
}

void SceneGame::checkWeapons()
{
    SpriteFire* weapon = nullptr;
    SpriteUnit* unit = nullptr;
    float width;
    Rect target;
    
    // 아군 탄환
    for(vector<SpriteFire*>::iterator iterWeapon = mArrFires.begin();
        iterWeapon != mArrFires.end();
        iterWeapon++)
    {
        weapon = (SpriteFire*)*iterWeapon;
        
        bool bHit = false;
        
        // 지상 유닛
        for(vector<SpriteUnit*>::iterator iterUnit = mArrEnermies.begin();
            iterUnit != mArrEnermies.end();
            iterUnit++)
        {
            unit = (SpriteUnit*)*iterUnit;
            if(unit->mDetected)
            {
                width = unit->getBoundingBox().size.width;
                if(unit->getType() == UNIT_STRATEGIC)
                    width *= 0.6;
                else if(unit->getType() == UNIT_SUBMARINE)
                    width *= 1.4;
                
                target = Rect(unit->getPosition().x - width / 2,
                              unit->getPosition().y - width / 2,
                              width, width);
                
                if(fireMatch(weapon->mTarget, unit->getType()) &&
                   target.containsPoint(weapon->getPosition()))
                {
                    bHit = true;
                    if(0 == unit->subEnergy(weapon->mDamage))
                    {
                    	SoundManager::playExplosion1();
                        mEnermyCtn++;
                        mScoreBoard->addScore(unit->mScore);
                        mScoreBoard->addMoney(unit->mScore * IMCOME_RATE);

                        switch(unit->getType())
                        {
                            case UNIT_SUBMARINE:
                                addWaterColumn(unit->getPosition(), 1.2, 0.10);
                                break;
                            case UNIT_PATROL:
                                addExplosion(unit->getPosition(), 1.0, 0.04, true);
                                addParticleExplosion(unit->getPosition(), 0.4);
                                break;
                            case UNIT_DESTROYER:
                                addExplosion(unit->getPosition(), 1.4, 0.05, true);
                                addParticleExplosion(unit->getPosition(), 0.5);
                                break;
                            case UNIT_CRUISER:
                                mCruiserCnt--;
                                addExplosion(unit->getPosition(), 2.0, 0.06, true);
                                addParticleExplosion(unit->getPosition(), 0.7);
                                break;
                            case UNIT_CARRIER:
                                mCarrierCnt--;
                                addExplosion(unit->getPosition(), 1.8, 0.06, true);
                                addParticleExplosion(unit->getPosition(), 0.6);
                                break;
                            case UNIT_HELICOPTER:
                            case UNIT_LYNX:
                                addExplosion(unit->getPosition(), 1.5, 0.05, true);
                                addParticleExplosion(unit->getPosition(), 0.4);
                                break;
                            case UNIT_BOMBER:
                            case UNIT_FIGHTER:
                                addExplosion(unit->getPosition(), 1.7, 0.06, true);
                                addParticleExplosion(unit->getPosition(), 0.5);
                                break;
                            case UNIT_STRATEGIC:
                                mStrategyBomberCtn--;
                                addExplosion(unit->getPosition(), 2.5, 0.07, true);
                                addParticleExplosion(unit->getPosition(), 1.5);
                                break;
                        }
                        
                        unit->removeFromParentAndCleanup(true);
                        iterUnit = mArrEnermies.erase(iterUnit);
                        iterUnit--;
                    }
                    else
                    {
                    	SoundManager::playExplosion1();
                        mScoreBoard->addScore(1);
                        if(unit->getType() == UNIT_SUBMARINE || weapon->mType == TYPE_TORPEDO)
                        {
                            addWaterColumn(weapon->getPosition(), 0.8, 0.08);
                        }
                        else
                        {
                            switch(weapon->mType)
                            {
                                case TYPE_VULCAN:
                                    addParticleFlash(weapon->getPosition());
                                    break;
                                case TYPE_CANNON:
                                    addParticleFlash(weapon->getPosition());
                                    break;
                                case TYPE_MISSILE:
                                    addExplosion(weapon->getPosition(), 0.6, 0.06, true);
                                    break;
                                case TYPE_TORPEDO: // 위에서 처리 됨.
                                case TYPE_BOMB:
                                case TYPE_NUCLEAR:
                                    // do nothing...
                                    break;
                            }
                        }
                    }
                    break;
                }
            }
        }
        
        if(bHit)
        {
            weapon->stopAllActions();
            weapon->removeFromParentAndCleanup(true);
            iterWeapon = mArrFires.erase(iterWeapon);
            iterWeapon--;
        }
    }
    
    // 적군 탄환
    for(vector<SpriteFire*>::iterator iterWeapon = mArrEnermyFires.begin();
        iterWeapon != mArrEnermyFires.end();
        iterWeapon++)
    {
        weapon = (SpriteFire*)*iterWeapon;
        
        bool bHit = false;
        
        
        if(batchSurface->getChildByTag(GAME_TAG_DOKDO)->getBoundingBox().containsPoint(weapon->getPosition()) &&
           rand() % 10 == 0) // 1/10 확률로만 피격...
        {
            bHit = true;
            mDokdoHP -= weapon->mDamage;
            if(weapon->mType == TYPE_MISSILE)
                addExplosion(weapon->getPosition(), 0.6, 0.05, true);
            else if(weapon->mType == TYPE_TORPEDO)
                addWaterColumn(weapon->getPosition(), 0.9, 0.09);
            else
                addParticleFlash(weapon->getPosition());
            
            if(mDokdoHP < 0)
            {
                mDokdoHP = 0;
                mGameState = GAME_STATE_OVER;
                mGameFinishTerm = 5.f;
                fireNuclear();
            }
            showDokdoEnergyBar();
        }
        else
        {
            // 지상 유닛
            for(vector<SpriteUnit*>::iterator iterUnit = mArrUnits.begin();
                iterUnit != mArrUnits.end();
                iterUnit++)
            {
                unit = (SpriteUnit*)*iterUnit;
                if(unit->mDetected &&
                fireMatch(weapon->mTarget, unit->getType()))
                {
                    width = unit->getBoundingBox().size.width;

                    if(unit->getType() == UNIT_KSS3)
                        width *= 1.4;
                
                    target = Rect(unit->getPosition().x - width / 2,
                                  unit->getPosition().y - width / 2,
                                  width, width);
                
                    if(target.containsPoint(weapon->getPosition()))
                    {
                        bHit = true;
                        if(0 == unit->subEnergy(weapon->mDamage))
                        {
                        	SoundManager::playExplosion1();
                            mForceCtn++;
                            mUnitCnt--;
                            switch (unit->getType()) {
                                case UNIT_KSS3:
                                    addWaterColumn(unit->getPosition(), 1.2, 0.10);
                                    mKSS3Cnt--;
                                    break;
                                case UNIT_PKG:
                                    addExplosion(unit->getPosition(), 1.2, 0.04, true);
                                    addParticleExplosion(unit->getPosition(), 0.4);
                                    mPKGCnt--;
                                    break;
                                case UNIT_KDX2:
                                    addExplosion(unit->getPosition(), 1.4, 0.05, true);
                                    addParticleExplosion(unit->getPosition(), 0.5);
                                    mKDX2Cnt--;
                                    break;
                                case UNIT_KDX3:
                                    addExplosion(unit->getPosition(), 1.6, 0.06, true);
                                    addParticleExplosion(unit->getPosition(), 0.6);
                                    mKDX3Cnt--;
                                    break;
                                case UNIT_DOKDO:
                                    addExplosion(unit->getPosition(), 2.0, 0.07, true);
                                    addParticleExplosion(unit->getPosition(), 0.7);
                                    mDOKDOCnt--;
                                    break;
                                case UNIT_E747:
                                    addExplosion(unit->getPosition(), 2.5, 0.08, false);
                                    addParticleExplosion(unit->getPosition(), 0.8);
                                    mE747Cnt--;
                                    break;
                                case UNIT_F15K:
                                    addExplosion(unit->getPosition(), 2.0, 0.07, false);
                                    addParticleExplosion(unit->getPosition(), 0.6);
                                    mUnitCnt++;
                                    break;
                            }
                        
                            unit->removeFromParentAndCleanup(true);
                            iterUnit = mArrUnits.erase(iterUnit);
                            iterUnit--;
                        }
                        else
                        {
                        	SoundManager::playExplosion2();
                            if(unit->getType() == UNIT_KSS3 || weapon->mType == TYPE_TORPEDO)
                                addWaterColumn(weapon->getPosition(), 0.8, 0.08);
                            else
                            {
                                switch(weapon->mType)
                                {
                                    case TYPE_VULCAN:
                                        addParticleFlash(weapon->getPosition());
                                        break;
                                    case TYPE_CANNON:
                                        addParticleFlash(weapon->getPosition());
                                        break;
                                    case TYPE_MISSILE:
                                        addExplosion(weapon->getPosition(), 0.5, 0.05, true);
                                        break;
                                    case TYPE_TORPEDO: // 위에서 처리 됨.
                                    case TYPE_BOMB:
                                    case TYPE_NUCLEAR:
                                        // do nothing...
                                        break;
                                }
                            }
                        }
                        break;
                    }
                }
            }
        }
        
        if(bHit)
        {
            weapon->stopAllActions();
            weapon->removeFromParentAndCleanup(true);
            iterWeapon = mArrEnermyFires.erase(iterWeapon);
            iterWeapon--;
        }
    }
}

void SceneGame::moveBtn(Sprite* spBtn, bool rev, int price, bool disable /* = false */)
{
    float cur = (100.0 / price) * mMineral;
    if(disable || mUnitCnt >= NAVY_MAX)
    {
        cur = 0;
    }
    
    if(cur >= 100.0)
    {
        spBtn->setOpacity(255);
        spBtn->setAnchorPoint(Vec2(rev ? 1: 0, 0.5));
    }
    else
    {
        spBtn->setOpacity(100);
        spBtn->setAnchorPoint(Vec2(rev ? (cur / 100.0) : 1 - (cur / 100.0), 0.5));
    }
}

void SceneGame::updateSummonBtn()
{
    moveBtn((Sprite*)batchInterface->getChildByTag(GAME_TAG_BTN_PKG), false, mPKGPrice, mPKGCnt >= PKG_MAX);
    moveBtn((Sprite*)batchInterface->getChildByTag(GAME_TAG_BTN_KDX2), true, mKDX2Price, mKDX2Cnt >= KDX2_MAX);
    moveBtn((Sprite*)batchInterface->getChildByTag(GAME_TAG_BTN_KSS3), false, mKSS3Price, mKSS3Cnt >= KSS3_MAX);
    moveBtn((Sprite*)batchInterface->getChildByTag(GAME_TAG_BTN_E747), true, mE747Price, mE747Cnt >= E747_MAX);
    moveBtn((Sprite*)batchInterface->getChildByTag(GAME_TAG_BTN_KDX3), false, mKDX3Price, mKDX3Cnt >= KDX3_MAX);
    moveBtn((Sprite*)batchInterface->getChildByTag(GAME_TAG_BTN_DOKDO), true, mDOKDOPrice, mDOKDOCnt >= DOKDO_MAX);
    
    // Nuclear Bomb
    Sprite* sprite = (Sprite*)batchInterface->getChildByTag(GAME_TAG_BTN_NUCLEAR);
    float cur = (100.0 / mNUCLEARPrice) * mNuclearMineral;
    if(cur >= 100.0)
    {
        cur = 100;
        sprite->setOpacity(255);
        ((Sprite*)sprite->getChildByTag(GAME_TAG_BTN_INNERIMG))->setOpacity(255);
        sprite->setAnchorPoint(Vec2(0 , 0.5));
    }
    else
    {
        sprite->setOpacity(100);
        ((Sprite*)sprite->getChildByTag(GAME_TAG_BTN_INNERIMG))->setOpacity(100);
        sprite->setAnchorPoint(Vec2(1 - (cur / 100.0), 0.5));
    }
    
    // F-15K
    cur = (100.0 / mF15KPrice) * mF15KMineral;
    if(cur >= 100.0)
    {
        cur = 100;
        ((Sprite*)batchInterface->getChildByTag(GAME_TAG_BTN_F15K))->setOpacity(255);
        ((Sprite*)batchInterface->getChildByTag(GAME_TAG_BTN_F15K))->setAnchorPoint(Vec2(1, 0.5));
    }
    else
    {
        ((Sprite*)batchInterface->getChildByTag(GAME_TAG_BTN_F15K))->setOpacity(100);
        ((Sprite*)batchInterface->getChildByTag(GAME_TAG_BTN_F15K))->setAnchorPoint(Vec2((cur / 100.0), 0.5));
    }
}

void SceneGame::updateWeaponBtn()
{
    float fCannonScale = 1.0 - (mCannonCoolTime / mCannonCoolTimeMax);
    Sprite * cannon = (Sprite*)batchInterface->getChildByTag(GAME_TAG_BTN_CANNON);
    Sprite * activate = (Sprite*)cannon->getChildByTag(GAME_TAG_BTN_ACTIVATE);
    activate->setScale(fCannonScale);
    
    float fMissileScale = 1.0 - (mMissileCoolTime / mMissileCoolTimeMax);
    Sprite * missile = (Sprite*)batchInterface->getChildByTag(GAME_TAG_BTN_MISSILE);
    Sprite * activate2 = (Sprite*)missile->getChildByTag(GAME_TAG_BTN_ACTIVATE);
    activate2->setScale(fMissileScale);
}

void SceneGame::addShootFire(Vec2 pt, float scale, float delayPerUnit, float angle)
{
    Sprite* spFire = Sprite::createWithSpriteFrameName("dok_01.png");
    spFire->setPosition(pt);
    spFire->setScale(scale);
    spFire->setRotation(angle);
    spFire->setAnchorPoint(Vec2(0.5, 0.2));
    batchSurfaceFire->addChild(spFire);
    
    Animation* animation = Animation::create();
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
    char szFile[32] = {0, };
    
    for(int i = 1; i <= 6; i++)
    {
        sprintf(szFile, "dok_%02d.png", i);
        animation->addSpriteFrame(frameCache->getSpriteFrameByName(szFile));
    }
    animation->setDelayPerUnit(delayPerUnit);
    
    Animate* animate = Animate::create(animation);
    CallFuncN* cf = CallFuncN::create(CC_CALLBACK_1(SceneGame::selfRemover, this));
    Sequence* sequence = Sequence::create(animate, cf, nullptr);
    spFire->runAction(sequence);
}

void SceneGame::addExplosion(Vec2 pt, float scale, float delayPerUnit, bool surface)
{
    Sprite* spExplosion = Sprite::createWithSpriteFrameName("explosion_effect_00.png");
    spExplosion->setPosition(pt);
    spExplosion->setScale(scale);
    if(surface)
    {
        batchSurfaceFire->addChild(spExplosion);
    }
    else
    {
        batchAirFire->addChild(spExplosion);
    }
    
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
    Animation* animation = Animation::create();
    char szFile[32] = {0, };
    for(int i = 0; i < 36; i++)
    {
        sprintf(szFile, "explosion_effect_%02d.png", i);
        SpriteFrame* frame =frameCache->getSpriteFrameByName(szFile);
        if(frame)
        {
            animation->addSpriteFrame(frame);
        }
    }
    animation->setDelayPerUnit(delayPerUnit);
    
    Animate* animate = Animate::create(animation);
    CallFuncN* cf = CallFuncN::create(CC_CALLBACK_1(SceneGame::selfRemover, this));
    Sequence* sequence = Sequence::create(animate, cf, nullptr);
    spExplosion->runAction(sequence);
}

void SceneGame::addWaterColumn(Vec2 pt, float scale, float delayPerUnit)
{
    Sprite* spWater = Sprite::createWithSpriteFrameName("water_column_00.png");
    spWater->setPosition(pt);
    spWater->setScale(scale);
    batchSurface->addChild(spWater, GAME_SURFACE_ZORDER_WATERCOLUMN);
    
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
    Animation* animation = Animation::create();
    char szFile[32] = {0, };
    for(int i = 0; i < 13; i++)
    {
        sprintf(szFile, "water_column_%02d.png", i);
        SpriteFrame* frame = frameCache->getSpriteFrameByName(szFile);
        if(frame)
        {
            animation->addSpriteFrame(frame);
        }
    }
    animation->setDelayPerUnit(delayPerUnit);
    
    Animate* animate = Animate::create(animation);
    CallFuncN* cf = CallFuncN::create(CC_CALLBACK_1(SceneGame::selfRemover, this));
    Sequence* sequence = Sequence::create(animate, cf, nullptr);
    spWater->runAction(sequence);
}

void SceneGame::bombFinished(Node* node)
{
    SpriteFire* bomb = (SpriteFire*) node;
    switch(bomb->mType)
    {
        case TYPE_BOMB:
        	SoundManager::playExplosion1();
            addExplosion(bomb->getPosition(), 1.2f, 0.06, true);
            
            if(batchSurface->getChildByTag(GAME_TAG_DOKDO)->getBoundingBox().containsPoint(bomb->getPosition()))
            {
                mDokdoHP -= bomb->mDamage;
                if(mDokdoHP < 0)
                {
                    mDokdoHP = 0;
                    mGameState = GAME_STATE_OVER;
                    mGameFinishTerm = 5.f;
                    fireNuclear();
                }
                showDokdoEnergyBar();
            }
            
            for(vector<SpriteUnit*>::iterator iter = mArrUnits.begin();
                iter != mArrUnits.end();
                iter++)
            {
                SpriteUnit* unit = (SpriteUnit*)*iter;
                if(50 >= DokdoCalculator::getDistance(bomb->getPosition(), unit->getPosition()))
                {
                    if(unit->mDetected &&
                       unit->isSurface() &&
                       unit->subEnergy(bomb->mDamage) == 0)
                    {
                        mForceCtn++;
                        mUnitCnt--;
                        
                        if(unit->getType() != UNIT_KSS3 ||
                           unit->getType() != UNIT_PKG)
                        {
                            addParticleExplosion(unit->getPosition(), 0.6f);
                        }
                        
                        switch (unit->getType())
                        {
                            case UNIT_KSS3:
                                addWaterColumn(unit->getPosition(), 1.2, 0.10);
                                mKSS3Cnt--;
                                break;
                            case UNIT_PKG:
                                addExplosion(unit->getPosition(), 1.2, 0.04, true);
                                mPKGCnt--;
                                break;
                            case UNIT_KDX2:
                                addExplosion(unit->getPosition(), 1.4, 0.05, true);
                                mKDX2Cnt--;
                                break;
                            case UNIT_KDX3:
                                addExplosion(unit->getPosition(), 1.6, 0.06, true);
                                mKDX3Cnt--;
                                break;
                            case UNIT_DOKDO:
                                addExplosion(unit->getPosition(), 2.0, 0.07, true);
                                mDOKDOCnt--;
                                break;
                                
                                // E747과 F15K는 파괴될 수 없지만;;;;
                            case UNIT_E747:
                                addExplosion(unit->getPosition(), 2.5, 0.08, false);
                                mE747Cnt--;
                                break;
                            case UNIT_F15K:
                                addExplosion(unit->getPosition(), 2.0, 0.07, false);
                                mUnitCnt++;
                                break;
                        }
                        
                        iter = mArrUnits.erase(iter);
                        iter--;
                        unit->removeFromParentAndCleanup(true);
                    }
                }
            }
            break;
            
        case TYPE_NUCLEAR:
        	SoundManager::playExplosion1();
            addExplosion(bomb->getPosition(), 6.f, 0.08, true);
            for(vector<SpriteUnit*>::iterator iter = mArrEnermies.begin();
                iter != mArrEnermies.end();
                iter++)
            {
                SpriteUnit* enermy = (SpriteUnit*)*iter;
                if(mGameState == GAME_STATE_OVER)
                {
                    addParticleExplosion(enermy->getPosition(), 0.7);
                    addExplosion(enermy->getPosition(), 3.0, 0.04, true);
                    iter = mArrEnermies.erase(iter);
                    iter--;
                    enermy->removeFromParentAndCleanup(true);
                }
                else
                {
                    if(NUCLEAR_RANGE >= DokdoCalculator::getDistance(bomb->getPosition(), enermy->getPosition()))
                    {
                        if(enermy->subEnergy(bomb->mDamage) == 0)
                        {
                            mScoreBoard->addScore(enermy->mScore);
                            mScoreBoard->addMoney(enermy->mScore * IMCOME_RATE);
                            
                            mEnermyCtn++;
                            addExplosion(enermy->getPosition(), 2.0, 0.04, true);
                            switch(enermy->getType())
                            {
                                case UNIT_CRUISER:
                                    mCruiserCnt--;
                                    break;
                                case UNIT_CARRIER:
                                    mCarrierCnt--;
                                    break;
                                case UNIT_STRATEGIC:
                                    mStrategyBomberCtn--;
                                    break;
                                default:
                                    break;
                            }
                            
                            if(enermy->getType() != UNIT_HELICOPTER ||
                               enermy->getType() != UNIT_LYNX ||
                               enermy->getType() != UNIT_PATROL ||
                               enermy->getType() != UNIT_SUBMARINE)
                            {
                                addParticleExplosion(enermy->getPosition(), 0.7);
                            }
                            
                            iter = mArrEnermies.erase(iter);
                            iter--;
                            
                            enermy->removeFromParentAndCleanup(true);
                        }
                    }
                }
            }
            break;
            
        default:
            break;
    }
    bomb->removeFromParentAndCleanup(true);
}

void SceneGame::weaponFinished(Node* node)
{
    SpriteFire* bullet = (SpriteFire*)node;
    
    switch(bullet->mType)
    {
        case TYPE_VULCAN:
        	SoundManager::playExplosion2();
            addWaterColumn(bullet->getPosition(), 0.4, 0.07);
            break;
        case TYPE_CANNON:
        	SoundManager::playExplosion2();
            addWaterColumn(bullet->getPosition(), 0.6, 0.09);
            break;
        case TYPE_MISSILE:
        	SoundManager::playExplosion2();
            addExplosion(bullet->getPosition(), 0.7, 0.05, true);
            break;
        case TYPE_TORPEDO:
        	SoundManager::playExplosion2();
            addWaterColumn(bullet->getPosition(), 0.7, 0.10);
            break;
        default:
            break; // bomb / nuclear는 이곳으로 오지 않고 bombFinished로 간다. 이것들은 mArrFires / mArrEnermyFires에 등록되지도 않음.
    }
    
    SpriteFire* tmp = nullptr;
    if(!bullet->mEnermy)
    {
        for(vector<SpriteFire*>::iterator iter = mArrFires.begin(); iter != mArrFires.end(); iter++)
        {
            tmp = (SpriteFire*)*iter;
            if(tmp == bullet)
            {
                mArrFires.erase(iter);
                break;
            }
        }
    }
    else
    {
        for(vector<SpriteFire*>::iterator iter = mArrEnermyFires.begin(); iter != mArrEnermyFires.end(); iter++)
        {
            tmp = (SpriteFire*)*iter;
            if(tmp == bullet)
            {
                mArrEnermyFires.erase(iter);
                break;
            }
        }
    }
    
    bullet->removeFromParentAndCleanup(true);
}

bool SceneGame::selectWeapon(Vec2 pt)
{
    Sprite* spCANNON = (Sprite*)batchInterface->getChildByTag(GAME_TAG_BTN_CANNON);
    Sprite* spMISSILE = (Sprite*)batchInterface->getChildByTag(GAME_TAG_BTN_MISSILE);
    Sprite *spMAX = (Sprite*)batchSurface->getChildByTag(GAME_TAG_RADAR_MAX);
    
    if(spCANNON->getBoundingBox().containsPoint(pt))
    {
    	SoundManager::playButton();
        spCANNON->setOpacity(255);
        ((Sprite*)spCANNON->getChildByTag(GAME_TAG_BTN_ACTIVATE))->setOpacity(255);
        ((Sprite*)spCANNON->getChildByTag(GAME_TAG_BTN_INNERIMG))->setOpacity(255);
        
        spMISSILE->setOpacity(120);
        ((Sprite*)spMISSILE->getChildByTag(GAME_TAG_BTN_ACTIVATE))->setOpacity(120);
        ((Sprite*)spMISSILE->getChildByTag(GAME_TAG_BTN_INNERIMG))->setOpacity(120);
        
        batchSurface->getChildByTag(GAME_TAG_RADAR_CANNON)->setVisible(true);
        batchSurface->getChildByTag(GAME_TAG_RADAR_MISSILE)->setVisible(false);
        
        spMAX->setScale(mCannonRange / (spMAX->getContentSize().width / 2));
        spMAX->setVisible(true);
        batchSurface->getChildByTag(GAME_TAG_RADAR_LINE)->setVisible(true);
        
        mSelectedWeapon = GAME_TAG_BTN_CANNON;
        return true;
    }
    else if(spMISSILE->getBoundingBox().containsPoint(pt))
    {
    	SoundManager::playButton();
        spCANNON->setOpacity(120);
        ((Sprite*)spCANNON->getChildByTag(GAME_TAG_BTN_ACTIVATE))->setOpacity(120);
        ((Sprite*)spCANNON->getChildByTag(GAME_TAG_BTN_INNERIMG))->setOpacity(120);
        
        spMISSILE->setOpacity(255);
        ((Sprite*)spMISSILE->getChildByTag(GAME_TAG_BTN_ACTIVATE))->setOpacity(255);
        ((Sprite*)spMISSILE->getChildByTag(GAME_TAG_BTN_INNERIMG))->setOpacity(255);
        
        batchSurface->getChildByTag(GAME_TAG_RADAR_MISSILE)->setVisible(true);
        batchSurface->getChildByTag(GAME_TAG_RADAR_CANNON)->setVisible(false);
        
        spMAX->setScale(mMissileRange / (spMAX->getContentSize().width / 2));
        spMAX->setVisible(true);
        batchSurface->getChildByTag(GAME_TAG_RADAR_LINE)->setVisible(true);
        
        mSelectedWeapon = GAME_TAG_BTN_MISSILE;
        return true;
    }
    return false;
}

bool SceneGame::selectSummon(Vec2 pt)
{
    if(mMineral >= mPKGPrice && mPKGCnt < PKG_MAX && mUnitCnt < NAVY_MAX &&
       batchInterface->getChildByTag(GAME_TAG_BTN_PKG)->boundingBox().containsPoint(pt))
    {
        if(addUnit(UNIT_PKG, mSaveData->unitLv.nPKGLv, false))
        {
        	SoundManager::playButton();
            mScoreBoard->addScore(FORCE_PKG_PRICE / 2);
            mPKGCnt++;
            mUnitCnt++;
            mMineral -= mPKGPrice;
        }
        return true;
    }
    else if(mMineral >= mKDX2Price && mKDX2Cnt < KDX2_MAX && mUnitCnt < NAVY_MAX &&
            batchInterface->getChildByTag(GAME_TAG_BTN_KDX2)->boundingBox().containsPoint(pt))
    {
        if(addUnit(UNIT_KDX2, mSaveData->unitLv.nKDX2Lv, false))
        {
        	SoundManager::playButton();
            mScoreBoard->addScore(FORCE_KDX2_PRICE / 2);
            mKDX2Cnt++;
            mUnitCnt++;
            mMineral -= mKDX2Price;
        }
        return true;
    }
    else if(mMineral >= mKSS3Price && mKSS3Cnt < KSS3_MAX && mUnitCnt < NAVY_MAX &&
            batchInterface->getChildByTag(GAME_TAG_BTN_KSS3)->boundingBox().containsPoint(pt))
    {
        if(addUnit(UNIT_KSS3, mSaveData->unitLv.nKSS3Lv, false))
        {
        	SoundManager::playButton();
            mScoreBoard->addScore(FORCE_KSS3_PRICE / 2);
            mKSS3Cnt++;
            mUnitCnt++;
            mMineral -= mKSS3Price;
        }
        return true;
    }
    else if(mMineral >= mE747Price && mE747Cnt < E747_MAX && mUnitCnt < NAVY_MAX &&
            batchInterface->getChildByTag(GAME_TAG_BTN_E747)->boundingBox().containsPoint(pt))
    {
        if(addUnit(UNIT_E747, mSaveData->unitLv.nE747Lv, false))
        {
        	SoundManager::playButton();
            mScoreBoard->addScore(FORCE_E747_PRICE / 2);
            mE747Cnt++;
            mUnitCnt++;
            mMineral -= mE747Price;
        }
        return true;
    }
    else if(mMineral >= mKDX3Price && mKDX3Cnt < KDX3_MAX && mUnitCnt < NAVY_MAX &&
            batchInterface->getChildByTag(GAME_TAG_BTN_KDX3)->boundingBox().containsPoint(pt))
    {
        if(addUnit(UNIT_KDX3, mSaveData->unitLv.nKDX3Lv, false))
        {
        	SoundManager::playButton();
            mScoreBoard->addScore(FORCE_KDX3_PRICE / 2);
            mKDX3Cnt++;
            mUnitCnt++;
            mMineral -= mKDX3Price;
        }
        return true;
    }
    else if(mMineral >= mDOKDOPrice && mDOKDOCnt < DOKDO_MAX && mUnitCnt < NAVY_MAX &&
            batchInterface->getChildByTag(GAME_TAG_BTN_DOKDO)->boundingBox().containsPoint(pt))
    {
        if(addUnit(UNIT_DOKDO, mSaveData->unitLv.nDOKDOLv, false))
        {
        	SoundManager::playButton();
            mScoreBoard->addScore(FORCE_DOKDO_PRICE / 2);
            mDOKDOCnt++;
            mUnitCnt++;
            mMineral -= mDOKDOPrice;
        }
        return true;
    }
    else if(mNuclearMineral >= mNUCLEARPrice &&
            batchInterface->getChildByTag(GAME_TAG_BTN_NUCLEAR)->boundingBox().containsPoint(pt))
    {
    	SoundManager::playButton();
        fireNuclear();
        mNuclearMineral = 0;
        return true;
    }
    else if(mF15KMineral >= mF15KPrice &&
            batchInterface->getChildByTag(GAME_TAG_BTN_F15K)->boundingBox().containsPoint(pt))
    {
    	SoundManager::playButton();
        fireF15K();
        mF15KMineral = 0;
        return true;
    }
    
    return false;
}

void SceneGame::onTouchesBegan(vector<Touch*> touches, Event* event)
{
    
}

void SceneGame::onTouchesMoved(vector<Touch*> touches, Event* event)
{
    
}

void SceneGame::destroyGame(int income, bool highscore)
{
	delete mSaveData;
    unscheduleUpdate();
    removeAllChildrenWithCleanup(true);
    getEventDispatcher()->removeEventListener(mTouchListener);
    setKeypadEnabled(false);
    Director::getInstance()->replaceScene(SceneMenu::createScene(
                                    mGameState == GAME_STATE_CLEAR || mDifficulty == MENU_TAG_ENDLESS ? true : false,
                                    mScoreBoard->getTime(),
                                    mScoreBoard->getScore(),
                                    mEnermyCtn,
                                    mForceCtn,
                                    income,
                                    highscore));
}

bool SceneGame::checkPause(Vec2 pt)
{
    if(pt.x > 430 && pt.y > 750 && mGameState == GAME_STATE_PLAY)
    {
    	SoundManager::playButton();
        pauseGame();
        return true;
    }
    else if(mGameState == GAME_STATE_PAUSE)
    {
        if(getChildByTag(GAME_TAG_PAUSEDLG)->getBoundingBox().containsPoint(pt))
        {
        	SoundManager::playButton();
            if(pt.x > mWinSize.width / 2)
            {
                resumeGame();
            }
            else
            {
                mGameState = GAME_STATE_OVER;
                Director::getInstance()->resume();
                getChildByTag(GAME_TAG_SEA)->setOpacity(255);
                mGameFinishTerm = 0.5;
            }
        }
        return true;
    }
    return false;
}

void SceneGame::resumeGame()
{
    mGameState = GAME_STATE_PLAY;
    Director::getInstance()->resume();
	SoundManager::playBGM();
    
    getChildByTag(GAME_TAG_SEA)->setOpacity(255);
    removeChildByTag(GAME_TAG_PAUSEDLG, true);
}

void SceneGame::pauseGame()
{
    mGameState = GAME_STATE_PAUSE;

    Director::getInstance()->pause();
	SoundManager::stopBGM();
    
    getChildByTag(GAME_TAG_SEA)->setOpacity(100);
    
    Sprite* spDlg = Sprite::create("paused.png", Rect(0, 0, 408, 170));
    spDlg->setPosition(Vec2(mWinSize.width / 2, mWinSize.height * 0.52));
    addChild(spDlg, GAME_ZORDER_INTERFACE, GAME_TAG_PAUSEDLG);
    
    Sprite* spTxt1 = Sprite::create("paused.png", Rect(0, 216, 158, 44));
    spTxt1->setPosition(Vec2(125, 66));
    spDlg->addChild(spTxt1, 1, GAME_TAG_PAUSETXT1);
    
    Sprite* spTxt2 = Sprite::create("paused.png", Rect(159, 171, 158, 44));
    spTxt2->setPosition(Vec2(285, 66));
    spDlg->addChild(spTxt2, 1, GAME_TAG_PAUSETXT2);
}

void SceneGame::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event)
{
}

void SceneGame::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
    if(keycode == EventKeyboard::KeyCode::KEY_BACK ||
       keycode == EventKeyboard::KeyCode::KEY_BACKSPACE)
    {
    	SoundManager::playButton();
        if(mGameState == GAME_STATE_PLAY)
        {
            pauseGame();
        }
        else if(mGameState == GAME_STATE_PAUSE)
        {
            resumeGame();
        }
    }
}

void SceneGame::onTouchesEnded(vector<Touch*> touches, Event* event)
{
    Vec2 pt = touches[0]->getLocation();
    if(mGameState == GAME_STATE_PLAY)
    {
        if(!checkPause(pt))
        {
            if(!selectWeapon(pt))
            {
                if(!selectSummon(pt))
                {
                    if(mSelectedWeapon == GAME_TAG_BTN_CANNON && mCannonCoolTime == 0)
                    {
                        mCannonCoolTime = mCannonCoolTimeMax;
                        if(mCannonRange >= DokdoCalculator::getDistance(ptDokdo, pt))
                        {
                            fireBullet(ptDokdo, pt, mCannonPower, false, SPEED_CANNON, TYPE_CANNON, TARGET_ALL);
                        }
                        else
                        {
                            float angle = atan2f(pt.x - ptDokdo.x, pt.y - ptDokdo.y) * m180PI;
                            Vec2 target = Vec2(mCannonRange * sinf(angle * mPI180) + ptDokdo.x,
                                               mCannonRange * cosf(angle * mPI180) + ptDokdo.y);
                        
                            fireBullet(ptDokdo, target, mCannonPower, false, SPEED_CANNON, TYPE_CANNON, TARGET_ALL);
                        }
                    }
                    else if(mSelectedWeapon == GAME_TAG_BTN_MISSILE && mMissileCoolTime == 0)
                    {
                        mMissileCoolTime = mMissileCoolTimeMax;
                        if(mMissileRange >= DokdoCalculator::getDistance(ptDokdo, pt))
                        {
                            fireMissile(ptDokdo, pt, mMissilePower, false);
                        }
                        else
                        {
                            float angle = atan2f(pt.x - ptDokdo.x, pt.y - ptDokdo.y) * m180PI;
                            Vec2 target = Vec2(mMissileRange * sinf(angle * mPI180) + ptDokdo.x,
                                               mMissileRange * cosf(angle * mPI180) + ptDokdo.y);
                            fireMissile(ptDokdo, target, mMissilePower, false);
                        }
                    }
                }
            }
        }
    }
    else if(mGameState == GAME_STATE_PAUSE)
    {
        checkPause(pt);
    }
    else if(mGameState == GAME_STATE_CLEAR)
    {
        
    }
    else if(mGameState == GAME_STATE_OVER)
    {
        
    }
}

bool SceneGame::isPaused()
{
    return mGameState == GAME_STATE_PAUSE;
}

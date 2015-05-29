//
//  SceneUpgrade.cpp
//  MyCppGame
//
//  Created by Jinryul Kim on 2014. 7. 28..
//
//

#include "SceneUpgrade.h"
#include "SpriteUnit.h"
#include "DokdoCalculator.h"
#include "LabelCreater.h"
#include "SaveManager.h"
#include "SoundManager.h"

USING_NS_CC;
using namespace std;

Scene* SceneUpgrade::createScene()
{
    Scene* scene = Scene::create();
    scene->setTag(SCENE_TAG_UPGRADE);
    SceneUpgrade* upgrade = SceneUpgrade::create();
    upgrade->setTag(LAYER_TAG_UPGRADE);
    upgrade->updateInformation(SaveManager::load());
    scene->addChild(upgrade);
    return scene;
}

void SceneUpgrade::updateInformation(DDC_SAVE_DATA* save)
{
    saveData = save;
    
    char szTEMP[16] = {0, };
    sprintf(szTEMP, "%012d", saveData->nMoney);
    labelMoney->setString(szTEMP);
    
    sprintf(szTEMP, "%02d", saveData->dokdoLv.nVulcanLv);
    labelLvVulcan->setString(szTEMP);
    
    sprintf(szTEMP, "%02d", saveData->dokdoLv.nCannonLv);
    labelLvCannon->setString(szTEMP);
    
    sprintf(szTEMP, "%02d", saveData->dokdoLv.nMissileLv);
    labelLvMissile->setString(szTEMP);
    
    sprintf(szTEMP, "%02d", curPage == 1 ? saveData->unitLv.nPKGLv : saveData->unitLv.nE747Lv);
    labelLvUnit1->setString(szTEMP);
    
    sprintf(szTEMP, "%02d", curPage == 1 ? saveData->unitLv.nKDX2Lv : saveData->unitLv.nKSS3Lv);
    labelLvUnit2->setString(szTEMP);
    
    sprintf(szTEMP, "%02d", curPage == 1 ? saveData->unitLv.nKDX3Lv : saveData->unitLv.nF15KLv);
    labelLvUnit3->setString(szTEMP);
    
    sprintf(szTEMP, "%d",  DokdoCalculator::getDokdoRange(DOKDO_VULCAN_RANGE, saveData->dokdoLv.nVulcanLv));
    ((Label*)getChildByTag(TAG_LABEL_VULCAN))->setString(szTEMP);
    
    sprintf(szTEMP, "%d",  DokdoCalculator::getDokdoSPM(DOKDO_VULCAN_SPM, saveData->dokdoLv.nVulcanLv));
    ((Label*)getChildByTag(TAG_LABEL_VULCAN + 1))->setString(szTEMP);
    
    sprintf(szTEMP, "%d",  DokdoCalculator::getDokdoDamage(DOKDO_VULCAN_POWER, saveData->dokdoLv.nVulcanLv));
    ((Label*)getChildByTag(TAG_LABEL_VULCAN + 2))->setString(szTEMP);
    
    sprintf(szTEMP, "%d",  DokdoCalculator::getDokdoRange(DOKDO_CANNON_RANGE, saveData->dokdoLv.nCannonLv));
    ((Label*)getChildByTag(TAG_LABEL_CANNON))->setString(szTEMP);
    
    sprintf(szTEMP, "%d",  DokdoCalculator::getDokdoSPM(DOKDO_CANNON_SPM, saveData->dokdoLv.nCannonLv));
    ((Label*)getChildByTag(TAG_LABEL_CANNON + 1))->setString(szTEMP);
    
    sprintf(szTEMP, "%d",  DokdoCalculator::getDokdoDamage(DOKDO_CANNON_POWER, saveData->dokdoLv.nCannonLv));
    ((Label*)getChildByTag(TAG_LABEL_CANNON + 2))->setString(szTEMP);
    
    sprintf(szTEMP, "%d",  DokdoCalculator::getDokdoRange(DOKDO_MISSILE_RANGE, saveData->dokdoLv.nMissileLv));
    ((Label*)getChildByTag(TAG_LABEL_MISSILE))->setString(szTEMP);
    
    sprintf(szTEMP, "%d",  DokdoCalculator::getDokdoSPM(DOKDO_MISSILE_SPM, saveData->dokdoLv.nMissileLv));
    ((Label*)getChildByTag(TAG_LABEL_MISSILE + 1))->setString(szTEMP);
    
    sprintf(szTEMP, "%d",  DokdoCalculator::getDokdoDamage(DOKDO_MISSILE_POWER, saveData->dokdoLv.nMissileLv));
    ((Label*)getChildByTag(TAG_LABEL_MISSILE + 2))->setString(szTEMP);
    
    upgradeBtnEnable(DokdoCalculator::getUpgradePrice(UPGRADE_VULCAN_PRICE, saveData->dokdoLv.nVulcanLv), spUpVulcan);
    upgradeBtnEnable(DokdoCalculator::getUpgradePrice(UPGRADE_CANNON_PRICE, saveData->dokdoLv.nCannonLv), spUpCannon);
    upgradeBtnEnable(DokdoCalculator::getUpgradePrice(UPGRADE_MISSILE_PRICE, saveData->dokdoLv.nMissileLv), spUpMissile);
    
    if(curPage == 1)
    {
        sprintf(szTEMP, "%02d", saveData->unitLv.nDOKDOLv);
        labelLvUnit4->setString(szTEMP);
        
        sprintf(szTEMP, "%d", DokdoCalculator::getUnitHP(FORCE_PKG_HP, saveData->unitLv.nPKGLv));
        ((Label*)getChildByTag(TAG_LABEL_UNIT1))->setString(szTEMP);
        sprintf(szTEMP, "%d", DokdoCalculator::getUnitRange(FORCE_PKG_VULCAN_RANGE, saveData->unitLv.nPKGLv));
        ((Label*)getChildByTag(TAG_LABEL_UNIT1+1))->setString(szTEMP);
        sprintf(szTEMP, "%d", DokdoCalculator::getUnitSPM(FORCE_PKG_VULCAN_SPM, saveData->unitLv.nPKGLv));
        ((Label*)getChildByTag(TAG_LABEL_UNIT1+2))->setString(szTEMP);
        sprintf(szTEMP, "%d", DokdoCalculator::getUnitDamage(FORCE_PKG_VULCAN_POWER, saveData->unitLv.nPKGLv));
        ((Label*)getChildByTag(TAG_LABEL_UNIT1+3))->setString(szTEMP);
        upgradeBtnEnable(DokdoCalculator::getUpgradePrice(UPGRADE_PKG_PRICE, saveData->unitLv.nPKGLv), spUpNavy1);
        
        sprintf(szTEMP, "%d", DokdoCalculator::getUnitHP(FORCE_KDX2_HP, saveData->unitLv.nKDX2Lv));
        ((Label*)getChildByTag(TAG_LABEL_UNIT2))->setString(szTEMP);
        sprintf(szTEMP, "%d", DokdoCalculator::getUnitRange(FORCE_KDX2_CANNON_RANGE, saveData->unitLv.nKDX2Lv));
        ((Label*)getChildByTag(TAG_LABEL_UNIT2+1))->setString(szTEMP);
        sprintf(szTEMP, "%d", DokdoCalculator::getUnitSPM(FORCE_KDX2_CANNON_SPM, saveData->unitLv.nKDX2Lv));
        ((Label*)getChildByTag(TAG_LABEL_UNIT2+2))->setString(szTEMP);
        sprintf(szTEMP, "%d", DokdoCalculator::getUnitDamage(FORCE_KDX2_CANNON_POWER, saveData->unitLv.nKDX2Lv));
        ((Label*)getChildByTag(TAG_LABEL_UNIT2+3))->setString(szTEMP);
        upgradeBtnEnable(DokdoCalculator::getUpgradePrice(UPGRADE_KDX2_PRICE, saveData->unitLv.nKDX2Lv), spUpNavy2);
        
        sprintf(szTEMP, "%d", DokdoCalculator::getUnitHP(FORCE_KDX3_HP, saveData->unitLv.nKDX3Lv));
        ((Label*)getChildByTag(TAG_LABEL_UNIT3))->setString(szTEMP);
        sprintf(szTEMP, "%d", DokdoCalculator::getUnitRange(FORCE_KDX3_MISSILE_RANGE, saveData->unitLv.nKDX3Lv));
        ((Label*)getChildByTag(TAG_LABEL_UNIT3+1))->setString(szTEMP);
        sprintf(szTEMP, "%d", DokdoCalculator::getUnitSPM(FORCE_KDX3_MISSILE_SPM, saveData->unitLv.nKDX3Lv));
        ((Label*)getChildByTag(TAG_LABEL_UNIT3+2))->setString(szTEMP);
        sprintf(szTEMP, "%d", DokdoCalculator::getUnitDamage(FORCE_KDX3_MISSILE_POWER, saveData->unitLv.nKDX3Lv));
        ((Label*)getChildByTag(TAG_LABEL_UNIT3+3))->setString(szTEMP);
        upgradeBtnEnable(DokdoCalculator::getUpgradePrice(UPGRADE_KDX3_PRICE, saveData->unitLv.nKDX3Lv), spUpNavy3);
        
        sprintf(szTEMP, "%d", DokdoCalculator::getUnitHP(FORCE_DOKDO_HP, saveData->unitLv.nDOKDOLv));
        ((Label*)getChildByTag(TAG_LABEL_UNIT4))->setString(szTEMP);
        sprintf(szTEMP, "%d", DokdoCalculator::getUnitRange(FORCE_DOKDO_RESTORATION_RANGE, saveData->unitLv.nDOKDOLv));
        ((Label*)getChildByTag(TAG_LABEL_UNIT4+1))->setString(szTEMP);
        sprintf(szTEMP, "%d", DokdoCalculator::getUnitSPM(FORCE_DOKDO_RESTORATION_SPM, saveData->unitLv.nDOKDOLv));
        ((Label*)getChildByTag(TAG_LABEL_UNIT4+2))->setString(szTEMP);
        sprintf(szTEMP, "%d", DokdoCalculator::getUnitDamage(FORCE_DOKDO_RESTORATION_POWER, saveData->unitLv.nDOKDOLv));
        ((Label*)getChildByTag(TAG_LABEL_UNIT4+3))->setString(szTEMP);
        upgradeBtnEnable(DokdoCalculator::getUpgradePrice(UPGRADE_DOKDO_PRICE, saveData->unitLv.nDOKDOLv), spUpNavy4);
    }
    else
    {
        sprintf(szTEMP, "%d", DokdoCalculator::getUnitHP(FORCE_E747_HP, saveData->unitLv.nE747Lv));
        ((Label*)getChildByTag(TAG_LABEL_UNIT1))->setString(szTEMP);
        sprintf(szTEMP, "%d", DokdoCalculator::getUnitRange(FORCE_E747_BMEWS_RANGE, saveData->unitLv.nE747Lv));
        ((Label*)getChildByTag(TAG_LABEL_UNIT1+1))->setString(szTEMP);
        ((Label*)getChildByTag(TAG_LABEL_UNIT1+2))->setString("0");
        ((Label*)getChildByTag(TAG_LABEL_UNIT1+3))->setString("0");
        upgradeBtnEnable(DokdoCalculator::getUpgradePrice(UPGRADE_E747_PRICE, saveData->unitLv.nE747Lv), spUpNavy1);
        
        sprintf(szTEMP, "%d", DokdoCalculator::getUnitHP(FORCE_KSS_HP, saveData->unitLv.nKSS3Lv));
        ((Label*)getChildByTag(TAG_LABEL_UNIT2))->setString(szTEMP);
        sprintf(szTEMP, "%d", DokdoCalculator::getUnitRange(FORCE_KSS_TORPEDO_RANGE, saveData->unitLv.nKSS3Lv));
        ((Label*)getChildByTag(TAG_LABEL_UNIT2+1))->setString(szTEMP);
        sprintf(szTEMP, "%d", DokdoCalculator::getUnitSPM(FORCE_KSS_TORPEDO_SPM, saveData->unitLv.nKSS3Lv));
        ((Label*)getChildByTag(TAG_LABEL_UNIT2+2))->setString(szTEMP);
        sprintf(szTEMP, "%d", DokdoCalculator::getUnitDamage(FORCE_KSS_TORPEDO_POWER, saveData->unitLv.nKSS3Lv));
        ((Label*)getChildByTag(TAG_LABEL_UNIT2+3))->setString(szTEMP);
        upgradeBtnEnable(DokdoCalculator::getUpgradePrice(UPGRADE_KSS3_PRICE, saveData->unitLv.nKSS3Lv), spUpNavy2);
        
        sprintf(szTEMP, "%d", DokdoCalculator::getUnitHP(FORCE_F15K_HP, saveData->unitLv.nF15KLv));
        ((Label*)getChildByTag(TAG_LABEL_UNIT3))->setString(szTEMP);
        sprintf(szTEMP, "%d", DokdoCalculator::getUnitRange(FORCE_F15K_MISSILE_RANGE, saveData->unitLv.nF15KLv));
        ((Label*)getChildByTag(TAG_LABEL_UNIT3+1))->setString(szTEMP);
        sprintf(szTEMP, "%d", DokdoCalculator::getUnitSPM(FORCE_F15K_MISSILE_SPM, saveData->unitLv.nF15KLv));
        ((Label*)getChildByTag(TAG_LABEL_UNIT3+2))->setString(szTEMP);
        sprintf(szTEMP, "%d", DokdoCalculator::getUnitDamage(FORCE_F15K_MISSILE_POWER, saveData->unitLv.nF15KLv));
        ((Label*)getChildByTag(TAG_LABEL_UNIT3+3))->setString(szTEMP);
        upgradeBtnEnable(DokdoCalculator::getUpgradePrice(UPGRADE_F15K_PRICE, saveData->unitLv.nF15KLv), spUpNavy3);
        
        spUpNavy4->stopAllActions();
        spUpNavy4->setOpacity(0);
    }
    
    SaveManager::save(saveData);
}

void SceneUpgrade::upgradeBtnEnable(int upgradePrice, Sprite* btn)
{
    char szTEMP[16] = {0, };
    
    if(upgradePrice > 0)
    {
        sprintf(szTEMP, "%06d", upgradePrice);
    }
    else
    {
        sprintf(szTEMP, "MAX LEVEL");
    }
    
    ((Label*)btn->getChildByTag(TAG_LABEL_PRICE))->setString(szTEMP);
    
    if(upgradePrice == 0 || saveData->nMoney < upgradePrice)
    {
        btn->stopAllActions();
        btn->setOpacity(0);
    }
    else
    {
        btn->setOpacity(255);
        btn->runAction(RepeatForever::create(Sequence::create(FadeOut::create(0.5), FadeIn::create(0.5), nullptr)));
    }
}

bool SceneUpgrade::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    Size winSize = Director::getInstance()->getWinSize();
    Sprite* spBK = Sprite::create("upgradebk.png");
    spBK->setPosition(Vec2(winSize.width/2, winSize.height/2));
    addChild(spBK, 1);
    
    spBack = Sprite::createWithSpriteFrameName("option_back.png");
    spBack->setPosition(Vec2(390, 66));
    spBack->setScale(1.1);
    addChild(spBack, 2);
    
    labelMoney = LabelCreater::createLabel("000000000000", "Wednesday.ttf", 28);
    labelMoney->setAnchorPoint(Vec2(1, 0));
    labelMoney->setPosition(Vec2(295, 46));
    labelMoney->setColor(Color3B(25, 181, 124));
    addChild(labelMoney, 2);
    
    labelLvVulcan = addLvLabel(Color3B(1, 104, 139), Vec2(134, 598));
    labelLvCannon = addLvLabel(Color3B(1, 104, 139), Vec2(134, 531));
    labelLvMissile = addLvLabel(Color3B(1, 104, 139), Vec2(134, 468));
    
    spUpVulcan = addUpgradeBtn("upgrade_button0.png", Vec2(382, 606), DOKDO_COLOR);
    spUpCannon = addUpgradeBtn("upgrade_button0.png", Vec2(382, 540), DOKDO_COLOR);
    spUpMissile = addUpgradeBtn("upgrade_button0.png", Vec2(382, 475), DOKDO_COLOR);
    
    addDokdoInfo(Vec2(170, 625), TAG_LABEL_VULCAN);
    addDokdoInfo(Vec2(170, 558), TAG_LABEL_CANNON);
    addDokdoInfo(Vec2(170, 495), TAG_LABEL_MISSILE);
    
    curPage = 1;
    spPage1 = Sprite::createWithSpriteFrameName("upgrade_01.png");
    spPage1->setPosition(Vec2(winSize.width/2, 250));
    addChild(spPage1, 2);
    
    spPage2 = Sprite::createWithSpriteFrameName("upgrade_02.png");
    spPage2->setPosition(Vec2(winSize.width/2, 250));
    spPage2->setOpacity(0);
    addChild(spPage2, 2);
    
    spPrev = Sprite::createWithSpriteFrameName("upgrade_03.png");
    spPrev->setAnchorPoint(Vec2(0, 0.5));
    spPrev->setPosition(Vec2(5, 250));
    addChild(spPrev, 3);
    
    spNext = Sprite::createWithSpriteFrameName("upgrade_04.png");
    spNext->setAnchorPoint(Vec2(1, 0.5));
    spNext->setPosition(Vec2(winSize.width - 5, 250));
    addChild(spNext, 3);
    
    labelLvUnit1 = addLvLabel(Color3B(148, 97, 22), Vec2(134, 340));
    labelLvUnit2 = addLvLabel(Color3B(148, 97, 22), Vec2(134, 340 - 65));
    labelLvUnit3 = addLvLabel(Color3B(148, 97, 22), Vec2(134, 340 - (65 * 2)));
    labelLvUnit4 = addLvLabel(Color3B(148, 97, 22), Vec2(134, 340 - (65 * 3)));
    
    spUpNavy1 = addUpgradeBtn("upgrade_button1.png", Vec2(382, 350), UNIT_COLOR);
    spUpNavy2 = addUpgradeBtn("upgrade_button1.png", Vec2(382, 350 - 65), UNIT_COLOR);
    spUpNavy3 = addUpgradeBtn("upgrade_button1.png", Vec2(382, 350 - (65 * 2)), UNIT_COLOR);
    spUpNavy4 = addUpgradeBtn("upgrade_button1.png", Vec2(382, 350 - (65 * 3)), UNIT_COLOR);
    
    addUnitInfo(Vec2(170, 370), TAG_LABEL_UNITINFO1);
    addUnitInfo(Vec2(170, 306), TAG_LABEL_UNITINFO2);
    addUnitInfo(Vec2(170, 240), TAG_LABEL_UNITINFO3);
    addUnitInfo(Vec2(170, 175), TAG_LABEL_UNITINFO4);
    
    mTouchListener = EventListenerTouchAllAtOnce::create();
    mTouchListener->onTouchesBegan = CC_CALLBACK_2(SceneUpgrade::onTouchesBegan, this);
    mTouchListener->onTouchesMoved = CC_CALLBACK_2(SceneUpgrade::onTouchesMoved, this);
    mTouchListener->onTouchesEnded = CC_CALLBACK_2(SceneUpgrade::onTouchesEnded, this);
    getEventDispatcher()->addEventListenerWithFixedPriority(mTouchListener, 1);
    
    setKeypadEnabled(true);
    
    return true;
}

void SceneUpgrade::addDokdoInfo(Vec2 pt, int tag)
{
    Label* range = LabelCreater::createLabel("Range", "Capsmall.ttf", INFO_FONTSIZE);
    range->setAnchorPoint(Vec2(0, 0.5));
    range->setPosition(pt);
    range->setColor(DOKDO_COLOR);
    addChild(range, 2);
    
    Label* spm = LabelCreater::createLabel("SPM", "Capsmall.ttf", INFO_FONTSIZE);
    spm->setAnchorPoint(Vec2(0, 0.5));
    spm->setPosition(Vec2(pt.x, pt.y-19));
    spm->setColor(DOKDO_COLOR);
    addChild(spm, 2);
    
    Label* damage = LabelCreater::createLabel("Damage", "Capsmall.ttf", INFO_FONTSIZE);
    damage->setAnchorPoint(Vec2(0, 0.5));
    damage->setPosition(Vec2(pt.x, pt.y - (36)));
    damage->setColor(DOKDO_COLOR);
    addChild(damage, 2);
    
    Label* range2 = LabelCreater::createLabel("0", "Capsmall.ttf", INFO_FONTSIZE);
    range2->setAnchorPoint(Vec2(1, 0.5));
    range2->setPosition(Vec2(INFO_RIGHT, range->getPosition().y));
    range2->setColor(DOKDO_COLOR);
    addChild(range2, 2, tag);
    
    Label* spm2 = LabelCreater::createLabel("00", "Capsmall.ttf", INFO_FONTSIZE);
    spm2->setAnchorPoint(Vec2(1, 0.5));
    spm2->setPosition(Vec2(INFO_RIGHT, spm->getPosition().y));
    spm2->setColor(DOKDO_COLOR);
    addChild(spm2, 2, tag + 1);
    
    Label* damage2 = LabelCreater::createLabel("000", "Capsmall.ttf", INFO_FONTSIZE);
    damage2->setAnchorPoint(Vec2(1, 0.5));
    damage2->setPosition(Vec2(INFO_RIGHT, damage->getPosition().y));
    damage2->setColor(DOKDO_COLOR);
    addChild(damage2, 2, tag + 2);
}

void SceneUpgrade::addUnitInfo(Vec2 pt, int tag)
{
    Label* hp = LabelCreater::createLabel("HP", "Capsmall.ttf", INFO_FONTSIZE);
    hp->setAnchorPoint(Vec2(0, 0.5));
    hp->setPosition(pt);
    hp->setColor(UNIT_COLOR);
    addChild(hp, 2, tag);
    
    Label* range = LabelCreater::createLabel("Range", "Capsmall.ttf", INFO_FONTSIZE);
    range->setAnchorPoint(Vec2(0, 0.5));
    range->setPosition(Vec2(pt.x, pt.y - 13));
    range->setColor(UNIT_COLOR);
    addChild(range, 2, tag + 1);
    
    Label* spm = LabelCreater::createLabel("SPM", "Capsmall.ttf", INFO_FONTSIZE);
    spm->setAnchorPoint(Vec2(0, 0.5));
    spm->setPosition(Vec2(pt.x, pt.y - (13 * 2)));
    spm->setColor(UNIT_COLOR);
    addChild(spm, 2, tag + 2);
    
    Label* damage = LabelCreater::createLabel("Damage", "Capsmall.ttf", INFO_FONTSIZE);
    damage->setAnchorPoint(Vec2(0, 0.5));
    damage->setPosition(Vec2(pt.x, pt.y - (13 * 3)));
    damage->setColor(UNIT_COLOR);
    addChild(damage, 2, tag + 3);
    
    Label* hp2 = LabelCreater::createLabel("0", "Capsmall.ttf", INFO_FONTSIZE);
    hp2->setAnchorPoint(Vec2(1, 0.5));
    hp2->setPosition(Vec2(INFO_RIGHT, hp->getPosition().y));
    hp2->setColor(UNIT_COLOR);
    addChild(hp2, 2, tag + 200);
    
    Label* range2 = LabelCreater::createLabel("00", "Capsmall.ttf", INFO_FONTSIZE);
    range2->setAnchorPoint(Vec2(1, 0.5));
    range2->setPosition(Vec2(INFO_RIGHT, range->getPosition().y));
    range2->setColor(UNIT_COLOR);
    addChild(range2, 2, tag + 201);
    
    Label* spm2 = LabelCreater::createLabel("000", "Capsmall.ttf", INFO_FONTSIZE);
    spm2->setAnchorPoint(Vec2(1, 0.5));
    spm2->setPosition(Vec2(INFO_RIGHT, spm->getPosition().y));
    spm2->setColor(UNIT_COLOR);
    addChild(spm2, 2, tag + 202);
    
    Label* damage2 = LabelCreater::createLabel("0000", "Capsmall.ttf", INFO_FONTSIZE);
    damage2->setAnchorPoint(Vec2(1, 0.5));
    damage2->setPosition(Vec2(INFO_RIGHT, damage->getPosition().y));
    damage2->setColor(UNIT_COLOR);
    addChild(damage2, 2, tag + 203);
}

Label* SceneUpgrade::addLvLabel(Color3B color, Vec2 pt)
{
    Label* label = LabelCreater::createLabel("00", "Capsmall.ttf", 36);
    label->setPosition(pt);
    label->setColor(color);
    addChild(label, 2);
    return label;
}

Sprite* SceneUpgrade::addUpgradeBtn(const char* btn, Vec2 pt, Color3B color)
{
    Sprite* spBtn = Sprite::createWithSpriteFrameName(btn);
    spBtn->setPosition(pt);
    addChild(spBtn, 3);
    
    Label* label = LabelCreater::createLabel("000000", "Wednesday.ttf", 28);
    label->setPosition(Vec2(spBtn->getContentSize().width/2, spBtn->getContentSize().height * 0.29));
    label->setColor(color);
    spBtn->addChild(label, 0, TAG_LABEL_PRICE);
    
    return spBtn;
}

void SceneUpgrade::touchHandle(Vec2 pt)
{
    spBack->setScale(1.1);
    spPrev->setScale(1.0);
    spNext->setScale(1.0);
    if(spBack->getBoundingBox().containsPoint(pt))
    {
        spBack->setScale(1.0);
    }
    else if(spPrev->getBoundingBox().containsPoint(pt))
    {
        spPrev->setScale(0.9);
    }
    else if(spNext->getBoundingBox().containsPoint(pt))
    {
        spNext->setScale(0.9);
    }
}

void SceneUpgrade::onTouchesBegan(vector<Touch*> touches, Event *unused_event)
{
    touchHandle(touches[0]->getLocation());
}

void SceneUpgrade::onTouchesMoved(vector<Touch*> touches, Event *unused_event)
{
    touchHandle(touches[0]->getLocation());
}

void SceneUpgrade::changePage()
{
    if(curPage == 1)    curPage = 2;
    else                curPage = 1;
    
    if(curPage == 1)
    {
        spPage1->runAction(FadeIn::create(0.2));
        spPage2->runAction(FadeOut::create(0.2));
        labelLvUnit1->runAction(FadeIn::create(0.2));
        labelLvUnit2->runAction(FadeIn::create(0.2));
        labelLvUnit3->runAction(FadeIn::create(0.2));
        labelLvUnit4->runAction(FadeIn::create(0.2));
        
        upgradeBtnFadeIn(spUpNavy1);
        upgradeBtnFadeIn(spUpNavy2);
        upgradeBtnFadeIn(spUpNavy3);
        upgradeBtnFadeIn(spUpNavy4);
        
        for(int i = 0; i < 4; i++)
        {
            getChildByTag(TAG_LABEL_UNITINFO4 + i)->runAction(FadeIn::create(0.2));
            getChildByTag(TAG_LABEL_UNIT4 + i)->runAction(FadeIn::create(0.2));
        }
    }
    else
    {
        spPage2->runAction(FadeIn::create(0.2));
        spPage1->runAction(FadeOut::create(0.2));
        
        labelLvUnit1->runAction(FadeIn::create(0.2));
        labelLvUnit2->runAction(FadeIn::create(0.2));
        labelLvUnit3->runAction(FadeIn::create(0.2));
        labelLvUnit4->runAction(FadeOut::create(0.2));
        
        upgradeBtnFadeIn(spUpNavy1);
        upgradeBtnFadeIn(spUpNavy2);
        upgradeBtnFadeIn(spUpNavy3);
        upgradeBtnFadeOut(spUpNavy4);
        
        for(int i = 0; i < 4; i++)
        {
            getChildByTag(TAG_LABEL_UNITINFO4 + i)->runAction(FadeOut::create(0.2));
            getChildByTag(TAG_LABEL_UNIT4 + i)->runAction(FadeOut::create(0.2));
        }
    }
    
    updateInformation(saveData);
}

void SceneUpgrade::upgradeBtnFadeIn(Sprite* btn)
{
    btn->runAction(FadeIn::create(0.2));
    btn->getChildByTag(TAG_LABEL_PRICE)->runAction(FadeIn::create(0.2));
}

void SceneUpgrade::upgradeBtnFadeOut(Sprite* btn)
{
    btn->runAction(FadeOut::create(0.2));
    btn->getChildByTag(TAG_LABEL_PRICE)->runAction(FadeOut::create(0.2));
}

void SceneUpgrade::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event)
{
}

void SceneUpgrade::destroyUpgrade()
{
	delete saveData;
    setKeypadEnabled(false);
    getEventDispatcher()->removeEventListener(mTouchListener);
    Director::getInstance()->popSceneWithTransitionSlideInL();
}

void SceneUpgrade::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
    if(keycode == EventKeyboard::KeyCode::KEY_BACK)
    {
    	SoundManager::playButton();
    	destroyUpgrade();
    }
}

void SceneUpgrade::onTouchesEnded(vector<Touch*> touches, Event *unused_event)
{
    spBack->setScale(1.1);
    spPrev->setScale(1.0);
    spNext->setScale(1.0);
    
    Vec2 pt = touches[0]->getLocation();
    if(spBack->getBoundingBox().containsPoint(pt))
    {
    	SoundManager::playButton();
    	destroyUpgrade();
    }
    else if(spPrev->getBoundingBox().containsPoint(pt) ||
            spNext->getBoundingBox().containsPoint(pt))
    {
    	SoundManager::playButton();
        changePage();
    }
    else if(spUpVulcan->getBoundingBox().containsPoint(pt))
    {
        if(saveData->nMoney >= DokdoCalculator::getUpgradePrice(UPGRADE_VULCAN_PRICE, saveData->dokdoLv.nVulcanLv) &&
           saveData->dokdoLv.nVulcanLv < MAX_LEVEL)
        {
        	SoundManager::playButton();
            saveData->nMoney -= DokdoCalculator::getUpgradePrice(UPGRADE_VULCAN_PRICE, saveData->dokdoLv.nVulcanLv);
            saveData->dokdoLv.nVulcanLv++;
            updateInformation(saveData);
        }
    }
    else if(spUpCannon->getBoundingBox().containsPoint(pt))
    {
        if(saveData->nMoney >= DokdoCalculator::getUpgradePrice(UPGRADE_CANNON_PRICE, saveData->dokdoLv.nCannonLv) &&
           saveData->dokdoLv.nCannonLv < MAX_LEVEL)
        {
        	SoundManager::playButton();
            saveData->nMoney -= DokdoCalculator::getUpgradePrice(UPGRADE_CANNON_PRICE, saveData->dokdoLv.nCannonLv);
            saveData->dokdoLv.nCannonLv++;
            updateInformation(saveData);
        }
    }
    else if(spUpMissile->getBoundingBox().containsPoint(pt))
    {
        if(saveData->nMoney >= DokdoCalculator::getUpgradePrice(UPGRADE_MISSILE_PRICE, saveData->dokdoLv.nMissileLv) &&
           saveData->dokdoLv.nMissileLv < MAX_LEVEL)
        {
        	SoundManager::playButton();
            saveData->nMoney -= DokdoCalculator::getUpgradePrice(UPGRADE_MISSILE_PRICE, saveData->dokdoLv.nMissileLv);
            saveData->dokdoLv.nMissileLv++;
            updateInformation(saveData);
        }
    }
    else if(spUpNavy1->getBoundingBox().containsPoint(pt))
    {
        if(curPage == 1)
        {
            if(saveData->nMoney >= DokdoCalculator::getUpgradePrice(UPGRADE_PKG_PRICE, saveData->unitLv.nPKGLv) &&
               saveData->unitLv.nPKGLv < MAX_LEVEL)
            {
            	SoundManager::playButton();
                saveData->nMoney -= DokdoCalculator::getUpgradePrice(UPGRADE_PKG_PRICE, saveData->unitLv.nPKGLv);
                saveData->unitLv.nPKGLv++;
                updateInformation(saveData);
            }
        }
        else
        {
            if(saveData->nMoney >= DokdoCalculator::getUpgradePrice(UPGRADE_E747_PRICE, saveData->unitLv.nE747Lv) &&
               saveData->unitLv.nE747Lv < MAX_LEVEL)
            {
            	SoundManager::playButton();
                saveData->nMoney -= DokdoCalculator::getUpgradePrice(UPGRADE_E747_PRICE, saveData->unitLv.nE747Lv);
                saveData->unitLv.nE747Lv++;
                updateInformation(saveData);
            }
        }
    }
    else if(spUpNavy2->getBoundingBox().containsPoint(pt))
    {
        if(curPage == 1)
        {
            if(saveData->nMoney >= DokdoCalculator::getUpgradePrice(UPGRADE_KDX2_PRICE, saveData->unitLv.nKDX2Lv) &&
               saveData->unitLv.nKDX2Lv < MAX_LEVEL)
            {
            	SoundManager::playButton();
                saveData->nMoney -= DokdoCalculator::getUpgradePrice(UPGRADE_KDX2_PRICE, saveData->unitLv.nKDX2Lv);
                saveData->unitLv.nKDX2Lv++;
                updateInformation(saveData);
            }
        }
        else
        {
            if(saveData->nMoney >= DokdoCalculator::getUpgradePrice(UPGRADE_KSS3_PRICE, saveData->unitLv.nKSS3Lv) &&
               saveData->unitLv.nKSS3Lv < MAX_LEVEL)
            {
            	SoundManager::playButton();
                saveData->nMoney -= DokdoCalculator::getUpgradePrice(UPGRADE_KSS3_PRICE, saveData->unitLv.nKSS3Lv);
                saveData->unitLv.nKSS3Lv++;
                updateInformation(saveData);
            }
        }
    }
    else if(spUpNavy3->getBoundingBox().containsPoint(pt))
    {
        if(curPage == 1)
        {
            if(saveData->nMoney >= DokdoCalculator::getUpgradePrice(UPGRADE_KDX3_PRICE, saveData->unitLv.nKDX3Lv) &&
               saveData->unitLv.nKDX3Lv < MAX_LEVEL)
            {
            	SoundManager::playButton();
                saveData->nMoney -= DokdoCalculator::getUpgradePrice(UPGRADE_KDX3_PRICE, saveData->unitLv.nKDX3Lv);
                saveData->unitLv.nKDX3Lv++;
                updateInformation(saveData);
            }
        }
        else
        {
            if(saveData->nMoney >= DokdoCalculator::getUpgradePrice(UPGRADE_F15K_PRICE, saveData->unitLv.nF15KLv) &&
               saveData->unitLv.nF15KLv < MAX_LEVEL)
            {
            	SoundManager::playButton();
                saveData->nMoney -= DokdoCalculator::getUpgradePrice(UPGRADE_F15K_PRICE, saveData->unitLv.nF15KLv);
                saveData->unitLv.nF15KLv++;
                updateInformation(saveData);
            }
        }
    }
    else if(spUpNavy4->getBoundingBox().containsPoint(pt))
    {
        if(curPage == 1)
        {
            if(saveData->nMoney >= DokdoCalculator::getUpgradePrice(UPGRADE_DOKDO_PRICE, saveData->unitLv.nDOKDOLv) &&
               saveData->unitLv.nDOKDOLv < MAX_LEVEL)
            {
            	SoundManager::playButton();
                saveData->nMoney -= DokdoCalculator::getUpgradePrice(UPGRADE_DOKDO_PRICE, saveData->unitLv.nDOKDOLv);
                saveData->unitLv.nDOKDOLv++;
                updateInformation(saveData);
            }
        }
    }
}

//
//  SceneUpgrade.h
//  MyCppGame
//
//  Created by Jinryul Kim on 2014. 7. 28..
//
//

#ifndef __DokdoDefenceCommand__SceneUpgrade__
#define __DokdoDefenceCommand__SceneUpgrade__

#include "cocos2d.h"
#include "Defines.h"

#define TAG_LABEL_PRICE         1000

#define TAG_LABEL_UNITINFO1     1100
#define TAG_LABEL_UNITINFO2     1110
#define TAG_LABEL_UNITINFO3     1120
#define TAG_LABEL_UNITINFO4     1130

#define TAG_LABEL_VULCAN        1200
#define TAG_LABEL_CANNON        1210
#define TAG_LABEL_MISSILE       1220

#define TAG_LABEL_UNIT1         1300
#define TAG_LABEL_UNIT2         1310
#define TAG_LABEL_UNIT3         1320
#define TAG_LABEL_UNIT4         1330

#define DOKDO_COLOR     Color3B(1, 190, 253)
#define UNIT_COLOR      Color3B(250, 192, 77)
#define INFO_RIGHT      315

#define INFO_FONTSIZE   16

class SceneUpgrade : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(SceneUpgrade);
    
    void updateInformation(DDC_SAVE_DATA* save);
    
private:
    virtual void onTouchesBegan(std::vector<cocos2d::Touch*>touches, cocos2d::Event* event);
    virtual void onTouchesMoved(std::vector<cocos2d::Touch*>touches, cocos2d::Event* event);
    virtual void onTouchesEnded(std::vector<cocos2d::Touch*>touches, cocos2d::Event* event);
    cocos2d::EventListenerTouchAllAtOnce* mTouchListener;
    
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
    
    cocos2d::Sprite* addUpgradeBtn(const char* btn, cocos2d::Vec2 pt, cocos2d::Color3B color);
    cocos2d::Label* addLvLabel(cocos2d::Color3B color, cocos2d::Vec2 pt);
    void touchHandle(cocos2d::Vec2 pt);
    void changePage();
    void upgradeBtnFadeIn(cocos2d::Sprite* btn);
    void upgradeBtnFadeOut(cocos2d::Sprite* btn);
    void addDokdoInfo(cocos2d::Vec2 pt, int tag);
    void addUnitInfo(cocos2d::Vec2 pt, int tag);
    void upgradeBtnEnable(int upgradePrice, cocos2d::Sprite* btn);
    
    void destroyUpgrade();

    cocos2d::Sprite* spBack;
    DDC_SAVE_DATA* saveData;
    cocos2d::Sprite *spPrev, *spNext;
    cocos2d::Sprite *spPage1, *spPage2;
    cocos2d::Sprite *spUpVulcan, *spUpCannon, *spUpMissile;
    cocos2d::Sprite *spUpNavy1, *spUpNavy2, *spUpNavy3, *spUpNavy4;
    cocos2d::Label* labelMoney;
    cocos2d::Label *labelLvVulcan, *labelLvCannon, *labelLvMissile;
    cocos2d::Label *labelLvUnit1, *labelLvUnit2, *labelLvUnit3, *labelLvUnit4;

    int curPage;
};

#endif /* defined(__DokdoDefenceCommand__SceneUpgrade__) */

//
//  SceneUpgrade.hpp
//  DokdoDefenceCommand
//
//  Created by 김진율 on 2021/04/05.
//

#ifndef SceneUpgrade_hpp
#define SceneUpgrade_hpp

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

USING_NS_CC;
using namespace std;

class SceneUpgrade : public Layer
{
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(SceneUpgrade);
    
    void updateInformation(DDC_SAVE_DATA* save);
    
private:
    virtual void onTouchesBegan(vector<cocos2d::Touch*>touches, Event* event);
    virtual void onTouchesMoved(vector<cocos2d::Touch*>touches, Event* event);
    virtual void onTouchesEnded(vector<cocos2d::Touch*>touches, Event* event);
    EventListenerTouchAllAtOnce* mTouchListener;
    
    void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
    
    Sprite* addUpgradeBtn(const char* btn, Vec2 pt, Color3B color);
    Label* addLvLabel(Color3B color, Vec2 pt);
    void touchHandle(Vec2 pt);
    void changePage();
    void upgradeBtnFadeIn(Sprite* btn);
    void upgradeBtnFadeOut(Sprite* btn);
    void addDokdoInfo(Vec2 pt, int tag);
    void addUnitInfo(Vec2 pt, int tag);
    void upgradeBtnEnable(int upgradePrice, Sprite* btn);
    
    void destroyUpgrade();

    Sprite* spBack;
    DDC_SAVE_DATA* saveData;
    Sprite *spPrev, *spNext;
    Sprite *spPage1, *spPage2;
    Sprite *spUpVulcan, *spUpCannon, *spUpMissile;
    Sprite *spUpNavy1, *spUpNavy2, *spUpNavy3, *spUpNavy4;
    Label* labelMoney;
    Label *labelLvVulcan, *labelLvCannon, *labelLvMissile;
    Label *labelLvUnit1, *labelLvUnit2, *labelLvUnit3, *labelLvUnit4;

    int curPage;
};

#endif /* SceneUpgrade_hpp */

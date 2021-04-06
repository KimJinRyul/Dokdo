//
//  SceneMenu.hpp
//  DokdoDefenceCommand
//
//  Created by 김진율 on 2021/04/02.
//

#ifndef SceneMenu_hpp
#define SceneMenu_hpp

#include "cocos2d.h"
#include "Defines.h"
//#include "SceneGame.h"
#include "SceneCredit.hpp"
#include "SceneUpgrade.hpp"
#include "DialogLevel.hpp"
#include "DialogOption.hpp"
#include "DialogScore.hpp"
#include "DialogResult.hpp"
#include "SaveManager.hpp"

class SceneMenu : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    static cocos2d::Scene* createScene(bool clear,
                                       float totaltime,
                                       int score,
                                       int enermyCtn,
                                       int forceCtn,
                                       int income,
                                       bool highscore);
    
    virtual bool init();
    CREATE_FUNC(SceneMenu);
    
    void setCleanData(bool clear,
                      float totaltime,
                      int score,
                      int enermyCtn,
                      int forceCtn,
                      int income,
                      bool highscore);
    void showDialogLevel();
    void hideDialogLevel();
    void showDialogOption();
    void hideDialogOption();
    void showDialogScore();
    void hideDialogScore();
    void showDialogResult(bool clear,
                          float totaltime,
                          int score,
                          int enermyCtn,
                          int forceCtn,
                          int income,
                          bool highscore);
    void hideDialogResult();
    
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
    
    virtual void onExit();
    virtual void onEnterTransitionDidFinish();
    
private:
    cocos2d::MenuItemSprite* createMenuItemSprite(const char* text, const char* hilight, const char* han, int tag);
    cocos2d::MenuItemSprite* createSNSMenu(const char* image, int tag);
    void onMenu(cocos2d::Ref* sender);
    void hideDefaultMenus();
    void showDefaultMenus();
    void onBACK(float dt);
    
private:
    bool bResult, bBack;
    cocos2d::Size mWinSize;
    cocos2d::SpriteBatchNode* menuBatchNode;
};


#endif /* SceneMenu_hpp */

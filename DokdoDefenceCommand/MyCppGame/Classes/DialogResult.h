//
//  DialogResult.h
//  MyCppGame
//
//  Created by Jinryul Kim on 2014. 8. 13..
//
//

#ifndef __DokdoDefenceCommand__DialogResult__
#define __DokdoDefenceCommand__DialogResult__

#include "cocos2d.h"
#include "LabelCreater.h"
#include "Defines.h"

class DialogResult : public cocos2d::LayerColor
{
public:
    virtual bool init();
    CREATE_FUNC(DialogResult);
    
    void Show(bool clear,
              float totaltime,
              int score,
              int enermyCtn,
              int forceCtn,
              int income,
              bool highscore);
    void Hide();
    
private:
    virtual void onTouchesBegan(std::vector<cocos2d::Touch*> touches, cocos2d::Event* event);
    virtual void onTouchesMoved(std::vector<cocos2d::Touch*> touches, cocos2d::Event* event);
    virtual void onTouchesEnded(std::vector<cocos2d::Touch*> touches, cocos2d::Event* event);
    cocos2d::EventListenerTouchAllAtOnce* mTouchListener;
    
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
    
    void touchHandle(cocos2d::Vec2 pt);
    void addTouchListener();
    void removeTouchListener();
    
    cocos2d::Sprite* spDlg;
    cocos2d::Sprite* spBack;
};

#endif /* defined(__DokdoDefenceCommand__DialogResult__) */

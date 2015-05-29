//
//  DialogOption.h
//  MyCppGame
//
//  Created by Jinryul Kim on 2014. 7. 28..
//
//

#ifndef __DokdoDefenceCommand__DialogOption__
#define __DokdoDefenceCommand__DialogOption__

#include "cocos2d.h"
#include "Defines.h"

#define TAG_DIALOG  1000
#define TAG_MUSIC   1001
#define TAG_SOUND   1002
#define TAG_RESET   1003
#define TAG_BACK    1004

#define ZORDER_DIALOG   1
#define ZORDER_BTN      2

#define SLIDE_LEFT      142
#define SLIDE_RIGHT     187

#define OPTION_KEY_MUSIC    "Music"
#define OPTION_KEY_SOUND    "Sound"

class DialogOption : public cocos2d::LayerColor
{
public:
    virtual bool init();
    CREATE_FUNC(DialogOption);
    
    void Show();
    void Hide();
    
private:
    cocos2d::SpriteBatchNode* mBatchNode;
    virtual void onTouchesBegan(std::vector<cocos2d::Touch*> touches, cocos2d::Event* event);
    virtual void onTouchesMoved(std::vector<cocos2d::Touch*> touches, cocos2d::Event* event);
    virtual void onTouchesEnded(std::vector<cocos2d::Touch*> touches, cocos2d::Event* event);
    cocos2d::EventListenerTouchAllAtOnce* mTouchListener;
    
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
    
    void addTouchListener();
    void removeTouchListener();
    void touchHandle(cocos2d::Vec2 pt);
    void setBtnsScale(float scale);
    
    cocos2d::Sprite* spDlg;
    cocos2d::Sprite* spMusic;
    cocos2d::Sprite* spSound;
    cocos2d::Sprite* spReset;
    cocos2d::Sprite* spBack;
    cocos2d::Rect rtDlg;
    
    bool bResetDlg;
};


#endif /* defined(__DokdoDefenceCommand__DialogOption__) */

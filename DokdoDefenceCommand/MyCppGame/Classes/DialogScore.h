//
//  DialogScore.h
//  MyCppGame
//
//  Created by Jinryul Kim on 2014. 7. 28..
//
//

#ifndef __DokdoDefenceCommand__DialogScore__
#define __DokdoDefenceCommand__DialogScore__

#include "cocos2d.h"
#include "LabelCreater.h"
#include "Defines.h"

#define TAG_LABEL_BASE  1000
#define TAG_LABEL_BASE2 2000
#define MAX_LABEL       12

class DialogScore : public cocos2d::LayerColor
{
public:
    virtual bool init();
    CREATE_FUNC(DialogScore);
    
    void Show();
    void Hide();
    
private:
    virtual void onTouchesBegan(std::vector<cocos2d::Touch*> touches, cocos2d::Event* event);
    virtual void onTouchesMoved(std::vector<cocos2d::Touch*> touches, cocos2d::Event* event);
    virtual void onTouchesEnded(std::vector<cocos2d::Touch*> touches, cocos2d::Event* event);
    cocos2d::EventListenerTouchAllAtOnce* mTouchListener;
    
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
    
    void addTouchListener();
    void removeTouchListener();
    void touchHandle(cocos2d::Vec2 pt);
    
    cocos2d::Sprite* spBack;
};

#endif /* defined(__DokdoDefenceCommand__DialogScore__) */

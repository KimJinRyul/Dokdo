//
//  SceneCredit.h
//  MyCppGame
//
//  Created by Jinryul Kim on 2014. 7. 25..
//
//

#ifndef __DokdoDefenceCommand__SceneCredit__
#define __DokdoDefenceCommand__SceneCredit__

#include "cocos2d.h"
#include "Defines.h"

class SceneCredit : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(SceneCredit);
    
private:
    virtual void onTouchesEnded(std::vector<cocos2d::Touch*> touches, cocos2d::Event* event);
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
    cocos2d::EventListenerTouchAllAtOnce* mTouchListener;
};

#endif /* defined(__DokdoDefenceCommand__SceneCredit__) */

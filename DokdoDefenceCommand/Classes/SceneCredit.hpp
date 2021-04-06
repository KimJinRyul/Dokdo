//
//  SceneCredit.hpp
//  DokdoDefenceCommand
//
//  Created by 김진율 on 2021/04/05.
//

#ifndef SceneCredit_hpp
#define SceneCredit_hpp

#include "cocos2d.h"
#include "Defines.h"

USING_NS_CC;
using namespace std;

class SceneCredit : public Layer
{
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(SceneCredit);
    
private:
    virtual void onTouchesEnded(vector<cocos2d::Touch*> touches, Event* event);
    void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
    EventListenerTouchAllAtOnce* mTouchListener;
};

#endif /* SceneCredit_hpp */

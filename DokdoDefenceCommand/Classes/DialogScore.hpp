//
//  DialogScore.hpp
//  DokdoDefenceCommand
//
//  Created by 김진율 on 2021/04/02.
//

#ifndef DialogScore_hpp
#define DialogScore_hpp

#include "cocos2d.h"
#include "LabelCreator.hpp"
#include "Defines.h"

#define TAG_LABEL_BASE  1000
#define TAG_LABEL_BASE2 2000
#define MAX_LABEL       12

USING_NS_CC;
using namespace std;

class DialogScore : public LayerColor {
public:
    virtual bool init();
    CREATE_FUNC(DialogScore);
    
    void Show();
    void Hide();
    
private:
    virtual void onTouchesBegan(vector<Touch*> touches, Event* event);
    virtual void onTouchesMoved(vector<Touch*> touches, Event* event);
    virtual void onTouchesEnded(vector<Touch*> touches, Event* event);
    EventListenerTouchAllAtOnce* mTouchListener;
    
    void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
    
    void addTouchListener();
    void removeTouchListener();
    void touchHandle(Vec2 pt);
    
    Sprite* spBack;
};

#endif /* DialogScore_hpp */

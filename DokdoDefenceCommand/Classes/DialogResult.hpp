//
//  DialogResult.hpp
//  DokdoDefenceCommand
//
//  Created by 김진율 on 2021/04/05.
//

#ifndef DialogResult_hpp
#define DialogResult_hpp

#include "cocos2d.h"
#include "LabelCreator.hpp"
#include "Defines.h"

USING_NS_CC;
using namespace std;

class DialogResult : public LayerColor
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
    virtual void onTouchesBegan(vector<cocos2d::Touch*> touches, Event* event);
    virtual void onTouchesMoved(vector<cocos2d::Touch*> touches, Event* event);
    virtual void onTouchesEnded(vector<cocos2d::Touch*> touches, Event* event);
    cocos2d::EventListenerTouchAllAtOnce* mTouchListener;
    
    void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
    
    void touchHandle(Vec2 pt);
    void addTouchListener();
    void removeTouchListener();
    
    Sprite* spDlg;
    Sprite* spBack;
};

#endif /* DialogResult_hpp */

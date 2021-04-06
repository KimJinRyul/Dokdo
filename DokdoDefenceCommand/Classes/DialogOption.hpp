//
//  DialogOption.hpp
//  DokdoDefenceCommand
//
//  Created by 김진율 on 2021/04/02.
//

#ifndef DialogOption_hpp
#define DialogOption_hpp


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

USING_NS_CC;
using namespace std;

class DialogOption : public LayerColor
{
public:
    virtual bool init();
    CREATE_FUNC(DialogOption);
    
    void Show();
    void Hide();
    
private:
    SpriteBatchNode* mBatchNode;
    virtual void onTouchesBegan(vector<Touch*> touches, Event* event);
    virtual void onTouchesMoved(vector<Touch*> touches, Event* event);
    virtual void onTouchesEnded(vector<Touch*> touches, Event* event);
    EventListenerTouchAllAtOnce* mTouchListener;
    
    void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
    
    void addTouchListener();
    void removeTouchListener();
    void touchHandle(Vec2 pt);
    void setBtnsScale(float scale);
    
    Sprite* spDlg;
    Sprite* spMusic;
    Sprite* spSound;
    Sprite* spReset;
    Sprite* spBack;
    Rect rtDlg;
    
    bool bResetDlg;
};

#endif /* DialogOption_hpp */

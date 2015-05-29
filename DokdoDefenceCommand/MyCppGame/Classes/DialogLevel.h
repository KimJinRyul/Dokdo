//
//  DialogLevel.h
//  MyCppGame
//
//  Created by Jinryul Kim on 2014. 7. 28..
//
//

#ifndef __DokdoDefenceCommand__DialogLevel__
#define __DokdoDefenceCommand__DialogLevel__

#include "cocos2d.h"
#include "Defines.h"

class DialogLevel : public cocos2d::LayerColor
{
public:
    virtual bool init();
    CREATE_FUNC(DialogLevel);
    
    void Show();
    void Hide();
    
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
    
private:
    cocos2d::MenuItemSprite* createMenuItemSprite(const char* text, const char* han, int tag, bool cleared);
    void onMenu(cocos2d::Ref* sender);
};

#endif /* defined(__DokdoDefenceCommand__DialogLevel__) */

//
//  DialogLevel.hpp
//  DokdoDefenceCommand
//
//  Created by 김진율 on 2021/04/05.
//

#ifndef DialogLevel_hpp
#define DialogLevel_hpp

#include "cocos2d.h"
#include "Defines.h"

USING_NS_CC;
using namespace std;

class DialogLevel : public LayerColor
{
public:
    virtual bool init();
    CREATE_FUNC(DialogLevel);
    
    void Show();
    void Hide();
    
    void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
    
private:
    MenuItemSprite* createMenuItemSprite(const char* text, const char* han, int tag, bool cleared);
    void onMenu(Ref* sender);
};

#endif /* DialogLevel_hpp */

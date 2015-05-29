//
//  LabelCreater.h
//  MyCppGame
//
//  Created by Jinryul Kim on 2014. 7. 30..
//
//

#ifndef __MyCppGame__LabelCreater__
#define __MyCppGame__LabelCreater__

#include "cocos2d.h"

class LabelCreater
{
public:
    static cocos2d::Label* createLabel(const char* text, const char* fontFile, float fontSize);
};

#endif /* defined(__MyCppGame__LabelCreater__) */

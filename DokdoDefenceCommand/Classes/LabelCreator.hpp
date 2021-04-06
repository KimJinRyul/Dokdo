//
//  LabelCreator.hpp
//  DokdoDefenceCommand
//
//  Created by 김진율 on 2021/04/02.
//

#ifndef LabelCreator_hpp
#define LabelCreator_hpp

#include "cocos2d.h"
USING_NS_CC;

class LabelCreator
{
public:
    static Label* createLabel(const char* text, const char* fontFile, float fontSize);
};

#endif /* LabelCreator_hpp */

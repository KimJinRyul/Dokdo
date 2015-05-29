//
//  LabelCreater.cpp
//  MyCppGame
//
//  Created by Jinryul Kim on 2014. 7. 30..
//
//

#include "LabelCreater.h"

USING_NS_CC;

Label* LabelCreater::createLabel(const char* text, const char* fontFile, float fontSize)
{
    Label* label = Label::createWithTTF(text, fontFile, fontSize);
    if(label == nullptr)
    {
        char szTEMP[32] = {0, };
        sprintf(szTEMP, "fonts/%s", fontFile);
        label = Label::createWithTTF(text, szTEMP, fontSize);
    }
    
    return label;
}
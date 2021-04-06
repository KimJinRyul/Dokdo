//
//  LabelCreator.cpp
//  DokdoDefenceCommand
//
//  Created by 김진율 on 2021/04/02.
//

#include "LabelCreator.hpp"

Label* LabelCreator::createLabel(const char* text, const char* fontFile, float fontSize) {
    Label* label = Label::createWithTTF(text, fontFile, fontSize);
    if (label == nullptr) {
        char szTEMP[32] = {0, };
        sprintf(szTEMP, "fonts/%s", fontFile);
        label = Label::createWithTTF(text, szTEMP, fontSize);
    }
    return label;
}

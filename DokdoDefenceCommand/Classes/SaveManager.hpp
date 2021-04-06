//
//  SaveManager.hpp
//  DokdoDefenceCommand
//
//  Created by 김진율 on 2021/04/02.
//

#ifndef SaveManager_hpp
#define SaveManager_hpp

#include "cocos2d.h"
#include "Defines.h"

USING_NS_CC;
using namespace std;

class SaveManager
{
public:
    static void createSaveIfNotExist();
    static void save(DDC_SAVE_DATA* saveData);
    static DDC_SAVE_DATA* load();
    static DDC_CLEAR_DATA* loadClear();
    static void saveClear(DDC_CLEAR_DATA* saveData);
};

#endif /* SaveManager_hpp */

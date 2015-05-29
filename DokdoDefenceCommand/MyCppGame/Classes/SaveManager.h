//
//  SaveManager.h
//  MyCppGame
//
//  Created by Jinryul Kim on 2014. 7. 31..
//
//

#ifndef __DokdoDefenceCommand__SaveManager__
#define __DokdoDefenceCommand__SaveManager__

#include "cocos2d.h"
#include "Defines.h"

class SaveManager
{
public:
    static void createSaveIfNotExist();
    static void save(DDC_SAVE_DATA* saveData);
    static DDC_SAVE_DATA* load();
    static DDC_CLEAR_DATA* loadClear();
    static void saveClear(DDC_CLEAR_DATA* saveData);

    // for debugging
    //static void showSave(DDC_SAVE_DATA* save);
};

#endif /* defined(__DokdoDefenceCommand__SaveManager__) */

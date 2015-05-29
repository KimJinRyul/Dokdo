//
//  SaveManager.cpp
//  MyCppGame
//
//  Created by Jinryul Kim on 2014. 7. 31..
//
//

#include "SaveManager.h"

USING_NS_CC;

void SaveManager::createSaveIfNotExist()
{
    std::string savePath = FileUtils::getInstance()->getWritablePath().append(SAVE_FILE);
    
    if(FileUtils::getInstance()->isFileExist(savePath))
    {

        FILE* fp = fopen(savePath.c_str(), "rb");
        fseek(fp, 0L, SEEK_END);
        int fileSize = ftell(fp);
        if(fileSize != sizeof(DDC_SAVE_DATA))
        {
            DDC_SAVE_DATA* saveData = new DDC_SAVE_DATA();
            save(saveData);
            delete saveData;
        }
    }
    else    // 없으니 하나 만들어 줌
    {

        DDC_SAVE_DATA* saveData = new DDC_SAVE_DATA();;
        save(saveData);
        delete saveData;
    }
    
    std::string clearPath = FileUtils::getInstance()->getWritablePath().append(CLEAR_FILE);
    if(FileUtils::getInstance()->isFileExist(clearPath))
    {
        FILE* fp = fopen(clearPath.c_str(), "rb");
        fseek(fp, 0L, SEEK_END);
        int fileSize = ftell(fp);
        if(fileSize != sizeof(DDC_CLEAR_DATA))
        {
            DDC_CLEAR_DATA* clearData = new DDC_CLEAR_DATA();
            saveClear(clearData);
            delete clearData;
        }
    }
    else
    {
        DDC_CLEAR_DATA* clearData = new DDC_CLEAR_DATA();
        saveClear(clearData);
        delete clearData;
    }
}

DDC_SAVE_DATA* SaveManager::load()
{
    std::string savePath = FileUtils::getInstance()->getWritablePath().append(SAVE_FILE);
    FILE* fp = fopen(savePath.c_str(), "rb");
    DDC_SAVE_DATA* saveData = new DDC_SAVE_DATA();
    fread(saveData, 1, sizeof(DDC_SAVE_DATA), fp);
    fclose(fp);

    return saveData;
}

void SaveManager::save(DDC_SAVE_DATA* saveData)
{
    std::string savePath = FileUtils::getInstance()->getWritablePath().append(SAVE_FILE);
    FILE* fp = fopen(savePath.c_str(), "wb");
    fwrite(saveData, 1, sizeof(DDC_SAVE_DATA), fp);
    fclose(fp);
}

DDC_CLEAR_DATA* SaveManager::loadClear()
{
    std::string savePath = FileUtils::getInstance()->getWritablePath().append(CLEAR_FILE);
    FILE* fp = fopen(savePath.c_str(), "rb");
    DDC_CLEAR_DATA* saveData = new DDC_CLEAR_DATA();
    fread(saveData, 1, sizeof(DDC_CLEAR_DATA), fp);
    fclose(fp);
    return saveData;
}

void SaveManager::saveClear(DDC_CLEAR_DATA* saveData)
{
    std::string savePath = FileUtils::getInstance()->getWritablePath().append(CLEAR_FILE);
    FILE* fp = fopen(savePath.c_str(), "wb");
    fwrite(saveData, 1, sizeof(DDC_CLEAR_DATA), fp);
    fclose(fp);
}

// for Debugging
/*
void SaveManager::showSave(DDC_SAVE_DATA* save)
{
	log("================== show save data ===================");
	log("Money: %d", save->nMoney);
	log("DokdoLv (%d, %d, %d)", save->dokdoLv.nVulcanLv, save->dokdoLv.nCannonLv, save->dokdoLv.nMissileLv);
	log("UnitLv (%d, %d, %d, %d, %d)", save->unitLv.nPKGLv, save->unitLv.nKDX2Lv, save->unitLv.nKDX3Lv,
										save->unitLv.nKSS3Lv, save->unitLv.nDOKDOLv);
	log("====================================================");
}*/

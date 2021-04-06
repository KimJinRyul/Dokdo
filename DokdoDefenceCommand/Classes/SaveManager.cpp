//
//  SaveManager.cpp
//  DokdoDefenceCommand
//
//  Created by 김진율 on 2021/04/02.
//

#include "SaveManager.hpp"

void SaveManager::createSaveIfNotExist() {
    string savePath = FileUtils::getInstance()->getWritablePath().append(SAVE_FILE);
    
    if (FileUtils::getInstance()->isFileExist(savePath)) {
        FILE* fp = fopen(savePath.c_str(), "rb");
        fseek(fp, 0L, SEEK_END);
        long fileSize = ftell(fp);
        if (fileSize != sizeof(DDC_SAVE_DATA)) {
            DDC_SAVE_DATA* saveData = new DDC_SAVE_DATA();
            save(saveData);
            delete saveData;
        }
    } else { // 없으니 하나 만들어 줌
        DDC_SAVE_DATA* saveData = new DDC_SAVE_DATA();;
        save(saveData);
        delete saveData;
    }
    
    string clearPath = FileUtils::getInstance()->getWritablePath().append(CLEAR_FILE);
    if (FileUtils::getInstance()->isFileExist(clearPath)) {
        FILE* fp = fopen(clearPath.c_str(), "rb");
        fseek(fp, 0L, SEEK_END);
        long fileSize = ftell(fp);
        if (fileSize != sizeof(DDC_CLEAR_DATA)) {
            DDC_CLEAR_DATA* clearData = new DDC_CLEAR_DATA();
            saveClear(clearData);
            delete clearData;
        }
    } else {
        DDC_CLEAR_DATA* clearData = new DDC_CLEAR_DATA();
        saveClear(clearData);
        delete clearData;
    }
}

DDC_SAVE_DATA* SaveManager::load() {
    string savePath = FileUtils::getInstance()->getWritablePath().append(SAVE_FILE);
    FILE* fp = fopen(savePath.c_str(), "rb");
    DDC_SAVE_DATA* saveData = new DDC_SAVE_DATA();
    fread(saveData, 1, sizeof(DDC_SAVE_DATA), fp);
    fclose(fp);
    return saveData;
}

void SaveManager::save(DDC_SAVE_DATA* saveData) {
    string savePath = FileUtils::getInstance()->getWritablePath().append(SAVE_FILE);
    FILE* fp = fopen(savePath.c_str(), "wb");
    fwrite(saveData, 1, sizeof(DDC_SAVE_DATA), fp);
    fclose(fp);
}

DDC_CLEAR_DATA* SaveManager::loadClear() {
    string savePath = FileUtils::getInstance()->getWritablePath().append(CLEAR_FILE);
    FILE* fp = fopen(savePath.c_str(), "rb");
    DDC_CLEAR_DATA* saveData = new DDC_CLEAR_DATA();
    fread(saveData, 1, sizeof(DDC_CLEAR_DATA), fp);
    fclose(fp);
    return saveData;
}

void SaveManager::saveClear(DDC_CLEAR_DATA* saveData) {
    string savePath = FileUtils::getInstance()->getWritablePath().append(CLEAR_FILE);
    FILE* fp = fopen(savePath.c_str(), "wb");
    fwrite(saveData, 1, sizeof(DDC_CLEAR_DATA), fp);
    fclose(fp);
}
